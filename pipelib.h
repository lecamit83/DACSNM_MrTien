#ifndef _pipelib_h_
#define _pipelib_h_

#include "utils.h"
#include "balan.h"

const int PIPE_READER_CODE = 0;
const int PIPE_WRITER_CODE = 1;
const int INPUT_LENGTH = 63;
const char DATA_INPUT_FILE[25] = "test.txt";
const char DATA_OUTPUT_FILE[25] = "result.txt";

void parentProcessing(int* fds) {
  char* inputString = malloc(sizeof(char) * INPUT_LENGTH);
  char outputString[INPUT_LENGTH];
  
  inputString = readFile(DATA_INPUT_FILE);
  // printf("INPUT: %s", inputString);
  // send 
  write(*(fds + PIPE_WRITER_CODE), inputString, INPUT_LENGTH);
  wait(NULL);
  read(*(fds + PIPE_READER_CODE), outputString, INPUT_LENGTH);
  // printf("OUTPUT: %s\n", outputString);
  close(*(fds + PIPE_READER_CODE));
  close(*(fds + PIPE_WRITER_CODE));

  writeFile(outputString, DATA_OUTPUT_FILE);
  exit(0);
}

void childProcessing(int* fds) {
  char pipeDataInput[INPUT_LENGTH];
  char pipeDataOutput[INPUT_LENGTH];

  read(*(fds + PIPE_READER_CODE), pipeDataInput, INPUT_LENGTH);
  // printf("%s", pipeDataInput);
  double rs = calculate(pipeDataInput);
  sprintf(pipeDataOutput, "%lf", rs);
  write(*(fds + PIPE_WRITER_CODE), pipeDataOutput, INPUT_LENGTH);
  
  close(*(fds + PIPE_READER_CODE));
  close(*(fds + PIPE_WRITER_CODE));
  exit(0);
}



#endif
