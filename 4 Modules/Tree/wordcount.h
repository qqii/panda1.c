#ifndef WORDCOUNT_H
#define WORDCOUNT_H

typedef struct WordCount {
  char *word;
  long count;
} WordCount;

WordCount new_wc(char *word, long count);
void free_wc(WordCount wc);
int cmp_wc(WordCount a, WordCount b);
void print_wc(WordCount wc);

char *lowercase(char *string);

#endif