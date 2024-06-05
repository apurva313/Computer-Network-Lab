#include <stdio.h>
#include <string.h>

void bitStuffing(char *input, char *output) {
    int i, j = 0, count = 0;
    int len = strlen(input);

    for (i = 0; i < len; i++) {
        if (input[i] == '1') {
            count++;
        } else {
            count = 0;
        }

        output[j++] = input[i];

        if (count == 5) {
            output[j++] = '0';
            count = 0;
        }
    }
    output[j] = '\0';
}

int main() {
    char input[100], output[120];
    
    printf("Enter the input bit string: ");
    scanf("%s", input);

    bitStuffing(input, output);

    printf("After bit stuffing: %s\n", output);

    return 0;
}
