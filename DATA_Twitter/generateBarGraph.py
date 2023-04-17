import matplotlib.pyplot as plt; plt.rcdefaults()
import matplotlib.pyplot as plt
from datetime import datetime
import os.path
import numpy as np

# Used to name files and directories based on date(Month-Day-Year-Hour)
date = datetime.date(datetime.now())
date_string = date.strftime("%m-%d-%y-%H")


# Generates the file path based on the current date_string, builds a directory if one does not exist
def generate_path():
    file_path = "./" + date_string + "/"
    if os.path.exists(file_path):
        return file_path
    os.mkdir(file_path)
    return file_path


# Opens and reads from a file with given data.
# Note: This method expects the file to be in the following format: 'Keyword:(Tweet) HeightOfGraph:(Height)'
def generate_xy_values(raw_data):
    file = open(raw_data, "r")
    keywords = []
    number_of_tweets = []
    for line in file:
        parsed_data = line.split(" ")
        if parsed_data[0].__contains__("Ryzen"):
            keywords.append(parsed_data[0].split(":")[1] + " 5")
            number_of_tweets.append(int(parsed_data[2].split(":")[1].split('\n')[0]))
        elif parsed_data[0] != " ":
            keywords.append(parsed_data[0].split(":")[1])
            number_of_tweets.append(int(parsed_data[1].split(":")[1].split('\n')[0]))
    file.close()
    xy = [keywords, number_of_tweets]
    return xy


# Receives a 2D array with expected values [[Keywords], [number_of_tweets]] and uses it to
# create and save a bar graph.
def create_bar_graph(xy):
    y_pos = np.arange(len(xy[0]))
    plt.bar(y_pos, xy[1], align='center')
    plt.xticks(y_pos, xy[0])
    plt.ylabel('Tweets')
    plt.title('Keyword Popularity on Twitter')
    file_name = generate_path() + date_string + ".png"
    plt.savefig(file_name, format='png')


# Main
if __name__ == "__main__":
    raw_data = generate_path() + "raw.txt"
    xy = generate_xy_values(raw_data)
    create_bar_graph(xy)
