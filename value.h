#ifndef VALUE_H
#define VALUE_H

union Value {
  double number;
};

typedef union Value Value;

#define TO_VAL(num) ( (Value) { .number = ( num ) } )

void printValue(Value *val);

#endif