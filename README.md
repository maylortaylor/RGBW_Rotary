# RGBW_Rotary LED Arudino project box

This is a patent-pending design for a LED light box made using WS2811 LED lights, an Arudino Nano, a potentiometer (brightness), and encoder knob (select pattern).

# Helpful things

-    make sure to setup your **Adafruit_NeoPixel** function how you want it.
     -    Number of LEDs on the strip
     -    Arduino Pin number (most are valid)
     -    pixel type flags
          -    NEO_GRBW == green, red, blue, white
          -    NEO_RGBW == red, green, blue, white
          -    This setting is used when using **strip.setPixelColor()**
-    if **NEO_GRBW** is used, then using **strip.setPixelColor()** will have the following parameters:
     -    pixel index
     -    green color
     -    red color
     -    blue color
     -    white color
-    if **NEO_RGBW** is used, then using **strip.setPixelColor()** will have the following parameters:
     -    pixel index
     -    red color
     -    green color
     -    blue color
     -    white color

# Files

## RGBW_Rotary

Main file. **Lots of variables at the top of the file.**
The main section of this file is the **CallColorFunction()**. This is a switch case of all of the **encoderPos** possibilities. Each **case** is a separate color pattern.

## Functions

A "catch-all" file for any necessary functions that are used throughout the project.

**TestCode** function is an important one. This function is called in the **RGBW_Rotary** file just before the **CallColorFunction()**. It will print out helpful information using the **Arduino Software** (**Tools > Serial Monitor**).

## Modes

This is where all of the color functions are stored. Add functions here to create new color functions. Once you create a color function, you will need to update the necessary variables (**upperLimit**). You will then need to add a **case** to the main switch case in the **CallColorFunction()**.

# Uploading new version

1. Check to make sure correct board is selected.
   **Tools > Board: Arudino Pro or Pro Mini**.
2. Make sure correct **COM** port is selected.
   **Tools > Port**.
3. Make sure correct **processor** is selected.
   **Tools > Processor > ATmega328p**.
