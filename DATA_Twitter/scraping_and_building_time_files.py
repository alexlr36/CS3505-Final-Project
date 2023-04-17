# Author: Alex Romero
# Date: 11-30-2020
#
# Generates a file(s) for a given Tweet keyword, adds the time stamps of found tweets to a file based on the keyword name.

import requests
from datetime import timedelta, datetime
import os.path

# Requests Array
requestsArray = ["PetOfTheDay" , "Steam", "Wind", "Ryzen 5", "xkcd"]
number_of_tweets = 100
payload={}
token = ""

def path():
  date = datetime.date(datetime.now())
  date_string = date.strftime("%m-%d-%y-%H")
  file_path = "./" + date_string + "/"
  if os.path.exists(file_path):
    return file_path + "textFiles/"
  os.mkdir(file_path)
  os.mkdir(file_path + "textFiles/")
  return file_path + "textFiles/"


# Loop through each element in requestsArray, use current string in the array to search for Tweets,
# then proceed to parse the timestamps into a file for later use.
for s in requestsArray:
  filepath = path()
  file = open((filepath + s + '.txt'), 'w')
  url = "https://api.twitter.com/2/tweets/search/recent?query=has:media {}&tweet.fields=created_at&max_results={}".format(s, number_of_tweets)

  headers = {
    'Authorization': f'Bearer {token}',
    'Cookie': 'personalization_id="v1_Ny8MxnTAyJ8F6Wnq+QBBiA=="; guest_id=v1%3A160533624325732650'
  }

  response = requests.request("GET", url, headers=headers, data=payload)

  # Parse the response based on when the pulled tweets were created at
  json_response = response.json()['data']
  file = open((filepath + s + '.txt'), 'a')
  for item in json_response:
    file.write(item['created_at'] + '\n')
  file.close()
