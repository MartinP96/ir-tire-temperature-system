#ifndef _IR_TIRE_SYSTEM
#define _IR_TIRE_SYSTEM

#include "Mlx_Ir_Sensor.h"
#include "CircularBuffer.h"

#define FRONT_SENSOR_ADDR   0x5B
#define REAR_SENSOR_ADDR    0x5A

// EEPPROM ADDR
#define SYS_STATE_ADDR 0
#define SAMPLING_TIME_ADDR 1
#define FILTER_SIZE_ADDR 3

struct Sensor_status
{
  uint8_t addr;
  bool used;
  bool comm_ok;
  bool filter_used; // TO BE REMOVED
  int data_index;
};

struct Sys_status
{
  unsigned int sampling_time;
  unsigned long measure_time;
  int filter_size;  // TO BE REMOVED
  bool enable_data_logging;
  unsigned long data_log_time;
  unsigned long data_log_interval;
};

class IR_Tire_System : public MLX90614
{
public:
  // Constructors
  IR_Tire_System(uint8_t _FrontSensorAddr = FRONT_SENSOR_ADDR,
    uint8_t _ReadSensorAddr = REAR_SENSOR_ADDR);

  // Getters/Setters
  bool GetFrontStatus(void);
  bool GetRearStatus(void);
  float GetFrontTemperature(void);
  float GetRearTemperature(void);
  bool GetRearSensorUsed(void);
  bool GetFrontSensorUsed(void);
  bool GetFrontFilterEnabled(void); // TO BE REMOVED
  bool GetRearFilterEnabled(void);  // TO BE REMOVED
  int GetFilterSize(void);  // TO BE REMOVED
  int GetSamplingTime(void);
  float GetFrontFiltered(void);
  float GetRearFiltered(void);
  bool GetDataLoggingEnabled(void);

  void SetFrontSensorUsed(bool status);
  void SetRearSensorUsed(bool status);
  void SetSamplingTime(unsigned int _sampling_time);
  void SetFrontFilterEnabled(bool status);  // TO BE REMOVED
  void SetRearFilterEnabled(bool status); // TO BE REMOVED
  void SetDataLogInterval(unsigned long interval);
  void SetDataLoggingEnabled(bool status);

  // Public methods
  void saveSettings(void);
  void readSysSettings(void);

  // Measurement functions
  void begin(void);
  void CheckComm(void);
  void measureTemp(unsigned long system_time);
  void iniFilter(void); // TO BE REMOVED
  float runningAverage(float* buff);
  void logData(unsigned long system_time);

  // Datalog buffer
  //CircularBuffer<float> dataBuffer;
  CircuralBuffer<float> dataBuffer;

private:
  // Private methods
  float readRearSensor(void);
  float readFrontSensor(void);
  float* allocateBuffer(int n); // TO BE REMOVED
  void  deleteBuffer(float* buff); // TO BE REMOVED

  Sys_status SystemStatus;
  Sensor_status FrontSensorStatus;
  Sensor_status RearSensorStatus;

  float frontTemperature;
  float frontTemperatureFiltered; // TO BE REMOVED
  float rearTemperature;
  float rearTemperatureFiltered; // TO BE REMOVED

  float* frontBuffer; // TO BE REMOVED
  float* rearBuffer;  // TO BE REMOVED
};

#endif
