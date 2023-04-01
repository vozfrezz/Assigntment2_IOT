
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "log.txt"
#define MAXLENGTHFILE 5000

char fileStr[MAXLENGTHFILE];
int filetoStr(char *str);

//---------------------------------------------------------------------------------//

int main() {
  filetoStr(fileStr);
  char filecpy[MAXLENGTHFILE];
  char request_Delimiters[] = "\"reqid\"";

  const char *line_Delimiters = "\'\n\'";

  char request_Ids[20][100];
  char requid_code[100];
  int elements_Count = 0;
  int errors_Count = 0;

  char *token = strtok(fileStr, line_Delimiters);
  if (token != NULL) {
    char *token_1 = strstr(token, request_Delimiters);
    if (token_1 != NULL) {
      strncpy(request_Ids[elements_Count++], token_1, strlen(token_1) - 1);
    };
  };
  while (token != NULL) {
    token = strtok(NULL, line_Delimiters);
    if (token != NULL) {
      char *token_2 = strstr(token, request_Delimiters);
      if (token_2 != NULL) {
        printf("\nrequest_Delimiters: %s\n", token_2);
        strncpy(requid_code, token_2, strlen(token_2) - 1);
        requid_code[strlen(token_2) - 1] = '\0';
      };
      strcpy(request_Ids[elements_Count++], requid_code);
    };
  };
  for (int i = 0; i < elements_Count; i++) {
    printf("\nRequid[%d]= %s", i, request_Ids[i]);
  };
  for (int i = 0; i < elements_Count; i += 2) {
    if (strcmp(request_Ids[i], request_Ids[i + 1]) != 0) {
      errors_Count++;
    };
  };
  printf("\n ERROR: %d", errors_Count);
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
