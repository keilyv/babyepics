exec O.$EPICS_HOST_ARCH/streamApp $0
dbLoadDatabase "O.Common/streamApp.dbd"
streamApp_registerRecordDeviceDriver

#where can protocols be located?
epicsEnvSet "STREAM_PROTOCOL_PATH", ".:protocols:../protocols/"

#set up the hardware
drvAsynSerialPortConfigure("LED1","/dev/ttyACM0")
asynSetOption ("LED1", 0, "baud", "9600")
asynSetOption ("LED1", 0, "bits", "8")
asynSetOption ("LED1", 0, "parity", "none")
asynSetOption ("LED1", 0, "stop", "1")
asynSetOption ("LED1", 0, "clocal", "Y")
asynSetOption ("LED1", 0, "crtscts", "N")

#load the records
dbLoadRecords "led.db"

#log debug output to file
streamSetLogfile StreamDebug.log

iocInit

#enable debug output
var streamDebug 1
