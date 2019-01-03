/***************************************************************************************
  WAVES FLOW
***************************************************************************************/
void RastaFlowSlow(){
  h += .001; //increment to make faster
  CatchHOverflow();
  float hTemp = h;

  for(uint16_t i=0; i<NUM_LEDS; i++) {
    hsv2rgb(hTemp, 1, float(brightness)/255, red, green, blue);
    strip.setPixelColor(i, strip.Color(red,blue/2,0,green/2));

    //slowly increment 'h' by small increments to make color flow
    hTemp += .025 * spacing; //decrease to space out the colors

  if (hTemp > 1){
    hTemp -= 1;
  }
  if (hTemp < 0){
    hTemp += 1;
  }
  }
  strip.show();
}

void WaterFlowSlow(){
  h += .0005; //increment to make faster
  CatchHOverflow();
  float hTemp = h;
  
  for(uint16_t i=0; i<NUM_LEDS; i++) {
    hsv2rgb(hTemp, 1, float(brightness)/255, red, green, blue);
    strip.setPixelColor(i, strip.Color(0,brightness,blue,green/3));

    //slowly increment 'h' by small increments to make color flow
    hTemp += .0045 * spacing; //decrease to space out the colors

  if (hTemp > 1){
    hTemp -= 1;
  }
  if (hTemp < 0){
    hTemp += 1;
  }
  } 
  strip.show();
}


void BlueGreen_Waves(){
  h += .0005 * spacing; //increment to make faster
  CatchHOverflow();
  float hTemp = h;

  for(uint16_t i=0; i<NUM_LEDS; i++) {
    hsv2rgb(hTemp, 1, float(brightness)/255, red, green, blue);
    strip.setPixelColor(i, strip.Color(0,brightness,blue,0));

    //slowly increment 'h' by small increments to make color flow
    hTemp += .020 * spacing; //decrease to space out the colors
  if (hTemp > 1){
    hTemp -= 1;
  }
  if (hTemp < 0){
    hTemp += 1;
  }
  }
  strip.show();
}


void RedWhite_Waves(){
  h += .0005 * spacing; //increment to make faster
  CatchHOverflow();
  float hTemp = h;
  
  for(uint16_t i=0; i<NUM_LEDS; i++) {
    hsv2rgb(hTemp, 1, float(brightness)/255, red, green, blue);
    strip.setPixelColor(i, strip.Color(brightness,0,0,green));

    //slowly increment 'h' by small increments to make color flow
    hTemp += .020 * spacing; //decrease to space out the colors
  if (hTemp > 1){
    hTemp -= 1;
  }
  if (hTemp < 0){
    hTemp += 1;
  }
  } 
  strip.show();
}

void BlueWhite_Waves(){
  h += .0005 * spacing; //increment to make faster
  CatchHOverflow();
  float hTemp = h;
  
  for(uint16_t i=0; i<NUM_LEDS; i++) {
    hsv2rgb(hTemp, 1, float(brightness)/255, red, green, blue);
    strip.setPixelColor(i, strip.Color(0,0,brightness,green));

    //slowly increment 'h' by small increments to make color flow
    hTemp += .020 * spacing; //decrease to space out the colors

  if (hTemp > 1){
    hTemp -= 1;
  }
  if (hTemp < 0){
    hTemp += 1;
  }
  } 
  strip.show();
}

/***************************************************************************************
  DUAL COLOR FLOWS
***************************************************************************************/

void DualColorFlowBounce(int _ledSpacing, float _speed, float _spacing, float _hHigh, float _hLow)
{
    h = GetH_BouncingWithLimits(_speed, _hHigh, _hLow);

    float hTemp = h;
    hTemp = h - _spacing; // space between colors
  if (hTemp > 1){
    hTemp -= 1;
  }
  if (hTemp < 0){
    hTemp += 1;
  }

    hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);
    hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

    for (uint16_t i = 0; i < NUM_LEDS; i = i + _ledSpacing)
    {
        strip.setPixelColor(i, strip.Color(red, green, blue));
        strip.setPixelColor(i + 1, strip.Color(red2, green2, blue2));
    }
    strip.show();
}
void LargeGroupColorFlowBounce(int _ledSpacing, float _speed, float _colorSpacing, float _hHigh, float _hLow)
{
    h = GetH_BouncingWithLimits(_speed, _hHigh, _hLow);

    float hTemp = h;
    hTemp = h - _colorSpacing; // space between colors
    if (hTemp > 1){
      hTemp -= 1;
    }
    if (hTemp < 0){
      hTemp += 1;
    }


    hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);
    hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

    for (uint16_t i = 0; i < NUM_LEDS; i = i + _ledSpacing)
    {
        strip.setPixelColor(i, strip.Color(red, green, blue));
        strip.setPixelColor(i + 1, strip.Color(red, green, blue));
        strip.setPixelColor(i + 2, strip.Color(red, green, blue));
        strip.setPixelColor(i + 3, strip.Color(red, green, blue));
        strip.setPixelColor(i + 4, strip.Color(red, green, blue));
        strip.setPixelColor(i + 5, strip.Color(red, green, blue));

        strip.setPixelColor(i + 6, strip.Color(red2, green2, blue2));
        strip.setPixelColor(i + 7, strip.Color(red2, green2, blue2));
        strip.setPixelColor(i + 8, strip.Color(red2, green2, blue2));
        strip.setPixelColor(i + 9, strip.Color(red2, green2, blue2));
        strip.setPixelColor(i + 10, strip.Color(red2, green2, blue2));
        strip.setPixelColor(i + 11, strip.Color(red2, green2, blue2));
    }
    strip.show();
}
/***************************************************************************************
  RAINBOW FLOW
***************************************************************************************/

void RainbowFlowSlow(float _speed, float _rainbowSpacing) {
  h = GetH_BouncingWithLimits(_speed, .97, .03);

  float hTemp = h;

  for(uint16_t i=0; i<NUM_LEDS; i++) {
    hsv2rgb(hTemp, 1, float(brightness)/255, red, green, blue);
    strip.setPixelColor(i, strip.Color(red,green,blue,0));

    //slowly increment 'h' by small increments to make color flow
    hTemp += _rainbowSpacing * spacing; //decrease to space out the colors

  if (hTemp > 1){
    hTemp -= 1;
  }
  if (hTemp < 0){
    hTemp += 1;
  }
  }
  strip.show();
}
void RainbowFlowSlow(float _speed, float _rainbowSpacing, float _hHigh, float _hLow) {
  h = GetH_BouncingWithLimits(_speed, _hHigh, _hLow);

  float hTemp = h;

  for(uint16_t i=0; i<NUM_LEDS; i++) {
    hsv2rgb(hTemp, 1, float(brightness)/255, red, green, blue);
    strip.setPixelColor(i, strip.Color(red,green,blue,0));

    //slowly increment 'h' by small increments to make color flow
    hTemp += _rainbowSpacing * spacing; //decrease to space out the colors

  if (hTemp > 1){
    hTemp -= 1;
  }
  if (hTemp < 0){
    hTemp += 1;
  }
  }
  strip.show();
}


/***************************************************************************************
  SINGLE COLORS
***************************************************************************************/

void warm_white()
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(brightness,0,0,brightness) );
  }
}

void warmer_white()
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(brightness,brightness/4,0,brightness/2) );
  }
}

void amber()
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(brightness,brightness/4,0,brightness/7) );
  }
}

void amber2()
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(brightness,brightness/4,0,0) );
    //strip.setPixelColor(i+1, strip.Color(255,0,0,0) );
  }
}

void all_red()
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(brightness, 0, 0, 0) );
  }
}
void all_green()
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(0, brightness, 0, 0) );
  }
}

void all_blue()
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(0, 0, brightness, 0) );
  }
}
void all_white()
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(0, 0, 0, brightness) );
  }
}

