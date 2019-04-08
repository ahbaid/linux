#!/bin/bash

# Author:       Ahbaid Gaffoor
# Name:         hostwatch.sh
# Use:          Watch a linux system 

while (true); do 
   # clear the screen
   clear 

   # show the date
   date 

   # show load averages
   echo -e "== uptime =="
   uptime

   # show extended iostats (-x) and omit devices with no activity (-z)
   echo -e "== iostat -xz =="
   iostat -xz 

   # memory stats, sample once
   echo -e "== vmstat 1 1 =="
   vmstat 1 1

   # memory segments
   echo -e "== ipcs -m =="
   ipcs -m

   # huge pages
   echo -e "== HugePages Info: =="
   cat /proc/meminfo | grep -i hugepages

   # pause for a second
   sleep 1

done
