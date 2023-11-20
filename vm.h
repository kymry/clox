#ifndef clox_vm_h
#define clox_vm_h

#include "object.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

// represents a single ongoing function call. Each time a function is called one of these structs is created.
typedef struct {
  ObjFunction* function; // the function being called
  uint8_t* ip;
  Value* slots; // points into the VMs value stack at the first slot this function can use
} CallFrame;

typedef struct {
  CallFrame frames[FRAMES_MAX];
  int frameCount; // current height of the call frame stack

  Value stack[STACK_MAX];
  Value* stackTop;
  Table globals;
  Table strings;
  Obj* objects;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif
