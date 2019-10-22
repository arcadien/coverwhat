message("-- Coverage mode activated")
if("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
  message("--    Building with llvm Code Coverage Tools")
  message(WARNING "--    LLVM-based coverage report is not implemented yet")
  
  # set Flags
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")

 # find_program(LLVM_COV_PATH llvm-cov*)
 # # Warning/Error messages
 # if(NOT LLVM_COV_PATH)
 #   message(FATAL_ERROR "llvm-cov not found! Aborting.")
 # endif()
 # # llvm-cov
 # set(TARGETÃNAME "SoftwareTransportTest.cpp_driver")
 # add_custom_target(${TARGET_NAME}-ccov-preprocessing
 #   COMMAND LLVM_PROFILE_FILE=default.profraw $<TARGET_FILE:${PROJECT_NAME}>
 #   COMMAND llvm-profdata merge -sparse default.profraw -o ${PROJECT_NAME}.profdata
 #   DEPENDS ${TARGET_NAME})
 # add_custom_target(${TARGET_NAME}-ccov-show
 #   COMMAND llvm-cov show $<TARGET_FILE:${TARGET_NAME}> -instr-profile=${PROJECT_NAME}.profdata -show-line-counts-or-regions
 #   DEPENDS ${TARGET_NAME}-ccov-preprocessing)
 # add_custom_target(${TARGET_NAME}-ccov-report
 #   COMMAND llvm-cov report $<TARGET_FILE:${TARGET_NAME}> -instr-profile=${PROJECT_NAME}.profdata
 #   DEPENDS ${TARGET_NAME}-ccov-preprocessing)
 #   add_custom_target(${TARGET_NAME}-ccov
 # COMMAND llvm-cov show $<TARGET_FILE:${TARGET_NAME}> -instr-profile=${PROJECT_NAME}.profdata -show-line-counts-or-regions -output-dir=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}-llvm-cov -format="html"
 #   DEPENDS ${TARGET_NAME}-ccov-preprocessing)
 #   add_custom_command(TARGET ${TARGET_NAME}-ccov POST_BUILD
 #   COMMAND ;
 #   COMMENT "Open ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET_NAME}-llvm-cov/index.html in your browser to view the coverage report."
 # )

elseif(CMAKE_COMPILER_IS_GNUCXX)
  message("--    Building with lcov Code Coverage Tools")

  find_program(LCOV_PATH lcov)
  find_program(GCOVR_PATH gcovr)
  find_program(GENHTML_PATH genhtml)

  # Warning/Error messages
  if(NOT (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    message(WARNING "Code coverage results with an optimized (non-Debug) build may be misleading")
  endif()
  if(NOT LCOV_PATH)
    message(FATAL_ERROR "lcov not found! Aborting...")
  endif()
  if(NOT GENHTML_PATH)
    message(FATAL_ERROR "genhtml not found! Aborting...")
  endif()
  if(NOT GCOVR_PATH)
    message(FATAL_ERROR "gcovr not found! Aborting...")
  endif()
  set(NO_INLINE "-fno-inline -fno-inline-small-functions -fno-default-inline")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage ${NO_INLINE}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage ${NO_INLINE}")

  set(GCOVR_EXCLUSIONS  "--gcov-exclude '.*test.*' --gcov-exclude '.*third_party.*'")

   add_custom_command(OUTPUT _ctest
     POST_BUILD
     COMMAND ctest --output-on-failure
    )
   add_custom_command(OUTPUT _run_gcovr_parser
     POST_BUILD
     COMMAND ${GCOVR_PATH} -r ${SOURCES_DIR} --object-dir=${CMAKE_BINARY_DIR} --gcov-exclude '.*test.*' --gcov-exclude '.*third_party.*'
     COMMAND ${GCOVR_PATH} -r ${SOURCES_DIR} --object-dir=${CMAKE_BINARY_DIR} --branches --exclude-unreachable-branches --gcov-exclude '.*test.*' --gcov-exclude '.*third_party.*'
     WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
   add_custom_target (coverage DEPENDS _ctest _run_gcovr_parser)

   add_custom_command(OUTPUT _run_gcovr_parser_html
     POST_BUILD
     COMMAND ${GCOVR_PATH} -r ${SOURCES_DIR} --html --html-details -o coverage.html         --object-dir=${CMAKE_BINARY_DIR} --gcov-exclude '.*test.*' --gcov-exclude '.*third_party.*'
     COMMAND ${GCOVR_PATH} -r ${SOURCES_DIR} --html --html-details -o branche-coverage.html --object-dir=${CMAKE_BINARY_DIR} --gcov-exclude '.*test.*' --gcov-exclude '.*third_party.*'
     WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
   add_custom_target (coverage_html DEPENDS _ctest _run_gcovr_parser_html)

   add_custom_command(OUTPUT _run_gcovr_parser_xml
     POST_BUILD
     COMMAND ${GCOVR_PATH} -r ${SOURCES_DIR} --xml -o coverage.xml --object-dir=${CMAKE_BINARY_DIR} --gcov-exclude '.*test.*' --gcov-exclude '.*third_party.*'
     COMMAND ${GCOVR_PATH} -r ${SOURCES_DIR} --xml -o branche-coverage.xml --object-dir=${CMAKE_BINARY_DIR} --gcov-exclude '.*test.*' --gcov-exclude '.*third_party.*'
     WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
   add_custom_target (coverage_cobertura DEPENDS _ctest _run_gcovr_parser_xml)

else()
  message(FATAL_ERROR "Code coverage requires Clang or GCC. Aborting.")
endif()
