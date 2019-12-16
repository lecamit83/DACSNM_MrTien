#ifndef _numberstack_h_
#define _numberstack_h_
#include <stdlib.h>
#include <stdio.h>
struct NumberStack {
  double value;
  struct NumberStack * next;
};

struct NumberStack* createNumberStack () {
  struct NumberStack* s = NULL; 
  return s;
}

int isNumberStackEmpty (struct NumberStack* s) {
  return s == NULL;
}

double popNumberStack(struct NumberStack** s) {
  if(isNumberStackEmpty(*s)) {
    return 0.0;
  }
  struct NumberStack* node = *s;
  (*s) = (*s)->next;
  node->next = NULL;
  double value = node->value;
  free(node);
  return value;
}

double peekNumberStack (struct NumberStack* s) {
  if(isNumberStackEmpty(s)) return 0.0;
  return s->value;
}

void pushNumberStack(struct NumberStack** s, double v) {
  struct NumberStack* node = (struct NumberStack*) malloc(sizeof(struct NumberStack)); 
  struct NumberStack* last = *s;
  node->value = v;
  node->next = last;
  *s = node;
}

void printNumberStack (struct NumberStack* s) {
  while (s != NULL) { 
    printf("%lf", s->value);
    s = s->next; 
  } 
  printf("\n");
}



#endif