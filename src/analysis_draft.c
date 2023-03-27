#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reverse_string(char *str);

int main() {
  char arr[200] = "Hello viet nam viet viet viet viet";
  char text[200]; // khai bao mang text voi muc dich la luu chuoi copy
  char *str_destination = text; // tao bien con tro luu dia chi mang text[]
  char keytext[] = "viet";      // tu khoa can tim

  int solan_lap = 0;

  char *strsearch = strstr(arr, keytext);

  printf("Chuoi copy la: %s\n", strsearch); // kiem tra chuoi con in ra

  while (strsearch != NULL) {
    reverse_string(strsearch); // dao nguoc chuoi de thuc hien loai bo tu khoa
    printf("-----------------------------------------------------\n");
    printf("Start: Chuoi strsearch reverse: %s\n", strsearch); // check hang
    int num_strsearch = strlen(strsearch);
    int num_keytext = strlen(keytext);

    printf("num_strsearch=:%d\n", num_strsearch);
    printf("num_strkeytext=:%d\n", num_keytext);

    int num = strlen(strsearch) - strlen(keytext); // tinh toan n phuc vu cho
    printf("n=: %d\n", num);

    strncpy(str_destination, strsearch,
            num);                    // copy chuoi reverse de bo tu khoa
    str_destination[num] = '\0';     // Add null terminator
    reverse_string(str_destination); // reverse chuoi lan thu 2
    printf("Chuoi string moi la: %s\n", str_destination); // check hang xem

    strcpy(strsearch, str_destination);
    printf("chuoi strsearch moi:%s\n", strsearch);

    //*str_destination = '\0';
    printf("check str_destination: %s\n", str_destination);
    strsearch = strstr(strsearch, keytext);

    printf("END: chuoi strsearch moi:%s\n", strsearch);
    printf("-----------------------------------------------------------\n");
    solan_lap++;
  };

  printf("So lan lap:%d\n", solan_lap);
  return 0;
};

void reverse_string(char *str) {
  int length = strlen(str);
  int i, j;

  for (i = 0, j = length - 1; i < j; i++, j--) {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
}
