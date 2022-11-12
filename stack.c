#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "stack.h"

static const unsigned int STACK_INITIAL_SIZE = 10u;

static inline void raiseOutOfMemoryError()
{
  puts("ERROR: Out of Memory");
  exit(1);
}

Stack* newStack(size_t dataSize)
{
    Stack* newStack = malloc(sizeof(Stack));
    void* data = malloc(dataSize * STACK_INITIAL_SIZE);

    if (!newStack || !data)
    {
      raiseOutOfMemoryError();
    }

    newStack->dataSize = dataSize;
    newStack->data = data;
    newStack->logicalLength = 0u;
    newStack->dataLength = STACK_INITIAL_SIZE;

    return newStack; 
}

static inline void* getStackTop(Stack* subject)
{
  return (char*)subject->data + (subject->logicalLength * subject->dataSize) - subject->dataSize;
}

static inline void moveDataToNewBlock(Stack* subject, unsigned int newDataLength, size_t newDataBytes)
{
  void* newData = malloc(newDataBytes);

  if (!newData)
  {
    raiseOutOfMemoryError();
  }

  memcpy(newData, subject->data, subject->dataLength * subject->dataSize);
  free(subject->data);

  subject->data = newData;
  subject->dataLength = newDataLength;
}

static inline bool resizeDataBlock(Stack* subject, unsigned int newDataLength, size_t newDataBytes)
{
  void* resizedData = realloc(subject->data, newDataBytes);

  if (!resizedData)
  {
    return false;
  }

  subject->data = resizedData;
  subject->dataLength = newDataLength;

  return true;
}

static void doubleStackCapacity(Stack* subject)
{
  unsigned int newDataLength = subject->dataLength * 2;
  unsigned int newDataBytes = newDataLength * subject->dataSize;

  if (resizeDataBlock(subject, newDataLength, newDataBytes))
  {
    return;
  }

  moveDataToNewBlock(subject, newDataLength, newDataBytes);
}

void pushStack(Stack* subject, void* data)
{
  if (subject->logicalLength == subject->dataLength - 1)
  {
    doubleStackCapacity(subject);
  }

  void* newStackTop = getStackTop(subject) + subject->dataSize;

  memcpy(newStackTop, data, subject->dataSize);
  subject->logicalLength++;
}

bool popStack(Stack* subject, void* output)
{
  if (subject->logicalLength < 1) {
    return false;
  }

  memcpy(output, getStackTop(subject), subject->dataSize);

  subject->logicalLength--;

  return true;
}

bool peekStack(Stack* subject, void* output)
{
  if (subject->logicalLength < 1) {
    return false;
  }

  memcpy(output, getStackTop(subject), subject->dataSize);

  return true;
}

void clearStack(Stack* subject)
{
  size_t dataSize = subject->dataSize;

  deleteStack(subject);

  subject = newStack(dataSize);
}

void deleteStack(Stack* subject)
{
  free(subject->data);
  free(subject);

  subject = NULL;
}
