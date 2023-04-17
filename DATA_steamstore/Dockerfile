FROM selenium/standalone-chrome   
RUN sudo apt-get update
RUN sudo apt-get install -y apt-utils
RUN sudo apt-get install -y python
RUN sudo apt-get update && sudo apt-get install -y python-pip

COPY datascrap_steam.py .
RUN sudo -H pip install --upgrade pip
RUN sudo -H pip install selenium
RUN sudo mkdir /pictures

