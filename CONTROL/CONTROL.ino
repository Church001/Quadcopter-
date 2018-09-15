//======================================================================================================================

void control(){
if (updateFlagsShared){
      getRemoteVals();
  }
  int setRoll, setPitch, setYaw;

  static boolean disarmRequested = false;
  static unsigned long disarmRequestedTime;

  static boolean throDown = false;
  static boolean throUp = false;

  if(motorsArmed&&rxVal[CHANNEL_THROTTLE]>THROTTLE_CUTOFF){
    //motor spins only when armed and throttle is above cutoff
    disarmRequested = false;

    
  setRoll  = (float)computeRollPID(remoteRoll);
  setPitch = (float)computePitchPID(remotePitch);
  setYaw   = (float)computeYawPID(remoteYaw);
//---------------------------------------------------------------------
  motorVal[0] = remoteThrottle + setRoll + setPitch + setYaw;
  motorVal[1] = remoteThrottle - setRoll + setPitch - setYaw;
  motorVal[2] = remoteThrottle - setRoll - setPitch + setYaw;
  motorVal[3] = remoteThrottle + setRoll - setPitch - setYaw;
    }//end of if
    else if(motorsArmed){
      motorVal[0]= MOTOR_ARM_START;
      motorVal[1]= MOTOR_ARM_START;
      motorVal[2]= MOTOR_ARM_START;
      motorVal[3]= MOTOR_ARM_START;

      if (rxVal[CHANNEL_YAW]>1850){

          if(disarmRequested){//if disarm was requested from previous loop
              if((millis()-disarmRequestTime)>1000){//if time was greater than 1 second
                
                disarmMotors();
                motorsArmed = false;
                disarmRequested = false;  //resetting disarm request flag
                  }//end of if disarmRequested
                }//end of if disarm time reached
                else{
                  disarmRequested = true; //set disarm request flag
                  disarmRequestTime = millis(); //save the time the request  was made
                  }//end of else
                  }
                else{
                disarmRequested =false;    
                    }//end of else
       
          
        }//end of if yaw channel set to max
      }//end of else if
//---------------------------------------------------------------------

//---------------------------------------------------------------------
  
  
  setMotor();
  }//end of control









//==================================================================================
  float computeRollPID(int setPoint){
  float P, I, D;
 float lastTime;
 float error;
 static float lastError, sumOfError;
 float  now = millis();

 int dt = (int)(now - lastTime)/1000;
 if(dt ==0){
  dt = 1;
  }


    error = setPoint - roll;
    sumOfError += error;
    P = KP_ROLL * error;
   
   I = I +( KI_ROLL * sumOfError)*dt;
 I = constrain(I, -I_MAX,I_MAX);
   D = KD_ROLL * (error - lastError)/dt;
  // }// end of if
  
  lastError = error;
  lastTime = now;
     return (P + I + D);
  }//end of roll pid



  float  computePitchPID(int setPoint){
float P, I, D;
 float lastTime;
 float error;
 static float lastError, sumOfError;
 float  now = millis();

 int dt = (int)(now - lastTime);
 if(dt ==0){
  dt = 1;
 }


 error = setPoint - pitch;
 sumOfError += error; 
 
 P = KP_PITCH * error;
 I = I + (KI_PITCH * sumOfError)*dt;
    I = constrain(I, -I_MAX,I_MAX);
 D = KD_PITCH * (error -lastError)/dt;

lastError = error;
lastTime = now;
 return (P + I + D);
    }//end of pitch pid

    
float  computeYawPID(int setPoint){
float P, I, D;
 float lastTime;
 float error;
 static float lastError, sumOfError;
 float  now = millis();

 int dt = (int)(now - lastTime);
 if (dt ==0){
  dt = 1;
  } 
 error = yaw - setPoint;
 sumOfError += error;
 
 P = KP_YAW * error;
 I = I + (KI_YAW * sumOfError)*dt;
   I = constrain(I, -I_MAX, I_MAX);
 D = KD_YAW * (error - lastError)/dt;

lastError = error;
lastTime = now;
 return (P + I + D);
  }// end of yaw pid



