#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// define constants for the filename and maximum file length.
#define FILENAME "log.txt"
#define MAX_LENGTH_FILE 5000
#define NETWORK_ADDRESS_LENGTH 4
#define MAXDEVICE 20
#define MAXLENGTHREQID 100

const char *lineDelimiter = "\'\n\'";
const char *colonDelimiter = ":";
const char *commaDelimiter = ".";
const char outgoingReportToken[] = "\"cmd\":\"set\"";
const char networkAddressToken[] = "\"type\":\"switch\",\"data\":[\"zwave-";
const char requestDelimiter[] = "\"reqid\"";
// read the content of the file.
int filetoStr(char *str);
// Reverses the given string
void reverseString(char *str);
// The function calculates the number of reports that have been sent.
int countReportsHaveSent(char *fileStr);
// The function calculates the number of reports that have been sent from a
// pre-specified device
int countOutgoingReportFromDevice(char *networkAddress, char *fileStr);
// The function extract the number and address of swiches that have exchanged
// information with the central of controller.
int getAdressAndEndpointOfSwitch(
    char *fileStr, char networkIds[MAXDEVICE][NETWORK_ADDRESS_LENGTH],
    char enpointIds[MAXDEVICE][NETWORK_ADDRESS_LENGTH]);
// The function that calculates the number of error reports have been sent.
int countErrorReportsHaveSent(char *fileStr,
                              char requestIds[MAXDEVICE][MAXLENGTHREQID]);
// The function that find maximum delay between the outgoing report and the
// response report..
int findMaxResponseDelay(char *fileStr,
                         char requestIds[MAXDEVICE][MAXLENGTHREQID],
                         char timeString[MAXDEVICE][MAXLENGTHREQID]);
// the function that calculate average delay between the outgoing report and
// the response report.
int findAverageDelay(char *fileStr, char requestIds[MAXDEVICE][MAXLENGTHREQID],
                     char timeString[MAXDEVICE][MAXLENGTHREQID]);

int main() {
  char fileStr[MAX_LENGTH_FILE] = "";
  char inputNetworkAddress[MAX_LENGTH_FILE] = "";
  char networksID[MAXDEVICE][NETWORK_ADDRESS_LENGTH] = {0};
  char enpointIds[MAXDEVICE][NETWORK_ADDRESS_LENGTH] = {0};
  char requestID[MAXDEVICE][MAXLENGTHREQID] = {0};
  char timeString[MAXDEVICE][MAXLENGTHREQID] = {0};

  // Read file content into fileStr
  filetoStr(fileStr);
  //---------------------------------------------------------------------------------
  /* // Exercise 01 */
  /* // Process the file content and get the number of reports sent */
  /* int numberOutgoingReport = countReportsHaveSent(fileStr); */
  /* // Print the number of reports sent. */
  /* printf("The number of reports sent:%d\n", numberOutgoingReport); */

  //---------------------------------------------------------------------------------
  /* // Exercise 02 */
  /* printf("\nEnter network address:"); */
  /* scanf("%s", inputNetworkAddress); */
  /* getchar(); */
  /* printf("\nThe network address: %s", inputNetworkAddress); */
  /* int reportSentFromDevice = */
  /*     countOutgoingReportFromDevice(inputNetworkAddress, fileStr); */
  /* printf("\nThe numbers of report have been sent=: %d",
   * reportSentFromDevice); */

  //---------------------------------------------------------------------------------
  // Exercise 03
  /*
  int elementsNumber = getAdressAndEndpointOfSwitch(fileStr, networksID,
  enpointIds);
  // Print the network address and endpoint.
  for (int i = 0; i < elementsNumber; i++) {
    printf("\nThe device %d have the address:NWK: %s, ENDPOINT:%s\n", i,
           networksID[i], enpointIds[i]);
  };
*/
  //---------------------------------------------------------------------------------
  // Exercise 04
  int countErrorRequid = countErrorReportsHaveSent(fileStr, requestID);
  // Print total errors.
  printf("\n ERROR: %d", countErrorRequid);

  //---------------------------------------------------------------------------------
  // Exercise 05
  /*  int maxResponseDelays =
        findMaxResponseDelay(fileStr, requestID, timeString);
    printf("\nThe value of max delay equal: %d millisecond", maxResponseDelays);
    */
  //---------------------------------------------------------------------------------
  // Exercise 06
  /* int averageResponseDelays =
       findAverageDelay(fileStr, requestID, timeString);
   printf("\nAverage delay between reports:%d millisecond",
          averageResponseDelays);
         */
  //---------------------------------------------------------------------------------
  return 0;
}

int countReportsHaveSent(char *fileStr) {
  char file_Copy[MAX_LENGTH_FILE];
  int reportSentCount = 0;

  // Search for the occurrence of reportsSentIds in fileStr
  char *ptrFoundMsgSentId = strstr(fileStr, outgoingReportToken);

  // Iterate through all occurrences of reportsSentIds in fileStr
  while (ptrFoundMsgSentId != NULL) {
    // Reverse the found string
    reverseString(ptrFoundMsgSentId);

    // Calculate the length difference between the reversed found string and
    // reportsSentIds
    int lengthWithoutmsgSenIds =
        strlen(ptrFoundMsgSentId) - strlen(outgoingReportToken);

    // Copy the substring from the reversed found string to fileCpy
    strncpy(file_Copy, ptrFoundMsgSentId, lengthWithoutmsgSenIds);

    // Add '\0' to ensure the string terminated
    file_Copy[lengthWithoutmsgSenIds] = '\0';

    // Reverse the substring back to its original form
    reverseString(file_Copy);

    // Update the original found string with the modified substring
    strcpy(ptrFoundMsgSentId, file_Copy);

    // Search for the next occurrence of reportsSentIds
    ptrFoundMsgSentId = strstr(ptrFoundMsgSentId, outgoingReportToken);

    // Increment the reports sent count
    reportSentCount++;
  }

  return reportSentCount;
}

// .....................EXERCISE 2................................................
int countOutgoingReportFromDevice(char *networkAddress, char *fileStr) {

  int reportSentCount = 0;

  // Tokenize the fileStr and extract relevant information.
  char *token = strtok(fileStr, lineDelimiter);
  if (strstr(token, outgoingReportToken) && strstr(token, networkAddress)) {
    // Print token for debugging purposes.
    printf("\n%s", token);
    reportSentCount++;
  };

  // Continue tokenizing until the end of the fileStr.
  while (token != NULL) {
    // Tokenize the fileStr and extract relevant information.
    token = strtok(NULL, lineDelimiter);
    if (token != NULL && strstr(token, outgoingReportToken) &&
        strstr(token, networkAddress)) {
      printf("\n%s", token);
      reportSentCount++;
    };
  };
  return reportSentCount;
}

// .....................EXERCISE 3................................................
int getAdressAndEndpointOfSwitch(
    char *fileStr, char networkIds[MAXDEVICE][NETWORK_ADDRESS_LENGTH],
    char enpointIds[MAXDEVICE][NETWORK_ADDRESS_LENGTH]) {
  int elementCount = 0;
  char networkId[NETWORK_ADDRESS_LENGTH];
  char enpointId[NETWORK_ADDRESS_LENGTH];
  int lenOfNetworkAddressToken = strlen(networkAddressToken);

  // Tokenize the fileStr and extract relevant information.
  char *token = strtok(fileStr, lineDelimiter);
  // Print token for debugging purposes.
  printf("Token: %s\n", token);

  // Continue tokenizing until the end of the fileStr.
  while (token != NULL) {
    // Extract network address from network address id.
    char *netword_AddressToken = strstr(token, networkAddressToken);
    if (netword_AddressToken != NULL) {
      printf("type_Swich: %s\n", netword_AddressToken);
      // Get network address from network address token.
      strncpy(networkId, netword_AddressToken + lenOfNetworkAddressToken,
              NETWORK_ADDRESS_LENGTH);
      // Add'\0' to ensure the string terminated.
      networkId[NETWORK_ADDRESS_LENGTH - 1] = '\0';
      // Get device code from network address token
      strncpy(enpointId, netword_AddressToken + 38, 1);
      // Add'\0' to ensure the string terminated.
      enpointId[1] = '\0';
      // print network address and device for debugging purposes.
      printf("\n string: %s", networkId);
      printf("\n device code: %s", enpointId);
      int isNotNewDevice = 0;
      // Found new device.
      for (int i = 0; i < elementCount; i++) {
        if (strcmp(networkId, networkIds[i]) == 0 &&
            strcmp(enpointId, enpointIds[i]) == 0) {
          isNotNewDevice = 1;
          break;
        };
      };
      // Add network address and endpoint.
      if (!isNotNewDevice) {
        strcpy(networkIds[elementCount], networkId);
        strcpy(enpointIds[elementCount], enpointId);
        elementCount++;
      };
    }
    token = strtok(NULL, lineDelimiter);
  };

  return elementCount;
}

// .....................EXERCISE 4................................................
int countErrorReportsHaveSent(char *fileStr,
                              char requestIds[MAXDEVICE][MAXLENGTHREQID]) {
  int elementCount = 0;
  int errors_Count = 0;
  // Tokenize the fileStr and extract relevant information.
  char *reportToken = strtok(fileStr, lineDelimiter);
  // Continue tokenizing until the end of the fileStr.
  while (reportToken != NULL) {
    char *requestToken = strstr(reportToken, requestDelimiter);
    if (requestToken != NULL) {
      strncpy(requestIds[elementCount++], requestToken,
              strlen(requestToken) - 1);
    };
    reportToken = strtok(NULL, lineDelimiter);
  };

  // Print request IDs for debugging purposes.
  for (int i = 0; i < elementCount; i++) {
    printf("\nRequid[%d]= %s", i, requestIds[i]);
  };
  // Calculate total errors.
  for (int i = 0; i < elementCount; i += 2) {
    if (strcmp(requestIds[i], requestIds[i + 1]) != 0) {
      errors_Count++;
    };
  };
  return errors_Count;
}

// .....................EXERCISE 5................................................
int findMaxResponseDelay(char *fileStr,
                         char requestIds[MAXDEVICE][MAXLENGTHREQID],
                         char timeString[MAXDEVICE][MAXLENGTHREQID]) {
  int timeMilisecond[MAXLENGTHREQID];
  int max_Delay = 0;
  int elementCount = 0;

  // Tokenize the fileStr and extract relevant information.
  char *token = strtok(fileStr, lineDelimiter);
  // Get time from token and add it to the timeString array.
  strncpy(timeString[elementCount], token + 17, 12);
  // Add'\0' to ensure the string terminated.
  timeString[elementCount][12] = '\0';
  // Get request id from token and add it to the requestIds array.
  strncpy(requestIds[elementCount], token + strlen(token) - 6, 6);
  // Add'\0' to ensure the string terminated.
  requestIds[elementCount][6] = '\0';
  // Plus 1 to elementCount.
  elementCount++;

  // Continue tokenizing until the end of the fileStr
  while (token != NULL) {
    token = strtok(NULL, lineDelimiter);
    if (token != NULL) {
      strncpy(timeString[elementCount], token + 17, 12);
      timeString[elementCount][12] = '\0';
      strncpy(requestIds[elementCount], token + strlen(token) - 6, 6);
      requestIds[elementCount][6] = '\0';
      elementCount++;
    };
  };

  // Print time and request IDs for debugging purposes.
  for (int i = 0; i < elementCount; i++) {
    printf("\nTime[%d]= %s, requestIds[%d]=%s", i, timeString[i], i,
           requestIds[i]);
  };

  // Convert time strings to milliseconds.
  for (int i = 0; i < elementCount; i++) {
    char *time_Part = strtok(timeString[i], colonDelimiter);
    int hour = atoi(time_Part);
    time_Part = strtok(NULL, colonDelimiter);
    int minute = atoi(time_Part);
    time_Part = strtok(NULL, commaDelimiter);
    int second = atoi(time_Part);
    time_Part = strtok(NULL, commaDelimiter);
    int millisecond = atoi(time_Part);
    long total_milliseconds =
        hour * 3600 * 1000 + minute * 60 * 1000 + second * 1000 + millisecond;
    timeMilisecond[i] = total_milliseconds;
  };

  // Print time in milliseconds for debugging purposes.
  for (int i = 0; i < elementCount; i++) {
    printf("\ntimeMilisecond[%d]= %d", i, timeMilisecond[i]);
  };

  // Calculate max delay between reports.
  for (int i = 0; i < elementCount; i += 2) {
    if (strcmp(requestIds[i], requestIds[i + 1]) == 0) {
      int result = timeMilisecond[i + 1] - timeMilisecond[i];
      if (result > max_Delay) {
        max_Delay = result;
      };
    };
  };
  return max_Delay;
}

// .....................EXERCISE 6................................................
int findAverageDelay(char *fileStr, char requestIds[MAXDEVICE][MAXLENGTHREQID],
                     char timeString[MAXDEVICE][MAXLENGTHREQID]) {

  int timeMilisecond[MAXLENGTHREQID];
  int totalTime_Delay = 0;
  int matching_Count = 0;
  int averageDelays = 0;
  char *token;

  int elementCount = 0;

  // Tokenize the fileStr and extract relevant information.
  token = strtok(fileStr, lineDelimiter);
  // Get time from token and add it to the timeString array.
  strncpy(timeString[elementCount], token + 17, 12);
  // Add'\0' to ensure the string terminated.
  timeString[elementCount][12] = '\0';

  // Get request id from token and add it to the requestIds array.
  strncpy(requestIds[elementCount], token + strlen(token) - 6, 6);
  // Add'\0' to ensure the string terminated.
  requestIds[elementCount][6] = '\0';
  // Plus 1 to elementCount.
  elementCount++;

  // Continue tokenizing until the end of the fileStr
  while (token != NULL) {
    token = strtok(NULL, lineDelimiter);
    if (token != NULL) {
      strncpy(timeString[elementCount], token + 17, 12);
      timeString[elementCount][12] = '\0';
      strncpy(requestIds[elementCount], token + strlen(token) - 6, 6);
      requestIds[elementCount][6] = '\0';
      elementCount++;
    };
  };
  // Print time and request IDs for debugging purposes.
  for (int i = 0; i < elementCount; i++) {
    printf("\ntime[%d]= %s, requestIds[%d]=%s", i, timeString[i], i,
           requestIds[i]);
  };

  // Convert time strings to milliseconds.
  for (int i = 0; i < elementCount; i++) {
    char *time_Part = strtok(timeString[i], colonDelimiter);
    int hour = atoi(time_Part);
    time_Part = strtok(NULL, colonDelimiter);
    int minute = atoi(time_Part);
    time_Part = strtok(NULL, commaDelimiter);
    int second = atoi(time_Part);
    time_Part = strtok(NULL, commaDelimiter);
    int millisecond = atoi(time_Part);
    long total_Milliseconds =
        hour * 3600 * 1000 + minute * 60 * 1000 + second * 1000 + millisecond;
    timeMilisecond[i] = total_Milliseconds;
  };
  // Print time in milliseconds for debugging purposes.
  for (int i = 0; i < elementCount; i++) {
    printf("\ntimeMilisecond[%d]= %d", i, timeMilisecond[i]);
  };
  // Calculate the total and average delay between reports.

  for (int i = 0; i < elementCount; i += 2) {
    if (strcmp(requestIds[i], requestIds[i + 1]) == 0) {
      totalTime_Delay =
          totalTime_Delay + (timeMilisecond[i + 1] - timeMilisecond[i]);
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
  status = fread(str, MAX_LENGTH_FILE, 1, fp);
  // printf("Noi dung cua file log.txt: \n%s",
  //        str);   // in noi dung cua file log.txt ra cua so terminal
  fclose(fp);    // dong file
  fp = NULL;     // gan gia tri NULL cho con tro fp
  return status; // tra ve gia tri la status
};

void reverseString(char *str) {
  int length = strlen(str);
  int i, j;

  for (i = 0, j = length - 1; i < j; i++, j--) {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
};
