// #include "LedDriver.h"
#include "LedDriver_MemoryMapped.h"
#include "DataTypes.h"
#include <stdlib.h>

//*** Data types ***//
typedef struct LedDriver_MemoryMappedStruct
{
  LedDriverStruct base;
  uint16_t * ledsAddress;   // store the LEDs' memory address locally
  uint16_t ledsImage;       // store the LEDs' state locally
} LedDriver_MemoryMappedStruct;

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
//Macro for frequent typecast
#define DRIVER_TYPECAST(oldVar, newVar) LedDriver_MemoryMapped oldVar = (LedDriver_MemoryMapped)newVar

//Helper functions
static uint16_t convertLedNumberToBit(uint8_t ledNumber);
static void updateHardware(LedDriver_MemoryMapped instance);
static BOOL isLedOutOfBounds(uint8_t ledNumber);
static void setLedImageBit(LedDriver_MemoryMapped instance, int ledNumber);
static void clearLedImageBit(LedDriver_MemoryMapped instance, int ledNumber);


//*** File-scope variables ***//


//*** Public functions ***//
LedDriver LedDriver_MemoryMapped_Create(uint16_t * address)
{
  LedDriver_MemoryMapped self = (LedDriver_MemoryMapped)calloc(1, sizeof(LedDriver_MemoryMappedStruct));
  self->base.driverType = "MemoryMapped";
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

void LedDriver_TurnOn(LedDriver instance, uint8_t ledNumber)
{
  CHECK_NULL(instance);
  DRIVER_TYPECAST(self, instance);
  if (isLedOutOfBounds(ledNumber))
  {
    return;
  }
  setLedImageBit(self, ledNumber);
  updateHardware(self);
}

void LedDriver_TurnOff(LedDriver instance, uint8_t ledNumber)
{
  CHECK_NULL(instance);
  DRIVER_TYPECAST(self, instance);
  if (isLedOutOfBounds(ledNumber))
  {
    return;
  }
  clearLedImageBit(self, ledNumber);
  updateHardware(self);
}

void LedDriver_TurnAllOn(LedDriver instance)
{
  CHECK_NULL(instance);
  DRIVER_TYPECAST(self, instance);
  self->ledsImage |= ALL_LEDS_ON;
  updateHardware(self);
}

void LedDriver_TurnAllOff(LedDriver instance)
{
  CHECK_NULL(instance);
  DRIVER_TYPECAST(self, instance);
  self->ledsImage = 0;
  updateHardware(self);
}

BOOL LedDriver_IsOn(LedDriver instance, uint8_t ledNumber)
{
  CHECK_NULL_RETURN_VALUE(instance, FALSE);
  DRIVER_TYPECAST(self, instance);
  if (isLedOutOfBounds(ledNumber))
  {
    return FALSE;
  }
  return self->ledsImage & convertLedNumberToBit(ledNumber);
}

BOOL LedDriver_IsOff(LedDriver instance, uint8_t ledNumber)
{
  CHECK_NULL_RETURN_VALUE(instance, TRUE);
  DRIVER_TYPECAST(self, instance);
  if (isLedOutOfBounds(ledNumber))
  {
    return TRUE;
  }
  return !LedDriver_IsOn(instance, ledNumber);  // pass instance to avoid typecast
}


//*** File-scope functions ***//
static uint16_t convertLedNumberToBit(uint8_t ledNumber)
{
  return 1 << (ledNumber-1);
}

// Set hardware memory from local copy of memory
// This is done in case the hardware is write-only
static void updateHardware(LedDriver_MemoryMapped self)
{
  *(self->ledsAddress) = self->ledsImage;
}

static BOOL isLedOutOfBounds(uint8_t ledNumber)
{
  return (ledNumber < FIRST_LED || ledNumber > LAST_LED);
}

static void setLedImageBit(LedDriver_MemoryMapped self, int ledNumber)
{
  self->ledsImage |= convertLedNumberToBit(ledNumber);
}

static void clearLedImageBit(LedDriver_MemoryMapped self, int ledNumber)
{
  self->ledsImage &= ~convertLedNumberToBit(ledNumber);
}
