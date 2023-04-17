#!/bin/bash

curl -s -O https://transmission.bpa.gov/Business/Operations/Wind/baltwg.txt
sed -i '1,11d' baltwg.txt

lineNumber=$(grep -n -P ":55\t[1-9]" baltwg.txt | tail -1 | cut -c1-4)

name=$(sed "${lineNumber}q;d" baltwg.txt | cut -c1-16 | xargs -0 date +"%s" -d)

gnuplot -e "set xdata time; set format x \"%H:%M\"; set timefmt \"%m/%d/%Y %H:%M\"; set xtics 10800; set term png size 750, 750; set output \"./${name}.png\"; set key font \",20\"; set key top center; set border 3; set xtics axis; plot \"baltwg.txt\" every ::$((lineNumber-287))::$lineNumber using 1:4 title \"Wind Power Generation (MW)\" with lines"

sudo mv ./${name}.png /mnt/efs/fs1/JavierFiles/