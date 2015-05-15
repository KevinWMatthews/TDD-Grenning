#include "LedDriver_MemoryMapped.h"
#include "DataTypes.h"
#include <stdlib.h>

//*** Data types ***//
typedef struct LedDriverStruct
{
  uint16_t * ledsAddress;   // store the LEDs' memory address locally
  uint16_t ledsImage;       // store the LEDs' state locally
} LedDriverStruct;

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


//*** File-scope function prototypes ***//
//Helper functions
static uint16_t convertLedNumberToBit(uint8_t ledNumber);
static void updateHardware(LedDriver self);
static BOOL isLedOutOfBounds(uint8_t ledNumber);
static void setLedImageBit(LedDriver self, int ledNumber);
static void clearLedImageBit(LedDriver self, int ledNumber);


//*** File-scope variables ***//


//*** Public functions ***//
LedDriver LedDriver_Create(uint16_t * address)
{
  LedDriver self = (LedDriver)calloc(1, sizeof(LedDriverStruct));
  self->ledsAddress = address;      // Set up local pointer to capture the address of external memory
  self->ledsImage = ALL_LEDS_OFF;   // Set local copy of memory
  updateHardware(self);
  return (LedDriver)self;
}

void LedDriver_Destroy(LedDriver * self)
{
  CHECK_NULL(self);
  free(*self);
  *self = NULL;
}

void LedDriver_TurnOn(LedDriver self, uint8_t ledNumber)
{
  if (isLedOutOfBounds(ledNumber))
  {
    return;
  }
  setLedImageBit(self, ledNumber);
  updateHardware(self);
}

void LedDriver_TurnOff(LedDriver self, uint8_t ledNumber)
{
  if (isLedOutOfBounds(ledNumber))
  {
    return;
  }
  clearLedImageBit(self, ledNumber);
  updateHardware(self);
}

void LedDriver_TurnAllOn(LedDriver self)
{
  self->ledsImage |= ALL_LEDS_ON;
  updateHardware(self);
}

void LedDriver_TurnAllOff(LedDriver self)
{
  self->ledsImage = 0;
  updateHardware(self);
}

BOOL LedDriver_IsOn(LedDriver self, uint8_t ledNumber)
{
  if (isLedOutOfBounds(ledNumber))
  {
    return FALSE;
  }
  return self->ledsImage & convertLedNumberToBit(ledNumber);
}

BOOL LedDriver_IsOff(LedDriver self, uint8_t ledNumber)
{
  if (isLedOutOfBounds(ledNumber))
  {
    return TRUE;
  }
  return !LedDriver_IsOn(self, ledNumber);
}


//*** File-scope functions ***//
static uint16_t convertLedNumberToBit(uint8_t ledNumber)
{
  return 1 << (ledNumber-1);
}

// Set hardware memory from local copy of memory
// This is done in case the hardware is write-only
static void updateHardware(LedDriver self)
{
  *(self->ledsAddress) = self->ledsImage;
}

static BOOL isLedOutOfBounds(uint8_t ledNumber)
{
  return (ledNumber < FIRST_LED || ledNumber > LAST_LED);
}

static void setLedImageBit(LedDriver self, int ledNumber)
{
  self->ledsImage |= convertLedNumberToBit(ledNumber);
}

static void clearLedImageBit(LedDriver self, int ledNumber)
{
  self->ledsImage &= ~convertLedNumberToBit(ledNumber);
}
