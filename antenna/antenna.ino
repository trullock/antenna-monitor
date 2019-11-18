#include <Arduino.h>
#include <SevSeg.h>

SevSeg sevseg;

void setup(){
  byte numDigits = 3;
  // set ground pins for digit 10s and 1s
  byte digitPins[] = {10, 11, 12};
  // set pins in standard ABCDEFG 7seg pattern
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 6};

  bool resistorsOnSegments = false;
  bool updateWithDelaysIn = false;
  byte hardwareConfig = COMMON_CATHODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100);

  Serial.begin(115200);
}


void loop() {

  // read avalue between 0 and 5 or 3.3V operating voltage from analog input.
  // 0 = 0V, 1023 = 5 or 3.3V
  int sensorValue = analogRead(A0);
  
  // map the analog value (0-1023) to the output range (0-90)
  float angle = mapFloat(sensorValue, 0, 1023, 0, 90);

  displayNumber(angle);
}


void displayNumber(float number){
  
  // multiply by 10 to shift the 1/10s into 1s
  int roundedNumber = number * 10;

  // send the number with no decimals
  sevseg.setNumber(roundedNumber, 1);
  sevseg.refreshDisplay();
}

float mapFloat(long x, long in_min, long in_max, long out_min, long out_max)
{
  if(x < in_min)
    return out_min;

  if(x > in_max)
    return out_max;
  
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}
