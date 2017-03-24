//Librerias Nesesarias
#include <AP_Common.h>
#include <AP_Math.h>
#include <AP_Param.h>
#include <AP_Progmem.h>
#include <AP_ADC.h>
#include <AP_InertialSensor.h>
#include <AP_HAL.h>
#include <AP_HAL_AVR.h>
//Mandamos a activar el sensor
const AP_HAL::HAL& hal = AP_HAL_AVR_APM2;  
AP_InertialSensor_MPU6000 ins; 

//Definimos variables para guardar el valor de los angulos de euler
float gyroPitch;
float gyroRoll;
float gyroYaw;

void setup()
{
ins.init(AP_InertialSensor::COLD_START,  AP_InertialSensor::RATE_100HZ, NULL);
hal.scheduler->suspend_timer_procs(); 
ins.dmp_init();                       
ins.push_gyro_offsets_to_dmp();
hal.scheduler->resume_timer_procs(); 
}

void loop()
{
  while (ins.num_samples_available() == 0);
  ins.update();
  
  Vector3f gyro = ins.get_gyro();
  gyroPitch = ((gyro.y)*180)/3.1416; 
  gyroRoll =  ((gyro.x)*180)/3.1416;
  gyroYaw =   ((gyro.z)*180)/3.1416;

 
  hal.console->printf_P(PSTR("Gyro PITCH: %4.1f  "), gyroPitch);
  hal.console->printf_P(PSTR("Gyro ROLL: %4.1f   "), gyroRoll);
  hal.console->printf_P(PSTR("Gyro Yaw: %4.1f\n  "), gyroYaw);
}
AP_HAL_MAIN(); 
