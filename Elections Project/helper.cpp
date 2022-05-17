
/*
    Title: C++ Implementation to Trim Char Array of Leading/Trailing White Space Not Working As Expected
    Author: jmucchiello
    Date: 17/08/2014
    Availability: https://stackoverflow.com/questions/25345598/c-implementation-to-trim-char-array-of-leading-trailing-white-space-not-workin

*/
void strStrip(char* str) {
    int begin = 0; // number of leading spaces
    char* charBuffer = str;
    while (*str && *str++ == ' ') ++begin;
    while (*str++); // move to end of string
    int end = str - charBuffer - 1;
    while (end > 0 && charBuffer[end - 1] == ' ') --end; // backup over trailing spaces
    charBuffer[end] = 0; // remove trailing spaces
    if (end <= begin || begin == 0) return; // exit if no leading spaces or string is now empty
    str = charBuffer + begin;
    while ((*charBuffer++ = *str++));  // remove leading spaces: K&R
}