#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define constants for the filename and maximum file length.
#define FILENAME "log.txt"
#define MAXLENGTHFILE 5000
// declare 2 global variables.
char fileStr[MAXLENGTHFILE];
int filetoStr(char *str);

//---------------------------------------------------------------------------------//

int main() {
  // Read file log.txt
  filetoStr(fileStr);
  char filecpy[MAXLENGTHFILE];
  // Declare local variables and pointers for execution purposes.
  char time_Strings[10][100];
  int time_Milisecond[100];
  int max_Delay = 0;
  const char *line_Delimiters = "\'\n\'";

  char request_Ids[20][100];
  int elements_Count = 0;

  // Tokenize the fileStr and extract relevant information.
  char *token = strtok(fileStr, line_Delimiters);
  // Get time from token and add it to the time_Strings array.
  strncpy(time_Strings[elements_Count], token + 17, 12);
  // Add'\0' to ensure the string terminated.
  time_Strings[elements_Count][12] = '\0';
  // Get request id from token and add it to the request_Ids array.
  strncpy(request_Ids[elements_Count], token + strlen(token) - 6, 6);
  // Add'\0' to ensure the string terminated.
  request_Ids[elements_Count][6] = '\0';
  // Plus 1 to elements_Count.
  elements_Count++;

  // Continue tokenizing until the end of the fileStr
  while (token != NULL) {
    token = strtok(NULL, line_Delimiters);
    if (token != NULL) {
      strncpy(time_Strings[elements_Count], token + 17, 12);
      time_Strings[elements_Count][12] = '\0';
      strncpy(request_Ids[elements_Count], token + strlen(token) - 6, 6);
      request_Ids[elements_Count][6] = '\0';
      elements_Count++;
    };
  };

  // Print time and request IDs for debugging purposes.
  for (int i = 0; i < elements_Count; i++) {
    printf("\nTime[%d]= %s, request_Ids[%d]=%s", i, time_Strings[i], i,
           request_Ids[i]);
  };

  // Convert time strings to milliseconds.
  for (int i = 0; i < elements_Count; i++) {
    char *time_Part = strtok(time_Strings[i], ":");
    int hour = atoi(time_Part);
    time_Part = strtok(NULL, ":");
    int minute = atoi(time_Part);
    time_Part = strtok(NULL, ".");
    int second = atoi(time_Part);
    time_Part = strtok(NULL, ".");
    int millisecond = atoi(time_Part);
    long total_milliseconds =
        hour * 3600 * 1000 + minute * 60 * 1000 + second * 1000 + millisecond;
    time_Milisecond[i] = total_milliseconds;
  };

  // Print time in milliseconds for debugging purposes.
  for (int i = 0; i < elements_Count; i++) {
    printf("\ntime_Milisecond[%d]= %d", i, time_Milisecond[i]);
  };

  // Calculate max delay between messages.
  for (int i = 0; i < elements_Count; i += 2) {
    if (strcmp(request_Ids[i], request_Ids[i + 1]) == 0) {
      int result = time_Milisecond[i + 1] - time_Milisecond[i];
      if (result > max_Delay) {
        max_Delay = result;
      };
    };
  };
  // Print the value of max delay between messages.
  printf("\nThe value of max delay equal: %d millisecond", max_Delay);
  return 0;
};

int filetoStr(char *str) {

  int status; // khoi tao 1 bien status co dang so nguyen

  FILE *fp = NULL; // khoi tao 1 bien con tro cau truc fp va gan gia tri ban
                   // dau la NULL

  fp = fopen(FILENAME,
             "r"); // mo file co ten la FILENAME hay 'log.txt' va mo o che do
                   // r "read only" va con tro fp se tro toi day.
                   //  dung fp de thuc hien doc va ghi du lieu
  if (fp == NULL) {
    //   printf("File does not exist\n"); // kiem tra neu fp == NULL thi tra
    //   ve ket
    // qua la file rong
    return -1; // tra ve gia tri la -1
  }
  status = fread(str, MAXLENGTHFILE, 1, fp);
  // printf("Noi dung cua file log.txt: \n%s",
  //        str);   // in noi dung cua file log.txt ra cua so terminal
  fclose(fp);    // dong file
  fp = NULL;     // gan gia tri NULL cho con tro fp
  return status; // tra ve gia tri la status
};
