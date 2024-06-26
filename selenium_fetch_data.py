from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
import time
import re

for y in range(2023,2017,-1):
    for m in range(1,13):
        all_links = set()
        f = open(f'./selenium/links/links_{y}_{m}.txt','r')
        for link in f.readlines():
            all_links.add(link)
        f.close()
        temp_driver = webdriver.Chrome(keep_alive=True)
        i=0
        for link in all_links:
            corpus = set()
            temp_driver.get(link)
            time.sleep(3)
            p_tags = temp_driver.find_elements(By.TAG_NAME,"p")
            f = open(f"./selenium/data/data_{y}_{m}.txt", "a", encoding='utf-8')
            
            for p in p_tags:
                para = p.text
                if para==' ':
                    continue
                if  re.search('^DS.*',para) or para=='***':
                    break
                para = re.sub(r"[^ঀ-ৱ।’\-|]+",' ',para)
                if para not in corpus:
                    corpus.add(para)
                    f.write(para)
                    f.write("\n")
            f.close()
            i += 1
        print(f"done: m-{m} y-{y}")
        temp_driver.quit()
