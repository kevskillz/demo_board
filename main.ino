#include <Stepper.h>

class LED {
    /*
       LEDs that control brightness need to be pins  3, 5, 6, 9, 10, or 11
    */
    public int LED_PIN;
    int state = HIGH;
    public LED(int pin) {
      LED_PIN = pin;
      pinMode(LED_PIN, OUTPUT);
    }

    public void turnOffLED() {
      analogWrite(LED_PIN, LOW);
    }
    public void setBrightness(int brightness) {
      analogWrite(LED_PIN, brightness);
    }
}

class SatelliteEarth {
    public const int SWITCH_PIN = -1;
    public const int SPEED = 200; // 0 - 255
    public const int A_ENABLE_PIN = -1;
    public const int IN_PINS[] = { -1, -1};

    public Satellite_Earth() {
      pinMode(SWITCH_PIN, INPUT);

      pinMode(IN_PINS[0], OUTPUT);
      pinMode(IN_PINS[1], OUTPUT);
      pinMode(A_ENABLE_PIN, OUTPUT);
      setSpeed(SPEED);

    }

    public void updateSatelliteEarth() {
      if (isSwitchPressed()) {
        digitalWrite(IN_PINS[0], HIGH);
        digitalWrite(IN_PINS[1], LOW); // swap pins/high to change dir
      }
    }

    private bool isSwitchPressed() {
      return (digitalRead(SWITCH_PIN) == HIGH);
    }

    public void setSpeed(int n) {
      analogWrite(A_ENABLE_PIN, n);
    }


}

class Constellation {
    int LEDs[10];
    int BUTTON_PIN;
    int NUM_LEDS;
    public Constellation(int LEDPinsArr[], int numLEDs, int buttonPIN) {
      for (int i = 0; i < numLEDs; i++) {
        LED temp(LEDPinsArr[i]);
        LEDs[i] = temp;
      }
      BUTTON_PIN = buttonPIN;
      NUM_LEDS = numLEDs;
      pinMode(BUTTON_PIN, INPUT);

    }

    public void updateConstellation() {
      if (digitalRead(BUTTON_PIN) == HIGH) {
        turnLEDsOn();
      }
      else {
        turnLEDsOff();
      }
    }

    private void turnLEDsOn () {
      for (int i = 0; i < NUM_LEDS; i++) {
        LEDs[i].setBrightness(255);
      }
    }

    private void turnLEDsOn () {
      for (int i = 0; i < NUM_LEDS; i++) {
        LEDs[i].turnOffLED)();
      }
    }

}





class Rocket {

    public const int MOTOR_PINS[] = { -1, -1, -1, -1};
    public const int LED_PINS[] = { -1, -1};
    public const int NUM_LEDS = 2;
    public const int POTENTIOMETER_PIN = -1;
    public const LED LEDs[NUM_LEDS];
    public const int POTENTIOMETER_MIN = -1;
    public const int MIN_ROCKET_POS = 0;
    public const float NUM_ROTATIONS_TO_GET_TO_HIGH_POINT = 3;
    public const int STEPS_PER_REVOLUTION = 32;
    public const int MAX_ROCKET_POS = NUM_ROTATIONS_TO_GET_TO_HIGH_POINT * STEPS_PER_REVOLUTION;
    public const int POTENTIOMETER_MAX = -1;
    public const int MAX_STEPS = -1;
    public const int pos = -1;
    Stepper rocket_motor(MAX_STEPS, MOTOR_PINS[0], MOTOR_PINS[1], MOTOR_PINS[2], MOTOR_PINS[3]);
    public void setSpeed(int n) {
      rocket_motor.setSpeed(n);
    }
    public Rocket() {

      for (int i = 0; i < NUM_LEDS; i++) {
        LED tempv(LED_PINS[i]);
        LEDs[i] = tempv;
      }


    }

    private int lastPotPos = POTENTIOMETER_MIN;


    public void updateRocket() {
      int data = analogRead(POTENTIOMETER_PIN);

      int perc = map(data, POTENTIOMETER_MIN, POTENTIOMETER_MAX, 0, 255);
      setLEDsBrightness(perc);

      data -= lastPotPos;
      int abs_data = abs(data);
      int sign;

      if (data < 0) sign = -1;
      else {
        sign = 1;
      }

      int numSteps = map(abs_data, POTENTIOMETER_MIN, POTENTIOMETER_MAX, MIN_ROCKET_POS, MAX_ROCKET_POS);


      rocket_motor.step(sign * numSteps);

      lastPotPos = data;
    }

    private void setLEDsBrightness (int brightness) {
      for (int i = 0; i < NUM_LEDS; i++) {
        LEDs[i].setBrightness(brightness);
      }
    }
    public void turnOff() {
      for (int i = 0; i < NUM_LEDS; i++) {
        LEDs[i].turnOff();
      }
    }


}

class UFO {
    public const int MIC_PIN = -1;
    public const int LED_PIN = -1;
    public const int THRESH = 600;
    LED led(LED_PIN);

    public void updateUFO() {
      if (readMic() > THRESH) {
        led.setBrightness(255);
      }
    }

    private int readMic() {
      return analogRead(MIC_PIN);
    }
}


UFO ufo;
Rocket rocket;
SatelliteEarth satEarth;

// LED Pins
const int daisyLEDPins[] = {};
const int daisyButtonPin = -1;

const int bearLEDPins[] = {};
const int bearButtonPin = -1;

const int dogLEDPins[] = {};
const int dogButtonPin = -1;

const int birdLEDPins[] = {};
const int birdButtonPin = -1;

const int gearLEDPins[] = {};
const int gearButtonPin = -1;


Constellation daisy(daisyLEDPins, sizeof(daisyLEDPins) / sizeof(daisyLEDPins[0]), daisyButtonPin);
Constellation bear(bearLEDPins, sizeof(bearLEDPins) / sizeof(bearLEDPins[0]), bearButtonPin);
Constellation dog(dogLEDPins, sizeof(dogLEDPins) / sizeof(dogLEDPins[0]), dogButtonPin);
Constellation bird(birdLEDPins, sizeof(birdLEDPins) / sizeof(birdLEDPins[0]), birdButtonPin);
Constellation gear(gearLEDPins, sizeof(gearLEDPins) / sizeof(gearLEDPins[0]), gearButtonPin);

void setup() {
  // put your setup code here, to run once:

}



void loop() {
  // put your main code here, to run repeatedly:

  daisy.updateConstellation();
  bear.updateConstellation();
  dog.updateConstellation();
  bird.updateConstellation();
  gear.updateConstellation();
  ufo.updateUFO();
  rocket.updateRocket();
  satEarth.updateSatelliteEarth();

  // delay(100);

}
