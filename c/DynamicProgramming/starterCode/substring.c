/**
 * Starter code for Code Along on Longest Common Substring
 * using Dynamic Programming.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DPUtils.h"

int _debug = 0;

enum { TABULATION = 2, NO_TABULATION = 1 };

char *getSubstring(int max, int end, const char *str) {
  if(max <= 0 || end <= 0) {
    return NULL;
  }
  char *res = (char*)malloc((max + 1) * sizeof(char));
  if(!res) {
    fprintf(stderr, "Memory Allocation Failed\n");
    return NULL;
  }
  strncpy(res, str + end - max, max);
  res[max] = '\0';
  return res;
}

char *longest_common_substring_no_tabulation(const char *str_one,
                                             const char *str_two) {
  int l1 = strlen(str_one);
  int l2 = strlen(str_two);
  int max = 0;
  int end_index = 0;

  for(int i = 0; i < l1; i++) {
    for(int j = 0; j < l2; j++) {
      int k = 0;
      while(i + k < l1 && j + k < l2 && str_one[i + k] == str_two[j + k]) {
        k++;
      }
      if(k > max) {
        max = k;
        end_index = i + k;
      }
    }
  }

  return getSubstring(max, end_index, str_one);
}

char *longest_common_substring_with_tabulation(const char *str_one,
                                               const char *str_two) {
  int l1 = strlen(str_one);
  int l2 = strlen(str_two);
  int max = 0;
  int endIdx = 0;

  int tab[l1 + 1][l2 + 1];
  memset(tab, 0, sizeof(tab));

  for(int i = 1; i <= l1; i++) {
    for(int j = 1; j <= l2; j++) {
      if(str_one[i - 1] == str_two[j - 1]) {
        tab[i][j] = tab[i-1][j-1] + 1;
        if(tab[i][j] > max) {
          max = tab[i][j];
          endIdx = i;
        }
      }
    }
  }
  return getSubstring(max, endIdx, str_one);
}

int time_substring(char *(*func)(const char *, const char *),
                   const char *str_one, const char *str_two) {
  clock_t start = clock();
  char *result = func(str_one, str_two);
  clock_t end = clock();
  if (result) {
    printf("Longest common substring (length: %ld): %s\n", strlen(result),
           result);
  } else {
    printf("No common substring found.\n");
  }
  free(result); // Free the allocated memory for the substring
  return (int)(end - start);
}

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <string1> <string2>\n", argv[0]);
    return 1;
  }
  const char *str_one = argv[1];
  const char *str_two = argv[2];

  int type = NO_TABULATION | TABULATION; // Default to both methods
  if (argc > 3) {
    type = atoi(argv[3]);
    if (type < NO_TABULATION || type > TABULATION) {
      printf(
          "Error: Invalid type. Use %d for no tabulation, %d for tabulation, "
          "or %d for both.\n",
          NO_TABULATION, TABULATION, NO_TABULATION | TABULATION);
      return 1;
    }
  }

  if (argc > 4) {
    _debug = atoi(argv[3]);
  }

  if ((type & NO_TABULATION) == NO_TABULATION) {
    printf("Longest common substring without tabulation (m^2 * n)\n");
    int time_taken = time_substring(longest_common_substring_no_tabulation,
                                    str_one, str_two);
    printTimeTaken(time_taken);
  }
  if ((type & TABULATION) == TABULATION) {
    printf("Longest common substring with tabulation (m * n)\n");
    int time_taken_tabulation = time_substring(
        longest_common_substring_with_tabulation, str_one, str_two);
    printTimeTaken(time_taken_tabulation);
  }

  return 0;
}
