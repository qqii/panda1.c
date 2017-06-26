/* Classify a triangle according to the integer lengths of its sides. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> 
// limits.h is included for INT_MAX, although test is hardcoded as
// strtol is used to convert the number instead of atoi

// Swaps two longs in place
void swap(long *long1, long *long2){
    long temp = *long1;
    *long1 = *long2;
    *long2 = temp;
}

// Given 3 longs, sorts them in place lowest to highest
void sort3(long *long1, long *long2, long *long3){
    if(*long1 > *long2){
        swap(long1, long2);
    }
    if(*long1 > *long3){
        swap(long1, long3);
    }
    if(*long2 > *long3){
        swap(long2, long3);
    }
}

// Given a string, tries to convert it to a long
// Returns -1 when beginnign with 0, contains decimals or larger than INT_MAX
// TODO?: Come up with a better name for this function?
long validatedstrtol(char *string){
    // Ambiguous as beginning with 0 may mean octal
    if(strncmp(string, "0", 1) == 0){
        return -1;
    }

    // Used to determine if the string is a valid number followed by an
    // invalid character
    char *temp;
    // strtol returns 0 if no valid number is found
    // As we don't accept 0 as a length there is no need to check if temp
    // is the same as string
    long converted = strtol(string, &temp, 10);

    // Found stuff after the number
    if(strlen(temp) != 0){
        return -1;
    }
    // Although we're using longs, the tests are for INT_MAX
    if(converted > INT_MAX){
        return -1;
    }

    return converted;
}

// Classify a triangle, given side lengths as strings
char *triangle(char *string1, char *string2, char *string3) {
    long length1 = validatedstrtol(string1);
    long length2 = validatedstrtol(string2);
    long length3 = validatedstrtol(string3);

    // Technically this can be moved down after the first few if statements
    sort3(&length1, &length2, &length3);

    // printf("Strings: %s, %s, %s\n", string1, string2, string3);
    // printf("Lengths: %ld, %ld, %ld\n", length1, length2, length3);

    // TODO?:
    // seperate the condition of each if statement into seperate functions?

    // validatedstrtol returns -1 if not a valid string
    if(length1 < 1 || length2 < 1 || length3 < 1){
        return "Illegal";
    }

    if(length1 == length2 && length1 == length3){
        return "Equilateral";
    }

    if(length1 == length2 || length1 == length3 || length2 == length3){
        return "Isosceles";
    }

    // Lengths are sorted lowest to highest
    if((length1*length1 + length2*length2) == length3*length3){
        return "Right";
    }

    if(length1+length2 == length3){
        return "Flat";
    }

    if(length1+length2 < length3){
        return "Impossible";
    }

    return "Scalene";
}

// Check that two strings are equal
void eq(char *actual, char *expected) {
    if (strcmp(actual, expected) != 0) {
        fprintf(stderr, "Test failure, actual: %s\n", actual);
        fprintf(stderr, "Expected: %s\n", expected);
        exit(1);
    }
}

// Run tests on the triangle function.
// TODO?: print more information on test failure, at least the line number
void test() {
    int mark = 0;
    eq(triangle("8", "8", "8"), "Equilateral"); mark++;
    eq(triangle("1073", "1073", "1073"), "Equilateral"); mark++;
    eq(triangle("15", "15", "13"), "Isosceles"); mark++;
    eq(triangle("15", "13", "15"), "Isosceles"); mark++;
    eq(triangle("13", "15", "15"), "Isosceles"); mark++;
    eq(triangle("25", "25", "27"), "Isosceles"); mark++;
    eq(triangle("25", "27", "25"), "Isosceles"); mark++;
    eq(triangle("27", "25", "25"), "Isosceles"); mark++;
    eq(triangle("3", "4", "5"), "Right"); mark++;
    eq(triangle("5", "12", "13"), "Right"); mark++;
    eq(triangle("5", "13", "12"), "Right"); mark++;
    eq(triangle("12", "5", "13"), "Right"); mark++;
    eq(triangle("12", "13", "5"), "Right"); mark++;
    eq(triangle("13", "5", "12"), "Right"); mark++;
    eq(triangle("13", "12", "5"), "Right"); mark++;
    eq(triangle("12", "14", "15"), "Scalene"); mark++;
    eq(triangle("12", "15", "14"), "Scalene"); mark++;
    eq(triangle("14", "12", "15"), "Scalene"); mark++;
    eq(triangle("14", "15", "12"), "Scalene"); mark++;
    eq(triangle("15", "12", "14"), "Scalene"); mark++;
    eq(triangle("15", "14", "12"), "Scalene"); mark++;
    eq(triangle("7", "9", "16"), "Flat"); mark++;
    eq(triangle("7", "16", "9"), "Flat"); mark++;
    eq(triangle("9", "16", "7"), "Flat"); mark++;
    eq(triangle("16", "7", "9"), "Flat"); mark++;
    eq(triangle("16", "9", "7"), "Flat"); mark++;
    eq(triangle("2", "3", "13"), "Impossible"); mark++;
    eq(triangle("2", "13", "3"), "Impossible"); mark++;
    eq(triangle("13", "2", "3"), "Impossible"); mark++;
    eq(triangle("0", "0", "0"), "Illegal"); mark++;
    eq(triangle("0", "10", "12"), "Illegal"); mark++;
    eq(triangle("10", "0", "12"), "Illegal"); mark++;
    eq(triangle("10", "12", "0"), "Illegal"); mark++;
    eq(triangle("-1", "-1", "-1"), "Illegal"); mark++;
    eq(triangle("-1", "10", "12"), "Illegal"); mark++;
    eq(triangle("10", "-1", "12"), "Illegal"); mark++;
    eq(triangle("10", "12", "-1"), "Illegal"); mark++;
    eq(triangle("x", "y", "z"), "Illegal"); mark++;
    eq(triangle("10", "12", "13.4"), "Illegal"); mark++;
    eq(triangle("03", "4", "5"), "Illegal"); mark++;
    eq(triangle("3", "04", "5"), "Illegal"); mark++;
    eq(triangle("3", "4", "05"), "Illegal"); mark++;
    eq(triangle("3x", "4y", "5z"), "Illegal"); mark++;
    eq(triangle("2147483648","2147483647","2147483647"),"Illegal"); mark++;
    eq(triangle("2147483647","2147483648","2147483647"),"Illegal"); mark++;
    eq(triangle("2147483647","2147483647","2147483648"),"Illegal"); mark++;
    eq(triangle("2147483647","2147483647","2147483647"),"Equilateral"); mark++;
    eq(triangle("1100000000","1705032704","1805032704"),"Scalene"); mark++;
    eq(triangle("2000000001","2000000002","2000000003"),"Scalene"); mark++;
    eq(triangle("150000002","666666671","683333338"),"Scalene"); mark++;
    printf("Tests passed: %d\n", mark);
}

// Run the program or, if there are no arguments, test it.
int main(int argc, char **argv) {
    if (argc == 1) {
        test();
    } else if (argc == 4) {
        char *result = triangle(argv[1], argv[2], argv[3]);
        printf("%s\n", result);
    } else {
        fprintf(stderr, "Use e.g.: ./triangle.o 3 4 5\n");
        exit(1);
    }
}
