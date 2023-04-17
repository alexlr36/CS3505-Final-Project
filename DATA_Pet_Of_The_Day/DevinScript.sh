#!/bin/bash
#These next three lines are to build the link to the image
link='petoftheday.com/'
image=$(curl -s petoftheday.com | grep -m 1 "img src=\"archive" | cut -c 55-82)
imageLink=$link$image
#This currTime variable will be used to create the name of the file
currTime=$(date +%s)
#check to see if the image is not already in the pets.txt file. If it isn't,
#add it and then convert the image link into an image that will be in the current directory
if ! grep -q $imageLink pets.txt; then
  echo $imageLink >> pets.txt
  curl -s $imageLink >> $currTime.jpg
fi