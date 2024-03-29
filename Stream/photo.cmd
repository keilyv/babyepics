exec O.$EPICS_HOST_ARCH/streamApp $0
dbLoadDatabase "O.Common/streamApp.dbd"
streamApp_registerRecordDeviceDriver

#where can protocols be located
epicsEnvSet "STREAM_PROTOCOL_PATH","."

#setup the hardware
drvAsynSerialPortConfigure ("pho","/dev/ttyACM0")
asynSetOption("pho", 0, "baud", "9600")
asynSetOption("pho", 0, "bits", "8")
asynSetOption("pho", 0, "parity", "none")
asynSetOption("pho", 0, "stop", "1")
asynSetOption("pho", 0, "clocal", "Y")
asynSetOption("pho", 0, "crtscts", "N")

#drvAsynIPPortConfigure "L0", "localhost:40000"
# vxi11Configure "L0", "192.168.1.24",0,0.0,"gpin0"

#load the records
dbLoadRecords "photo.db"

#log debug output to file
#streamSetLogfile StreamDebug.log

iocInit

#enable debug output
#var streamDebug 1
