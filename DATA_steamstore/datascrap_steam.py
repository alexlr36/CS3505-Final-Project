from selenium import webdriver
from selenium.webdriver.chrome.options import Options
import os
from datetime import datetime
from datetime import date

import time
 




BIGoptions = Options()
BIGoptions.headless = True
BIGoptions.add_argument("--window-size=1920,1200")
BIGoptions.add_argument("no-sandbox")

#PATH = "/usr/bin/chromedriver"
driver = webdriver.Chrome(options=BIGoptions)
now = datetime.now()

today = now.strftime("M%m%d%Y,%H%M%S")

print(today)


driver.get("https://store.steampowered.com/stats")
driver.set_window_size(1920, 2000)
driver.get_screenshot_as_file("/data/"+today+"test.png")

print("/data/"+today+"test.png")


# driver.close()  #this is closing one tab
time.sleep(0.005)
driver.quit() # this closes window
