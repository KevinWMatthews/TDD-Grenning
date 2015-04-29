/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "MockIO.h"

static struct MockIOInstance
{
  unsigned char allocFailure;

  int IO_Read_CallCount;
  int IO_Read_CallsExpected;

  ioData *IO_Read_Return;
  ioData *IO_Read_Return_Head;
  ioData *IO_Read_Return_Tail;

  ioAddress *IO_Read_Expected_offset;
  ioAddress *IO_Read_Expected_offset_Head;
  ioAddress *IO_Read_Expected_offset_Tail;

  int IO_Write_CallCount;
  int IO_Write_CallsExpected;

  ioAddress *IO_Write_Expected_offset;
  ioAddress *IO_Write_Expected_offset_Head;
  ioAddress *IO_Write_Expected_offset_Tail;

  ioData *IO_Write_Expected_data;
  ioData *IO_Write_Expected_data_Head;
  ioData *IO_Write_Expected_data_Tail;
} Mock;

extern jmp_buf AbortFrame;

void MockIO_Verify(void)
{
  TEST_ASSERT_EQUAL_MESSAGE(0, Mock.allocFailure, "Unable to allocate memory for mock");
  TEST_ASSERT_EQUAL_MESSAGE(Mock.IO_Read_CallsExpected, Mock.IO_Read_CallCount, "Function 'IO_Read' called unexpected number of times.");
  TEST_ASSERT_EQUAL_MESSAGE(Mock.IO_Write_CallsExpected, Mock.IO_Write_CallCount, "Function 'IO_Write' called unexpected number of times.");
}

void MockIO_Init(void)
{
  MockIO_Destroy();
}

void MockIO_Destroy(void)
{

  if (Mock.IO_Read_Return_Head)
  {
    free(Mock.IO_Read_Return_Head);
  }
  Mock.IO_Read_Return=NULL;
  Mock.IO_Read_Return_Head=NULL;
  Mock.IO_Read_Return_Tail=NULL;

  if (Mock.IO_Read_Expected_offset_Head)
  {
    free(Mock.IO_Read_Expected_offset_Head);
  }
  Mock.IO_Read_Expected_offset=NULL;
  Mock.IO_Read_Expected_offset_Head=NULL;
  Mock.IO_Read_Expected_offset_Tail=NULL;

  if (Mock.IO_Write_Expected_offset_Head)
  {
    free(Mock.IO_Write_Expected_offset_Head);
  }
  Mock.IO_Write_Expected_offset=NULL;
  Mock.IO_Write_Expected_offset_Head=NULL;
  Mock.IO_Write_Expected_offset_Tail=NULL;

  if (Mock.IO_Write_Expected_data_Head)
  {
    free(Mock.IO_Write_Expected_data_Head);
  }
  Mock.IO_Write_Expected_data=NULL;
  Mock.IO_Write_Expected_data_Head=NULL;
  Mock.IO_Write_Expected_data_Tail=NULL;
  memset(&Mock, 0, sizeof(Mock));
}

ioData IO_Read(ioAddress offset)
{
  Mock.IO_Read_CallCount++;
  if (Mock.IO_Read_CallCount > Mock.IO_Read_CallsExpected)
  {
    TEST_FAIL("Function 'IO_Read' called more times than expected");
  }

  if (Mock.IO_Read_Expected_offset != Mock.IO_Read_Expected_offset_Tail)
  {
    ioAddress* p_expected = Mock.IO_Read_Expected_offset;
    Mock.IO_Read_Expected_offset++;
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE(
        (void*)p_expected, (void*)&(offset), sizeof(ioAddress),
        "Function 'IO_Read' called with unexpected value for argument 'offset'.");
  }

  if (Mock.IO_Read_Return != Mock.IO_Read_Return_Tail)
  {
    ioData toReturn = *Mock.IO_Read_Return;
    Mock.IO_Read_Return++;
    return toReturn;
  }
  else
  {
    return *(Mock.IO_Read_Return_Tail - 1);
  }
}

void ExpectParameters_IO_Read(ioAddress offset)
{

  {
    int sz = 0;
    ioAddress *pointer = Mock.IO_Read_Expected_offset_Head;
    while (pointer && pointer != Mock.IO_Read_Expected_offset_Tail) { sz++; pointer++; }
    if (sz == 0)
    {
      Mock.IO_Read_Expected_offset_Head = (ioAddress*)malloc(2*sizeof(ioAddress));
      if (!Mock.IO_Read_Expected_offset_Head)
        Mock.allocFailure++;
    }
    else
    {
      ioAddress *ptmp = (ioAddress*)realloc(Mock.IO_Read_Expected_offset_Head, sizeof(ioAddress) * (sz+1));
      if (!ptmp)
        Mock.allocFailure++;
      else
        Mock.IO_Read_Expected_offset_Head = ptmp;
    }
    memcpy(&Mock.IO_Read_Expected_offset_Head[sz], &offset, sizeof(ioAddress));
    Mock.IO_Read_Expected_offset_Tail = &Mock.IO_Read_Expected_offset_Head[sz+1];
  }
  Mock.IO_Read_Expected_offset = Mock.IO_Read_Expected_offset_Head;
  Mock.IO_Read_Expected_offset += Mock.IO_Read_CallCount;
}

void IO_Read_ExpectAndReturn(ioAddress offset, ioData toReturn)
{
  Mock.IO_Read_CallsExpected++;
  ExpectParameters_IO_Read(offset);

  {
    int sz = 0;
    ioData *pointer = Mock.IO_Read_Return_Head;
    while (pointer && pointer != Mock.IO_Read_Return_Tail) { sz++; pointer++; }
    if (sz == 0)
    {
      Mock.IO_Read_Return_Head = (ioData*)malloc(2*sizeof(ioData));
      if (!Mock.IO_Read_Return_Head)
        Mock.allocFailure++;
    }
    else
    {
      ioData *ptmp = (ioData*)realloc(Mock.IO_Read_Return_Head, sizeof(ioData) * (sz+1));
      if (!ptmp)
        Mock.allocFailure++;
      else
        Mock.IO_Read_Return_Head = ptmp;
    }
    memcpy(&Mock.IO_Read_Return_Head[sz], &toReturn, sizeof(ioData));
    Mock.IO_Read_Return_Tail = &Mock.IO_Read_Return_Head[sz+1];
  }
  Mock.IO_Read_Return = Mock.IO_Read_Return_Head;
  Mock.IO_Read_Return += Mock.IO_Read_CallCount;
}

void IO_Write(ioAddress offset, ioData data)
{

  Mock.IO_Write_CallCount++;
  if (Mock.IO_Write_CallCount > Mock.IO_Write_CallsExpected)
  {
    TEST_FAIL("Function 'IO_Write' called more times than expected");
  }

  if (Mock.IO_Write_Expected_offset != Mock.IO_Write_Expected_offset_Tail)
  {
    ioAddress* p_expected = Mock.IO_Write_Expected_offset;
    Mock.IO_Write_Expected_offset++;
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE((void*)p_expected, (void*)&(offset), sizeof(ioAddress), "Function 'IO_Write' called with unexpected value for argument 'offset'.");

  }

  if (Mock.IO_Write_Expected_data != Mock.IO_Write_Expected_data_Tail)
  {
    ioData* p_expected = Mock.IO_Write_Expected_data;
    Mock.IO_Write_Expected_data++;
    TEST_ASSERT_EQUAL_MEMORY_MESSAGE((void*)p_expected, (void*)&(data), sizeof(ioData), "Function 'IO_Write' called with unexpected value for argument 'data'.");

  }
}

void ExpectParameters_IO_Write(ioAddress offset, ioData data)
{

  {
    int sz = 0;
    ioAddress *pointer = Mock.IO_Write_Expected_offset_Head;
    while (pointer && pointer != Mock.IO_Write_Expected_offset_Tail) { sz++; pointer++; }
    if (sz == 0)
    {
      Mock.IO_Write_Expected_offset_Head = (ioAddress*)malloc(2*sizeof(ioAddress));
      if (!Mock.IO_Write_Expected_offset_Head)
        Mock.allocFailure++;
    }
    else
    {
      ioAddress *ptmp = (ioAddress*)realloc(Mock.IO_Write_Expected_offset_Head, sizeof(ioAddress) * (sz+1));
      if (!ptmp)
        Mock.allocFailure++;
      else
        Mock.IO_Write_Expected_offset_Head = ptmp;
    }
    memcpy(&Mock.IO_Write_Expected_offset_Head[sz], &offset, sizeof(ioAddress));
    Mock.IO_Write_Expected_offset_Tail = &Mock.IO_Write_Expected_offset_Head[sz+1];
  }
  Mock.IO_Write_Expected_offset = Mock.IO_Write_Expected_offset_Head;
  Mock.IO_Write_Expected_offset += Mock.IO_Write_CallCount;

  {
    int sz = 0;
    ioData *pointer = Mock.IO_Write_Expected_data_Head;
    while (pointer && pointer != Mock.IO_Write_Expected_data_Tail) { sz++; pointer++; }
    if (sz == 0)
    {
      Mock.IO_Write_Expected_data_Head = (ioData*)malloc(2*sizeof(ioData));
      if (!Mock.IO_Write_Expected_data_Head)
        Mock.allocFailure++;
    }
    else
    {
      ioData *ptmp = (ioData*)realloc(Mock.IO_Write_Expected_data_Head, sizeof(ioData) * (sz+1));
      if (!ptmp)
        Mock.allocFailure++;
      else
        Mock.IO_Write_Expected_data_Head = ptmp;
    }
    memcpy(&Mock.IO_Write_Expected_data_Head[sz], &data, sizeof(ioData));
    Mock.IO_Write_Expected_data_Tail = &Mock.IO_Write_Expected_data_Head[sz+1];
  }
  Mock.IO_Write_Expected_data = Mock.IO_Write_Expected_data_Head;
  Mock.IO_Write_Expected_data += Mock.IO_Write_CallCount;
}

void IO_Write_Expect(ioAddress offset, ioData data)
{
  Mock.IO_Write_CallsExpected++;
  ExpectParameters_IO_Write(offset, data);
}

