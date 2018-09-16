#####################################
# M&M Sorter                        #
# By: Ethan Zohar and Benji Saltz   #
# Sorts M&M's by colour             #
#####################################

#Imports all needed libraries
import gspread
from oauth2client.service_account import ServiceAccountCredentials
import serial

#Tells python to read from the serial port
arduinoData = serial.Serial('/dev/ttyACM1', 9600)

#Initializes needed values
colourValue = [0,0,0,0,0,0]
total = 0
message = ''
serialData = "X"
indexCounter = 0
count = 0
lastCount = 0
 
# use creds to create a client to intract with the Google Drive API
scope = ['https://spreadsheets.google.com/feeds']
creds = ServiceAccountCredentials.from_json_keyfile_name('client_secret.json', scope)
client = gspread.authorize(creds)
 
# Find a workbook by name and open the first sheet
sheet = client.open("M&M").sheet1

#Write to the serial port '1' to start the program
arduinoData.write(b'1')

#While waiting for a message
while True:
    if arduinoData.inWaiting() > 0:
        serialData = arduinoData.readline()
        serialData = serialData[:-2]
        print(serialData)
        break
    #Break once a message has been recieved

#Convert the message to integers
for i in serialData:
    message += chr(i)

#Put all of the integers in the list colourValue
for i in message:
    if i == " ":
        colourValue[indexCounter] = int(serialData[lastCount+1 : count])
        indexCounter += 1
        lastCount = count
    count += 1

#Calculate the total
for i in range(6):
    total += int(colourValue[i])

#Put the values into the google Sheet
for i in range(6):
   sheet.update_cell(4,i+2, colourValue[i])
sheet.update_cell(7,2,total)

print(colourValue)
print(total)

