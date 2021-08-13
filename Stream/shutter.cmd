exec O.$EPICS_HOST_ARCH/streamApp $0
dbLoadDatabase "O.Common/streamApp.dbd"
streamApp_registerRecordDeviceDriver

epicsEnvSet "STREAM_PROTOCOL_PATH","."

drvAsynSerialPortConfigure ("shu", "/dev/ttyACM0")
asynSetOption("shu", 0, "baud", "9600")
asynSetOption("shu", 0, "bits", "8")
asynSetOption("shu", 0, "parity", "none")
asynSetOption("shu", 0, "stop", "1")
asynSetOption("shu", 0, "clocal", "Y")
asynSetOption("shu", 0, "crtscts", "N")

dbLoadRecords "shutter.db"

iocInit
