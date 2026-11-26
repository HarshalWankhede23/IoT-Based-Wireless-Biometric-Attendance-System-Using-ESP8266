from openpyxl import load_workbook
from datetime import datetime
from datetime import date
import serial
import time
ser = serial.Serial(port='COM3', baudrate=115200)

def sysInfo():
    print("----Biometric Smart Wireless Attendance System----")
    time.sleep(1)
    print("-----------Wait for system get ready!-------------")
    time.sleep(3)
    print()
    print('                  System Ready!                    ')
    
sysInfo()

while(True):
    line = ser.readline()   # read a byte
    if line:
        string = line.decode().rstrip()  # convert the byte string to a unicode string
        sID = string[0]
        
        if(string[0]=='1'):
            name= '2024024-Pawan'
            print('Data receiving...')
        print(string)
        if(string[0]=='2'):
            name= '2024037-Aryan'
        if(string[0]=='3'):
            name= '2024050-Harshwardhan'
        if(string[0]=='4'):
            name= '2024060-Harshal'
        if(string[0]=='5'):
            name= '2124802-Toshik'
            
        if(string[1]=='1'):
            Attendance= 'P'
        if(string[1]=='0'):
            Attendance= 'A'
            
        if(string[2]=='W'):
            Period= 'EC409E'
        if(string[2]=='C'):
            Period= 'EC503E'
        if(string[2]=='O'):
            Period= 'EC505E'
        if(string[2]=='M'):
            Period= 'MN101E'
        if(string[2]=='E'):
            Period= 'EC413E'
            
        wb = load_workbook('attendance.xlsx')
        work_sheet = wb.active
        max_row = work_sheet.max_row
        
        #print("Max Row =",max_row)
        date = date.today()
        #print("Today's date:", date)
        now = datetime.now()
        time = now.strftime("%H:%M:%S")
        #print("Current Time =", time)
        srNo = int(max_row)
        if(sID!='0'):
            work_sheet.append([srNo, sID, name, Attendance, date , time, Period])
        else:
            work_sheet.append([''])
            print('Data received and stord in excel file.')
            print('')
        wb.save('attendance.xlsx')
 



    


