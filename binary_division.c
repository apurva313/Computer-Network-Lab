#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to convert a binary string to an integer
int binaryToInt(const char *binary) {
    int result = 0;
    for (int i = 0; binary[i] != '\0'; i++) {
        result = result * 2 + (binary[i] - '0');
    }
    return result;
}

// Function to convert an integer to a binary string
char* intToBinary(int n) {
    if (n == 0) {
        return "0";
    }
    char *binary = (char *)malloc(32 * sizeof(char));
    binary[31] = '\0';
    int index = 30;
    while (n > 0) {
        binary[index--] = (n % 2) + '0';
        n /= 2;
    }
    return &binary[index + 1];
}

// Function to perform binary division
void binaryDivision(const char *dividend, const char *divisor, char *quotient, char *remainder) {
    int dividendInt = binaryToInt(dividend);
    int divisorInt = binaryToInt(divisor);
    
    if (divisorInt == 0) {
        printf("Error: Division by zero\n");
        return;
    }

    int quotientInt = dividendInt / divisorInt;
    int remainderInt = dividendInt % divisorInt;

    strcpy(quotient, intToBinary(quotientInt));
    strcpy(remainder, intToBinary(remainderInt));
}

int main() {
    char dividend[32];
    char divisor[32];
    char quotient[32] = {0};
    char remainder[32] = {0};

    printf("Enter the dividend (binary): ");
    scanf("%s", dividend);
    printf("Enter the divisor (binary): ");
    scanf("%s", divisor);

    binaryDivision(dividend, divisor, quotient, remainder);

    printf("Quotient: %s\n", quotient);
    printf("Remainder: %s\n", remainder);

    return 0;
}
