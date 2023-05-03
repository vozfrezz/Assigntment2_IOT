#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// define constants for the filename and maximum file length.
#define FILENAME "log.txt"
#define MAX_LENGTH_FILE 5000
#define NETWORK_ADDRESS_LENGTH 4
#define MAX_REPORT 20
#define MAX_LEN_REQUID 100

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
    char *fileStr, char networkIds[MAX_REPORT][NETWORK_ADDRESS_LENGTH],
    char endpointIds[MAX_REPORT][NETWORK_ADDRESS_LENGTH]);
// The function that calculates the number of error reports have been sent.
int countErrorReportsHaveSent(char *fileStr,
                              char requestIds[MAX_REPORT][MAX_LEN_REQUID]);
// The function that find maximum delay between the outgoing report and the
// response report..
int findMaxResponseDelay(char *fileStr,
                         char requestIds[MAX_REPORT][MAX_LEN_REQUID],
                         char timeString[MAX_REPORT][MAX_LEN_REQUID]);
// The function that convert string time to integer millisecond.
long convertTimeStrToMilisecond(char timeString[]);
// the function that calculate average delay between the outgoing report and
// the response report.
int findAverageDelay(char *fileStr, char requestIds[MAX_REPORT][MAX_LEN_REQUID],
                     char timeString[MAX_REPORT][MAX_LEN_REQUID]);

int main() {
  char fileStr[MAX_LENGTH_FILE] = "";
  char inputNetworkAddress[MAX_LENGTH_FILE] = "";
  char networksID[MAX_REPORT][NETWORK_ADDRESS_LENGTH] = {0};
  char endpointIds[MAX_REPORT][NETWORK_ADDRESS_LENGTH] = {0};
  char requestID[MAX_REPORT][MAX_LEN_REQUID] = {0};
  char timeString[MAX_REPORT][MAX_LEN_REQUID] = {0};

  // Read file content into fileStr
  filetoStr(fileStr);
  //---------------------------------------------------------------------------------
  /* // Exercise 01 */
  /* // Process the file content and get the number of reports sent */
  /* int numberOutgoingReport = countReportsHaveSent(fileStr); */
  /* // Print the number of reports sent. */
  /* printf("The number of reports sent:%d\n", numberOutgoingReport); */

  //---------------------------------------------------------------------------------
  // Exercise 02
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
  /* int elementsNumber = */
  /*     getAdressAndEndpointOfSwitch(fileStr, networksID, endpointIds); */
  /* // Print the network address and endpoint. */
  /* for (int i = 0; i < elementsNumber; i++) { */
  /*   printf("\nThe device %d have the address:NWK: %s, ENDPOINT:%s", i, */
  /*          networksID[i], endpointIds[i]); */
  /* }; */

  //---------------------------------------------------------------------------------
  // Exercise 04
  /* int countErrorRequid = countErrorReportsHaveSent(fileStr, requestID); */
  /* // Print total errors. */
  /* printf("\n ERROR: %d", countErrorRequid); */

  //---------------------------------------------------------------------------------
  // Exercise 05
  /* int maxResponseDelays = findMaxResponseDelay(fileStr, requestID,
   * timeString); */
  /* printf("\nThe value of max delay equal: %d millisecond",
   * maxResponseDelays); */

  //---------------------------------------------------------------------------------
  // Exercise 06
  int averageResponseDelays = findAverageDelay(fileStr, requestID, timeString);
  printf("\nAverage delay between reports:%d millisecond",
         averageResponseDelays);

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
  char *report = strtok(fileStr, lineDelimiter);
  if (strstr(report, outgoingReportToken) && strstr(report, networkAddress)) {
    // Print report for debugging purposes.
    printf("\n%s", report);
    reportSentCount++;
  };

  // Continue reportizing until the end of the fileStr.
  while (report != NULL) {
    // Tokenize the fileStr and extract relevant information.
    report = strtok(NULL, lineDelimiter);
    if (report != NULL && strstr(report, outgoingReportToken) &&
        strstr(report, networkAddress)) {
      printf("\n%s", report);
      reportSentCount++;
    };
  };
  return reportSentCount;
}

// .....................EXERCISE 3................................................
int getAdressAndEndpointOfSwitch(
    char *fileStr, char networkIds[MAX_REPORT][NETWORK_ADDRESS_LENGTH],
    char endpointIds[MAX_REPORT][NETWORK_ADDRESS_LENGTH]) {
  int elementCount = 0;
  char networkId[NETWORK_ADDRESS_LENGTH];
  char enpointId[NETWORK_ADDRESS_LENGTH];
  int lenOfNetworkAddressToken = strlen(networkAddressToken);

  // Tokenize the fileStr and extract relevant information.
  char *report = strtok(fileStr, lineDelimiter);
  // Print report for debugging purposes.
  printf("Token: %s\n", report);

  // Continue reportizing until the end of the fileStr.
  while (report != NULL) {
    // Extract network address from network address id.
    char *netword_AddressToken = strstr(report, networkAddressToken);
    if (netword_AddressToken != NULL) {
      printf("Type swich: %s\n", netword_AddressToken);
      // Get network address from network address report.
      strncpy(networkId, netword_AddressToken + lenOfNetworkAddressToken,
              NETWORK_ADDRESS_LENGTH);
      // Add'\0' to ensure the string terminated.
      networkId[NETWORK_ADDRESS_LENGTH - 1] = '\0';
      // Get device code from network address report
      strncpy(enpointId, netword_AddressToken + 38, 1);
      // Add'\0' to ensure the string terminated.
      enpointId[1] = '\0';
      // print network address and device for debugging purposes.
      printf("\n Network address: %s", networkId);
      printf("\n Endpoints: %s", enpointId);
      int isNotNewDevice = 0;
      // Found new device.
      for (int i = 0; i < elementCount; i++) {
        if (strcmp(networkId, networkIds[i]) == 0 &&
            strcmp(enpointId, endpointIds[i]) == 0) {
          isNotNewDevice = 1;
          break;
        };
      };
      // Add network address and endpoint.
      if (!isNotNewDevice) {
        strcpy(networkIds[elementCount], networkId);
        strcpy(endpointIds[elementCount], enpointId);
        elementCount++;
      };
    }
    report = strtok(NULL, lineDelimiter);
  };

  return elementCount;
}

// .....................EXERCISE 4................................................
int countErrorReportsHaveSent(char *fileStr,
                              char requestIds[MAX_REPORT][MAX_LEN_REQUID]) {
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
                         char requestIds[MAX_REPORT][MAX_LEN_REQUID],
                         char timeString[MAX_REPORT][MAX_LEN_REQUID]) {
  int timeMilisecond[MAX_LEN_REQUID];
  int max_Delay = 0;
  int elementCount = 0;

  // Tokenize the fileStr and extract relevant information.
  char *report = strtok(fileStr, lineDelimiter);
  // Continue reportizing until the end of the fileStr
  while (report != NULL) {
    strncpy(timeString[elementCount], report + 17, 12);
    timeString[elementCount][12] = '\0';
    strncpy(requestIds[elementCount], report + strlen(report) - 6, 6);
    requestIds[elementCount][6] = '\0';
    elementCount++;
    report = strtok(NULL, lineDelimiter);
  };

  // Print time and request IDs for debugging purposes.
  for (int i = 0; i < elementCount; i++) {
    printf("\nTime[%d]= %s, requestIds[%d]=%s", i, timeString[i], i,
           requestIds[i]);
  };

  // Convert time strings to milliseconds.
  for (int i = 0; i < elementCount; i++) {
    timeMilisecond[i] = convertTimeStrToMilisecond(timeString[i]);
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

// Function that convert time string to integer milisecond.
long convertTimeStrToMilisecond(char timeString[]) {
  long totalMillisecond = 0;
  char *timePart = strtok(timeString, colonDelimiter);
  int hour = atoi(timePart);
  timePart = strtok(NULL, colonDelimiter);
  int minute = atoi(timePart);
  timePart = strtok(NULL, commaDelimiter);
  int second = atoi(timePart);
  timePart = strtok(NULL, commaDelimiter);
  int millisecond = atoi(timePart);
  totalMillisecond =
      hour * 3600 * 1000 + minute * 60 * 1000 + second * 1000 + millisecond;
  return totalMillisecond;
}

// .....................EXERCISE 6................................................
int findAverageDelay(char *fileStr, char requestIds[MAX_REPORT][MAX_LEN_REQUID],
                     char timeString[MAX_REPORT][MAX_LEN_REQUID]) {

  int timeMilisecond[MAX_LEN_REQUID];
  int totalTime_Delay = 0;
  int matching_Count = 0;
  int averageDelays = 0;
  int elementCount = 0;

  // Tokenize the fileStr and extract relevant information.
  char *report = strtok(fileStr, lineDelimiter);

  // Continue tokenizing until the end of the fileStr
  while (report != NULL) {
    // Get time from report and add it to the timeString array.
    strncpy(timeString[elementCount], report + 17, 12);
    // Add'\0' to ensure the string terminated.
    timeString[elementCount][12] = '\0';
    // Get request id from report and add it to the requestIds array.
    strncpy(requestIds[elementCount], report + strlen(report) - 6, 6);
    // Add'\0' to ensure the string terminated.
    requestIds[elementCount][6] = '\0';
    // Plus 1 to elementCount.
    elementCount++;
    report = strtok(NULL, lineDelimiter);
  };

  // Print time and request IDs for debugging purposes.
  for (int i = 0; i < elementCount; i++) {
    printf("\nTime[%d]= %s, requestIds[%d]=%s", i, timeString[i], i,
           requestIds[i]);
  };

  // Convert time strings to milliseconds.
  for (int i = 0; i < elementCount; i++) {
    timeMilisecond[i] = convertTimeStrToMilisecond(timeString[i]);
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
  averageDelays = totalTime_Delay / matching_Count;
  return averageDelays;
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
