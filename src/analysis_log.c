#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "log.txt" // chi dinh dua gia tri chuoi "log.txt" vao FILENAME
#define MAXLENGTHFILE 5000 // kich thuoc mang gia tri 5000
// khong can su dung typedef de dinh nghia struc FILE FILE vi trong thu vien co
// roi

char fileStr[MAXLENGTHFILE]; // tao 1 mang co ten la fileStr kich thuong 5000
int filetoStr(char *str); // khai bao ham nguyen mau ten filetoStr voi tham so
                          // la 1 pointer dinh dang char co ten la

// void reverse_string(char *str);
//---------------------------------------------------------------------------------//

int main() {
  filetoStr(fileStr);
  char filecpy[MAXLENGTHFILE]; // declare an array to store the modified string
  char *str_destination =
      filecpy; // pointer to store an address of the filecpy array.
  char keyword[] = "\"cmd\":\"set\"";
  char *token;
  const char *delimiters = "\'\n\'";

  // printf("\n delemiters : %s",delimiters);

  char network_token[MAXLENGTHFILE] = "";
  /* printf("\nNhap ma network token:");
   scanf("%s", network_token);
   printf("\nchuoi network token la: %s", network_token);
 */
  //  int token_length = strlen(network_token);
  int numblock = 0;
  token = strtok(fileStr, delimiters);

  while (token != NULL) {

    token = strtok(NULL, delimiters);
    char *is_cmdset = strstr(token, keyword);
    char *is_networktoken = strstr(token, network_token);
    if (is_cmdset && is_networktoken) {

      printf("%s\n", token);
      numblock++;
    }

    printf("numblock=%d", numblock);
  }
  /* int count_loop = 0;
   char *str_search = strstr(fileStr, keyword);

   while (str_search != NULL) {
     reverse_string(str_search); // dao nguoc chuoi de thuc hien loai bo tu khoa
     printf("-----------------------------------------------------\n");
     printf("Start: Chuoi str_search reverse: %s\n", str_search); // check hang
     int num_str_search = strlen(str_search);
     int num_keyword = strlen(keyword);

     printf("num_str_search=:%d\n", num_str_search);
     printf("num_strkeyword=:%d\n", num_keyword);

     int num = strlen(str_search) - strlen(keyword); // tinh toan n phuc vu cho
     printf("n=: %d\n", num);

     strncpy(str_destination, str_search,
             num);                    // copy chuoi reverse de bo tu khoa
     str_destination[num] = '\0';     // Add null terminator
     reverse_string(str_destination); // reverse chuoi lan thu 2
     printf("Chuoi string moi la: %s\n", str_destination); // check hang xem

     strcpy(str_search, str_destination);
     printf("chuoi str_search moi:%s\n", str_search);

     // *str_destination = '\0';
     printf("check str_destination: %s\n", str_destination);
     str_search = strstr(str_search, keyword);

     printf("END: chuoi str_search moi:%s\n", str_search);
     printf("-----------------------------------------------------------\n");
     count_loop++;
   };

   printf("So lan lap:%d\n", count_loop);
   */
  return 0;
}

int filetoStr(char *str) {

  int status; // khoi tao 1 bien status co dang so nguyen

  FILE *fp = NULL; // khoi tao 1 bien con tro cau truc fp va gan gia tri ban dau
                   // la NULL

  fp = fopen(FILENAME,
             "r"); // mo file co ten la FILENAME hay 'log.txt' va mo o che do r
                   // "read only" va con tro fp se tro toi day.
                   //  dung fp de thuc hien doc va ghi du lieu
  if (fp == NULL) {
    printf("File does not exist\n"); // kiem tra neu fp == NULL thi tra ve ket
                                     // qua la file rong
    return -1;                       // tra ve gia tri la -1
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
