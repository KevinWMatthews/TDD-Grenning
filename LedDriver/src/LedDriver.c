#include "LedDriver.h"
#include "DataTypes.h"

enum
{
  ALL_LEDS_ON  = ~0,
  ALL_LEDS_OFF = ~ALL_LEDS_ON
};

enum
{
  FIRST_LED = 1,
  LAST_LED = 16
};

// Create a local pointer so we can hang on to the LEDs' memory address after initialization
static uint16_t* ledsAddress;
// Assume that hardware's memory is write-only, so we need to store the LED state locally
static uint16_t ledsImage;

static uint16_t convertLedNumberToBit(uint8_t ledNumber)
{
  return 1 << (ledNumber-1);
}

// Set hardware memory from local copy of memory
// This is done in case the hardware is write-only
static void updateHardware(void)
{
  *ledsAddress = ledsImage;
}

static BOOL isLedOutOfBounds(uint8_t ledNumber)
{
  return (ledNumber < FIRST_LED || ledNumber > LAST_LED);
}

static void setLedImageBit(int ledNumber)
{
  ledsImage |= convertLedNumberToBit(ledNumber);
}

static void clearLedImageBit(int ledNumber)
{
  ledsImage &= ~convertLedNumberToBit(ledNumber);
}

void LedDriver_Create(uint16_t* address)
{
  ledsAddress = address;      // Set up local pointer
  ledsImage = ALL_LEDS_OFF;   // Set local memory
  updateHardware();
}

void LedDriver_TurnOn(uint8_t ledNumber)
{
  if (isLedOutOfBounds(ledNumber))
  {
    return;
  }
  setLedImageBit(ledNumber);
  updateHardware();
}

void LedDriver_TurnOff(uint8_t ledNumber)
{
  if (isLedOutOfBounds(ledNumber))
  {
    return;
  }
  clearLedImageBit(ledNumber);
  updateHardware();
}

void LedDriver_TurnAllOn(void)
{
  ledsImage |= ALL_LEDS_ON;
  updateHardware();
}

void LedDriver_TurnAllOff(void)
{
  ledsImage = 0;
  updateHardware();
}

BOOL LedDriver_IsOn(uint8_t ledNumber)
{
  if (isLedOutOfBounds(ledNumber))
  {
    return FALSE;
  }
  return ledsImage & convertLedNumberToBit(ledNumber);
}

BOOL LedDriver_IsOff(uint8_t ledNumber)
{
  if (isLedOutOfBounds(ledNumber))
  {
    return TRUE;
  }
  return !LedDriver_IsOn(ledNumber);
}
