#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "log.txt" // chi dinh dua gia tri chuoi "log.txt" vao FILENAME
#define MAXLENGTHFILE 5000 // kich thuoc mang gia tri 5000

char fileStr[MAXLENGTHFILE]; // tao 1 mang co ten la fileStr kich thuong 5000
int filetoStr(char *str); // khai bao ham nguyen mau ten filetoStr voi tham so
                          // la 1 pointer dinh dang char co ten la

// void reverse_string(char *str);
//---------------------------------------------------------------------------------//

int main() {
  filetoStr(fileStr);
  char filecpy[MAXLENGTHFILE]; // declare an array to store the modified string
  char keyword[] = "\"cmd\":\"set\"";
  char type_id[] = "\"type\":\"switch\"";
  char *token;
  char *token_1;
  const char *delimiters = "\'\n\'";

  char network_id[100];
  char device_id[100];

  // printf("\n delemiters : %s",delimiters);

  char network_token[MAXLENGTHFILE] = "";
  token_1 = strtok(fileStr, delimiters);
  printf("Token: %s\n", token_1);
  token_1 = strstr(token_1, type_id);
  // token_1 = strtok(NULL, delimiters);
  // if (token_1 && strstr(token_1, type_id)) {
  printf("Token: %s\n", token_1);
  char *network_id_name = strstr(token_1, "zwave-");

  printf("Token: %s\n", network_id_name);

  char *token_2 = strtok(network_id_name, "\"]");

  printf("Token: %s\n", token_2);

  strncpy(network_id, token_2 + 6, 4);
  strncpy(device_id, token_2 + strlen(token_2) - 1, 1);
  // if (token_1 != NULL) {
  //};
  // };
  printf("\nnetwork: %s", network_id);
  printf("\ndevice: %s", device_id);
  /* while (token_1 != NULL) {
   };
   */

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

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
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
  reverse_string(arr);
  char text[100] = "future";
  char *str = arr;
  int num = strlen(arr) - strlen(text);
  printf("%u\n", num);
  // strcpy(str, text);

  reverse_string(arr);
  printf("%s\n", arr);
  return 0;
}*/
