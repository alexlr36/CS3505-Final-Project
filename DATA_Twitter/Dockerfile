# This image will be based on the ubuntu image.  Build it using the
# command in the comment below.  You may omit the ubuntu pull if you already
# did it.  Before running the build, change into the directory containing
# this Dockerfile.
#
# docker pull ubuntu
# docker build --tag web_scraper_STEAM  .
# 
# (Don't forget the trailing . to specify that this directory is the context.)

FROM ubuntu

# Set a default shell.

SHELL ["/bin/bash", "-c"]

# The timezone library stops the docker build and waits for user input to
# select a timezone. This breaks the build. To get around this, 
# set up timezone information prior to installing that library. This
# Docker code does that. Composited from two sources:
# https://rtfm.co.ua/en/docker-configure-tzdata-and-timezone-during-build/
# https://serverfault.com/questions/949991/how-to-install-tzdata-on-a-ubuntu-docker-image

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ="America/Salt Lake City"

# Install a handful of useful libraries.  Note that this is generally against
# best practices -- containers should be lean, and not include 'things you
# might use'.  In our case, we're using the containers for development, so
# this may be reasonable here.

RUN apt-get -y update && apt-get -y install \
  apt-utils \
    g++ \
    python \ 
    default-jdk \
    wget \
    python3-pip \
    curl \
    build-essential
    
RUN pip install selenium
RUN pip3 install image

# Copy in the files from the current folder (recursively) For our purposes,
# put them in /copied

COPY ./cs3505

RUN  cd /cs3505 && gcc simple_HTML_extraction.c && ./a.out && bash PetOfTheDayScript.sh && datascrap.py && scraping_and_building_timefiles.py && createImg.py