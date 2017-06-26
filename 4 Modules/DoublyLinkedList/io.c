// Implimentation for IO functions.

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

// Reads from an entire FILE pointer to a pointer to a null terminated character array.
// This functions closes the FILE since the entire contents are returned.
char *read(FILE *in) {
  char *buffer;
  int length;

  fseek(in, 0, SEEK_END);
  length = ftell(in);
  rewind(in);

  buffer = (char *) malloc((length + 1) * sizeof(char));
  fread(buffer, 1, length, in);
  fclose(in);

  buffer[length] = '\0';

  return buffer;
}

// Reads a line from a FILE pointer to a pointer to a null terminated character array.
// This function does not close the FILE since it may not be at the end of the file.
char *readline(FILE *in) {
  // Code modified from Ian's C Slides on Pointers
  int length = 0;
  int capacity = 2; // Sacrifices more computation time for less allocated memory
  char *line = (char *) malloc(capacity * sizeof(char));

  while (true) {
    fgets(line + length, capacity - length, in);

    if (feof(in)) {
      break;
    } else {
      length = strlen(line);
      if (line[length - 1] == '\n' || line[length - 1] == '\r') {
        break;
      } else {
        capacity *= 2;
        line = (char *) realloc(line, capacity * sizeof(char));
      }
    }
  }

  line[strcspn(line, "\r\n")] = '\0';

  return line;
}

// Opens and reads an file given a file name into a pointer to a null terminated character 
// array.
// Creates an error and prints it to stderr if it failed to pen the file.
char *readfile(char *filename) {
  FILE *in = fopen(filename, "r");

  if (in == NULL) {
    fprintf(stderr, "Can't open file \"%s\".\n", filename);
    exit(1);
  }

  return read(in);
}

// Returns the first word from a pointer to a character array, incrementing the pointer
// to the end of the word.
// This function will modify the string and will not allocate memory.
// Words are defined to start with an alphanumerical character, contains alphanumerical
// characters or apostrophes and end on an alphanumerical character. All other characters
// are counted as spaces.
// Returns '\0' if no word was found.
char *word(char **string) {
  char *wordptr;
  int i;

  for (i = 0; !isalnum((*string)[i]); i++) {
    if ((*string)[i] == '\0') {
      return '\0';
    }
  }

  wordptr = *string + i;
  for (i++; isalnum((*string)[i]) || (*string)[i] == '\''; i++);

  if ((*string)[i] == '\0') {
    *string += i; // Otherwise the next call will loop through random memory
  } else if ((*string)[i-1] == '\'') {
    (*string)[i-1] = '\0'; // Words cannot end in an apostrophe but can contain them
    *string += i;
  } else {
    (*string)[i] = '\0';
    *string += i + 1;
  }

  return wordptr;
}

// Converts a string into a pointer to an array of character arrays.
// This function will modify the string and will not allocate memory.
// The array of character arrays ends with a character array containing a single null
// terminator ('\0').
char **wordarray(char *string) {
  // Uses a similar idea as readline, doubling the allocated memory as needed.
  int i = 0;
  int max = 1;
  char **wordarray = (char **) malloc(max * sizeof(char *));

  wordarray[i] = word(&string);
  while (wordarray[i] != '\0') {
    i++;
    if (i >= max) {
      max *= 2;
      wordarray = (char **) realloc(wordarray, max * sizeof(char *));
    }
    wordarray[i] = word(&string);
  }

  return wordarray;
}