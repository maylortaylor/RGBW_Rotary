/***************************************************************************************
  Test Code
***************************************************************************************/
void TestCode()
{
    Serial.print("   Hue:   ");
    Serial.print(h);
    Serial.print(analogRead(3));
    Serial.print("   Encoder Position:  ");
    Serial.print(encoderPos);
    Serial.print("   Encoder Button:  ");
    Serial.print(encoderButton);
    Serial.print("   Brightness >> ");
    Serial.println(brightnessValue);
}

float GetH_BouncingWithLimits(float _speed, float _hHigh, float _hLow) {
    if (h > _hHigh)
    {
        h = _hHigh;
        fadeDirection = 0;
    }
    if (h < _hLow)
    {
        h = _hLow;
        fadeDirection = 1;
    }

    if (fadeDirection == 1)
    {
        h += _speed * spacing; // increment to make faster
    }
    if (fadeDirection == 0)
    {
        h -= _speed * spacing; // decrement to make faster
    }

    return h;
}
void CatchHOverflow(){
  if (h > 1){
    h -= 1;
  }
  if (h < 0){
    h += 1;
  }
}
// void CatchHTempOverflow() {
//   if (hTemp > 1){
//     hTemp -= 1;
//   }
//   if (hTemp < 0){
//     hTemp += 1;
//   }
// }

/***************************************************************************************
  Encoder
***************************************************************************************/
void GetEncoderButtonValue()
{
    encoderButton = digitalRead(4); // read digital pin 4

    // // if encoder button is pressed, set encoder position = 1 (1st pattern)
    // if (encoderButton == 0)
    // {
    //     if (randomMode == 1)
    //     {
    //         for (uint16_t i = 0; i < PWM_MaxPixels; i++)
    //         {
    //             strip.setPixelColor(i, strip.Color(currBrightness, 0, 0)); // Red
    //         }
    //         randomMode = 0;
    //     }
    //     else
    //     {
    //         for (uint16_t i = 0; i < PWM_MaxPixels; i++)
    //         {
    //             strip.setPixelColor(i, strip.Color(0, currBrightness, 0)); // Green
    //         }
    //         randomMode = 1;
    //     }
    //     strip.show();
    //     delay(250);
    // }

    if (encoderButton == 0) {
      encoderPos = 1;
    }
}
/***************************************************************************************
  Rotary Encoder Functions
***************************************************************************************/		

void PinA()
{
    cli(); // stop interrupts happening before we read pin values
    reading
        = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
    if (reading == B00001100 && aFlag)
    { // check that we have both pins at detent (HIGH) and that we are expecting detent on this
      // pin's rising edge
        encoderPos--; // decrement the encoder's position count
        bFlag = 0; // reset flags for the next turn
        aFlag = 0; // reset flags for the next turn
    }
    else if (reading == B00000100)
        bFlag = 1; // signal that we're expecting pinB to signal the transition to detent from free
                   // rotation
    sei(); // restart interrupts
}

void PinB()
{

    cli(); // stop interrupts happening before we read pin values
    reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's
                          // values
    if (reading == B00001100 && bFlag)
    { // check that we have both pins at detent (HIGH) and that we are expecting detent on this
      // pin's rising edge
        encoderPos++; // increment the encoder's position count
        bFlag = 0; // reset flags for the next turn
        aFlag = 0; // reset flags for the next turn
    }
    else if (reading == B00001000)
        aFlag = 1; // signal that we're expecting pinA to signal the transition to detent from free
                   // rotation
    sei(); // restart interrupts
}

void CheckEncoderKnobLimits() {
  if (encoderPos > upperLimit)
  {
      encoderPos = lowerLimit;
  }
  else if (encoderPos < lowerLimit)
  {
      encoderPos = upperLimit;
  }
}


/***************************************************************************************
  hsv2rgb
  Function: Calculate RGB values for colors represented
    in Hue, Saturation, and Value (brightness).
***************************************************************************************/	
void hsv2rgb(float H, float S, float V, int& R, int& G, int& B)
{
  int var_i;
  float var_1, var_2, var_3, var_h, var_r, var_g, var_b;
  if ( S == 0 )                       //HSV values = 0 ÷ 1
  {
    R = V * 255;
    G = V * 255;
    B = V * 255;
  }
  else
  {
    var_h = H * 6;
    if ( var_h == 6 ) var_h = 0;      //H must be < 1
    var_i = int( var_h ) ;            //Or ... var_i = floor( var_h )
    var_1 = V * ( 1 - S );
    var_2 = V * ( 1 - S * ( var_h - var_i ) );
    var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );

    if ( var_i == 0 ) {
    var_r = V     ;
    var_g = var_3 ;
    var_b = var_1 ;
    }
    else if ( var_i == 1 ) {
    var_r = var_2 ;
    var_g = V     ;
    var_b = var_1 ;
    }
    else if ( var_i == 2 ) {
    var_r = var_1 ;
    var_g = V     ;
    var_b = var_3 ;
    }
    else if ( var_i == 3 ) {
    var_r = var_1 ;
    var_g = var_2 ;
    var_b = V     ;
    }
    else if ( var_i == 4 ) {
    var_r = var_3 ;
    var_g = var_1 ;
    var_b = V     ;
    }
    else                   {
    var_r = V     ;
    var_g = var_1 ;
    var_b = var_2 ;
    }

    //RGB results = 0 ÷ 255 (Production)
    R = (var_r) * 255;
    G = (var_g) * 255;
    B = (var_b) * 255;
  }
}

