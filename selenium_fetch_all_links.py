from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
import time
import re

website = 'https://pib.gov.in/indexd.aspx'
path = "D:/Downloads/chrome-win64"

driver = webdriver.Chrome(keep_alive=True)

driver.get(website)
time.sleep(5)

location = driver.find_element("xpath",'//select[@id="Bar1_ddlregion"]/option[@value="23"]')
location.click()
time.sleep(15)

view_more = driver.find_element("xpath",'//div[@class="more-release"]/a[@href="Allrel.aspx"]')
view_more.click()
time.sleep(5)
all_day = driver.find_element("xpath",'//select[@id="ContentPlaceHolder1_ddlday"]/option[@value="0"]')
all_day.click()
time.sleep(3)

rootPageUrl = 'https://pib.gov.in/PressReleasePage.aspx'

for y in range(2017,2024):
    year = driver.find_element("xpath",f'//select[@id="ContentPlaceHolder1_ddlYear"]/option[@value="{y}"]') 
    year.click()
    time.sleep(5)

    for m in range(1,13):
        month = driver.find_element("xpath",f'//select[@id="ContentPlaceHolder1_ddlMonth"]/option[@value="{m}"]')
        month.click()
        time.sleep(5)

        all_links = set()
        a_tags = driver.find_elements(By.TAG_NAME,'a')

        for a in a_tags:
            link = a.get_attribute("href")
            if re.search("^"+rootPageUrl+".*", link):
                all_links.add(link)
        f = open(f"./selenium/links/links_{y}_{m}.txt", "w", encoding='utf-8')
        for link in all_links:
            f.write(link)
            f.write("\n")
        f.close()
        print(f"links done: m-{m} y-{y}")


driver.quit()