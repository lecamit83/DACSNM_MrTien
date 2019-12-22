#ifndef _utils_h_
#define _utils_h_

#include <ctype.h>
char operators[13][7] = {"+", "-", "*", "/", "(", ")", "~", "sin", "cos", "tan", "sqrt", "log"};

char * readFile(const char * filename) {
  const int MAX_LENGTH = 63;
  char * data = malloc(sizeof(char) * MAX_LENGTH);
  int i = 0;
  char ch;
  FILE * fin = fopen(filename, "r");

  if (fin == NULL) {
    perror("Error while opening the file.\n");
    exit(0);
  }

  while((ch = fgetc(fin)) != EOF) {
    data[i] = ch;
    data[i + 1] = '\n';
    i += 1; 
  }
  fclose(fin);
  return data;
}

void writeFile(char* s ,const char * filename) {
  FILE * fout = fopen(filename, "w+");
  fputs(s, fout);
  fclose(fout);
}

char *trim(char *s) {
  while (isspace((unsigned char) *s)) s++;
  if (*s) {
    char *p = s;
    while (*p) p++;
    while (isspace((unsigned char) *(--p)));
    p[1] = '\0';
  }
  return s;
}

int isDigital(char c) {
  return c == '.' || (c >= '0' && c <= '9');
}

int isOperator(char* c) {
  for(int i = 0; i < 13; i++) {
    if(strcmp(operators[i], c) == 0) return 1;
  }
  return 0;
}

char** split(char * math, const char * c) {
  // printf("%d", counter);
  // printf("CHAR: %c\n", c[0]);
  char ** result;
  int counter = 0;
  char * str = malloc(strlen(math) * sizeof(char));
  char * temp = malloc(strlen(math) * sizeof(char));
  char * last_sharp = 0;
  strcpy(str, math);
  strcpy(temp, math);

  while(*temp) {
    if(c[0] == *temp) {
      counter += 1;
    }
    temp++;
  }

  
  result = malloc((counter + 1)*sizeof(char *));
  int index = 0;
  char* ptr = strtok(str, c);
	while (ptr != NULL)
	{
    result[index++] = strdup(ptr);
		ptr = strtok(NULL, c);
	}
  return result;
}

int length (char ** math) {
  int count = 0;
  while (*(math + count++));
  return count - 1;
}

int getPriority (char* operator) {
  if(
      !strcmp(operator, "cos") 
    || !strcmp(operator, "sin") 
    || !strcmp(operator, "tan") 
    || !strcmp(operator, "sqrt") 
    || !strcmp(operator, "log")) return 4;
  if(!strcmp(operator, "(") || !strcmp(operator, ")")) return 1;
  if(!strcmp(operator, "+") || !strcmp(operator, "-")) return 2;
  if(!strcmp(operator, "*") || !strcmp(operator, "/")) return 3;
  return 0;
}

int getOperands(char* operator) {
  if(
      !strcmp(operator, "cos") 
    || !strcmp(operator, "sin") 
    || !strcmp(operator, "tan") 
    || !strcmp(operator, "sqrt") 
    || !strcmp(operator, "log")) return 1;
  return 2;
}


// char operators[13][7] = {"+", "-", "*", "/", "(", ")", "~", "sin", "cos", "tan", "arcsin", "sqrt", "log"};
//(23424-(424324*2+3)+(4*(24-3)-(4-7))-(23423/(-34)))
#endif