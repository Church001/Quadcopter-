
//======================================================================================================================
//============                                                                       ===================================
//======================================================================================================================

//====================INITIALIZING MOTOR FUNCTION=============================
void initMotor(void){
 esc1.attach(escPin1);
 esc2.attach(escPin2);
 esc3.attach(escPin3);
 esc4.attach(escPin4);
  //setMotor(1000);
  }

//=================================SETTING MOTOR FUNTION====================

void setMotor(){
   
esc1.writeMicroseconds(motorVal[0]);
esc2.writeMicroseconds(motorVal[1]);
esc3.writeMicroseconds(motorVal[2]);
esc4.writeMicroseconds(motorVal[3]);

    }//ending setmotor routine

//===============================DISARMING MOTORS===========================

void disarmMotors(){
  motorVal[0] = 0;
  motorVal[1] = 0;
  motorVal[2] = 0;
  motorVal[3] = 0;
 setMotor();
  }//end of disarm function

//============================ARMING MOTORS==================================


void armMotors(){
  motorVal[0] = 1000;
  motorVal[1] = 1000;
  motorVal[2] = 1000;
  motorVal[3] = 1000;
 setMotor();
  }//end of arming motors



