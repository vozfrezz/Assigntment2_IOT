#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "log.txt" // chi dinh dua gia tri chuoi "log.txt" vao FILENAME
#define MAXLENGTHFILE 5000 // kich thuoc mang gia tri 5000

char fileStr[MAXLENGTHFILE]; // tao 1 mang co ten la fileStr kich thuong 5000
int filetoStr(char *str); // khai bao ham nguyen mau ten filetoStr voi tham so

int main() {
  filetoStr(fileStr);
  char filecpy[MAXLENGTHFILE]; // declare an array to store the modified string
  char *token;
  char time_Strings[10][100];

  int time_Milisecond[100];
  int totalTime_Delay = 0;
  int matching_Count = 0;
  const char *line_Delimiters = "\'\n\'";

  char request_Ids[20][100];
  int elements_Count = 0;

  token = strtok(fileStr, line_Delimiters);
  strncpy(time_Strings[elements_Count], token + 17, 12);
  time_Strings[elements_Count][12] = '\0';
  strncpy(request_Ids[elements_Count], token + strlen(token) - 6, 6);
  request_Ids[elements_Count][6] = '\0';
  elements_Count++;
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
  for (int i = 0; i < elements_Count; i++) {
    printf("\ntime[%d]= %s, request_Ids[%d]=%s", i, time_Strings[i], i,
           request_Ids[i]);
  };

  for (int i = 0; i < elements_Count; i++) {
    char *time_Part = strtok(time_Strings[i], ":");
    int hour = atoi(time_Part);
    time_Part = strtok(NULL, ":");
    int minute = atoi(time_Part);
    time_Part = strtok(NULL, ".");
    int second = atoi(time_Part);
    time_Part = strtok(NULL, ".");
    int millisecond = atoi(time_Part);
    long total_Milliseconds =
        hour * 3600 * 1000 + minute * 60 * 1000 + second * 1000 + millisecond;
    time_Milisecond[i] = total_Milliseconds;
  };

  for (int i = 0; i < elements_Count; i++) {
    printf("\ntime_Milisecond[%d]= %d", i, time_Milisecond[i]);
  }
  for (int i = 0; i < elements_Count; i += 2) {
    if (strcmp(request_Ids[i], request_Ids[i + 1]) == 0) {
      totalTime_Delay =
          totalTime_Delay + (time_Milisecond[i + 1] - time_Milisecond[i]);
      matching_Count++;
    };
  };
  printf("\nTotal delay betwwen messages: %d millisecond", totalTime_Delay);
  printf("\nAverage delay between messages:%d millisecond",
         (totalTime_Delay / matching_Count));
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

void reverse_String(char *str) {
  int length = strlen(str);
  int i, j;

  for (i = 0, j = length - 1; i < j; i++, j--) {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
};

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_String(char *str) {
  int length = strlen(str);
  int i, j;

  for (i = 0, j = length - 1; i < j; i++, j--) {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
}
*//*
int main() {
  char arr[100] = "Hello viet nam";
  reverse_String(arr);
  char text[100] = "future";
  char *str = arr;
  int num = strlen(arr) - strlen(text);
  printf("%u\n", num);
  // strcpy(str, text);

  reverse_String(arr);
  printf("%s\n", arr);
  return 0;
}*/
