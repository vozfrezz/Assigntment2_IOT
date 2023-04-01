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
  char filecpy[MAXLENGTHFILE];
  char message_sentIds[] = "\"cmd\":\"set\"";
  char netword_AddressIds[] = "\"type\":\"switch\",\"data\":[\"zwave-";
  const char *delimiters = "\'\n\'";
  char network_Id[15][5];
  char device_Id[15][5];
  int elements_Count = 0;
  char network_IdCode[100];
  char device_IdCode[100];

  // Tokenize the fileStr and extract relevant information.
  char *token = strtok(fileStr, delimiters);
  // Print token for debugging purposes.
  printf("Token: %s\n", token);

  // Continue tokenizing until the end of the fileStr.
  while (token != NULL) {
    token = strtok(NULL, delimiters);
    if (token != NULL) {
      char *message_SentToken = strstr(token, message_sentIds);
      // Check if message sent token is not NULL.
      if (message_SentToken != NULL) {
        // Print message sent token for debugging purposes.
        printf("\ncmd_Set: %s\n", message_SentToken);
        // Extract network address from network address id.
        char *netword_AddressToken =
            strstr(message_SentToken, netword_AddressIds);
        if (netword_AddressToken != NULL) {
          printf("type_Swich: %s\n", netword_AddressToken);
          // Get network address from network adress token.
          strncpy(network_IdCode, netword_AddressToken + 31, 4);
          // Add'\0' to ensure the string terminated.
          network_IdCode[4] = '\0';
          // Get device code from network address token
          strncpy(device_IdCode, netword_AddressToken + 38, 1);
          // Add'\0' to ensure the string terminated.
          device_IdCode[1] = '\0';
          // print network address and device for debugging purposes.
          printf("\n string: %s", network_IdCode);
          printf("\n device code: %s", device_IdCode);
          int isNotNewDevice = 0;
          // Found new device.
          for (int i = 0; i < elements_Count; i++) {
            if (strcmp(network_IdCode, network_Id[i]) == 0 &&
                strcmp(device_IdCode, device_Id[i]) == 0) {
              isNotNewDevice = 1;
              break;
            };
          };
          // Add network address and endpoint.
          if (!isNotNewDevice) {
            strcpy(network_Id[elements_Count], network_IdCode);
            strcpy(device_Id[elements_Count], device_IdCode);
            elements_Count++;
          };
        }
      }
    };
  };
  // Print the network address and enpoint.
  for (int i = 0; i < elements_Count; i++) {
    printf("\nThiet bi %d co dia chi la:NWK: %s, ENDPOINT:%s\n", i,
           network_Id[i], device_Id[i]);
  };
  return 0;
};

// Function to read the content of a file and store it in the str variable.
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
