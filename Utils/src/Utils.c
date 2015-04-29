#include "Utils.h"

int FormatOutput_Impl(const char* input, ...)
{
  // Actual implementation
  // We're substituting for this
}

int (*FormatOutput)(const char* format, ...) = FormatOutput_Impl;
