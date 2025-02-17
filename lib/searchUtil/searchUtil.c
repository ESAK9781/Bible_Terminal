#include <string.h>
#include "searchUtil.h"


/**
 * @brief search a string for a substring
 * @param string the string to search in
 * @param substring the substring to search for
 * @return index of substring if found, -1 if not
 */
int searchString(char * string, char * substring) {
    int subStringLen = strlen(substring);


    int stringIndex = 0;
    int searchStringIndex = 0;
    while (string[stringIndex] != '\0') {
        if (string[stringIndex] == substring[searchStringIndex]) {
            searchStringIndex++;
        } else {
            searchStringIndex = 0;
        }

        if (searchStringIndex == subStringLen - 1) {
            return stringIndex - searchStringIndex + 1;
        }

        stringIndex++;
    }


    return -1;
}

