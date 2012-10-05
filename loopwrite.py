#!/usr/bin/python

#This program write total_files with text_lines each
#in an infinite loop deleting and re-writing the oldest files

import os
import time

#Number file to write
total_files = 300

#Number of test lines written for each file
text_lines = 500000

#Set the user led to indicate the SD card traffic
os.system("echo mmc0 > /sys/class/leds/user_led/trigger ")

loop_counter=0

#Infinite loop
while True:
    for file_counter in range(total_files+1):

		#Target path and filename
        filename = "/media/data/ACME%04d" % (file_counter); 

        if os.path.exists(filename):
            print "Delete:%s" % (filename)
            os.remove(filename)

        print "Create:%s" % (filename)
        f = open(filename,'w')
        for line_counter in range(text_lines+1):

			#Text line format
            f.write("L_%06d\n" % (line_counter))
        f.close
    loop_counter=loop_counter+1
    print "Loop # " , loop_counter  
