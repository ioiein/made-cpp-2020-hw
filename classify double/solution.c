#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>



/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64(double number) {
    return *((uint64_t*)(&number));
}

bool getBit(const uint64_t number, const uint8_t index) {
    /// Your code here...
    uint64_t Bit = (number >> index) & 1;
    return Bit;
}


/**
 * Checkers here:
 */

bool checkForPlusZero(uint64_t number) {
    /// Your code here.
    for (int i = 0; i < 64; i++)
        printf("%u", getBit(number, i));
    return number == 0;
}

bool checkForMinusZero(uint64_t number) {
    return number == (uint64_t)0x8000000000000000;
}

bool checkForPlusInf(uint64_t number) {
    /// Your code here.
    if (getBit(number, 0) != 0)
        return false;
    for (int i = 1; i <= 11; i++)
    {
        if (getBit(number, i) != 1)
            return false;
    }
    for (int i = 12; i <= 63; i++)
    {
        if (getBit(number, i) != 0)
            return false;
    }
    return true;
}

bool checkForMinusInf(uint64_t number) {
    /// Your code here.
    if (getBit(number, 0) != 1)
        return false;
    for (int i = 1; i <= 11; i++)
    {
        if (getBit(number, i) != 1)
            return false;
    }
    for (int i = 12; i <= 63; i++)
    {
        if (getBit(number, i) != 0)
            return false;
    }
    return true;
}

bool checkForPlusNormal(uint64_t number) {
    /// Your code here.
    for (int i = 2; i <= 12; i++)
        if (getBit(number, i) != getBit(number, 1) && getBit(number, 0) == 0)
            return true;
    return false;
}

bool checkForMinusNormal(uint64_t number) {
    /// Your code here.
    for (int i = 2; i <= 12; i++)
        if (getBit(number, i) != getBit(number, 1) && getBit(number, 0) == 1)
            return true;
    return false;
}

bool checkForPlusDenormal(uint64_t number) {
    /// Your code here.
    return getBit(number, 0) == 0 && ((number & 0x0FFF) == 0) && ((number >> 12 & 0x0FFFFFFFFFFFFF) > 0);
}

bool checkForMinusDenormal(uint64_t number) {
    /// Your code here.
    return getBit(number, 0) == 1 && ((number & 0x0FFF) == 0) && ((number >> 12 & 0x0FFFFFFFFFFFFF) > 0);
}

bool checkForSignalingNan(uint64_t number) {
    /// Your code here.
    for (int i = 1; i <= 12; i++)
        if (getBit(number, i) != 1)
            return false;
    if (getBit(number, 13) != 0 || getBit(number, 63) != 1)
        return false;
    return true;
}

bool checkForQuietNan(uint64_t number) {
    /// Your code here.
    for (int i = 1; i <= 13; i++)
        if (getBit(number, i) != 1)
            return false;
    return true;
}


void classify(double number) {
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

    else if (checkForMinusNormal(convertToUint64(number))) {
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