// Configuration
// =============

// 0: test: 16x16 WS2812 matrix
// 1: final 3*5*(3-pix) + 2*5*(1-pix) WS2811
// 2: Schmalhans: 1*5*(3-pix) + 3*1-narrowpix + 1*5*(3-pix)
#define PIXELARRANGEMENT 2

#if PIXELARRANGEMENT==1

// real hardware

// Number of LEDs around the tube. One too much looks better (italic text look)
// than one to few (backwards leaning text look)
// Higher number = diameter of the torch gets larger
const uint16_t ledsPerLevel = 5;

// Number of "windings" of the LED strip around (or within) the tube
// Higher number = torch gets taller
const uint16_t levels = 5;

const uint16_t ledsPerPixel = 3; // triple LEDs per pixel
#define SINGLEPIXEL_FROM_INDEX 15 // after index 15, fall back to single LED per pixel
#define SINGLEPIXEL_TO_INDEX 25 // after index 15, fall back to single LED per pixel


// set to true if you wound the torch clockwise (as seen from top). Note that
// this reverses the entire animation (in contrast to mirrorText, which only
// mirrors text).
const bool reversedX = false;
// set to true if every other row in the LED matrix is ordered backwards.
// This mode is useful for WS2812 modules which have e.g. 16x16 LEDs on one
// flexible PCB. On these modules, the data line starts in the lower left
// corner, goes right for row 0, then left in row 1, right in row 2 etc.
const bool alternatingX = true;

const bool swapXY = true;

const bool reversedY = false;

// Set this to the LED type in use.
// - ws2811_brg is WS2811 driver chip wired to LEDs in B,R,G order
// - ws2812 is WS2812 LED chip in standard order for this chip: G,R,B
#define LED_TYPE p44_ws2812::ws2811_brg

#elif PIXELARRANGEMENT==0

// test hardware

// Number of LEDs around the tube. One too much looks better (italic text look)
// than one to few (backwards leaning text look)
// Higher number = diameter of the torch gets larger
const uint16_t ledsPerLevel = 16;

// Number of "windings" of the LED strip around (or within) the tube
// Higher number = torch gets taller
const uint16_t levels = 16;

const uint16_t ledsPerPixel = 1; // double LEDs per pixel

// set to true if you wound the torch clockwise (as seen from top). Note that
// this reverses the entire animation (in contrast to mirrorText, which only
// mirrors text).
const bool reversedX = false;
// set to true if every other row in the LED matrix is ordered backwards.
// This mode is useful for WS2812 modules which have e.g. 16x16 LEDs on one
// flexible PCB. On these modules, the data line starts in the lower left
// corner, goes right for row 0, then left in row 1, right in row 2 etc.
const bool alternatingX = true;

const bool swapXY = false;

const bool reversedY = false;

// Set this to the LED type in use.
// - ws2811_brg is WS2811 driver chip wired to LEDs in B,R,G order
// - ws2812 is WS2812 LED chip in standard order for this chip: G,R,B
#define LED_TYPE p44_ws2812::ws2812


#elif PIXELARRANGEMENT==2

// 3 of 5 verticals, use single pixels

// Number of LEDs around the tube. One too much looks better (italic text look)
// than one to few (backwards leaning text look)
// Higher number = diameter of the torch gets larger
const uint16_t ledsPerLevel = 5;

// Number of "windings" of the LED strip around (or within) the tube
// Higher number = torch gets taller
const uint16_t levels = 5;

const uint16_t ledsPerPixel = 3; // triple LEDs per pixel
#define SINGLEPIXEL_FROM_INDEX 5 // after index 15, fall back to single LED per pixel
#define SINGLEPIXEL_TO_INDEX 19 // after index 15, fall back to single LED per pixel
#define SINGLEPIXEL_HORIZONTAL 3 // 3 consecutive LEDs represent 3 pixels horizontally


// set to true if you wound the torch clockwise (as seen from top). Note that
// this reverses the entire animation (in contrast to mirrorText, which only
// mirrors text).
const bool reversedX = false;
// set to true if every other row in the LED matrix is ordered backwards.
// This mode is useful for WS2812 modules which have e.g. 16x16 LEDs on one
// flexible PCB. On these modules, the data line starts in the lower left
// corner, goes right for row 0, then left in row 1, right in row 2 etc.
const bool alternatingX = true;

const bool swapXY = true;

const bool reversedY = false;

// Set this to the LED type in use.
// - ws2811_brg is WS2811 driver chip wired to LEDs in B,R,G order
// - ws2812 is WS2812 LED chip in standard order for this chip: G,R,B
#define LED_TYPE p44_ws2812::ws2811_brg


#else
  #error "unknown PIXELARRANGEMENT"
#endif



// Set this to true if you wound the LED strip clockwise, starting at the bottom of the
// tube, when looking onto the tube from the top. The default winding direction
// for versions of MessageTorch which did not have this setting was 0, which
// means LED strip was usually wound counter clock wise from bottom to top.
// Note: this setting only reverses the direction of text rendering - the torch
//   animation itself is not affected
const bool mirrorText = false;



/*
 * Spark Core library to control WS2812 based RGB LED devices
 * using SPI to create bitstream.
 * Future plan is to use DMA to feed the SPI, so WS2812 bitstream
 * can be produced without CPU load and without blocking IRQs
 *
 * (c) 2014 by luz@plan44.ch (GPG: 1CC60B3A)
 * Licensed as open source under the terms of the MIT License
 * (see LICENSE.TXT)
 */


// Declaration (would go to .h file once library is separated)
// ===========================================================

class p44_ws2812 {

public:
  typedef enum {
    ws2811_brg,
    ws2812
  } LedType;

private:
  typedef struct {
    unsigned int red:5;
    unsigned int green:5;
    unsigned int blue:5;
  } __attribute((packed)) RGBPixel;

  LedType ledType; // the LED type
  uint16_t numLeds; // number of LEDs
  uint16_t ledsPerPixel; // number of LEDs per pixel
  uint16_t numPixels; // number of pixels
  RGBPixel *pixelBufferP; // the pixel buffer
  uint16_t pixelsPerRow; // number of pixels per row
  uint16_t numRows; // number of rows
  bool xReversed; // even (0,2,4...) rows go backwards, or all if not alternating
  bool yReversed; // Y reversed
  bool alternating; // direction changes after every row
  bool swapXY; // swap X and Y

public:

  /// create driver for a WS2812 LED chain
  /// @param aLedType type of LEDs
  /// @param aNumLeds number of physical LEDs in the chain (not necessarily pixels, when aLedsPerPixel>1)
  /// @param aPixelsPerRow number of consecutive LEDs in the WS2812 chain that build a row (usually x direction, y if swapXY was set)
  /// @param aXReversed X direction is reversed
  /// @param aAlternating X direction is reversed in first row, normal in second, reversed in third etc..
  /// @param aSwapXY X and Y reversed (for up/down wiring)
  /// @param aYReversed Y direction is reversed
  /// @param aLedsPerPixel number of consecutive LEDS to be treated as a single pixel
  p44_ws2812(LedType aLedType, uint16_t aNumLeds, uint16_t aPixelsPerRow=0, bool aXReversed=false, bool aAlternating=false, bool aSwapXY=false, bool aYReversed=false, uint16_t aLedsPerPixel=1);

  /// destructor
  ~p44_ws2812();

  /// begin using the driver
  void begin();

  /// transfer RGB values to LED chain
  /// @note this must be called to update the actual LEDs after modifying RGB values
  /// with setColor() and/or setColorDimmed()
  void show();

  /// set color of one LED
  /// @param aRed intensity of red component, 0..255
  /// @param aGreen intensity of green component, 0..255
  /// @param aBlue intensity of blue component, 0..255
  void setColorXY(uint16_t aX, uint16_t aY, byte aRed, byte aGreen, byte aBlue);
  void setColor(uint16_t aLedNumber, byte aRed, byte aGreen, byte aBlue);

  /// set color of one LED, scaled by a visible brightness (non-linear) factor
  /// @param aRed intensity of red component, 0..255
  /// @param aGreen intensity of green component, 0..255
  /// @param aBlue intensity of blue component, 0..255
  /// @param aBrightness brightness, will be converted non-linear to PWM duty cycle for uniform brightness scale, 0..255
  void setColorDimmedXY(uint16_t aX, uint16_t aY, byte aRed, byte aGreen, byte aBlue, byte aBrightness);
  void setColorDimmed(uint16_t aLedNumber, byte aRed, byte aGreen, byte aBlue, byte aBrightness);

  /// get current color of LED
  /// @param aRed set to intensity of red component, 0..255
  /// @param aGreen set to intensity of green component, 0..255
  /// @param aBlue set to intensity of blue component, 0..255
  /// @note for LEDs set with setColorDimmed(), this returns the scaled down RGB values,
  ///   not the original r,g,b parameters. Note also that internal brightness resolution is 5 bits only.
  void getColorXY(uint16_t aX, uint16_t aY, byte &aRed, byte &aGreen, byte &aBlue);
  void getColor(uint16_t aLedNumber, byte &aRed, byte &aGreen, byte &aBlue);

  /// @return number of pixels
  int getNumPixels();
  /// @return number of Pixels in X direction
  uint16_t getSizeX();
  /// @return number of Pixels in Y direction
  uint16_t getSizeY();

private:

  uint16_t ledIndexFromXY(uint16_t aX, uint16_t aY);


};



// Implementation (would go to .cpp file once library is separated)
// ================================================================

static const uint8_t pwmTable[32] = {0, 1, 1, 2, 3, 4, 6, 7, 9, 10, 13, 15, 18, 21, 24, 28, 33, 38, 44, 50, 58, 67, 77, 88, 101, 115, 132, 150, 172, 196, 224, 255};

p44_ws2812::p44_ws2812(LedType aLedType, uint16_t aNumLeds, uint16_t aPixelsPerRow, bool aXReversed, bool aAlternating, bool aSwapXY, bool aYReversed, uint16_t aLedsPerPixel)
{
  numLeds = aNumLeds; // raw number of LEDs
  ledsPerPixel = aLedsPerPixel;
  if (ledsPerPixel<1) ledsPerPixel=1;
  numPixels = numLeds/ledsPerPixel;
  ledType = aLedType;
  if (aPixelsPerRow==0) {
    pixelsPerRow = numPixels; // single row
    numRows = 1;
  }
  else {
    pixelsPerRow = aPixelsPerRow; // set row size
    numRows = (numPixels-1)/pixelsPerRow+1; // calculate number of (full or partial) rows
  }
  xReversed = aXReversed;
  alternating = aAlternating;
  swapXY = aSwapXY;
  yReversed = aYReversed;
  // allocate the buffer
  if((pixelBufferP = new RGBPixel[numPixels])!=NULL) {
    memset(pixelBufferP, 0, sizeof(RGBPixel)*numPixels); // all LEDs off
  }
}

p44_ws2812::~p44_ws2812()
{
  // free the buffer
  if (pixelBufferP) delete pixelBufferP;
}


int p44_ws2812::getNumPixels()
{
  return numPixels;
}


uint16_t p44_ws2812::getSizeX()
{
  return swapXY ? numRows : pixelsPerRow;
}


uint16_t p44_ws2812::getSizeY()
{
  return swapXY ? pixelsPerRow : numRows;
}




void p44_ws2812::begin()
{
  // begin using the driver
  SPI.begin();
  switch (ledType) {
    case ws2811_brg:
      SPI.setClockDivider(SPI_CLOCK_DIV16); // WS2811: System clock is 72MHz, we need 4.5MHz for SPI
      break;
    case ws2812:
      SPI.setClockDivider(SPI_CLOCK_DIV8); // WS2812: System clock is 72MHz, we need 9MHz for SPI
      break;
  }
  SPI.setBitOrder(MSBFIRST); // MSB first for easier scope reading :-)
  SPI.transfer(0); // make sure SPI line starts low (Note: SPI line remains at level of last sent bit, fortunately)
}

void p44_ws2812::show()
{
  // Note: on the spark core, system IRQs might happen which exceed 50uS
  // causing WS2812 chips to reset in midst of data stream.
  // Thus, until we can send via DMA, we need to disable IRQs while sending
  __disable_irq();
  switch(ledType) {
    case ws2811_brg: {
      // transfer RGB values to LED chain
      for (uint16_t i=0; i<numPixels; i++) {
        byte b;
        byte lbp = ledsPerPixel;
        byte o = i;
        #ifdef SINGLEPIXEL_FROM_INDEX
        if ((i>=SINGLEPIXEL_FROM_INDEX) && (i<=SINGLEPIXEL_TO_INDEX)) {
          lbp = 1;
          #if SINGLEPIXEL_HORIZONTAL>1
          int sidx = i-SINGLEPIXEL_FROM_INDEX;
          int sx = sidx % SINGLEPIXEL_HORIZONTAL;
          int sy = sidx / SINGLEPIXEL_HORIZONTAL;
          o = ((SINGLEPIXEL_HORIZONTAL-1-sx)*ledsPerLevel) + (sx&1 ? ledsPerLevel-1-sy : sy) + SINGLEPIXEL_FROM_INDEX;
          #endif
        }
        #endif
        RGBPixel *pixP = &(pixelBufferP[o]);
        for (uint16_t r=0; r<lbp; r++) {
          // Order of PWM data for WS2811 LEDs usually is BRG
          // - blue
          b = pwmTable[pixP->blue];
          for (byte j=0; j<8; j++) {
            SPI.transfer(b & 0x80 ? 0x7C : 0x40);
            b = b << 1;
          }
          // - red
          b = pwmTable[pixP->red];
          for (byte j=0; j<8; j++) {
            SPI.transfer(b & 0x80 ? 0x7C : 0x40);
            b = b << 1;
          }
          // - green
          b = pwmTable[pixP->green];
          for (byte j=0; j<8; j++) {
            SPI.transfer(b & 0x80 ? 0x7C : 0x40);
            b = b << 1;
          }
        }
      }
    }
    case ws2812: {
      // transfer RGB values to LED chain
      for (uint16_t i=0; i<numPixels; i++) {
        RGBPixel *pixP = &(pixelBufferP[i]);
        byte b;
        for (uint16_t r=0; r<ledsPerPixel; r++) {
          // Order of PWM data for WS2812 LEDs is G-R-B
          // - green
          b = pwmTable[pixP->green];
          for (byte j=0; j<8; j++) {
            SPI.transfer(b & 0x80 ? 0x7E : 0x70);
            b = b << 1;
          }
          // - red
          b = pwmTable[pixP->red];
          for (byte j=0; j<8; j++) {
            SPI.transfer(b & 0x80 ? 0x7E : 0x70);
            b = b << 1;
          }
          // - blue
          b = pwmTable[pixP->blue];
          for (byte j=0; j<8; j++) {
            SPI.transfer(b & 0x80 ? 0x7E : 0x70);
            b = b << 1;
          }
        }
      }
    }
  } // switch
  __enable_irq();
}


uint16_t p44_ws2812::ledIndexFromXY(uint16_t aX, uint16_t aY)
{
  if (swapXY) { uint16_t tmp = aY; aY = aX; aX = tmp; }
  if (yReversed) { aY = numRows-1-aY; }
  uint16_t ledindex = aY*pixelsPerRow;
  bool reversed = xReversed;
  if (alternating) {
    if (aY & 0x1) reversed = !reversed;
  }
  if (reversed) {
    ledindex += (pixelsPerRow-1-aX);
  }
  else {
    ledindex += aX;
  }
  return ledindex;
}


void p44_ws2812::setColorXY(uint16_t aX, uint16_t aY, byte aRed, byte aGreen, byte aBlue)
{
  uint16_t ledindex = ledIndexFromXY(aX,aY);
  if (ledindex>=numPixels) return;
  RGBPixel *pixP = &(pixelBufferP[ledindex]);
  // linear brightness is stored with 5bit precision only
  pixP->red = aRed>>3;
  pixP->green = aGreen>>3;
  pixP->blue = aBlue>>3;
}


void p44_ws2812::setColor(uint16_t aLedNumber, byte aRed, byte aGreen, byte aBlue)
{
  int y = aLedNumber / getSizeX();
  int x = aLedNumber % getSizeX();
  setColorXY(x, y, aRed, aGreen, aBlue);
}


void p44_ws2812::setColorDimmedXY(uint16_t aX, uint16_t aY, byte aRed, byte aGreen, byte aBlue, byte aBrightness)
{
  setColorXY(aX, aY, (aRed*aBrightness)>>8, (aGreen*aBrightness)>>8, (aBlue*aBrightness)>>8);
}


void p44_ws2812::setColorDimmed(uint16_t aLedNumber, byte aRed, byte aGreen, byte aBlue, byte aBrightness)
{
  int y = aLedNumber / getSizeX();
  int x = aLedNumber % getSizeX();
  setColorDimmedXY(x, y, aRed, aGreen, aBlue, aBrightness);
}


void p44_ws2812::getColor(uint16_t aLedNumber, byte &aRed, byte &aGreen, byte &aBlue)
{
  int y = aLedNumber / getSizeX();
  int x = aLedNumber % getSizeX();
  getColorXY(x, y, aRed, aGreen, aBlue);
}


void p44_ws2812::getColorXY(uint16_t aX, uint16_t aY, byte &aRed, byte &aGreen, byte &aBlue)
{
  uint16_t ledindex = ledIndexFromXY(aX,aY);
  if (ledindex>=numPixels) return;
  RGBPixel *pixP = &(pixelBufferP[ledindex]);
  // linear brightness is stored with 5bit precision only
  aRed = pixP->red<<3;
  aGreen = pixP->green<<3;
  aBlue = pixP->blue<<3;
}



// Utilities
// =========


uint16_t random(uint16_t aMinOrMax, uint16_t aMax = 0)
{
  if (aMax==0) {
    aMax = aMinOrMax;
    aMinOrMax = 0;
  }
  uint32_t r = aMinOrMax;
  aMax = aMax - aMinOrMax + 1;
  r += rand() % aMax;
  return r;
}


inline void reduce(byte &aByte, byte aAmount, byte aMin = 0)
{
  int r = aByte-aAmount;
  if (r<aMin)
    aByte = aMin;
  else
    aByte = (byte)r;
}


inline void increase(byte &aByte, byte aAmount, byte aMax = 255)
{
  int r = aByte+aAmount;
  if (r>aMax)
    aByte = aMax;
  else
    aByte = (byte)r;
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
void wheel(byte WheelPos, byte &red, byte &green, byte &blue) {
  if(WheelPos < 85) {
    red = WheelPos * 3;
    green = 255 - WheelPos * 3;
    blue = 0;
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    red = 255 - WheelPos * 3;
    green = 0;
    blue = WheelPos * 3;
  } else {
    WheelPos -= 170;
    red = 0;
    green = WheelPos * 3;
    blue = 255 - WheelPos * 3;
  }
}


int hexToInt(char aHex)
{
  if (aHex<'0') return 0;
  aHex -= '0';
  if (aHex>9) aHex -= 7;
  if (aHex>15) return 0;
  return aHex;
}



#define CHAR_LAYER 1

#if CHAR_LAYER

// Super simple 5x5 font

const int numGlyphs = 96; // 96 ASCII 0x20..0x7F
const int glyphHeight = 5;
const int glyphWidth = 5;


uint8_t font5x5Bytes[80*6] = {
  0x00, 0x00, 0x00, 0x00, 0x00, //   0x20 (0)
  0x00, 0x00, 0xb8, 0x00, 0x00, // ! 0x21 (1)
  0x00, 0x08, 0x00, 0x08, 0x00, // " 0x22 (2)
  0x50, 0xf8, 0x50, 0xf8, 0x50, // # 0x23 (3)
  0xb8, 0xa8, 0xf8, 0xa8, 0xe8, // $ 0x24 (0)
  0x88, 0x40, 0x20, 0x10, 0x88, // % 0x25 (1)
  0x50, 0xa8, 0xa8, 0x40, 0xa0, // & 0x26 (2)
  0x00, 0x00, 0x08, 0x00, 0x00, // ' 0x27 (7)
  0x00, 0x70, 0x88, 0x00, 0x00, // ( 0x28 (8)
  0x00, 0x00, 0x88, 0x70, 0x00, // ) 0x29 (9)
  0x20, 0x20, 0xf8, 0x20, 0x20, // * 0x2A (10)
  0x48, 0x20, 0xf8, 0x20, 0x48, // + 0x2B (11)
  0x00, 0x00, 0xC0, 0x00, 0x00, // , 0x2C (12)
  0x20, 0x20, 0x20, 0x20, 0x20, // - 0x2D (13)
  0x00, 0x00, 0x80, 0x00, 0x00, // . 0x2E (14)
  0x00, 0xc0, 0x20, 0x18, 0x00, // / 0x2F (15)

  0xf8, 0xc8, 0xa8, 0x98, 0xf8, // 0 0x30 (0)
  0x00, 0x90, 0xf8, 0x80, 0x00, // 1 0x31 (1)
  0xc8, 0xa8, 0xa8, 0xa8, 0x90, // 2 0x32 (2)
  0x88, 0xa8, 0xa8, 0xa8, 0xd8, // 3 0x33 (3)
  0x78, 0x40, 0xe0, 0x40, 0x40, // 4 0x34 (4)
  0xb8, 0xa8, 0xa8, 0xa8, 0x48, // 5 0x35 (5)
  0xf8, 0xa8, 0xa8, 0xa8, 0xe8, // 6 0x36 (6)
  0x08, 0x08, 0xc8, 0x28, 0x18, // 7 0x37 (7)
  0xf8, 0xa8, 0xa8, 0xa8, 0xf8, // 8 0x38 (8)
  0xb8, 0xa8, 0xa8, 0xa8, 0xf8, // 9 0x39 (9)
  0x00, 0x00, 0x88, 0x00, 0x00, // : 0x3A (10)
  0x00, 0x00, 0xC8, 0x00, 0x00, // : 0x3B (11)
  0x00, 0x20, 0x50, 0x88, 0x00, // < 0x3C (12)
  0x50, 0x50, 0x50, 0x50, 0x50, // = 0x3D (13)
  0x00, 0x88, 0x50, 0x20, 0x00, // > 0x3E (14)
  0x10, 0x08, 0xa8, 0x10, 0x00, // ? 0x3F (15)

  0xf8, 0x88, 0xa8, 0xa8, 0xb8, // @ 0x40 (0)
  0xf8, 0x48, 0x48, 0x48, 0xf8, // A 0x41 (1)
  0xf8, 0xa8, 0xa8, 0xa8, 0xd8, // B 0x42 (2)
  0xf8, 0x88, 0x88, 0x88, 0x88, // C 0x43 (3)
  0xf8, 0x88, 0x88, 0x88, 0x70, // D 0x44 (4)
  0xf8, 0xa8, 0xa8, 0xa8, 0x88, // E 0x45 (5)
  0xf8, 0x28, 0x28, 0x28, 0x08, // F 0x46 (6)
  0xf8, 0x88, 0x88, 0xa8, 0xe8, // G 0x47 (7)
  0xf8, 0x20, 0x20, 0x20, 0xf8, // H 0x48 (8)
  0x88, 0x88, 0xf8, 0x88, 0x88, // I 0x49 (9)
  0xc0, 0x80, 0x80, 0x88, 0xf8, // J 0x4A (10)
  0xf8, 0x20, 0x20, 0x50, 0x88, // K 0x4B (11)
  0xf8, 0x80, 0x80, 0x80, 0x80, // L 0x4C (12)
  0xf8, 0x10, 0x20, 0x10, 0xf8, // M 0x4D (13)
  0xf8, 0x10, 0x20, 0x40, 0xf8, // N 0x4E (14)
  0x70, 0x88, 0x88, 0x88, 0x70, // O 0x4F (15)

  0xf8, 0x28, 0x28, 0x28, 0x10, // P 0x50 (0)
  0x78, 0x48, 0xc8, 0x48, 0x78, // Q 0x51 (1)
  0xf8, 0x28, 0x28, 0x28, 0xd0, // R 0x52 (2)
  0xb8, 0xa8, 0xa8, 0xa8, 0xe8, // S 0x53 (3)
  0x08, 0x08, 0xf8, 0x08, 0x08, // T 0x54 (4)
  0xf8, 0x80, 0x80, 0x80, 0xf8, // U 0x55 (5)
  0x18, 0x60, 0x80, 0x60, 0x18, // V 0x56 (6)
  0x78, 0x80, 0x60, 0x80, 0x78, // W 0x57 (7)
  0x88, 0x50, 0x20, 0x50, 0x88, // X 0x58 (8)
  0x18, 0x20, 0xc0, 0x20, 0x18, // Y 0x59 (9)
  0x88, 0xc8, 0xa8, 0x98, 0x88, // Z 0x5A (10)
  0x00, 0xf8, 0x88, 0x00, 0x00, // [ 0x5B (11)
  0x00, 0x18, 0x20, 0xc0, 0x00, // \ 0x5C (12)
  0x00, 0x00, 0x88, 0xf8, 0x00, // ] 0x5D (1)
  0x00, 0x10, 0x08, 0x10, 0x00, // ^ 0x5E (0)
  0x80, 0x80, 0x80, 0x80, 0x80, // _ 0x5F (1)

  0x00, 0x00, 0x08, 0x10, 0x00, // ` 0x60 (0)
  0xf8, 0x48, 0x48, 0x48, 0xf8, // A 0x41 (1)
  0xf8, 0xa8, 0xa8, 0xa8, 0xd8, // B 0x42 (2)
  0xf8, 0x88, 0x88, 0x88, 0x88, // C 0x43 (3)
  0xf8, 0x88, 0x88, 0x88, 0x70, // D 0x44 (4)
  0xf8, 0xa8, 0xa8, 0xa8, 0x88, // E 0x45 (5)
  0xf8, 0x28, 0x28, 0x28, 0x08, // F 0x46 (6)
  0xf8, 0x88, 0x88, 0xa8, 0xe8, // G 0x47 (7)
  0xf8, 0x20, 0x20, 0x20, 0xf8, // H 0x48 (8)
  0x88, 0x88, 0xf8, 0x88, 0x88, // I 0x49 (9)
  0xc0, 0x80, 0x80, 0x88, 0xf8, // J 0x4A (10)
  0xf8, 0x20, 0x20, 0x50, 0x88, // K 0x4B (11)
  0xf8, 0x80, 0x80, 0x80, 0x80, // L 0x4C (12)
  0xf8, 0x10, 0x20, 0x10, 0xf8, // M 0x4D (13)
  0xf8, 0x10, 0x20, 0x40, 0xf8, // N 0x4E (14)
  0x70, 0x88, 0x88, 0x88, 0x70, // O 0x4F (15)

  0xf8, 0x28, 0x28, 0x28, 0x10, // P 0x50 (0)
  0x78, 0x48, 0xc8, 0x48, 0x78, // Q 0x51 (1)
  0xf8, 0x28, 0x28, 0x28, 0xd0, // R 0x52 (2)
  0xb8, 0xa8, 0xa8, 0xa8, 0xe8, // S 0x53 (3)
  0x08, 0x08, 0xf8, 0x08, 0x08, // T 0x54 (4)
  0xf8, 0x80, 0x80, 0x80, 0xf8, // U 0x55 (5)
  0x18, 0x60, 0x80, 0x60, 0x18, // V 0x56 (6)
  0x78, 0x80, 0x60, 0x80, 0x78, // W 0x57 (7)
  0x88, 0x50, 0x20, 0x50, 0x88, // X 0x58 (8)
  0x18, 0x20, 0xc0, 0x20, 0x18, // Y 0x59 (9)
  0x88, 0xc8, 0xa8, 0x98, 0x88, // Z 0x5A (10)
  0x00, 0x20, 0xf8, 0x88, 0x00, // { 0x7B (0)
  0x00, 0x00, 0xF8, 0x00, 0x00, // | 0x7C (12)
  0x00, 0x88, 0xf8, 0x20, 0x00, // } 0x7D (13)
  0x00, 0x10, 0x08, 0x10, 0x08, // ~ 0x7E (14)
  0xF8, 0x88, 0x88, 0x88, 0xF8, // } 0x7F (15)

};

#else

// Simple 7 pixel height dot matrix font
// =====================================
// Note: the font is derived from a monospaced 7*5 pixel font, but has been adjusted a bit
//       to get rendered proportionally (variable character width, e.g. "!" has width 1, whereas "m" has 7)
//       In the fontGlyphs table below, every char has a number of pixel colums it consists of, and then the
//       actual column values encoded as a string.

typedef struct {
  uint8_t width;
  const char *cols;
} glyph_t;

const int numGlyphs = 102; // 96 ASCII 0x20..0x7F plus 6 ÄÖÜäöü
const int rowsPerGlyph = 7;
const int glyphSpacing = 2;

static const glyph_t fontGlyphs[numGlyphs] = {
  { 5, "\x00\x00\x00\x00\x00" },  //   0x20 (0)
  { 1, "\x5f" },                  // ! 0x21 (1)
  { 3, "\x03\x00\x03" },          // " 0x22 (2)
  { 5, "\x28\x7c\x28\x7c\x28" },  // # 0x23 (3)
  { 5, "\x24\x2a\x7f\x2a\x12" },  // $ 0x24 (4)
  { 5, "\x4c\x2c\x10\x68\x64" },  // % 0x25 (5)
  { 5, "\x30\x4e\x55\x22\x40" },  // & 0x26 (6)
  { 1, "\x01" },                  // ' 0x27 (7)
  { 3, "\x1c\x22\x41" },          // ( 0x28 (8)
  { 3, "\x41\x22\x1c" },          // ) 0x29 (9)
  { 5, "\x01\x03\x01\x03\x01" },  // * 0x2A (10)
  { 5, "\x08\x08\x3e\x08\x08" },  // + 0x2B (11)
  { 2, "\x50\x30" },              // , 0x2C (12)
  { 5, "\x08\x08\x08\x08\x08" },  // - 0x2D (13)
  { 2, "\x60\x60" },              // . 0x2E (14)
  { 5, "\x40\x20\x10\x08\x04" },  // / 0x2F (15)

  { 5, "\x3e\x51\x49\x45\x3e" },  // 0 0x30 (0)
  { 3, "\x42\x7f\x40" },          // 1 0x31 (1)
  { 5, "\x62\x51\x49\x49\x46" },  // 2 0x32 (2)
  { 5, "\x22\x41\x49\x49\x36" },  // 3 0x33 (3)
  { 5, "\x0c\x0a\x09\x7f\x08" },  // 4 0x34 (4)
  { 5, "\x4f\x49\x49\x49\x31" },  // 5 0x35 (5)
  { 5, "\x3e\x49\x49\x49\x32" },  // 6 0x36 (6)
  { 5, "\x03\x01\x71\x09\x07" },  // 7 0x37 (7)
  { 5, "\x36\x49\x49\x49\x36" },  // 8 0x38 (8)
  { 5, "\x26\x49\x49\x49\x3e" },  // 9 0x39 (9)
  { 2, "\x66\x66" },              // : 0x3A (10)
  { 2, "\x56\x36" },              // ; 0x3B (11)
  { 4, "\x08\x14\x22\x41" },      // < 0x3C (12)
  { 4, "\x24\x24\x24\x24" },      // = 0x3D (13)
  { 4, "\x41\x22\x14\x08" },      // > 0x3E (14)
  { 5, "\x02\x01\x59\x09\x06" },  // ? 0x3F (15)

  { 5, "\x3e\x41\x5d\x55\x5e" },  // @ 0x40 (0)
  { 5, "\x7c\x0a\x09\x0a\x7c" },  // A 0x41 (1)
  { 5, "\x7f\x49\x49\x49\x36" },  // B 0x42 (2)
  { 5, "\x3e\x41\x41\x41\x22" },  // C 0x43 (3)
  { 5, "\x7f\x41\x41\x22\x1c" },  // D 0x44 (4)
  { 5, "\x7f\x49\x49\x41\x41" },  // E 0x45 (5)
  { 5, "\x7f\x09\x09\x01\x01" },  // F 0x46 (6)
  { 5, "\x3e\x41\x49\x49\x7a" },  // G 0x47 (7)
  { 5, "\x7f\x08\x08\x08\x7f" },  // H 0x48 (8)
  { 3, "\x41\x7f\x41" },          // I 0x49 (9)
  { 5, "\x30\x40\x40\x40\x3f" },  // J 0x4A (10)
  { 5, "\x7f\x08\x0c\x12\x61" },  // K 0x4B (11)
  { 5, "\x7f\x40\x40\x40\x40" },  // L 0x4C (12)
  { 7, "\x7f\x02\x04\x0c\x04\x02\x7f" },  // M 0x4D (13)
  { 5, "\x7f\x02\x04\x08\x7f" },  // N 0x4E (14)
  { 5, "\x3e\x41\x41\x41\x3e" },  // O 0x4F (15)

  { 5, "\x7f\x09\x09\x09\x06" },  // P 0x50 (0)
  { 5, "\x3e\x41\x51\x61\x7e" },  // Q 0x51 (1)
  { 5, "\x7f\x09\x09\x09\x76" },  // R 0x52 (2)
  { 5, "\x26\x49\x49\x49\x32" },  // S 0x53 (3)
  { 5, "\x01\x01\x7f\x01\x01" },  // T 0x54 (4)
  { 5, "\x3f\x40\x40\x40\x3f" },  // U 0x55 (5)
  { 5, "\x1f\x20\x40\x20\x1f" },  // V 0x56 (6)
  { 5, "\x7f\x40\x38\x40\x7f" },  // W 0x57 (7)
  { 5, "\x63\x14\x08\x14\x63" },  // X 0x58 (8)
  { 5, "\x03\x04\x78\x04\x03" },  // Y 0x59 (9)
  { 5, "\x61\x51\x49\x45\x43" },  // Z 0x5A (10)
  { 3, "\x7f\x41\x41" },          // [ 0x5B (11)
  { 5, "\x04\x08\x10\x20\x40" },  // \ 0x5C (12)
  { 3, "\x41\x41\x7f" },          // ] 0x5D (13)
  { 4, "\x04\x02\x01\x02" },      // ^ 0x5E (14)
  { 5, "\x40\x40\x40\x40\x40" },  // _ 0x5F (15)

  { 2, "\x01\x02" },              // ` 0x60 (0)
  { 5, "\x20\x54\x54\x54\x78" },  // a 0x61 (1)
  { 5, "\x7f\x44\x44\x44\x38" },  // b 0x62 (2)
  { 5, "\x38\x44\x44\x44\x08" },  // c 0x63 (3)
  { 5, "\x38\x44\x44\x44\x7f" },  // d 0x64 (4)
  { 5, "\x38\x54\x54\x54\x18" },  // e 0x65 (5)
  { 5, "\x08\x7e\x09\x09\x02" },  // f 0x66 (6)
  { 5, "\x48\x54\x54\x54\x38" },  // g 0x67 (7)
  { 5, "\x7f\x08\x08\x08\x70" },  // h 0x68 (8)
  { 3, "\x48\x7a\x40" },          // i 0x69 (9)
  { 5, "\x20\x40\x40\x48\x3a" },  // j 0x6A (10)
  { 4, "\x7f\x10\x28\x44" },      // k 0x6B (11)
  { 3, "\x3f\x40\x40" },          // l 0x6C (12)
  { 7, "\x7c\x04\x04\x38\x04\x04\x78" },  // m 0x6D (13)
  { 5, "\x7c\x04\x04\x04\x78" },  // n 0x6E (14)
  { 5, "\x38\x44\x44\x44\x38" },  // o 0x6F (15)

  { 5, "\x7c\x14\x14\x14\x08" },  // p 0x70 (0)
  { 5, "\x08\x14\x14\x7c\x40" },  // q 0x71 (1)
  { 5, "\x7c\x04\x04\x04\x08" },  // r 0x72 (2)
  { 5, "\x48\x54\x54\x54\x24" },  // s 0x73 (3)
  { 5, "\x04\x04\x7f\x44\x44" },  // t 0x74 (4)
  { 5, "\x3c\x40\x40\x40\x7c" },  // u 0x75 (5)
  { 5, "\x1c\x20\x40\x20\x1c" },  // v 0x76 (6)
  { 7, "\x7c\x40\x40\x38\x40\x40\x7c" },  // w 0x77 (7)
  { 5, "\x44\x28\x10\x28\x44" },  // x 0x78 (8)
  { 5, "\x0c\x50\x50\x50\x3c" },  // y 0x79 (9)
  { 5, "\x44\x64\x54\x4c\x44" },  // z 0x7A (10)
  { 3, "\x08\x36\x41" },          // { 0x7B (11)
  { 1, "\x7f" },                  // | 0x7C (12)
  { 3, "\x41\x36\x08" },          // } 0x7D (13)
  { 4, "\x04\x02\x04\x08" },      // ~ 0x7E (14)
  { 5, "\x7F\x41\x41\x41\x7F" },  //   0x7F (15)

  { 5, "\x7D\x0a\x09\x0a\x7D" },  // Ä 0x41 (1)
  { 5, "\x3F\x41\x41\x41\x3F" },  // Ö 0x4F (15)
  { 5, "\x3D\x40\x40\x40\x3D" },  // Ü 0x55 (5)
  { 5, "\x20\x55\x54\x55\x78" },  // ä 0x61 (1)
  { 5, "\x38\x45\x44\x45\x38" },  // ö 0x6F (15)
  { 5, "\x3c\x41\x40\x41\x7c" },  // ü 0x75 (5)
};


#endif


// Main program
// ============

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGBColor;


// moved defining constants for number of LEDs to top of file

#ifndef NUM_LEDS
#define NUM_LEDS (ledsPerLevel*levels*ledsPerPixel) // standard formula
#endif
const uint16_t numLeds = NUM_LEDS; // total number of LEDs

p44_ws2812 leds(LED_TYPE, numLeds, ledsPerLevel, reversedX, alternatingX, swapXY, reversedY, ledsPerPixel); // create WS281x driver

// parameters

int cycle_wait = 20; // don't go too low on Electron, or cloud will get unreliable

typedef enum {
  mode_text,
  mode_testpixel,
  mode_colorwheel,
  numModes
};
byte mode = mode_text;

byte text_red = 0;
byte text_green = 255;
byte text_blue = 180;

byte bg_red = 0;
byte bg_green = 30;
byte bg_blue = 0;

int brightness = 255; // overall brightness
int fade_base = 42; // base brightness for cross-fading

// char params
int briHighlight = 255; // highlight intensity
int briNormal = 200; // normal intensity
int fadeIn = 0;  // fade in time to highlight
int highlight = 3; // highlight sustain time
int backnormal = 3; // fade down time to normal
int normal = 10; // normal sustain time
int fadeout = 5; // fade out to zero time
int pause = 2; // pause time

// text params
int cycles_per_px = 5;
int text_repeats = 15; // text displays until faded down to almost zero
int fade_per_repeat = 15; // how much to fade down per repeat
int text_base_line = 0;


// Cloud API
// =========

// this function automagically gets called upon a matching POST request
int handleParams(String command)
{
  //look for the matching argument "coffee" <-- max of 64 characters long
  int p = 0;
  while (p<(int)command.length()) {
    int i = command.indexOf(',',p);
    if (i<0) i = command.length();
    int j = command.indexOf('=',p);
    if (j<0) break;
    String key = command.substring(p,j);
    String value = command.substring(j+1,i);
    int val = value.toInt();
    // global params
    if (key=="wait")
      cycle_wait = val;
    else if (key=="mode")
      mode = val;
    else if (key=="brightness")
      brightness = val;
    else if (key=="fade_base")
      fade_base = val;
    // text color params
    else if (key=="text_red")
      text_red = val;
    else if (key=="text_green")
      text_green = val;
    else if (key=="text_blue")
      text_blue = val;
    // char params
    else if (key=="bri_highlight")
      briHighlight = val;
    else if (key=="bri_normal")
      briNormal = val;
    else if (key=="fade_in")
      fadeIn = val;
    else if (key=="highlight")
      highlight = val;
    else if (key=="back_normal")
      backnormal = val;
    else if (key=="normal")
      normal = val;
    else if (key=="fade_out")
      fadeout = val;
    else if (key=="pause")
      pause = val;
    // bg color params
    else if (key=="bg_red")
      bg_red = val;
    else if (key=="bg_green")
      bg_green = val;
    else if (key=="bg_blue")
      bg_blue = val;
    // text params
    else if (key=="cycles_per_px")
      cycles_per_px = val;
    else if (key=="text_repeats")
      text_repeats = val;
    else if (key=="text_base_line")
      text_base_line = val;
    else if (key=="fade_per_repeat")
      fade_per_repeat = val;
    p = i+1;
  }
  return 1;
}


#if CHAR_LAYER

// char layer
// ==========

String text;
int textIndex = 0;
enum {
  s_start,
  s_fadeIn,
  s_highlight,
  s_backnormal,
  s_normal,
  s_fadeout,
  s_pause
} rsta; // render state
char cchar = 0; // current char
int cbri16 = 0; // current brightness * 256
int briStep; // inc or dec per step
int stateSteps = 0; // remaining number of steps for current state
int repeatText = 0;


void resetTextRender()
{
  textIndex = 0;
  stateSteps = 0;
  cbri16 = 0;
  rsta = s_start;
}


void resetText()
{
  text = "";
  repeatText = 0;
  resetTextRender();
}



// this function automagically gets called upon a matching POST request
int newMessage(String aText)
{
  // URL decode
  String txt = "";
  int i = 0;
  char c;
  while (i<(int)aText.length()) {
    if (aText[i]=='%') {
      if ((int)aText.length()<=i+2) break; // end of text
      // get hex
      c = (hexToInt(aText[i+1])<<4) + hexToInt(aText[i+2]);
      i += 2;
    }
    // Ä = C3 84
    // Ö = C3 96
    // Ü = C3 9C
    // ä = C3 A4
    // ö = C3 B6
    // ü = C3 BC
    else if (aText[i]==0xC3) {
      if ((int)aText.length()<=i+1) break; // end of text
      switch (aText[i+1]) {
        case 0x84: c = 0x80; break; // Ä
        case 0x96: c = 0x81; break; // Ö
        case 0x9C: c = 0x82; break; // Ü
        case 0xA4: c = 0x83; break; // ä
        case 0xB6: c = 0x84; break; // ö
        case 0xBC: c = 0x85; break; // ü
        default: c = 0x7F; break; // unknown
      }
      i += 1;
    }
    else {
      c = aText[i];
    }
    // put to output string
    txt += String(c);
    i++;
  }
  // decode start-of-message commands
  if (txt.length()>0) {
    if (txt[0]=='+') {
      // append
      text += txt.substring(1);
    }
    else if (txt[0]=='=') {
      // replace
      text = txt.substring(1);
      resetTextRender();
    }
    else {
      // also replace
      text = txt;
      resetTextRender();
    }
  }
  return 1;
}


char nextChar()
{
  char c = 0; // none
  while (textIndex<text.length()) {
    c = text[textIndex];
    textIndex++;
    if (c!='\\') {
      // just show c
      break;
    }
    // is escape sequece
    c = 0;
    if (textIndex<text.length()) {
      char e = text[textIndex];
      textIndex++;
      if (e=='\\') {
        c = e;
        break;
      }
      else if (e=='(') {
        // repeat 3 times: \(3;
        // repeat forever: \(;
        int i = text.indexOf(';',textIndex);
        if (i>=0) {
          if (i>textIndex) {
            // repeat count
            repeatText = text.substring(textIndex,i-textIndex).toInt();
          }
          else {
            // forever
            repeatText = 9999; // forever
          }
          textIndex=i+1;
        }
      }
      else if (e==')') {
        // end repeat: \)
        if (repeatText>0) {
          // repeat
          if (repeatText<9999)
            repeatText--;
          textIndex = 0;
        }
        else {
          // done repeating
          text.remove(0,textIndex);
          textIndex = 0;
        }
      }
      else if (e=='#') {
        // color change: \#rrggbb;
        // color change: \#rgb;
        int i = text.indexOf(';',textIndex);
        int cc;
        if (i==textIndex+6) {
          cc = hexToInt(text[textIndex++]);
          text_red = (cc<<4) + hexToInt(text[textIndex++]);
          cc = hexToInt(text[textIndex++]);
          text_green = (cc<<4) + hexToInt(text[textIndex++]);
          cc = hexToInt(text[textIndex++]);
          text_blue = (cc<<4) + hexToInt(text[textIndex++]);
        }
        else if (i==textIndex+3) {
          cc = hexToInt(text[textIndex++]);
          text_red = (cc<<4) + cc;
          cc = hexToInt(text[textIndex++]);
          text_green = (cc<<4) + cc;
          cc = hexToInt(text[textIndex++]);
          text_blue = (cc<<4) + cc;
        }
        textIndex=i+1;
      }
      else if (e=='_') {
        // pause: \_20;
        int i = text.indexOf(';',textIndex);
        if (i>=0) {
          stateSteps = text.substring(textIndex,i-textIndex).toInt();
          // show a space
          textIndex=i+1;
          c = ' ';
          rsta = s_pause;
          break;
        }
        textIndex=i+1;
      }
    }
  }
  return c;
}



void textStep()
{
  if (stateSteps>0) {
    stateSteps--;
    cbri16 += briStep;
    return;
  }
  // end of this state, calc next
  switch (rsta) {
    case s_start: {
      cchar = nextChar();
      if (cchar) {
        rsta = s_fadeIn;
        cbri16 = 0;
        // fade to highlight
        stateSteps = fadeIn;
        briStep = (briHighlight*0x100) / (stateSteps+1);
      }
      break;
    }
    case s_fadeIn: {
      rsta = s_highlight;
      // stay
      stateSteps = highlight;
      cbri16 = briHighlight*0x100;
      briStep = 0;
      break;
    }
    case s_highlight: {
      rsta = s_backnormal;
      // fade to normal
      stateSteps = backnormal;
      briStep = ((briNormal-briHighlight)*0x100) / (stateSteps+1);
      break;
    }
    case s_backnormal: {
      rsta = s_normal;
      // stay
      stateSteps = normal;
      cbri16 = briNormal*0x100;
      briStep = 0;
      break;
    }
    case s_normal: {
      rsta = s_fadeout;
      // fade to zero
      stateSteps = fadeout;
      briStep = ((-briNormal)*0x100) / (stateSteps+1);
      break;
    }
    case s_fadeout: {
      rsta = s_pause;
      // stay
      cbri16 = 0;
      stateSteps = pause;
      briStep = 0;
      break;
    }
    case s_pause: {
      rsta = s_start;
      cbri16 = 0;
      break;
    }
  }
}



int glyphIndexForChar(const char aChar)
{
  if (aChar==0) return 0;
  int i = aChar-0x20;
  if (i<0 || i>=numGlyphs) i = 95; // ASCII 0x7F-0x20
  return i;
}


byte charBrightnessAt(int aX, int aY)
{
  if (aY>=glyphHeight || aX>=glyphWidth) return 0;
  char col = font5x5Bytes[glyphIndexForChar(cchar)*glyphWidth+aX];
  if (col & (0x80>>aY)) {
    return cbri16>>8;
  }
  return 0;
}


#else

// text layer
// ==========

// text layer, but only one strip around the tube (ledsPerLevel) with the height of the characters (rowsPerGlyph)
const int textPixels = ledsPerLevel*rowsPerGlyph;
byte textLayer[textPixels];
String text;

int textPixelOffset;
int textCycleCount;
int repeatCount;


// this function automagically gets called upon a matching POST request
int newMessage(String aText)
{
  // URL decode
  text = "";
  int i = 0;
  char c;
  while (i<(int)aText.length()) {
    if (aText[i]=='%') {
      if ((int)aText.length()<=i+2) break; // end of text
      // get hex
      c = (hexToInt(aText[i+1])<<4) + hexToInt(aText[i+2]);
      i += 2;
    }
    // Ä = C3 84
    // Ö = C3 96
    // Ü = C3 9C
    // ä = C3 A4
    // ö = C3 B6
    // ü = C3 BC
    else if (aText[i]==0xC3) {
      if ((int)aText.length()<=i+1) break; // end of text
      switch (aText[i+1]) {
        case 0x84: c = 0x80; break; // Ä
        case 0x96: c = 0x81; break; // Ö
        case 0x9C: c = 0x82; break; // Ü
        case 0xA4: c = 0x83; break; // ä
        case 0xB6: c = 0x84; break; // ö
        case 0xBC: c = 0x85; break; // ü
        default: c = 0x7F; break; // unknown
      }
      i += 1;
    }
    else {
      c = aText[i];
    }
    // put to output string
    text += String(c);
    i++;
  }
  // initiate display of new text
  textPixelOffset = -ledsPerLevel;
  textCycleCount = 0;
  repeatCount = 0;
  return 1;
}


void resetText()
{
  for(int i=0; i<textPixels; i++) {
    textLayer[i] = 0;
  }
}


void crossFade(byte aFader, byte aValue, byte &aOutputA, byte &aOutputB)
{
  byte baseBrightness = (aValue*fade_base)>>8;
  byte varBrightness = aValue-baseBrightness;
  byte fade = (varBrightness*aFader)>>8;
  aOutputB = baseBrightness+fade;
  aOutputA = baseBrightness+(varBrightness-fade);
}


int glyphIndexForChar(const char aChar)
{
  int i = aChar-0x20;
  if (i<0 || i>=numGlyphs) i = 95; // ASCII 0x7F-0x20
  return i;
}


void renderText()
{
  // fade between rows
  byte maxBright = 255-repeatCount*fade_per_repeat;
  byte thisBright, nextBright;
  crossFade(255*textCycleCount/cycles_per_px, maxBright, thisBright, nextBright);
  // generate vertical rows
  int activeCols = ledsPerLevel-2;
  // calculate text length in pixels
  int totalTextPixels = 0;
  int textLen = (int)text.length();
  for (int i=0; i<textLen; i++) {
    // sum up width of individual chars
    totalTextPixels += fontGlyphs[glyphIndexForChar(text[i])].width + glyphSpacing;
  }
  for (int x=0; x<ledsPerLevel; x++) {
    uint8_t column = 0;
    // determine font column
    if (x<activeCols) {
      int colPixelOffset = textPixelOffset + x;
      if (colPixelOffset>=0) {
        // visible column
        // - calculate character index
        int charIndex = 0;
        int glyphOffset = colPixelOffset;
        const glyph_t *glyphP = NULL;
        while (charIndex<textLen) {
          glyphP = &fontGlyphs[glyphIndexForChar(text[charIndex])];
          int cw = glyphP->width + glyphSpacing;
          if (glyphOffset<cw) break; // found char
          glyphOffset -= cw;
          charIndex++;
        }
        // now we have
        // - glyphP = the glyph,
        // - glyphOffset=column offset within that glyph (but might address a spacing column not stored in font table)
        if (charIndex<textLen) {
          // is a column of a visible char
          if (glyphOffset<glyphP->width) {
            // fetch glyph column
            column = glyphP->cols[glyphOffset];
          }
        }
      }
    }
    // now render columns
    for (int glyphRow=0; glyphRow<rowsPerGlyph; glyphRow++) {
      int i;
      int leftstep;
      if (mirrorText) {
        i = (glyphRow+1)*ledsPerLevel - 1 - x; // LED index, x-direction mirrored
        leftstep = 1;
      }
      else {
        i = glyphRow*ledsPerLevel + x; // LED index
        leftstep = -1;
      }
      if (glyphRow < rowsPerGlyph) {
        if (column & (0x40>>glyphRow)) {
          textLayer[i] = thisBright;
          // also adjust pixel left to this one
          if (x>0) {
            increase(textLayer[i+leftstep], nextBright, maxBright);
          }
          continue;
        }
      }
      textLayer[i] = 0; // no text
    }
  }
  // increment
  textCycleCount++;
  if (textCycleCount>=cycles_per_px) {
    textCycleCount = 0;
    textPixelOffset++;
    if (textPixelOffset>totalTextPixels) {
      // text shown, check for repeats
      repeatCount++;
      if (text_repeats!=0 && repeatCount>=text_repeats) {
        // done
        text = ""; // remove text
      }
      else {
        // show again
        textPixelOffset = -ledsPerLevel;
        textCycleCount = 0;
      }
    }
  }
}

#endif


// Main program
// ============

void setup()
{
  resetText();
  leds.begin();
  // remote control
  Particle.function("params", handleParams); // parameters
  Particle.function("message", newMessage); // text message display
}



byte cnt = 0;

void loop()
{
  if (mode==mode_testpixel) {
    // go through pixels one by one
    for (int i=0; i<leds.getNumPixels(); i++) {
      leds.setColor(i,i==cnt ? 200 : 0,0,0);
    }
    cnt++;
    if (cnt>=leds.getNumPixels()) cnt=0;
    // transmit colors to the leds
    leds.show();
    delay(cycle_wait*20); // ~400mS
  }
  else if (mode==mode_colorwheel) {
    // colorwheel
    byte r,g,b;
    for (int x=0; x<leds.getSizeX(); x++) {
      for (int y=0; y<leds.getSizeY(); y++) {
        wheel((cnt+y*30+x)&0xFF, r, g, b);
        leds.setColorDimmedXY(x, y, r, g, b, brightness);
      }
    }
    cnt++;
    // transmit colors to the leds
    leds.show();
    delay(cycle_wait);
  }
  else if (mode==mode_text) {
    #if CHAR_LAYER
    // render the char
    textStep();
    for (int x=0; x<leds.getSizeX(); x++) {
      for (int y=0; y<leds.getSizeY(); y++) {
        uint8_t b = charBrightnessAt(x,y);
        if (b>0) {
          leds.setColorDimmedXY(x, y, text_red, text_green, text_blue, (b*brightness)>>8);
        }
        else {
          leds.setColorDimmedXY(x, y, bg_red, bg_green, bg_blue, brightness);
        }
      }
    }
    #else
    // render the text
    renderText();
    int textStart = text_base_line*ledsPerLevel;
    int textEnd = textStart+rowsPerGlyph*ledsPerLevel;
    // just single color lamp + text display
    for (int i=0; i<leds.getNumPixels(); i++) {
      if (i>=textStart && i<textEnd && textLayer[i-textStart]>0) {
        leds.setColorDimmed(i, text_red, text_green, text_blue, (textLayer[i-textStart]*brightness)>>8);
      }
      else {
        leds.setColorDimmed(i, bg_red, bg_green, bg_blue, brightness);
      }
    }
    #endif
    // transmit colors to the leds
    leds.show();
    // wait
    delay(cycle_wait); // latch & reset needs 50 microseconds pause, at least.
  }
}




