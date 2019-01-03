#include <Adafruit_NeoPixel.h>

//**** BEGIN CONFIGURATION ******

#define NUM_LEDS 120
#define DATA_PIN 6
#define brightnessKnob A1
#define patternKnob A2
#define spacing 2 //2 for 30 leds/meter, 1 for 60 leds/meter

/***************************************************************************************
  Adafruit_NeoPixle Setup
***************************************************************************************/
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRBW + NEO_KHZ800);

//****** END CONFIGURATION ******

/***************************************************************************************
  Encoder Variables
***************************************************************************************/

int upperLimit = 12; // max number of patterns (encoder)
int lowerLimit = 1;  // minimum number of patterns (encoder)

static int pinA = 2; // Our first hardware interrupt pin is digital pin 2

static int pinB = 3; // Our second hardware interrupt pin is digital pin 3

volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that
                         // the encoder has arrived at a detent

volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that
                         // the encoder has arrived at a detent (opposite direction to when aFlag is
                         // set)

volatile byte encoderPos = 1; // this variable stores our current value of encoder position. Change
                              // to int or uin16_t instead of byte if you want to record a larger
                              // range than 0-255

volatile byte oldEncPos = 0; // stores the last encoder position value so we can compare to the
                             // current reading and see if it has changed (so we know when to print
                             // to the serial monitor)

volatile byte reading = 0; // somewhere to store the direct values we read from our interrupt pins
                           // before checking to see if we have moved a whole detent

/***************************************************************************************
  Other Variables
***************************************************************************************/
int encoderButton, fadeDirection;
int brightness = 255;
int brightnessValue = 0;
int tempValue = 0;
int tempValue2 = 0;
int program = 0;
int red, green, blue, white = 0;
int red2, green2, blue2, white2;
float h, hTemp = 0;

void setup()
{
  //Initialize Serial port
  Serial.begin(115200);

  /***************************************************************************************
      Encoder Setup
  ***************************************************************************************/

  pinMode(pinA, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or
                               // 3.3V for most cases)

  pinMode(pinB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or
                               // 3.3V for most cases)

  attachInterrupt(0, PinA, RISING); // set an interrupt on PinA, looking for a rising edge signal
                                    // and executing the "PinA" Interrupt Service Routine (below)

  attachInterrupt(1, PinB, RISING); // set an interrupt on PinB, looking for a rising edge signal
                                    // and executing the "PinB" Interrupt Service Routine (below)

  /***************************************************************************************
  ***************************************************************************************/

  // encoder button
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);
  // for lazy GRND problem solving
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  // encoder 1
  pinMode(A0, OUTPUT);   // set Analog_0 to OUTPUT
  digitalWrite(A0, LOW); // set Analog_0 to LOW
  // encoder 2
  pinMode(A2, OUTPUT);    // set Analog_1 to OUTPUT
  digitalWrite(A2, HIGH); // set Analog_1 to HIGH
  // brightness
  pinMode(A1, INPUT); // set Analog_2 to INPUT

  //Initiate LED pixel strip
  strip.setBrightness(255);
  strip.begin();
  strip.show();
}

void loop()
{

  //**** READ USER INPUTS ****
  GetEncoderButtonValue();
  //Read brightness wheel
  tempValue = analogRead(brightnessKnob);

  //filter noise
  if ((tempValue > brightnessValue + 2) || (tempValue + 2 < brightnessValue))
  {
    //check minimum value - is 12 it?
    brightnessValue = tempValue;
    tempValue = constrain(tempValue, 20, 1005);
    tempValue = map(tempValue, 20, 1005, 0, 255);
    brightness = tempValue;
  }

  CheckEncoderKnobLimits();

  TestCode();
  //**** RUN SELECTED PATTERN ****
  CallColorFunction();
}

void CallColorFunction()
{
  switch (encoderPos)
  {
  case 1:
    all_red();
    break;
  case 2:
    amber();
    break;
  case 3:
    warmer_white();
    break;
  case 4:
    warm_white();
    break;
  case 5:
    RainbowFlowSlow(.00003, .0045);
    break;
  case 6:
    LargeGroupColorFlowBounce(12, .0001, .3, .9, .5); // ??
    break;
  case 7:
    RastaFlowSlow();
    break;
  case 8:
    BlueWhite_Waves();
    break;
  case 9:
    BlueGreen_Waves();
    break;
  case 10:
    RainbowFlowSlow(.0001, .0014);
    break;
  case 11:
    RainbowFlowSlow(.0005, .0083);
    break;
  case 12:
    RainbowFlowSlow(.0001, .0014, .82, .38);
    break;
    //  case 13:
    //   // LargeGroupColorFlowBounce(12, .0001, .3, .9, .5); // ??
    //   RainbowFlowSlow(.001, .0014, .82, .38);
    //   break;
    //  case 14:
    //   RedWhite_Waves();// ----
    //   break;
    //  case 15:
    //   RainbowFlowSlow(.001, .0014, .82, .38);
    //   break;
  }
  strip.show();
}

//**** END MAIN LOOP ****
