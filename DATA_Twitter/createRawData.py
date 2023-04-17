# Author: Alex Romero
# Date: 11-30-2020
#
# Generates a 'bar' based on the amount of tweets for a given time. Use
# heightOfGraph(filename, (days, hours, minutes), time span) to determine height, and then
# use createImage(imagename, barHeight) to generate bar. This can be used in combination
# with ffmpeg or another sort of image generator to create a graph.

from datetime import timedelta, datetime
import os.path


def save_raw_data(tweet, height):
    directory = generate_path("")
    raw_data_name = "raw" + ".txt"
    f = open(directory + raw_data_name, 'a')
    f.write("Keyword:" + tweet + " Height:" + str(height) + '\n')
    f.close()


def generate_path(file_name):
    date = datetime.date(datetime.now())
    date_string = date.strftime("%m-%d-%y-%H")
    path = "./" + date_string + "/" + file_name
    if os.path.exists(path):
        return path
    os.mkdir(path)
    return path


# Count the number of relevant tweets for in each txt file.
# Note: Due to the popularity of each keyword, there are more or less Tweets available for each keyword,
# given in a certain time-span, thus this method treats all the keywords in their own individual cases.
# More specifically: time should be equal to an integer, and span should be equal to 'd', or 'h', or 'm'
# indicating days, hours, or minutes. if anything other than this is passed to the method, there is no
# guarantee it will perform as expected.
def height_of_graph(file_name, time, span):
    file = open(file_name, "r")

    comparator_date = datetime.fromisoformat(file.readline().split('.')[0])
    # if we need to use 'days' as our time
    if time == 'd':
        comparator_date = comparator_date - timedelta(days=span)
    # if we need to use 'hours' as our time
    elif time == 'h':
        # If statement in case we need to go back a day, and adjust
        if comparator_date.hour - span < 0:
            calc_remaining_time = comparator_date.hour - span
            comparator_date = comparator_date.replace(day=(comparator_date.day - 1))
            comparator_date = comparator_date.replace(hour=(23 + calc_remaining_time), minute=00)
        else:
            comparator_date = comparator_date.replace(hour=(comparator_date.hour - span))
    # if we need to use 'minutes' as our time
    elif time == 'm':
        if comparator_date.minute - span < 0:
            comparator_date = comparator_date - timedelta(hours=1)
            comparator_date = comparator_date.replace((comparator_date.minute + 60) - span)
        else:
            comparator_date = comparator_date.replace(minute=(comparator_date.minute - span))

    # Loop though file, add 1px for every item entry, this can be adjusted later depending on the size of the final
    # ffmpeg design.
    height = 1
    for line in file:
        s = line
        if len(s) > 1 :
            current_tweet_date = datetime.fromisoformat(s.split('.')[0])
            if current_tweet_date >= comparator_date:
                height = height + 1
            else:
                # print(height, file_name)
                file.close
                return height

    file.close
    return height


if __name__ == "__main__":
    requestsArray = [["PetOfTheDay", 'd', 5], ["Steam", 'm', 5], ["Wind", 'm', 5], ["Ryzen 5", 'h', 5], ["xkcd", 'h', 8]]

    for item in requestsArray:
        file_path = generate_path("textFiles/")
        graphHeight = height_of_graph(file_path + item[0] + ".txt", item[1], item[2])
        save_raw_data(item[0], graphHeight)
        # file_path = generate_path("images/")
        # create_image(file_path, item[0], graphHeight)
