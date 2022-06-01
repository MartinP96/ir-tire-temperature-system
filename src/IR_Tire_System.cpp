#include "IR_Tire_System.h"
#include <Arduino.h>
#include <EEPROM.h>

/****************************************
            Class Constructor
*****************************************/
IR_Tire_System :: IR_Tire_System(uint8_t _FrontSensorAddr, uint8_t _RearSensorAddr):
frontTemperatureFiltered{0},rearTemperatureFiltered{0},
frontBuffer{NULL}, rearBuffer{NULL},FrontSensorStatus{_FrontSensorAddr,false,false,false},
RearSensorStatus{_RearSensorAddr,false,false,false},SystemStatus{100,0,10,false,0,100},
dataBuffer(100){
}

/****************************************
          Basic getters and setters
*****************************************/
// Getters
bool IR_Tire_System::GetFrontStatus(void) {return FrontSensorStatus.comm_ok;}
bool IR_Tire_System::GetRearStatus(void) {return RearSensorStatus.comm_ok;}
float IR_Tire_System::GetFrontTemperature(void) {return frontTemperature;}
float IR_Tire_System::GetRearTemperature(void) {return rearTemperature;}
bool IR_Tire_System::GetRearSensorUsed(void) {return RearSensorStatus.used;}
bool IR_Tire_System::GetFrontSensorUsed(void) {return FrontSensorStatus.used;}
bool IR_Tire_System::GetFrontFilterEnabled(void) {return FrontSensorStatus.filter_used;}
bool IR_Tire_System::GetRearFilterEnabled(void) {return RearSensorStatus.filter_used;}
int IR_Tire_System::GetFilterSize(void) {return SystemStatus.filter_size;}
int IR_Tire_System::GetSamplingTime(void){return SystemStatus.sampling_time;}
float IR_Tire_System::GetFrontFiltered(void) {return frontTemperatureFiltered;}
float IR_Tire_System::GetRearFiltered(void) {return rearTemperatureFiltered;}
bool IR_Tire_System::GetDataLoggingEnabled(void) {return SystemStatus.enable_data_logging;}

// Setters
void IR_Tire_System::SetFrontSensorUsed(bool status) {FrontSensorStatus.used = status;}
void IR_Tire_System::SetRearSensorUsed(bool status) {RearSensorStatus.used = status;}
void IR_Tire_System::SetSamplingTime(unsigned int _sampling_time) {
  if (_sampling_time < 1) {
    SystemStatus.sampling_time = 1;
  } else {
    SystemStatus.sampling_time = _sampling_time;
  }
}
void IR_Tire_System::SetFrontFilterEnabled(bool status) {FrontSensorStatus.filter_used = status;}
void IR_Tire_System::SetRearFilterEnabled(bool status) {RearSensorStatus.filter_used = status;}
void IR_Tire_System::SetDataLogInterval(unsigned long interval) {SystemStatus.data_log_interval = interval;}
void IR_Tire_System::SetDataLoggingEnabled(bool status) {SystemStatus.enable_data_logging = status;}

/****************************************
            Begin operation
*****************************************/
void IR_Tire_System :: begin(void)
{
  Wire.setSDA(PB9);
  Wire.setSCL(PB8);
  Wire.begin();
}

/****************************************
            Check communication
*****************************************/
void IR_Tire_System :: CheckComm(void)
{
  uint8_t frontAddr = readDeviceAddr(FrontSensorStatus.addr);
  uint8_t rearAddr = readDeviceAddr(RearSensorStatus.addr);
  if (FrontSensorStatus.used)
  {
    // Front sensor
    if(frontAddr == FrontSensorStatus.addr)
    {
      //Serial.println("Front Sensor comm OK!");
      FrontSensorStatus.comm_ok = true;
    }
    else
    {
      //Serial.println("Front Sensor comm NOK!");
        FrontSensorStatus.comm_ok = false;
    }
  } else {
    FrontSensorStatus.comm_ok = true;
  }

  if (RearSensorStatus.used)
  {
    //  Rear sensor
    if(rearAddr == RearSensorStatus.addr)
    {
      //Serial.println("Rear Sensor comm OK!");
      RearSensorStatus.comm_ok = true;
    }
    else
    {
      //Serial.println("Rear Sensor comm NOK!");
      RearSensorStatus.comm_ok = false;
    }
  } else {
      RearSensorStatus.comm_ok = true;
  }
}

  /****************************************
              Read Rear Sensor Temp
  *****************************************/
  float IR_Tire_System :: readRearSensor(void)
  {
    return  readObjectTemp(RearSensorStatus.addr);
  }

  /****************************************
              Read Front Sensor Temp
  *****************************************/
  float IR_Tire_System :: readFrontSensor(void)
  {
    return readObjectTemp(FrontSensorStatus.addr);
  }

  /****************************************
              Measure Temperature
  *****************************************/
  void IR_Tire_System :: measureTemp(unsigned long system_time)
{
    CheckComm();
    if (system_time - SystemStatus.measure_time >= SystemStatus.sampling_time){

      if (FrontSensorStatus.used && FrontSensorStatus.comm_ok){
        frontTemperature = readFrontSensor();
        //Serial.println(frontTemperature);

        // If front filter is enabled filter data and return filtered data
        if (FrontSensorStatus.filter_used) {
          frontBuffer[FrontSensorStatus.data_index] = frontTemperature;
        //  frontTemperatureFiltered = runningAverage(frontBuffer);
          frontTemperature = runningAverage(frontBuffer);
          FrontSensorStatus.data_index++;
          if (FrontSensorStatus.data_index == SystemStatus.filter_size) {
            FrontSensorStatus.data_index = 0;
          }
        }

      }
      if (RearSensorStatus.used && RearSensorStatus.comm_ok){
        rearTemperature = readRearSensor();

        // TEST TEST
        if (SystemStatus.enable_data_logging)
        {
          if (!dataBuffer.isBufferFull())
          {
            Serial.println(rearTemperature);
            dataBuffer.writeToBuffer(rearTemperature);
            SystemStatus.data_log_time = system_time;
              //Serial.println("Measurement logged");

            if (dataBuffer.isBufferFull())
            {
              SystemStatus.enable_data_logging = false;
              Serial.println("Buffer full!");
            }
          }
          else
          {
            SystemStatus.enable_data_logging = false;
          }
        }
        // END TEST

        // If front filter is enabled filter data and return filtered data
        /*if (RearSensorStatus.filter_used) {
          rearBuffer[RearSensorStatus.data_index] = rearTemperature;
          rearTemperature = runningAverage(rearBuffer);
          RearSensorStatus.data_index++;
          if (RearSensorStatus.data_index == SystemStatus.filter_size) {
            RearSensorStatus.data_index = 0;
          }
        } */
      }
      SystemStatus.measure_time = system_time;
    }
  }

  /******************************************************
          Log measured data to data buffer
  *******************************************************/
void IR_Tire_System::logData(unsigned long system_time)
{
  if (SystemStatus.enable_data_logging)
  {
    if (!dataBuffer.isBufferFull())
    {
      if (system_time - SystemStatus.data_log_time >= SystemStatus.data_log_interval)
      {
        dataBuffer.writeToBuffer(rearTemperature);
        SystemStatus.data_log_time = system_time;
        //Serial.println("Measurement logged");
      }

      if (dataBuffer.isBufferFull())
      {
        SystemStatus.enable_data_logging = false;
        Serial.println("Buffer full!");
      }
    }
    else
    {
      SystemStatus.enable_data_logging = false;
    }
  }
}

  /******************************************************
        Inicialization of runninga average filter
  *******************************************************/
void IR_Tire_System::iniFilter()
 {
   // If buffer already exist - delete it
   deleteBuffer(frontBuffer);
   deleteBuffer(rearBuffer);

   // Allocate new data buffer
   frontBuffer = allocateBuffer(SystemStatus.filter_size);
   rearBuffer = allocateBuffer(SystemStatus.filter_size);
 }

 /******************************************************
            Running average filter
 *******************************************************/
float IR_Tire_System::runningAverage(float* buff)
{
  float sum = 0;
  for(int i = 0; i < SystemStatus.filter_size; i++) {
    sum = sum + buff[i];
  }
  sum = sum/SystemStatus.filter_size;
  return sum;
}

 /****************************************
             Alocate Data Buffer
 *****************************************/
 float* IR_Tire_System::allocateBuffer(int n)
 {
   float* ptr;
   ptr = new float[n];

   // Inicialize data buffer (with zeros)
   for(int i = 0; i < n; i++) {
     ptr[i] = 0;
   }
   return ptr;
 }

 /****************************************
             Delete Data Buffer
 *****************************************/
 void IR_Tire_System::deleteBuffer(float* buff)
 {
   if(buff != NULL) {
     delete [] buff;
   }
 }

 /*********************************************
             Read Settings from EEPROM memory
 **********************************************/
void IR_Tire_System::readSysSettings(void)
{
  EEPROM.get(SAMPLING_TIME_ADDR,SystemStatus.sampling_time);
  EEPROM.get(FILTER_SIZE_ADDR,SystemStatus.filter_size);
  uint8_t flag_status;
  EEPROM.get(10,flag_status);
  FrontSensorStatus.used = (flag_status >> 0) & 1;
  FrontSensorStatus.filter_used = (flag_status >> 2) & 1;
  RearSensorStatus.used = (flag_status >> 1) & 1;
  RearSensorStatus.filter_used = (flag_status >> 3) & 1;
}

/*************************************************
      Save System Settings to EEPROM memory
**************************************************/
void IR_Tire_System::saveSettings(void)
{
  uint8_t flag_status = 0x00;

  // Build firtst data byte
  flag_status |= (FrontSensorStatus.used << 0) | (FrontSensorStatus.filter_used << 2) |
  (RearSensorStatus.used << 1) |  (RearSensorStatus.filter_used << 3);

  //Write data to eeprom
  EEPROM.update(10, flag_status);
}
