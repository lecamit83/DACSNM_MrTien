#ifndef _balan_h_
#define _balan_h_
#include "operatorstack.h"
#include "numberstack.h"
#include <math.h>

const int MAX_LENGTH = 63;
const int MAX_LENGTH_OPERATOR = 7;
const double MATH_PI = 3.14159265358979323846;
const int TRUE = 1;
const int FALSE = 0;

char* trimRegex(char * mathRegex) {
  return trim(mathRegex);
}
char* formatRegex(char* mathRegex) {
  char* result = malloc(MAX_LENGTH * sizeof(char));
  char* temp = malloc(MAX_LENGTH * sizeof(char));
  int index = 0;

  for (int i = 0; i < strlen(mathRegex); i++) {
    if(!isDigital(mathRegex[i])) {
      if(mathRegex[i] == ' ') continue;
      if(strlen(temp) != 0) { 
        strcat(result, temp);
        strcat(result, "#");
      }
      char *operator = malloc(MAX_LENGTH_OPERATOR * sizeof(char));
      operator[0] = mathRegex[i];
      if(isOperator(operator)) {
        strcat(result, operator);
        strcat(result, "#");
      } else {
        do {
          operator[strlen(operator)] = mathRegex[++i];
        } while(mathRegex[i] && !isOperator(operator));
        strcat(result, operator);
        strcat(result, "#");
      }
      // Reset temp
      for (index=0; index < MAX_LENGTH; index++) { temp[index] = '\0'; } 
      free(operator);
      index=0;
    } else {
      temp[index++] = mathRegex[i];
      if((i + 1) == strlen(mathRegex)) {
        strcat(result, temp);
        strcat(result, "#");
      }
    }
  }
  return result;
}

double doCalc(char* operator, double numberOne,  double numberTwo) {
  if(strcmp(operator,"*") == 0) {
    return numberOne * numberTwo;
  } 
  if(strcmp(operator,"/") == 0) {
    return numberOne / numberTwo;
  } 
  if(strcmp(operator,"-") == 0) {
    return numberOne - numberTwo;
  } 
  if(strcmp(operator,"+") == 0) {
    return numberOne + numberTwo;
  }
}

double doCalcOneOperand(char* operator, double a) {
  double val = MATH_PI * a / 180; 
  if(!strcmp(operator, "cos")) return cos(val);
  if(!strcmp(operator, "sin")) return sin(val);
  if(!strcmp(operator, "tan")) return tan(val);
  if(!strcmp(operator, "sqrt")) return sqrt(a);
  if(!strcmp(operator, "log")) return log10(a);
}

char** infixToPostfix(char * formatMath) {
  char ** math = split(formatMath, "#");
  const int len = length(math);
  printf("LEN: %d", len);
  for(size_t i = 0; i < len; i++) {
    printf("%s ", *(math + i));
  }
  printf("\n");
  // printf("CASM");
  char ** postfix = malloc (len * sizeof(char*));
  int index = 0;
  struct OperatorStack* s = create();
  for(int i = 0; i < len; i++) {
    // printOperatorStack(s);
    if(isOperator(*(math + i))) { 
      if (strcmp(*(math + i), "(") == 0) {
        push(&s, *(math + i));
        if(isOperator(*(math + i + 1)) && getPriority(*(math + i + 1)) == 2) {
          postfix[index++] = strdup("0");
        }
      } else if (strcmp(*(math + i), ")") == 0) {
        char* topToken = pop(&s);
        while (strcmp(topToken, "(") != 0) {
          postfix[index++] = strdup(topToken);
          topToken = pop(&s);
        }
      } else {
        while(!isEmpty(s) && (getPriority(peek(s)) >= getPriority(*(math + i)))) {
          postfix[index++] = strdup(pop(&s));
        }
        push(&s, *(math + i));
      }
    } else {
      postfix[index++] = strdup(*(math + i));
    }
  }
  free(s);
  postfix[index] = NULL;
  for(size_t i = 0; i < index; i++) {
    printf("%s ", postfix[i]);
  }
  printf("\n");
  return postfix;
}

double calc(char** postfix) {
  const int len = length(postfix);
  struct NumberStack* numberStack = createNumberStack();
  for(size_t i = 0; i < len; i++) { 
    if(!isOperator(*(postfix + i))) { 
      double atofNumber = atof(*(postfix + i));
      pushNumberStack(&numberStack, atofNumber); 
    } else {
      if(getOperands(*(postfix + i)) == 2) {
        double a = popNumberStack(&numberStack);
        double b = popNumberStack(&numberStack);
        double value = doCalc(*(postfix + i), b, a);
        pushNumberStack(&numberStack, value);
      } else {
        double a = popNumberStack(&numberStack);
        double value = doCalcOneOperand(*(postfix + i), a);
        pushNumberStack(&numberStack, value);
      }
      
    }
  }
  return popNumberStack(&numberStack);
}

double calculate(char * mathRegex) {
  char * trimMath = trimRegex(mathRegex);
  printf("TRIM: %s\n", trimMath);
  char * formatMath = formatRegex(trimMath);
  printf("FORMAT: %s\n", formatMath);
  char ** postfixString = infixToPostfix(formatMath);
  double result = calc(postfixString);
  return result;
}


#endif

