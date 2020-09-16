#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}

bool getBit (const uint64_t number, const uint8_t index) {
    /// Your code here...
    return ((bool)((number >> index) & 1));
}


/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    /// Your code here.
    return number == 0;
}

bool checkForMinusZero (uint64_t number) {
    return number == 0x8000000000000000;
}

bool checkForPlusInf (uint64_t number) {
    /// Your code here.
    if (getBit(number, 63) != 0)
        return false;
    for (int i = 62; i >= 52; i--)
    {
        if (getBit(number, i) != 1)
            return false;
    }
    for (int i = 51; i >= 0; i--)
    {
        if (getBit(number, i) != 0)
            return false;
    }
    return true;
}

bool checkForMinusInf (uint64_t number) {
    /// Your code here.
    if (getBit(number, 63) != 1)
        return false;
    for (int i = 62; i >= 52; i--)
    {
        if (getBit(number, i) != 1)
            return false;
    }
    for (int i = 51; i >= 0; i--)
    {
        if (getBit(number, i) != 0)
            return false;
    }
    return true;
}

bool checkForPlusNormal (uint64_t number) {
    /// Your code here.
    return getBit(number, 62) != getBit(number, 52) && getBit(number, 63) == 0;
}

bool checkForMinusNormal (uint64_t number) {
    /// Your code here.
    return getBit(number,62) != getBit(number,52) && getBit(number, 63) == 1;
}

bool checkForPlusDenormal (uint64_t number) {
    /// Your code here.
    return getBit(number, 63) == 0 && ((number >> 52) & 0x07FF == 0) && (number & 0x07FFFFFFFFFFFF);
}

bool checkForMinusDenormal (uint64_t number) {
    /// Your code here.
    return getBit(number, 63) == 1 && ((number >> 52) & 0x07FF == 0) && (number & 0x07FFFFFFFFFFFF);
}

bool checkForSignalingNan (uint64_t number) {
    /// Your code here.
    return getBit(number, 0) != getBit(number, 51) && number >> 52 > 0x07FF;
}

bool checkForQuietNan (uint64_t number) {
    /// Your code here.
    return number >> 51 > 0x0FFF;
}


void classify (double number) {
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n");
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n");
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n");
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus regular\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Minus regular\n");
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n");
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n");
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signailing NaN\n");
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n");
    }

    else {
        printf("Error.\n");
    }
}