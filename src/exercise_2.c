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
  // Declare local variables and pointers for execution purposes.
  char message_sentIds[] = "\"cmd\":\"set\"";
  const char *line_Delimiters = "\'\n\'";
  char network_Code[MAXLENGTHFILE] = "";
  int messageSent_Count = 0;

  printf("\nEnter network token:");
  scanf("%s", network_Code);
  printf("\nNetwork token: %s", network_Code);

  // Tokenize the fileStr and extract relevant information.
  char *token = strtok(fileStr, line_Delimiters);
  if (strstr(token, message_sentIds) && strstr(token, network_Code)) {
    // Print token for debugging purposes.
    printf("\n%s", token);
    messageSent_Count++;
  };

  // Continue tokenizing until the end of the fileStr.
  while (token != NULL) {
    // Tokenize the fileStr and extract relevant information.
    token = strtok(NULL, line_Delimiters);
    if (token != NULL && strstr(token, message_sentIds) &&
        strstr(token, network_Code)) {
      printf("\n%s", token);
      messageSent_Count++;
    };
  };

  printf("\nThe numbers of message sent=: %d", messageSent_Count);
  return 0;
};

int filetoStr(char *str) {

  int status; // khoi tao 1 bien status co dang so nguyen

  FILE *fp = NULL; // khoi tao 1 bien con tro cau truc fp va gan gia tri ban dau
                   // la NULL

  fp = fopen(FILENAME,
             "r"); // mo file co ten la FILENAME hay 'log.txt' va mo o che do r
                   // "read only" va con tro fp se tro toi day.
                   //  dung fp de thuc hien doc va ghi du lieu
  if (fp == NULL) {
    //   printf("File does not exist\n"); // kiem tra neu fp == NULL thi tra ve
    //   ket
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
