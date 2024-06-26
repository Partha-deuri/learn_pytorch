from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
import time
import re

website = 'https://live.bible.is/bible/ASMDPI/GEN/1'

driver = webdriver.Chrome()

driver.get(website)
time.sleep(5)

f_count=0

for i in range(200):
    if i%10 == 0:
        f_count +=1
        file.close()
        file = open(f"./data/text_bible_as_{f_count:003}.txt",'w', encoding='utf-8')
    chapter = driver.find_element("xpath",'//div[@class="chapter justify"]')
    ch = chapter.text
    ch = re.sub(r'[a-zA-Z0-9]',' ',ch)
    file.write(ch)
    file.write('\n')
    print(f'Pages done: {i+1:003}')
    next_page = driver.find_element("xpath",'//div[@class="arrow-wrapper next"]')
    next_page.click()
    time.sleep(3)


print(f"\n\t\t*** Task Completed ***\n\n")

get_url = driver.current_url
print("The current url is:"+str(get_url))

driver.quit()
