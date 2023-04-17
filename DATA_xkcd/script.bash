#!/bin/bash
imageURL=$(curl -s https://xkcd.com | grep "Image URL" | cut -c 39-)
if ! grep -q $imageURL index.txt
then
    currTime=$(date +%s)
    echo $currTime $imageURL >> index.txt
    curl -s -o ${currTime}.png $imageURL
fi