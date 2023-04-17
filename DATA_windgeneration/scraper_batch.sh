#!/bin/bash

curl -s -O https://transmission.bpa.gov/Business/Operations/Wind/baltwg.txt
sed -i '1,11d' baltwg.txt

for i in `seq 289 12 1957`
do
    name=$(sed "${i}q;d" baltwg.txt | cut -c1-16 | xargs -0 date +"%s" -d)
    echo $name
    gnuplot -e "set xdata time; set format x \"%H:%M\"; set timefmt \"%m/%d/%Y %H:%M\"; set xtics 10800; set term png size 750, 750; set output \"./files/${name}.png\"; set key font \",20\"; set key top center; set border 3; set xtics axis; plot \"baltwg.txt\" every ::$((i-287))::$i using 1:4 title \"Wind Power Generation (MW)\" with lines"
done