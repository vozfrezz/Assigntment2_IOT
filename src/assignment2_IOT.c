#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// define constants for the filename and maximum file length.
#define FILENAME "log.txt"
#define MAXLENGTHFILE 5000
#define IDLENGTH 5
#define MAXDEVICE 20
#define MAXLENGTHREQID 100

const char *line_Delimiters = "\'\n\'";
const char *colon_Delimiters = ":";
const char *comma_Delimiters = ".";
const char message_sentIds[] = "\"cmd\":\"set\"";
// read the content of the file.
int filetoStr(char *str);
// Reverses the given string
void reverse_string(char *str);
// The function calculates the number of messages that have been sent.
int calculateMessage(char *fileStr);
// The function calculates the number of messages that have been sent from a
// pre-specified device
int countSentMessagesFromDevice(char *network_Code, char *fileStr);
// The function extract the number and adress of swiches that have exchanged
// information with the central of controller.
int extractDeviceInfo(char *fileStr, char network_Id[MAXDEVICE][IDLENGTH],
                      char device_Id[MAXDEVICE][IDLENGTH]);
// The function that calculates the number of error messages have been sent.
int countErroredSentMessages(char *fileStr,
                             char request_Ids[MAXDEVICE][MAXLENGTHREQID]);
// The function that find maximum delay between the outgoing message and the
// response message..
int findMaxResponseDelay(char *fileStr,
                         char request_Ids[MAXDEVICE][MAXLENGTHREQID],
                         char time_Strings[MAXDEVICE][MAXLENGTHREQID]);
// the function that calculate average delay between the outgoing message and
// the response message.
int findAverageDelay(char *fileStr, char request_Ids[MAXDEVICE][MAXLENGTHREQID],
                     char time_Strings[MAXDEVICE][MAXLENGTHREQID]);

int main() {
  char fileStr[MAXLENGTHFILE];
  char deviceID[MAXLENGTHFILE] = "";
  char network_Id[MAXDEVICE][IDLENGTH];
  char device_Id[MAXDEVICE][IDLENGTH];
  char requid_Id[MAXDEVICE][MAXLENGTHREQID];
  char time_Strings[MAXDEVICE][MAXLENGTHREQID];

  // Read file content into fileStr
  filetoStr(fileStr);

  //---------------------------------------------------------------------------------
  // Exercise 01
  // Process the file content and get the number of messages sent
  int messageSent_Count = calculateMessage(fileStr);

  // Print the number of messages sent.
  printf("The number of messages sent:%d\n", messageSent_Count);

  //---------------------------------------------------------------------------------
  // Exercise 02
  /* printf("\nEnter network token:");
   scanf("%s", deviceID);
   getchar();
   printf("\nNetwork token: %s", deviceID);
   int messageSentFromDevice = countSentMessagesFromDevice(deviceID, fileStr);
   printf("\nThe numbers of message sent=: %d", messageSentFromDevice);
 */
  //---------------------------------------------------------------------------------
  // Exercise 03
  /*
  int elementsNumber = extractDeviceInfo(fileStr, network_Id, device_Id);
  // Print the network address and enpoint.
  for (int i = 0; i < elementsNumber; i++) {
    printf("\nThe device %d have the address:NWK: %s, ENDPOINT:%s\n", i,
           network_Id[i], device_Id[i]);
  };
*/
  //---------------------------------------------------------------------------------
  // Exercise 04
  /*int countErrorRequid = countErroredSentMessages(fileStr, requid_Id);
  // Print total errors.
  printf("\n ERROR: %d", countErrorRequid);
*/
  //---------------------------------------------------------------------------------
  // Exercise 05
  /*  int maxResponseDelays =
        findMaxResponseDelay(fileStr, requid_Id, time_Strings);
    printf("\nThe value of max delay equal: %d millisecond", maxResponseDelays);
    */
  //---------------------------------------------------------------------------------
  // Exercise 06
  /* int averageResponseDelays =
       findAverageDelay(fileStr, requid_Id, time_Strings);
   printf("\nAverage delay between messages:%d millisecond",
          averageResponseDelays);
         */
  //---------------------------------------------------------------------------------
  return 0;
}

int calculateMessage(char *fileStr) {
  char file_Copy[MAXLENGTHFILE];
  int messageSent_Count = 0;

  // Search for the occurrence of messagesSentIds in fileStr
  char *str_search = strstr(fileStr, message_sentIds);

  // Iterate through all occurrences of messagesSentIds in fileStr
  while (str_search != NULL) {
    // Reverse the found string
    reverse_string(str_search);

    // Calculate the length difference between the reversed found string and
    // messagesSentIds
    int num = strlen(str_search) - strlen(message_sentIds);

    // Copy the substring from the reversed found string to fileCpy
    strncpy(file_Copy, str_search, num);

    // Add '\0' to ensure the string terminated
    file_Copy[num] = '\0';

    // Reverse the substring back to its original form
    reverse_string(file_Copy);

    // Update the original found string with the modified substring
    strcpy(str_search, file_Copy);

    // Search for the next occurrence of messagesSentIds
    str_search = strstr(str_search, message_sentIds);

    // Increment the messages sent count
    messageSent_Count++;
  }

  return messageSent_Count;
}

int countSentMessagesFromDevice(char *network_Code, char *fileStr) {

  int messageSent_Count = 0;

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
  return messageSent_Count;
}

// exercise 3.............................................................

int extractDeviceInfo(char *fileStr, char network_Id[MAXDEVICE][IDLENGTH],
                      char device_Id[MAXDEVICE][IDLENGTH]) {
  char filecpy[MAXLENGTHFILE];
  char netword_AddressIds[] = "\"type\":\"switch\",\"data\":[\"zwave-";
  int elements_Count = 0;
  char network_IdCode[IDLENGTH];
  char device_IdCode[IDLENGTH];

  // Tokenize the fileStr and extract relevant information.
  char *token = strtok(fileStr, line_Delimiters);
  // Print token for debugging purposes.
  printf("Token: %s\n", token);

  // Continue tokenizing until the end of the fileStr.
  while (token != NULL) {
    token = strtok(NULL, line_Delimiters);
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

  return elements_Count;
}

//.......................................................................
int countErroredSentMessages(char *fileStr,
                             char request_Ids[MAXDEVICE][MAXLENGTHREQID]) {
  char request_Delimiters[] = "\"reqid\"";
  char requid_code[MAXLENGTHREQID];
  int elements_Count = 0;
  int errors_Count = 0;
  // Tokenize the fileStr and extract relevant information.
  char *token = strtok(fileStr, line_Delimiters);
  if (token != NULL) {
    char *token_1 = strstr(token, request_Delimiters);
    if (token_1 != NULL) {
      strncpy(request_Ids[elements_Count++], token_1, strlen(token_1) - 1);
    };
  };

  // Continue tokenizing until the end of the fileStr.
  while (token != NULL) {
    token = strtok(NULL, line_Delimiters);
    if (token != NULL) {
      char *token_2 = strstr(token, request_Delimiters);
      if (token_2 != NULL) {
        // printf("\nrequest_Delimiters: %s\n", token_2);
        strncpy(requid_code, token_2, strlen(token_2) - 1);
        requid_code[strlen(token_2) - 1] = '\0';
      };
      strcpy(request_Ids[elements_Count++], requid_code);
    };
  };

  // Print request IDs for debugging purposes.
  for (int i = 0; i < elements_Count; i++) {
    printf("\nRequid[%d]= %s", i, request_Ids[i]);
  };
  // Calculate total errors.
  for (int i = 0; i < elements_Count; i += 2) {
    if (strcmp(request_Ids[i], request_Ids[i + 1]) != 0) {
      errors_Count++;
    };
  };
  return errors_Count;
}
//.......................................................................

int findMaxResponseDelay(char *fileStr,
                         char request_Ids[MAXDEVICE][MAXLENGTHREQID],
                         char time_Strings[MAXDEVICE][MAXLENGTHREQID]) {
  int time_Milisecond[MAXLENGTHREQID];
  int max_Delay = 0;
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
    char *time_Part = strtok(time_Strings[i], colon_Delimiters);
    int hour = atoi(time_Part);
    time_Part = strtok(NULL, colon_Delimiters);
    int minute = atoi(time_Part);
    time_Part = strtok(NULL, comma_Delimiters);
    int second = atoi(time_Part);
    time_Part = strtok(NULL, comma_Delimiters);
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
  return max_Delay;
}

//.......................................................................
int findAverageDelay(char *fileStr, char request_Ids[MAXDEVICE][MAXLENGTHREQID],
                     char time_Strings[MAXDEVICE][MAXLENGTHREQID]) {

  int time_Milisecond[MAXLENGTHREQID];
  int totalTime_Delay = 0;
  int matching_Count = 0;
  int averageDelays = 0;
  char *token;

  int elements_Count = 0;

  // Tokenize the fileStr and extract relevant information.
  token = strtok(fileStr, line_Delimiters);
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
    printf("\ntime[%d]= %s, request_Ids[%d]=%s", i, time_Strings[i], i,
           request_Ids[i]);
  };

  // Convert time strings to milliseconds.
  for (int i = 0; i < elements_Count; i++) {
    char *time_Part = strtok(time_Strings[i], colon_Delimiters);
    int hour = atoi(time_Part);
    time_Part = strtok(NULL, colon_Delimiters);
    int minute = atoi(time_Part);
    time_Part = strtok(NULL, comma_Delimiters);
    int second = atoi(time_Part);
    time_Part = strtok(NULL, comma_Delimiters);
    int millisecond = atoi(time_Part);
    long total_Milliseconds =
        hour * 3600 * 1000 + minute * 60 * 1000 + second * 1000 + millisecond;
    time_Milisecond[i] = total_Milliseconds;
  };
  // Print time in milliseconds for debugging purposes.
  for (int i = 0; i < elements_Count; i++) {
    printf("\ntime_Milisecond[%d]= %d", i, time_Milisecond[i]);
  };
  // Calculate the total and average delay between messages.

  for (int i = 0; i < elements_Count; i += 2) {
    if (strcmp(request_Ids[i], request_Ids[i + 1]) == 0) {
      totalTime_Delay =
          totalTime_Delay + (time_Milisecond[i + 1] - time_Milisecond[i]);
      matching_Count++;
    };
  };
  return averageDelays = totalTime_Delay / matching_Count;
}

// Function to read the content of a file and store it in the str variable.
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
