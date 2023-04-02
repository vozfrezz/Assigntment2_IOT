#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// define constants for the filename and maximum file length.
#define FILENAME "log.txt"
#define MAXLENGTHFILE 5000
// declare global variables.
char fileStr[MAXLENGTHFILE];
int filetoStr(char *str);
// Reverses the given string
void reverse_string(char *str);
//---------------------------------------------------------------------------------//

int main() {
  // Read file content into fileStr
  filetoStr(fileStr);

  char file_Copy[MAXLENGTHFILE];
  char messages_sentIds[] = "\"cmd\":\"set\"";
  int messageSent_Count = 0;

  // Search for the occurrence of messagesSentIds in fileStr
  char *str_search = strstr(fileStr, messages_sentIds);
  // Iterate through all occurrences of messagesSentIds in fileStr
  while (str_search != NULL) {
    // Reverse the found string
    reverse_string(str_search);
    // Calculate the length difference between the reversed found string and
    // messagesSentIds
    int num = strlen(str_search) - strlen(messages_sentIds);
    // Copy the substring from the reversed found string to fileCpy
    strncpy(file_Copy, str_search, num);
    // Add '\0' to ensure the string terminated.
    file_Copy[num] = '\0';
    // Reverse the substring back to its original form
    reverse_string(file_Copy);
    // Update the original found string with the modified substring
    strcpy(str_search, file_Copy);
    // Search for the next occurrence of messagesSentIds
    str_search = strstr(str_search, messages_sentIds);
    // Increment the messages sent count
    messageSent_Count++;
  };
  // Print the number of messages sent.
  printf("The number of messages sent:%d\n", messageSent_Count);
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

void reverse_string(char *str) {
  int length = strlen(str);
  int i, j;

  for (i = 0, j = length - 1; i < j; i++, j--) {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
};
