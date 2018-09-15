
#include <Wire.h>
#include <Servo.h>
//#include <PinChangeInt.h>

#define KP_ROLL 3.9
#define KI_ROLL 0.03
#define KD_ROLL 3.2

#define KP_PITCH KP_ROLL
#define KI_PITCH KI_ROLL
#define KD_PITCH KD_ROLL

#define KP_YAW 3.4
#define KI_YAW 0.02
#define KD_YAW 1.4

#define I_MAX 1.5

#define GYRO_X_OFFSET 103
#define GYRO_Y_OFFSET 94
#define GYRO_Z_OFFSET 41

///------------------------REMOTE DECLARATIONS------------------------------------
#define RX_PIN_CH0 6                         
#define RX_PIN_CH1 7                                 
#define RX_PIN_CH2 8                                 
#define RX_PIN_CH3 4 

#define CHANNEL_THROTTLE 0                         
#define CHANNEL_ROLL 1                               
#define CHANNEL_PITCH 2                            
#define CHANNEL_YAW 3        

                                             
#define RX_FLAG_CH0 1  //B00000001               
#define RX_FLAG_CH1 2  //B00000010                   
#define RX_FLAG_CH2 4  //B00000100                 
#define RX_FLAG_CH3 8  //B00001000       

#define YAW_RMIN 1080                                
#define YAW_RMAX 1850                                
#define ROLL_RMIN 1084                             
#define ROLL_RMAX 1856                              
#define PITCH_RMIN 1092                          
#define PITCH_RMAX 1860                            
                                                    
#define MOTOR_ARM_START 1000                        
#define MOTOR_MAX_LEVEL 1800                        
                                                  
#define THROTTLE_CUTOFF 1050                       
#define THROTTLE_RMAX 1860                           
                                                     
#define THROTTLE_WMIN MOTOR_ARM_START                
#define THROTTLE_WMAX MOTOR_MAX_LEVEL                
                                                    
#define ROLL_A_MAX 20.0                             
#define PITCH_A_MAX 20.0                           
#define YAW_A_MAX 60.0                              
                                                  
#define YAW_RX_MULT YAW_A_MAX/400                   
#define YAW_RX_SUB 1500*YAW_RX_MULT                  
                                                    
#define ROLL_RX_MULT ROLL_A_MAX/400                 
#define ROLL_RX_SUB 1500*ROLL_RX_MULT               
                                                    
#define PITCH_RX_MULT PITCH_A_MAX/400               
#define PITCH_RX_SUB 1500*PITCH_RX_MULT


#define RED 2
#define GREEN 5
#define BLUE 4
               
///-------------------------MOTOR DECLARATIONS------------------------------------
Servo esc1;
Servo esc2;
Servo esc3;
Servo esc4;
int escPin1 = 3;
int escPin2 = 9;
int escPin3 = 10;
int escPin4 = 11;

//-----------------------STATE ESTIMATION---------------------------
//Declaring some global variables
int gyro_x, gyro_y, gyro_z;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
boolean set_gyro_angles;

long acc_x, acc_y, acc_z, acc_total_vector;
float angle_roll_acc, angle_pitch_acc;

float angle_pitch, angle_roll;
int angle_pitch_buffer, angle_roll_buffer;
float pitch, roll, yaw;

//-----------------------------REMOTE VALS----------------------------
int remoteRoll = 0;
int remotePitch = 0;
int remoteYaw  = 0;
int remoteThrottle;

volatile byte updateFlagsShared;
volatile int rxValShared[4];
unsigned long rxStart[4];
int rxVal[4];
//----------------------------------------------------------
 unsigned long loopTime;
 int motorVal[4];
int temp;
boolean motorsArmed;
unsigned long disarmRequestTime;
//-------------------------PID CONFIGURATION-------------------------------



void setup() {
  Serial.begin(115200);
//initMotor();
 sensorInit();
 delay(100);
 //remoteInit();
     motorVal[0] = 1000;
     motorVal[1] = 1000;
     motorVal[2] = 1000;
     motorVal[3] = 1000;
  setMotor();
  delay(2000);
}


//=======================================================================
void loop(){
    loopTime = millis();
  updateSensor();   
  stateEstimation();

    remoteThrottle = 1200;
 
  control();
  
  
  //=======================PRINTING PRESS============================
 printMotorOutPut();
 //printRollPitch();
 //printRemoteVals();
 //printOffsets();
}// end loop loop



/*
* i update yaw into the control mixture. trying to observe the performance (RESULT: it works well)
* 
*/


 
