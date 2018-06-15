
 

void remoteInit(){
  PCintPort::attachInterrupt(RX_PIN_CH0, chan0, CHANGE);
  PCintPort::attachInterrupt(RX_PIN_CH1, chan1, CHANGE);
  PCintPort::attachInterrupt(RX_PIN_CH2, chan2, CHANGE);
  PCintPort::attachInterrupt(RX_PIN_CH3, chan3, CHANGE);
    Serial.print("done initializing remote...");
    digitalWrite(GREEN, HIGH);
      delay(500);
    digitalWrite(GREEN, LOW);
     delay(250);
  }

  

//======================================================================================================================
//============                                                                       ===================================

void getRemoteVals(){
   noInterrupts();  
  byte updateFlags = updateFlagsShared; 
  for (int i=0; i<4; i++){
    if (updateFlagsShared & 1<<i){
      if(600 < rxValShared[i] && rxValShared[i] < 2200){
        rxVal[i] = rxValShared[i];
      }
    }
  }
    
  updateFlagsShared = 0;
  interrupts();
  rxMapping(updateFlags);
  }//end get remote values




//======================================================================================================================
//============                                                                       ===================================


void rxMapping(byte updateFlags){

  if(updateFlags & 1<<CHANNEL_THROTTLE){ 
   remoteThrottle = map(rxVal[CHANNEL_THROTTLE], THROTTLE_CUTOFF, THROTTLE_RMAX, THROTTLE_WMIN, THROTTLE_WMAX);
  }
  if(updateFlags & 1<<CHANNEL_ROLL){ 
  remoteRoll  = (float)rxVal[CHANNEL_ROLL]*ROLL_RX_MULT - ROLL_RX_SUB;
  remoteRoll  = constrain(remoteRoll, -ROLL_A_MAX, ROLL_A_MAX);
  }
  if(updateFlags & 1<<CHANNEL_PITCH){ 
   remotePitch = (float)rxVal[CHANNEL_PITCH]*PITCH_RX_MULT - PITCH_RX_SUB;
   remotePitch = constrain(remotePitch, -PITCH_A_MAX, PITCH_A_MAX);
  }
  if(updateFlags & 1<<CHANNEL_YAW){ 
   remoteYaw   = (float)rxVal[CHANNEL_YAW]*YAW_RX_MULT - YAW_RX_SUB;
   remoteYaw   = constrain(remoteYaw, -YAW_A_MAX, YAW_A_MAX);
  }
}


//-------------------------------------------------------------------------------------------------


void chan0(){
  if (digitalRead(RX_PIN_CH0) == HIGH)
  {
    rxStart[0] = micros();
  }
  else
  {
    rxValShared[0] = micros() - rxStart[0];
    rxStart[0] = 0;
    updateFlagsShared |= RX_FLAG_CH0;
  }
}
//-------------------------------------------------------------------------------------------------

void chan1(){
  if (digitalRead(RX_PIN_CH1) == HIGH)
  {
    rxStart[1] = micros();
  }
  else
  {
    rxValShared[1] = micros() - rxStart[1];
    rxStart[1] = 0;
    updateFlagsShared |= RX_FLAG_CH1;
  }
}
//-------------------------------------------------------------------------------------------------

void chan2(){
   if (digitalRead(RX_PIN_CH2) == HIGH)
  {
    rxStart[2] = micros();
  }
  else
  {
    rxValShared[2] = micros() - rxStart[2];
    rxStart[2] = 0;
    updateFlagsShared |= RX_FLAG_CH2;
  }
}
//-------------------------------------------------------------------------------------------------

void chan3(){
  if (digitalRead(RX_PIN_CH3) == HIGH)
  {
    rxStart[3] = micros();
  }
  else
  {
    rxValShared[3] = micros() - rxStart[3];
    rxStart[3] = 0;
    updateFlagsShared |= RX_FLAG_CH3;
  }
}



