
#include <stdio.h>
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

int main() {
  char arr[100] = "Hello viet nam";
  reverse_string(arr);
  /* char text[100] = "future";
  char *str = arr;
  int num = strlen(arr) - strlen(text);
  printf("%u\n", num);
  // strcpy(str, text);

*/
  reverse_string(arr);
  printf("%s\n", arr);
  return 0;
}
