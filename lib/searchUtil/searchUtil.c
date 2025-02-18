#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "searchUtil.h"


/**
 * @brief search a string for a substring
 * @param string the string to search in
 * @param substring the substring to search for
 * @return index of substring if found, -1 if not
 */
int searchString(char * string, char * substring) {
    int subStringLen = strlen(substring);

    char * lowerString = calloc(subStringLen + 1, sizeof(char));
    for (int i = 0; i < subStringLen + 1; i++) {
        lowerString[i] = tolower(substring[i]);
    }


    int stringIndex = 0;
    int searchStringIndex = 0;
    while (string[stringIndex] != '\0') {
        if (tolower(string[stringIndex]) == lowerString[searchStringIndex]) {
            searchStringIndex++;
        } else {
            searchStringIndex = 0;
        }

        if (searchStringIndex == subStringLen - 1) {
            return stringIndex - searchStringIndex + 1;
        }

        stringIndex++;
    }

    free(lowerString);

    return -1;
}

