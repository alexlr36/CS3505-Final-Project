#!/bin/bash

backslash="/"
dot="."
dash="-"
zero="0"
TODAY=$(date +%m-%d-%y)
png=".png"
path=$dot$backslash$TODAY$dash$zero$zero$backslash$TODAY$dash$zero$zero$png
UNIX=$(date +%s)
sudo cp $path /mnt/efs/fs1/AlexFiles/$UNIX$png
