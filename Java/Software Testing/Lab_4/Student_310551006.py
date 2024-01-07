#%%
from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait
# %%
options = webdriver.ChromeOptions()
options.add_argument("--start-maximized")
driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)

driver.get("https://www.nycu.edu.tw/")
driver.maximize_window()

# WebDriverWait(driver, 10).until(EC.element_to_be_clickable((By.XPATH, "//ul[@id='menu-1-9942884']/li[2]")))
driver.find_element(By.XPATH, "//ul[@id='menu-1-9942884']/li[2]").click()

# WebDriverWait(driver, 10).until(EC.element_to_be_clickable((By.XPATH, "//ul[@class='su-posts su-posts-list-loop']/li[1]")))
driver.find_element(By.XPATH, "//ul[@class='su-posts su-posts-list-loop']/li[1]/a").click()#click the first news of the list

print("Title:\n", driver.find_element(By.TAG_NAME, "h1").text)
print("Content:\n", driver.find_element(By.XPATH, "//div[@class='entry-content clr']").text)

#switch to new tab - google.com
driver.switch_to.new_window('tab')
driver.get("https://www.google.com")

driver.find_element(By.TAG_NAME, "input").send_keys("310551006")#search 310551006
driver.find_element(By.XPATH, "//input[@class='gNO89b']").submit()
driver.implicitly_wait(5)
print("Title:\n", driver.find_element(By.XPATH, "//div[@class='v7W49e']/div[2]//h3").text)
# %%
