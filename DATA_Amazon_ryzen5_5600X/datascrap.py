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


driver.get("https://www.amazon.com/AMD-Ryzen-5600X-12-Thread-Processor/dp/B08166SLDF?ref_=ast_sto_dp")
driver.set_window_size(1920, 2000)
driver.get_screenshot_as_file("/pictures/"+today+"test.png")

print("im working")


# driver.close()  #this is closing one tab
time.sleep(0.005)
driver.quit() # this closes window
