const int ledpin = 3;
const int soundpin = A0;
const int buttonpin = 2;

const int MAX_LED_POWER = 255;
const int LED_REFRESING_STEP_POWER = 5; // 51 steps
const int LED_REFRESHING_FREQUENCE_MS = 80;
const int NOISE_LED_POWER = 10;

const bool ZATUH_FEATURE_TOGGLE = true;

void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(soundpin, INPUT);
  Serial.begin(9600);
}


int actualLedPower;
unsigned long lastLedPowerSetTime = millis();

void loop(){
    int loudness = analogRead(soundpin);
Serial.println(loudness);
if (loudness < 350) {
 loudness = 350;
}
    
    int futureLedPower = map(loudness, 350, 550, 0, MAX_LED_POWER); // 50
    //futureLedPower = MAX_LED_POWER - futureLedPower; // 200


    if (ZATUH_FEATURE_TOGGLE) {
      if (futureLedPower > actualLedPower) {
        actualLedPower = futureLedPower;
      } 
  
      bool isTimeToSetLedPower = (millis() - LED_REFRESHING_FREQUENCE_MS) > lastLedPowerSetTime;
      if (isTimeToSetLedPower) {
  
        lastLedPowerSetTime = millis();
        Serial.println(100);
  
        actualLedPower -= LED_REFRESING_STEP_POWER;
              
      }
  
      

    } else {
      actualLedPower = futureLedPower;
    }

    if (actualLedPower < NOISE_LED_POWER) {
          actualLedPower = 0;
        }
    //Serial.println(actualLedPower);
    analogWrite(ledpin, actualLedPower);
}
