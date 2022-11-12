#include <stdio.h>

#include "stack.h"

static inline void dumpStackInfo(Stack* stack)
{
  puts("---------------------------");
  printf("Stack logical length: %d\n", stack->logicalLength);
  printf("Stack data length:    %d\n", stack->dataLength);
  puts("---------------------------");
}

static inline void testStackClear(Stack* intStack)
{
  puts("-- Test: clearStack --");

  clearStack(intStack);

  dumpStackInfo(intStack);
}

static inline void testStackDelete(Stack* intStack)
{
  puts("-- Test: deleteStack --");

  deleteStack(intStack);
  puts("OK");
}

static inline void testStackPush(Stack* intStack)
{
  puts("-- Test: pushStack --");

  for (unsigned int i = 0u; i < 11u; i++)
  {
    int pushValue = i + 31;

    printf("Pushing value onto stack: %d\n", pushValue);
    pushStack(intStack, &pushValue);
  }

  dumpStackInfo(intStack);
}

static inline void testStackPeekPop(Stack* intStack)
{
  puts("-- Test: peekStack & popStack --");

  int stackValue;

  while(peekStack(intStack, &stackValue))
  {
    printf("Peeked value from stack: %d\n", stackValue);

    popStack(intStack, &stackValue);
    printf("Popped value from stack: %d\n", stackValue);
  }

  dumpStackInfo(intStack);
}

static inline Stack* testNewStack()
{
  puts("-- Test: newStack --");
  
  Stack* intStack = newStack(sizeof(int));

  dumpStackInfo(intStack);

  return intStack;
}

int main(int argc, const char* argv[])
{
  Stack* intStack = testNewStack();

  testStackPush(intStack);
  testStackPeekPop(intStack);
  testStackDelete(intStack);

  intStack = newStack(sizeof(int));

  testStackClear(intStack);

  return 0;
}
