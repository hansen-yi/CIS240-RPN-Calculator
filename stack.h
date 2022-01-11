#include <stdbool.h>

typedef struct number_st {
  int top, bottom;
} number;

typedef struct stack_node_st {
  number val;
  struct stack_node_st *next;
} stack_node;

typedef struct Stack_st {
  stack_node *first, *second;
} Stack;

void stack_init(Stack *s);

void addToStack(Stack *s, int decimal);

int gcd(int num1, int num2);

number lcm(int num1, int num2);

bool add(Stack *s);

bool subtract(Stack *s);

bool multiply(Stack *s);

bool divide(Stack *s);

bool dup(Stack *s);

bool swap(Stack *s);

void print();

bool drop(Stack *s);

void clear(Stack *s);
