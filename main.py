import socket
import struct
import serial
import yaml

def bitsToFloat32(data, pos):
    try:
        val = struct.unpack('f', data[pos:pos+4])[0]
    except struct.error as _:
        val = 0
    except Exception as e:
        val = 0
    return val

def writeArduino(msg):
    arduino.write(bytes(msg, 'utf-8'))
    arduino.write(b'\n')

def debugPrint(msg):
    global debugMsg
    if (debugMsg == True):
        print(msg)


# begin reading the config from config.yml

with open('config.yml', 'r') as ymlRead:
    configFile = yaml.safe_load(ymlRead)

# setting the main configuration
config = configFile['CONFIGURATION']
DIRT_IP = config['dirtip']
DIRT_PORT = config['dirtport']
arduinoPort = config['arduinoport']

# setting the game configuration
gameCfg = configFile['GAME']
useMph = gameCfg['mph']
trueVel = gameCfg['truevelocity']

# setting the debug configuration
debugCfg = configFile['DEBUG']
debugMsg = debugCfg['debugmessages']
messageMode = debugCfg['messagemode']

print('Welcome! You are using version 1.0.0 of the DRallyDash app.')
print('author: Csongoose')
print('Establilishing connection with the arduino...')

arduino = serial.Serial(port=arduinoPort, baudrate=9600, timeout=.1)

sock = socket.socket(socket.AF_INET,
                     socket.SOCK_DGRAM)
sock.bind((DIRT_IP, DIRT_PORT))

ledVal = 0
prevLedVal = 4
loop = False
mainloop = True
firstLoop = True
sFirstLoop = True

debugPrint('Debug mode enabled.')

print('Starting up...')

while mainloop:             # start main loop
    if (messageMode == True):
        if(firstLoop == True):
            print('Message mode enabled, type *start* to start the program normally, *exit* to exit the program, type message you want to send to the arduino.')
            firstLoop = False
        message = input()
        if (message == 'start'):
            loop = True
            print('Program started')
        elif (message == 'exit'):
            mainloop = False
            loop = False
            print('Stopping process...')
        elif (message == ""):
            print('Error: The input given cannot be empty!')
        else:
            writeArduino(message)
            print('Message sent to arduino is: ' + message + ' encoded to bytes as utf-8')
    else:
        loop = True

    while loop:
        if (sFirstLoop == True):
            debugPrint('Main loop started')
            print('App is ready!')
            sFirstLoop = False
        data, addr = sock.recvfrom(4096)                # define data
        maxRpm = (bitsToFloat32(data, 252) * 10)        # get max RPM
        rpm = (bitsToFloat32(data, 148) * 10)           # get RPM
        maxRpmFourth = maxRpm / 4                       # math for the LEDs
        upperFourth = maxRpmFourth / 4                  # math for the LEDs again (I know I could do it with one equation)


        if (trueVel == True):
            speed = (bitsToFloat32(data, 28))           # get speed (velocity)
        else:
            speed = (((bitsToFloat32(data, 108)) + (bitsToFloat32(data, 112))) / 2)     # get the speed of front tires

        if (useMph == True):
            spdiUnit = speed * 2.23693629               # get speed in Mph
        else:
            spdiUnit = speed * 3.60                     # get speed in Kph
        rndSpd = round(spdiUnit)                        # round speed to the nearest 1
        debugPrint('Measured speed is: ' + str(rndSpd))
        spdMsg = 's' + '%03d' % rndSpd
        writeArduino(spdMsg)

        if ((rpm > maxRpm - (upperFourth)) and (ledVal !=4)):
            debugPrint('RPM LEDs: 4/4')
            ledVal = 4
            writeArduino('r4')
        elif (rpm > maxRpm - (2 * upperFourth) and (ledVal !=3) and (rpm < (maxRpm - upperFourth))):
            debugPrint('RPM LEDs: 3/4')
            ledVal = 3
            writeArduino('r3')
        elif (rpm > maxRpm - (3 * upperFourth) and (ledVal !=2) and (rpm < maxRpm - (2 * upperFourth))):
            debugPrint('RPM LEDs: 2/4')
            ledVal = 2
            writeArduino('r2')
        elif (rpm > maxRpm - (4 * upperFourth) and (ledVal !=1) and (rpm < maxRpm - (3 * upperFourth))):
            debugPrint('RPM LEDs: 1/4')
            ledVal = 1
            writeArduino('r1')
        elif (ledVal !=0 and (rpm < maxRpm - (4 * upperFourth))):
            debugPrint('RPM LEDs: 0/4')
            ledVal = 0
            writeArduino('r0')