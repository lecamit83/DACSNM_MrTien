#ifndef _operatorstack_h_
#define _operatorstack_h_
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
struct OperatorStack {
  char* value;
  struct OperatorStack* next;
};

struct OperatorStack* create () {
  struct OperatorStack* s = NULL; 
  return s;
}

int isEmpty (struct OperatorStack* s) {
  return s == NULL;
}

char* pop(struct OperatorStack** s) {
  if(isEmpty(*s)) {
    return "$";
  }
  struct OperatorStack* node = *s;
  (*s) = (*s)->next;
  node->next = NULL;
  char* value = strdup(node->value);
  free(node);
  return value;
}

char* peek (struct OperatorStack* s) {
  if(isEmpty(s)) return "$";
  return s->value;
}

void push(struct OperatorStack** s, char* op) {
  struct OperatorStack* node = (struct OperatorStack*) malloc(sizeof(struct OperatorStack)); 
  struct OperatorStack* last = *s;
  node->value = strdup(op);
  node->next = last;
  *s = node;
}



void printOperatorStack (struct OperatorStack* s) {
  // check for OperatorStack underflow 
  while (s != NULL) { 
    printf("%s", s->value);
    // assign temp link to temp 
    s = s->next; 
  } 
  printf("\n");
}




#endif 