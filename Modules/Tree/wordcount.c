#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wordcount.h"

WordCount new_wc(char *word, long count) {
  char *lower = lowercase(word);
  WordCount wc = {
    .word = (char *) malloc((strlen(word) + 1) * sizeof(char)),
    .count = count
  };

  strcpy(wc.word, lower);

  free(lower);
  return wc;
}

int cmp_wc(WordCount a, WordCount b) {
  return strcmp(a.word, b.word);
}

void free_wc(WordCount wc) { 
  free(wc.word); 
}

void print_wc(WordCount wc) {
  printf("WordCount = {.word = \"%s\", .count = %ld}\n", wc.word, wc.count);
}

char *lowercase(char *string) {
  char *lowerstr = (char *)malloc((strlen(string) + 1) * sizeof(char));

  for (long i = 0; string[i] != '\0'; i++) {
    lowerstr[i] = tolower(string[i]);
  }

  lowerstr[strlen(string)] = '\0';

  return lowerstr;
}