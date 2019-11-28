#!/bin/bash

#
# Provide a simple report file for size of 
# produced AVR firmware.
# Process devices firmware first, then unit test firmwares.

REPORT="size-report.html"
rm -f $REPORT
touch $REPORT

echo "<html><head></head><body><pre>" >> $REPORT
for elf in *.elf; do 
	if [[ $elf != *Test* ]]; then
	  echo $elf >> $REPORT
	  avr-size -C --mcu=atmega328p $elf >> $REPORT
	fi
done

for elf in *.elf; do 
	if [[ $elf == *Test* ]]; then
	  echo $elf >> $REPORT
	  avr-size -C --mcu=atmega328p $elf >> $REPORT
	fi
done

echo "</pre></body></html>" >> $REPORT
