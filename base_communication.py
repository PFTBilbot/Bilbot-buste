import serial,time
    
with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as arduino:
    time.sleep(0.1) #wait for serial to open
    if arduino.isOpen():
        print("{} connected!".format(arduino.port))
        while True:
            cmd=input("Enter command : ")
            arduino.write(cmd.encode())
            
            if  arduino.inWaiting()>0: 
                answer=arduino.readline()
                print(answer)
                arduino.flushInput() #remove data after reading