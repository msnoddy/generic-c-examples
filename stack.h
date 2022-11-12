#include <stdbool.h>

typedef struct
{
  size_t dataSize;
  void* data;
  int logicalLength;
  int dataLength;
} Stack;

Stack* newStack(size_t dataSize);

void pushStack(Stack* subject, void* data);

bool popStack(Stack* subject, void* output);

bool peekStack(Stack* subject, void* output);

void clearStack(Stack* subject);

void deleteStack(Stack* subject);
