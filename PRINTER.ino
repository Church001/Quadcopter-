

 void printMotorOutPut(){
  Serial.print("MOTOR0 =");Serial.print(motorVal[0]);Serial.print("\t");
  Serial.print("MOTOR1 =");Serial.print(motorVal[1]);Serial.print("\t");
  Serial.print("MOTOR2 =");Serial.print(motorVal[2]);Serial.print("\t");
  Serial.print("MOTOR3 =");Serial.println(motorVal[3]);
  }

 void printRollPitch(){
    Serial.print(" PITCH =  "); Serial.print(pitch);
    Serial.print(" ROLL =   "); Serial.print(roll);
    Serial.print(" YAW =   "); Serial.println(roll);
    }

void printOffsets(){
  Serial.print("GYRO X OFFSET = "); Serial.print(gyro_x_cal);Serial.print("\t");
  Serial.print("GYRO Y OFFSET = "); Serial.print(gyro_y_cal);Serial.print("\t");
  Serial.print("GYRO Z OFFSET = "); Serial.println(gyro_z_cal);
  }
  
void printRemoteVals(){
    
    
    }

