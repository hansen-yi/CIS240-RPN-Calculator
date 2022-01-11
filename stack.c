#include <stdio.h> 
#include <stdlib.h>
#include "stack.h"

void stack_init(Stack *s) {
  s->first = NULL;
  s->second = NULL;
}

void addToStack(Stack *s, int decimal) {
  stack_node *node = malloc(sizeof(stack_node));
  
  if (node == NULL) {
    printf("Couldn't allocate space for a new stack node\n");
    exit(EXIT_FAILURE);
  }
  
  node->next = NULL;
  node->val.top = decimal;
  node->val.bottom = 1;
  
  if (!s->first) {
    s->first = node;
  } else {
    s->second = s->first;
    s->first = node;
    s->first->next = s->second;
  }
}

int gcd(int num1, int num2) {
  if (num1 < 0 ) {
    num1 = -1 * num1;
  }
  if (num2 < 0 ) {
    num2 = -1 * num2;
  }
  
  int larger, smaller;
  if (num1 > num2) {
    larger = num1;
    smaller = num2;
  }
  if (num2 > num1) {
    larger = num2;
    smaller = num1;
  }
  if (num1 == num2) {
    return num1;
  } else {
    return gcd(larger-smaller, smaller);
  }
  
}

number lcm(int num1, int num2) {
  int gcf = gcd(num1, num2);
  int m = (num1 * num2) / gcf;
  number mul;
  mul.top = m / num1;
  mul.bottom = m / num2;
  return mul;
}

bool add(Stack *s) {
  if (!s->second) {
    return false;
  }
  int ft = s->first->val.top;
  int fb = s->first->val.bottom;
  int st = s->second->val.top;
  int sb = s->second->val.bottom;
  drop(s);
  drop(s);
  number multiples = lcm(fb, sb);
  int sol_top = (ft * multiples.top) + (st * multiples.bottom);
  int sol_bot = (fb * multiples.top);
  int gcf;
  
  if (sol_top < 0 && sol_bot < 0) {
    gcf = gcd(-sol_top, -sol_bot);
  }
  if (sol_top < 0) {
    gcf = gcd(-sol_top, sol_bot);
  }
  if (sol_bot < 0) {
    gcf = gcd(sol_top, -sol_bot);
    int psoltop = -1 * sol_top;
    int psolbot = -1 * sol_bot;
    sol_top = psoltop;
    sol_bot = psolbot;
  }
  if (sol_top > 0 && sol_bot >0 ) {
    gcf = gcd(sol_top, sol_bot);
  }
  
  if (sol_top == 0) {
    sol_bot = 1;
    gcf = 1;
  }
  
  number sol;
  sol.top = sol_top / gcf;
  sol.bottom = sol_bot / gcf;
  
  addToStack(s, 0);
  s->first->val=sol;
  return true;
}

bool subtract(Stack *s) {
  if (!s->second) {
    return false;
  }
  int ft = s->first->val.top;
  int fb = s->first->val.bottom;
  int st = s->second->val.top;
  int sb = s->second->val.bottom;
  drop(s);
  drop(s);
  number multiples = lcm(fb, sb);
  int sol_top = -(ft * multiples.top) + (st * multiples.bottom);
  int sol_bot = (fb * multiples.top);
  int gcf;
  if (sol_top < 0) {
    gcf = gcd(-sol_top, sol_bot);
  }
  if (sol_top > 0) {
    gcf = gcd(sol_top, sol_bot);
  }
  
  if (sol_top == 0) {
    sol_bot = 1;
    gcf = 1;
  }
  
  number sol;
  sol.top = sol_top / gcf;
  sol.bottom = sol_bot / gcf;
  
  addToStack(s, 0);
  s->first->val=sol;
  return true;
}

bool multiply(Stack *s) {
  if (!s->second) {
    return false;
  }
  int ft = s->first->val.top;
  int fb = s->first->val.bottom;
  int st = s->second->val.top;
  int sb = s->second->val.bottom;
  int sol_top = ft * st;
  int sol_bot = fb * sb;
  int gcf;
  if (ft!=0 && st!=0) {
    gcf = gcd(sol_top, sol_bot);
  }
  if (ft == 0 || st == 0) {
    gcf = 1;
    sol_bot = 1;
  }
  drop(s);
  drop(s);
  
  number sol;
  sol.top = sol_top / gcf;
  sol.bottom = sol_bot / gcf;
  addToStack(s, 0);
  s->first->val=sol;
  return true;
}
  

bool divide(Stack *s) {
  if (!s->second) {
    return false;
  }
  if (s->first->val.top == 0) {
    clear(s);
    printf("DIVIDE BY ZERO\n");
    exit(EXIT_FAILURE);
  }
  int ft = s->first->val.top;
  int fb = s->first->val.bottom;
  int st = s->second->val.top;
  int sb = s->second->val.bottom;
  int sol_top = fb * st;
  int sol_bot = ft * sb;
  int gcf;
  if (sol_top < 0 && sol_bot < 0) {
    int psoltop = -1 * sol_top;
    int psolbot = -1 * sol_bot;
    gcf = gcd(psoltop, psolbot);
    sol_top = psoltop;
    sol_bot = psolbot;
  }
  if (sol_top < 0) {
    gcf = gcd(-sol_top, sol_bot);
  }
  if (sol_bot < 0) {
    gcf = gcd(sol_top, -sol_bot);
    int psoltop = -1 * sol_top;
    int psolbot = -1 * sol_bot;
    sol_top = psoltop;
    sol_bot = psolbot;
  }
  
  if (ft!=0 && st!=0) {
    gcf = gcd(sol_top, sol_bot);
  }
  if (ft == 0 || st == 0) {
    gcf = 1;
    sol_bot = 1;
  }
  drop(s);
  drop(s);
  number sol;
  sol.top = sol_top / gcf;
  sol.bottom = sol_bot / gcf;
  
  addToStack(s, 0);
  s->first->val=sol;
  return true;
}

bool dup(Stack *s) {
  if (!s->first) {
    return false;
  }
  number toDup = s->first->val;
  addToStack(s, 0);
  s->first->val = toDup;
  return true;
}

bool swap(Stack *s) {
  if (!s->second) {
    return false;
  }
  stack_node* third = s->second->next;
  stack_node* storedFirst = s->first;
  s->first = s->second;
  s->first->next = storedFirst;
  s->second = storedFirst;
  s->second->next = third;
  return true;
}


void print(Stack *s) {
  stack_node *curr = s->first;
  printf("\nStack CONTAINS: ");
  while(curr) {
    printf("%d/%d, ", curr->val.top, curr->val.bottom);
    curr = curr->next;
  }
  printf(".\n");
}

bool drop(Stack *s) {
  if (!s->first) {
    return false;
  }
  stack_node* newFirst;
  stack_node* newSec;
  if (!s->second) {
    newFirst = NULL;
    newSec = NULL;
  } else {
    newFirst = s->second;
    newSec = s->second->next;
  }
  free(s->first);
  s->first=newFirst;
  s->second=newSec;
  return true;
}

void clear(Stack *s) {
  while(drop(s));
}
