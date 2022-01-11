#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#define MAX_COMMAND_LENGTH 100

int main () {
  char input[MAX_COMMAND_LENGTH];
  int val;
  char op[MAX_COMMAND_LENGTH];
  char badOp [MAX_COMMAND_LENGTH];
  
  Stack theStack;
  stack_init(&theStack);
  
  while(1) {
  fgets (input, MAX_COMMAND_LENGTH, stdin);
  
  if (sscanf (input, "%d", &val) == 1) {
    addToStack(&theStack, val);
    printf("%d/%d\n", theStack.first->val.top, theStack.first->val.bottom); 
  }
  
  if (sscanf (input, "%s%s", op, badOp) == 1 && strcmp(op, "+")==0) {
    if (add(&theStack)){
      printf("%d/%d\n", theStack.first->val.top, theStack.first->val.bottom); 
    } else {
      printf("STACK ERROR\n");
    }
  }
  
  if (sscanf (input, "%s%s", op, badOp) == 1 && strcmp(op, "-")==0) {
    if (subtract(&theStack)) {
      printf("%d/%d\n", theStack.first->val.top, theStack.first->val.bottom); 
    } else {
      printf("STACK ERROR\n");
    }
  }
  
  if (sscanf (input, "%s%s", op, badOp) == 1 && strcmp(op, "*")==0) {
    if (multiply(&theStack)) {
      printf("%d/%d\n", theStack.first->val.top, theStack.first->val.bottom);
    } else {
      printf("STACK ERROR\n");
    }
  }
  
  if (sscanf (input, "%s%s", op, badOp) == 1 && strcmp(op, "/")==0) {
    if (divide(&theStack)) {
      printf("%d/%d\n", theStack.first->val.top, theStack.first->val.bottom); 
    } else {
      printf("STACK ERROR\n");
    }
  }
  
  if (sscanf (input, "%s%s", op, badOp) == 1 && strcasecmp(op, "dup")==0) {
    if (dup(&theStack)) {
      printf("%d/%d\n", theStack.first->val.top, theStack.first->val.bottom); 
    } else {
      printf("STACK ERROR\n");
    }
  }
  
  if (sscanf (input, "%s%s", op, badOp) == 1 && strcasecmp(op, "swap")==0) {
    if (swap(&theStack)) {
      printf("%d/%d\n", theStack.first->val.top, theStack.first->val.bottom); 
    } else {
      printf("STACK ERROR\n");
    }
  }
  
  if (sscanf (input, "%s%s", op, badOp) == 1 && strcmp(op, "quit")==0) {
    clear(&theStack);
    exit(EXIT_SUCCESS); 
  }
  
  if (sscanf (input, "%s%s", op, badOp) == 1 && strcasecmp(op, "drop")==0) {
    bool dropAttempt = drop(&theStack);
    if (dropAttempt && theStack.first != NULL) {
      printf("%d/%d\n", theStack.first->val.top, theStack.first->val.bottom);\
    } 
    if (!dropAttempt) {
      printf("STACK ERROR\n");
    } else {
    }
  }
  
  if (sscanf (input, "%s%s", op, badOp) == 1 && strcasecmp(op, "clear")==0) {
    clear(&theStack);
    if (theStack.first == NULL) {
    } else {
      printf("%d/%d\n", theStack.first->val.top, theStack.first->val.bottom); 
    }
  }
  if (sscanf (input, "%s%s", op, badOp) == 2 || sscanf (input, "%s%s", op, badOp) == 0 || (strcasecmp(op, "clear")!=0 && strcasecmp(op, "drop")!=0 && strcasecmp(op, "quit")!=0 && strcasecmp(op, "swap")!=0 && strcasecmp(op, "dup")!=0 && strcasecmp(op, "*")!=0 && strcasecmp(op, "/")!=0 && strcasecmp(op, "+")!=0 && strcasecmp(op, "-")!=0) && sscanf (input, "%d", &val) != 1) {
    printf("INVALID COMMAND\n");
  }
  }
}
