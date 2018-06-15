//======================================================================================================================
//============                                                                       ===================================
//======================================================================================================================

//=============================================================================
void stateEstimation(){
  gyro_x -= GYRO_X_OFFSET;//gyro_x_cal;                                                
  gyro_y -= GYRO_Y_OFFSET;//gyro_y_cal;                                                
  gyro_z -= GYRO_Z_OFFSET;//gyro_z_cal;                                                
         
  //Gyro angle calculations . Note 0.0000305343 = 1 / (250Hz x 131)
  angle_pitch += gyro_x * 0.0000305343;                                   //Calculate the traveled pitch angle and add this to the angle_pitch variable
  angle_roll += gyro_y * 0.0000305343;                                    //Calculate the traveled roll angle and add this to the angle_roll variable
  //0.000000532994 = 0.0000305343 * (3.142(PI) / 180degr) The Arduino sin function is in radians
  angle_pitch += angle_roll * sin(gyro_z * 0.000000532994);               //If the IMU has yawed transfer the roll angle to the pitch angel
  angle_roll -= angle_pitch * sin(gyro_z * 0.000000532994);               //If the IMU has yawed transfer the pitch angle to the roll angel
  
  //Accelerometer angle calculations
  acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));  //Calculate the total accelerometer vector
  //57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
  angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296;       //Calculate the pitch angle
  angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296;       //Calculate the roll angle
  
  angle_pitch_acc -= 0.0;                                              //Accelerometer calibration value for pitch
  angle_roll_acc -= 0.0;                                               //Accelerometer calibration value for roll

  if(set_gyro_angles){                                                 //If the IMU is already started
    angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;     //Correct the drift of the gyro pitch angle with the accelerometer pitch angle
    angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;        //Correct the drift of the gyro roll angle with the accelerometer roll angle
  }
  else{                                                                //At first start
    angle_pitch = angle_pitch_acc;                                     //Set the gyro pitch angle equal to the accelerometer pitch angle 
    angle_roll = angle_roll_acc;                                       //Set the gyro roll angle equal to the accelerometer roll angle 
    set_gyro_angles = true;                                            //Set the IMU started flag
  }
  
  //To dampen the pitch and roll angles a complementary filter is used
  pitch = (pitch * 0.89 + angle_pitch * 0.11);   //Take 90% of the output pitch value and add 10% of the raw pitch value
  roll = (roll  * 0.89 + angle_roll * 0.11);  
  yaw = gyro_z * 0.0000305343;
  }

 

