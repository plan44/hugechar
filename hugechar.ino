// Configuration
// =============

// PIXELARRANGEMENT:
// 0: test: 16x16 WS2812 matrix
// 1: first Bracheninstallation, mixed verticals: 3*5*(3-pix) + 2*5*(1-pix) WS2811
// 2: final Bracheninstallation luz verticals
// 3: final Bracheninstallation serge verticals
// 4: Schmalhans: 1*5*(3-pix) + 3*1-narrowpix + 1*5*(3-pix)


#if PLATFORM_ID == 0 // Core
  #define PIXELARRANGEMENT 0
#elif PLATFORM_ID == 6 // Photon
  #define PIXELARRANGEMENT 0
#elif PLATFORM_ID == 10 // Electron
  #define PIXELARRANGEMENT 1
#else
  #error "*** PLATFORM_ID not supported by this firmware. PLATFORM should be Core, Photon, P1 or Electron ***"
#endif


#if PIXELARRANGEMENT==0

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

#elif PIXELARRANGEMENT==1

// real hardware, mixed verticals

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


#elif PIXELARRANGEMENT==2

// real hardware, luz's verticals

// Number of LEDs around the tube. One too much looks better (italic text look)
// than one to few (backwards leaning text look)
// Higher number = diameter of the torch gets larger
const uint16_t ledsPerLevel = 5;

// Number of "windings" of the LED strip around (or within) the tube
// Higher number = torch gets taller
const uint16_t levels = 5;

const uint16_t ledsPerPixel = 3; // triple LEDs per pixel

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


#elif PIXELARRANGEMENT==3

// real hardware, serge's verticals

// Number of LEDs around the tube. One too much looks better (italic text look)
// than one to few (backwards leaning text look)
// Higher number = diameter of the torch gets larger
const uint16_t ledsPerLevel = 5;

// Number of "windings" of the LED strip around (or within) the tube
// Higher number = torch gets taller
const uint16_t levels = 5;

const uint16_t ledsPerPixel = 1; // single (adressable) LEDs per pixel

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


#elif PIXELARRANGEMENT==4

// 3 of 5 verticals, use single pixels in the middle vertical to simulate 3 verticals

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


typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} RGBColor;


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



void webColorToRGB(String aWebColor, RGBColor &aColor)
{
  int cc;
  int i=0;
  if (aWebColor.length()==6) {
    // RRGGBB
    cc = hexToInt(aWebColor[i++]);
    aColor.r = (cc<<4) + hexToInt(aWebColor[i++]);
    cc = hexToInt(aWebColor[i++]);
    aColor.g = (cc<<4) + hexToInt(aWebColor[i++]);
    cc = hexToInt(aWebColor[i++]);
    aColor.b = (cc<<4) + hexToInt(aWebColor[i++]);
  }
  else if (aWebColor.length()==3) {
    // RGB
    cc = hexToInt(aWebColor[i++]);
    aColor.r = (cc<<4) + cc;
    cc = hexToInt(aWebColor[i++]);
    aColor.g = (cc<<4) + cc;
    cc = hexToInt(aWebColor[i++]);
    aColor.b = (cc<<4) + cc;
  }
}




// Super simple 5x5 font

const int numGlyphs = 96+6; // 96 ASCII 0x20..0x7F + 6 umlauts
const int glyphHeight = 5;
const int glyphWidth = 5;


uint8_t font5x5Bytes[numGlyphs*glyphWidth] = {
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
  0x80, 0x40, 0x20, 0x10, 0x08, // / 0x2F (15)

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
  0xf0, 0x28, 0x28, 0x28, 0xf0, // A 0x41 (1)
  0xf8, 0xa8, 0xa8, 0xa8, 0x50, // B 0x42 (2)
  0xf8, 0x88, 0x88, 0x88, 0x88, // C 0x43 (3)
  0xf8, 0x88, 0x88, 0x88, 0x70, // D 0x44 (4)
  0xf8, 0xa8, 0xa8, 0xa8, 0x88, // E 0x45 (5)
  0xf8, 0x28, 0x28, 0x28, 0x08, // F 0x46 (6)
  0xf8, 0x88, 0x88, 0xa8, 0xe8, // G 0x47 (7)
  0xf8, 0x20, 0x20, 0x20, 0xf8, // H 0x48 (8)
  0x00, 0x88, 0xf8, 0x88, 0x00, // I 0x49 (9)
  0xc0, 0x80, 0x80, 0x88, 0xf8, // J 0x4A (10)
  0xf8, 0x20, 0x20, 0x50, 0x88, // K 0x4B (11)
  0xf8, 0x80, 0x80, 0x80, 0x80, // L 0x4C (12)
  0xf8, 0x10, 0x20, 0x10, 0xf8, // M 0x4D (13)
  0xf8, 0x10, 0x20, 0x40, 0xf8, // N 0x4E (14)
  0x70, 0x88, 0x88, 0x88, 0x70, // O 0x4F (15)

  0xf8, 0x28, 0x28, 0x28, 0x10, // P 0x50 (0)
  0x70, 0x88, 0x88, 0xC8, 0xF0, // Q 0x51 (1)
  0xf8, 0x28, 0x28, 0x28, 0xd0, // R 0x52 (2)
  0xb8, 0xa8, 0xa8, 0xa8, 0xe8, // S 0x53 (3)
  0x08, 0x08, 0xf8, 0x08, 0x08, // T 0x54 (4)
  0xf8, 0x80, 0x80, 0x80, 0xf8, // U 0x55 (5)
  0x38, 0x40, 0x80, 0x40, 0x38, // V 0x56 (6)
  0x78, 0x80, 0x60, 0x80, 0x78, // W 0x57 (7)
  0x88, 0x50, 0x20, 0x50, 0x88, // X 0x58 (8)
  0x18, 0x20, 0xc0, 0x20, 0x18, // Y 0x59 (9)
  0x88, 0xc8, 0xa8, 0x98, 0x88, // Z 0x5A (10)
  0x00, 0xf8, 0x88, 0x00, 0x00, // [ 0x5B (11)
  0x08, 0x10, 0x20, 0x40, 0x80, // \ 0x5C (12)
  0x00, 0x00, 0x88, 0xf8, 0x00, // ] 0x5D (1)
  0x00, 0x10, 0x08, 0x10, 0x00, // ^ 0x5E (0)
  0x80, 0x80, 0x80, 0x80, 0x80, // _ 0x5F (1)

  0x00, 0x00, 0x08, 0x10, 0x00, // ` 0x60 (0)
  0xf0, 0x28, 0x28, 0x28, 0xf0, // A 0x41 (1)
  0xf8, 0xa8, 0xa8, 0xa8, 0x50, // B 0x42 (2)
  0xf8, 0x88, 0x88, 0x88, 0x88, // C 0x43 (3)
  0xf8, 0x88, 0x88, 0x88, 0x70, // D 0x44 (4)
  0xf8, 0xa8, 0xa8, 0xa8, 0x88, // E 0x45 (5)
  0xf8, 0x28, 0x28, 0x28, 0x08, // F 0x46 (6)
  0xf8, 0x88, 0x88, 0xa8, 0xe8, // G 0x47 (7)
  0xf8, 0x20, 0x20, 0x20, 0xf8, // H 0x48 (8)
  0x00, 0x88, 0xf8, 0x88, 0x00, // I 0x49 (9)
  0xc0, 0x80, 0x80, 0x88, 0xf8, // J 0x4A (10)
  0xf8, 0x20, 0x20, 0x50, 0x88, // K 0x4B (11)
  0xf8, 0x80, 0x80, 0x80, 0x80, // L 0x4C (12)
  0xf8, 0x10, 0x20, 0x10, 0xf8, // M 0x4D (13)
  0xf8, 0x10, 0x20, 0x40, 0xf8, // N 0x4E (14)
  0x70, 0x88, 0x88, 0x88, 0x70, // O 0x4F (15)

  0xf8, 0x28, 0x28, 0x28, 0x10, // P 0x50 (0)
  0x70, 0x88, 0x88, 0xC8, 0xF0, // Q 0x51 (1)
  0xf8, 0x28, 0x28, 0x28, 0xd0, // R 0x52 (2)
  0xb8, 0xa8, 0xa8, 0xa8, 0xe8, // S 0x53 (3)
  0x08, 0x08, 0xf8, 0x08, 0x08, // T 0x54 (4)
  0xf8, 0x80, 0x80, 0x80, 0xf8, // U 0x55 (5)
  0x38, 0x40, 0x80, 0x40, 0x38, // V 0x56 (6)
  0x78, 0x80, 0x60, 0x80, 0x78, // W 0x57 (7)
  0x88, 0x50, 0x20, 0x50, 0x88, // X 0x58 (8)
  0x18, 0x20, 0xc0, 0x20, 0x18, // Y 0x59 (9)
  0x88, 0xc8, 0xa8, 0x98, 0x88, // Z 0x5A (10)
  0x00, 0x20, 0xf8, 0x88, 0x00, // { 0x7B (0)
  0x00, 0x00, 0xF8, 0x00, 0x00, // | 0x7C (12)
  0x00, 0x88, 0xf8, 0x20, 0x00, // } 0x7D (13)
  0x00, 0x10, 0x08, 0x10, 0x08, // ~ 0x7E (14)
  0xF8, 0x88, 0xA8, 0x88, 0xF8, // } 0x7F (15)

  0xE8, 0x50, 0x48, 0x50, 0xE8, // Ä 0x80
  0x78, 0x88, 0x88, 0x88, 0x78, // Ö 0x81
  0xE8, 0x80, 0x80, 0x80, 0xE8, // Ü 0x82
  0xE8, 0x50, 0x48, 0x50, 0xE8, // ä 0x83
  0x78, 0x88, 0x88, 0x88, 0x78, // ö 0x84
  0xE8, 0x80, 0x80, 0x80, 0xE8, // ü 0x85

};


const char *startupText = "\\#0F0;LEDIGIT/HUGECHAR v1.2\\_200;";
const char *defaultText = "\\(;\\#;LUECHTTURM!  STADIONBRACHE  CENTRAL PARK ZUERICH\\_100;\\#F00;\\@\\$\\_100;\\)";

const int numRandomWords = 28;
const char *randomWords[numRandomWords] = {
  "UNIVERSUM",
  "LIVING ROOM",
  "FREIRAUM",
  "RETENTIONSFLAECHE",
  "GRUENRAUM",
  "GRUNDWASSER",
  "ZIRKUS",
  "GRUENE LOUNGE",
  "ALLMEND",
  "FUSSBALL",
  "FESTPLATZ",
  "QUARTIERPARK",
  "PICKNICK",
  "SPIELPLATZ",
  "STADTLUNGE",
  "MULTIFUNKTIONAL",
  "MOEGLICHKEITSRAUM",
  "TAVOLATA",
  "BIODIVERSITAET",
  "BRAETELN",
  "SPIEL UND SPASS",
  "OASE",
  "GRUENE LUNGE",
  "QUARTIERLEBEN",
  "PROJEKTIONSFLAECHE",
  "WURZELGEMUESE",
  "EXPERIMENTIERFELD",
  "LEDIGIT"
};




// Main program
// ============

// moved defining constants for number of LEDs to top of file

#ifndef NUM_LEDS
#define NUM_LEDS (ledsPerLevel*levels*ledsPerPixel) // standard formula
#endif
const uint16_t numLeds = NUM_LEDS; // total number of LEDs

p44_ws2812 leds(LED_TYPE, numLeds, ledsPerLevel, reversedX, alternatingX, swapXY, reversedY, ledsPerPixel); // create WS281x driver

// parameters
// ==========

int cycle_wait = 50; // don't go too low (<20) on Electron, or cloud will get unreliable

typedef enum {
  mode_standby,
  mode_text,
  mode_testpixel,
  mode_colorwheel,
  numModes
};
byte mode = mode_text;
bool modeChanged = true;

#define TIMER_OFF 99
typedef struct {
  byte hour; // TIMER_OFF = disabled
  byte minute;
} TimerSetting;

TimerSetting startTime = { 20, 00 }; // start operating in timerMode
byte timerMode = mode_text;
TimerSetting stopTime = { 9, 00 }; // stop operating (go to mode_standby)
TimerSetting brightTime = { 6, 00 }; // start using full brightness (unless illu_off)
TimerSetting dimTime = { 1, 00 }; // stop forcing full brightness (auto mode from illumination)


RGBColor defaultTextColor = { 255, 204, 68 }; // warm white
RGBColor textColor = defaultTextColor;

RGBColor backGroundColor = { 0, 0, 0 };

int brightness = 255; // overall brightness, possibly auto-adjusted via light level
int fade_base = 42; // base brightness for cross-fading

// char params
int briHighlight = 255; // highlight intensity
int briNormal = 250; // normal intensity
int fadeIn = 0;  // fade in time to highlight
int highlight = 3; // highlight sustain time
int backnormal = 3; // fade down time to normal
int normal = 9; // normal sustain time
int fadeout = 7; // fade out to zero time
int pause = 2; // pause time

// text params
int cycles_per_px = 5;
int text_repeats = 15; // text displays until faded down to almost zero
int fade_per_repeat = 15; // how much to fade down per repeat
int text_base_line = 0;

// automatic brightness reduction
int brightness_max = 255; // brightness at highest light level, 0 to disable auto-brightness
int brightness_min = 168; // brightness at lowest light level
int illu_off = 500; // above this illumination level, LEDs will be turned off (not visible anyway)
int illu_max = 60; // between illu_off and illu_max, brightness is full
int illu_min = 1; // between illu_max and illu_min, brightness varies proportionally between max and brightness_min
int always_max = 0; // force max brightness, even if illumination is low

// reporting
int reportInterval = 0; // no automatic report by default
int minToNextReport = 0;
int illuminationLevel = 0; // illumination level
int illuAvgInterval = 300; // average interval in seconds
int illuminationLevelAvg = -1; // averaged
float supplyVoltage = 0; // supply voltage in V
float batteryVoltage = 0; // battery voltage in V


// globals
// =======

// char layer
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


void setMode(byte aNewMode)
{
  if (aNewMode!=mode) {
    mode = aNewMode;
    modeChanged = true;

  }
}

void parseTime(String aTStr, TimerSetting &aTime)
{
  if (aTStr=="none") {
    aTime.hour = TIMER_OFF; // disable
  }
  else {
    int i = aTStr.indexOf(':');
    if (i>0) {
      aTime.hour = aTStr.substring(0,i).toInt();
      aTime.minute = aTStr.substring(i+1).toInt();
    }
  }
}



// Cloud API
// =========

String status;

void updateStatus()
{
  status = String::format(
    "{ \"mode\":%d, \"VSup\":%.3f, \"VBat\":%.3f, \"illu\":%d, \"illuAvg\":%d, \"bri\":%d, \"next\":\"%s\" }",
    mode, supplyVoltage, batteryVoltage, illuminationLevel, illuminationLevelAvg, brightness,
    text.substring(textIndex, textIndex+20).c_str()
  );
}

void reportStatus()
{
  updateStatus();
  Particle.publish("status", status);
}



int smooth(int aNewValue, long &aAccu, int aSteps=5)
{
  aAccu = aAccu*(aSteps-1)/aSteps+aNewValue;
  return (aAccu+aSteps-1)/aSteps;
}



void calcBrightness()
{
  static long briAccu = 0;
  int newBri = brightness;
  if (brightness_max>0) {
    // auto-brightness is enabled
    if (always_max) {
      // max level (unless overridden by illu_off below)
      newBri = brightness_max;
    }
    if (illuminationLevelAvg>=0) {
      // we have an averaged light level
      if (illu_off>0 && illuminationLevelAvg>illu_off) {
        newBri = 0;
      }
      else if (illu_max>0 && illuminationLevelAvg>=illu_max) {
        newBri = brightness_max;
      }
      else if (!always_max && illu_min>0 && illuminationLevelAvg<illu_min) {
        newBri = brightness_min;
      }
      else if (!always_max && illu_min>0 && illu_max>illu_min) {
        newBri = brightness_min + (brightness_max-brightness_min)*(illuminationLevelAvg-illu_min)/(illu_max-illu_min);
      }
    }
    // smooth transitioning
    brightness = smooth(newBri, briAccu, 7);
  }
}


// this function automagically gets called upon a matching POST request
int handleParams(String command)
{
  String key;
  int p = 0;
  while (p<(int)command.length()) {
    int i = command.indexOf(',',p);
    if (i<0) i = command.length();
    int j = command.indexOf('=',p);
    if (j<0) {
      // no assignment, just command
      key = command.substring(p,i); // from..to (NOT from, len!!)
      if (key=="report") {
        reportStatus();
      }
      else if (key=="update") {
        updateStatus();
      }
      else if (key=="restart") {
        System.reset();
      }
      // next
      p = i+1;
      continue;
    }
    key = command.substring(p,j); // from..to (NOT from, len!!)
    String value = command.substring(j+1,i); // from..to (NOT from, len!!)
    int val = value.toInt();
    // global params
    if (key=="wait") {
      // prevent too busy mainloop makes remote control fail
      if (val>=20) cycle_wait = val;
    }
    else if (key=="report_interval") {
      reportInterval = val;
      if (val>0) minToNextReport = 1; // report next minute
    }
    else if (key=="mode")
      setMode(val);
    else if (key=="bri")
      brightness = val;
    else if (key=="bri_max")
      brightness_max = val;
    else if (key=="bri_min")
      brightness_min = val;
    else if (key=="always_max")
      always_max = val;
    else if (key=="illu_off")
      illu_off = val;
    else if (key=="illu_max")
      illu_max = val;
    else if (key=="illu_min")
      illu_min = val;
    else if (key=="illu_avg_intvl")
      illuAvgInterval = val;
    else if (key=="fade_base")
      fade_base = val;
    // timer params
    else if (key=="timer_mode")
      timerMode = val;
    else if (key=="start_tm")
      parseTime(value, startTime);
    else if (key=="stop_tm")
      parseTime(value, stopTime);
    else if (key=="bri_tm")
      parseTime(value, brightTime);
    else if (key=="dim_tm")
      parseTime(value, dimTime);
    // text color params
    else if (key=="def_text_col")
      webColorToRGB(value, defaultTextColor);
    else if (key=="text_col")
      webColorToRGB(value, textColor);
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
    else if (key=="bg_col")
      webColorToRGB(value, backGroundColor);
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


// char layer
// ==========

void resetText()
{
  text = "";
  repeatText = 0;
  textIndex = 0;
  stateSteps = 0;
  cbri16 = 0;
  rsta = s_start;
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
  // (ignore completely empty texts, these could come from misguided/accidental form posts)
  if (txt.length()>0) {
    if (txt[0]=='+') {
      // append
      text += txt.substring(1);
      // end repeats
      if (repeatText>1) repeatText=1;
    }
    else if (txt[0]=='=') {
      // replace, if empty -> default text
      resetText();
      text = txt.substring(1);
      if (text.length()==0) text = defaultText;
    }
    else if (txt=="-") {
      // switch off
      resetText();
    }
    else {
      // No command prefix: default to append and continue with standard text
      text += txt;
      text += " \\="; // at end, back to standard text
      // end repeats of current text
      if (repeatText>1) repeatText=1;
    }
  }
  return 1;
}


char nextChar()
{
  String subCmd;
  char c = 0; // none
  if (textIndex>=text.length()) {
    // has run to end, remove old text
    text = "";
    textIndex = 0;
  }
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
      else if (e=='@') {
        // random word from list
        int i = text.indexOf("\\$",textIndex);
        if (i>=0) {
          // - get word
          String word = randomWords[random(numRandomWords-1)];
          // - replace
          String newText = text.substring(0,textIndex);
          newText.concat(word);
          newText.concat(text.substring(i));
          text = newText;
          // run the text that is now at textIndex!
        }
      }
      else if (e=='$') {
        // NOP: end of substitution
      }
      else if (e=='=') {
        // back to standard text
        text = defaultText;
        textIndex = 0;
      }
      else if (e=='(') {
        // repeat 3 times: \(3;
        // repeat forever: \(;
        // - repeat must be at beginning of text
        text.remove(0, textIndex-2);
        textIndex = 2; // "\(" at beginning
        // - now process
        int i = text.indexOf(';',textIndex);
        if (i>=0) {
          if (repeatText==0) {
            // set new repeat only if not already running
            if (i>textIndex) {
              // repeat count
              subCmd = text.substring(textIndex,i); // from..to (NOT from, len!!)
              repeatText = subCmd.toInt();
            }
            else {
              // forever
              repeatText = 9999; // forever
            }
          }
          textIndex=i+1;
        }
      }
      else if (e==')') {
        // end repeat: \)
        if (repeatText>1) {
          // repeat
          if (repeatText<9999)
            repeatText--;
          textIndex = 0;
        }
        else {
          // done repeating
          text.remove(0, textIndex);
          textIndex = 0;
          repeatText=0;
        }
      }
      else if (e=='#') {
        // color change: \#rrggbb;
        // color change: \#rgb;
        // random color change: \#RND;
        int i = text.indexOf(';',textIndex);
        if (i>=0) {
          if (i>textIndex) {
            subCmd = text.substring(textIndex,i); // from..to (NOT from, len!!)
            if (subCmd=="RND") {
              wheel(random(255), textColor.r, textColor.g, textColor.b);
            }
            else {
              webColorToRGB(subCmd, textColor);
            }
          }
          else {
            // back to default
            textColor = defaultTextColor;
          }
          textIndex=i+1;
        }
      }
      else if (e=='_') {
        // pause: \_20;
        int i = text.indexOf(';',textIndex);
        if (i>=0) {
          subCmd = text.substring(textIndex,i); // from..to (NOT from, len!!)
          stateSteps = subCmd.toInt();
          // show a space
          textIndex=i+1;
          c = 0; // not a char, only state change!
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
      cchar = nextChar(); // might change state and return 0
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


// Main program
// ============

#define SUPPLY_VOLTAGE A0
#define LIGHT_LEVEL A1
#define LIGHT_LEVEL_PWR A6



void setup()
{
  resetText();
  text = startupText;
  text.concat(defaultText);
  leds.begin();
  // Time zone
  Time.zone(1); // UTC+1
  Time.setDSTOffset(1);
  Time.beginDST(); // assume summer
  //Time.endDST(); // assume winter
  // remote control
  Particle.function("params", handleParams); // parameters
  Particle.function("message", newMessage); // text message display
  // status
  Particle.variable("status", status);
  // Serial
  Serial.begin();
  Serial.println("Hello LEDigit/HugeChar");
  // LDR power pin
  pinMode(LIGHT_LEVEL_PWR, OUTPUT);
  digitalWrite(LIGHT_LEVEL_PWR, HIGH);
}



byte cnt = 0;
byte lastCheckedSec = 99;
byte lastCheckedMin = 99;
FuelGauge fuel;

void loop()
{
  static long illAccu = 0;
  // Real time
  if (timerMode!=mode_standby) {
    if (Time.second()!=lastCheckedSec) {
      lastCheckedSec = Time.second();
      // once per second
      // Power Supply:
      // - Theory: Voltage/11/3.3*4096 = ADC (1k/10k valtage divider)
      // - Actual: 541==4.89V -> ADC*4.89/541 = Voltage [V]
      supplyVoltage =  (float)analogRead(SUPPLY_VOLTAGE)*4.89/541;
      // Light:
      illuminationLevel = analogRead(LIGHT_LEVEL);
      illuminationLevelAvg = smooth(illuminationLevel, illAccu, 5);
      // Electron battery
      batteryVoltage = fuel.getVCell();
      updateStatus();
      Serial.printlnf("illuminationLevel=%d, illuminationLevelAvg=%d, bri=%d, PowerSupply=%.2fV, Battery=%.2fV", illuminationLevel, illuminationLevelAvg, brightness, supplyVoltage, batteryVoltage);
    }
    if (Time.minute()!=lastCheckedMin) {
      lastCheckedMin = Time.minute();
      // once per minute
      if (minToNextReport>0) {
        minToNextReport--;
        if (minToNextReport==0) {
          reportStatus();
          minToNextReport = reportInterval; // re-load
        }
      }
      // mode timers
      if (startTime.hour!=TIMER_OFF && Time.hour()==startTime.hour && lastCheckedMin==startTime.minute) {
        setMode(timerMode);
      }
      else if (stopTime.hour!=TIMER_OFF && Time.hour()==stopTime.hour && lastCheckedMin==stopTime.minute) {
        setMode(mode_standby);
      }
      // brightness timers
      if (brightTime.hour!=TIMER_OFF && Time.hour()==brightTime.hour && lastCheckedMin==brightTime.minute) {
        // force using brightness_max
        always_max = 1;
      }
      else if (dimTime.hour!=TIMER_OFF && Time.hour()==dimTime.hour && lastCheckedMin==dimTime.minute) {
        // allow dimdown
        always_max = 0;
      }
    }
  }
  // Display
  if (mode==mode_standby) {
    if (modeChanged) {
      // switch off
      for (int i=0; i<leds.getNumPixels(); i++) {
        leds.setColor(i,0,0,0);
      }
      leds.show();
    }
    // just sleep some seconds
    //System.sleep(SLEEP_MODE_DEEP, 15, SLEEP_NETWORK_STANDBY);
    //System.sleep(15);
    delay(10000);
  }
  else {
    // recalculate auto-brightness
    calcBrightness();
  }
  if (mode==mode_testpixel) {
    // go through pixels one by one, full red
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
    for (int i=0; i<leds.getNumPixels(); i++) {
      wheel((cnt+i*5)&0xFF, r, g, b);
      leds.setColorDimmed(i, r, g, b, brightness);
    }
    cnt++;
    // transmit colors to the leds
    leds.show();
    delay(cycle_wait);
  }
  else if (mode==mode_text) {
    // render the char
    textStep();
    for (int x=0; x<leds.getSizeX(); x++) {
      for (int y=0; y<leds.getSizeY(); y++) {
        uint8_t b = charBrightnessAt(x,y);
        if (b>0) {
          leds.setColorDimmedXY(x, y, textColor.r, textColor.g, textColor.b, (b*brightness)>>8);
        }
        else {
          leds.setColorDimmedXY(x, y, backGroundColor.r, backGroundColor.g, backGroundColor.b, brightness);
        }
      }
    }
    // transmit colors to the leds
    leds.show();
    // wait
    delay(cycle_wait); // latch & reset needs 50 microseconds pause, at least.
  }
  modeChanged = false;
}





