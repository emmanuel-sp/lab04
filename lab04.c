#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Converts given binary string into an unsigned integer.
 * Places integer into sized 1 integer array "decimals"
 */
void binaryToDecimal(char * binary, unsigned int decimals[]);

/**
 * Converts given unsigned integer into binary string.
 * Places string into char array "binary"
 */
void decimalToBinary(unsigned int decimal, char binary[], int bitSize);

int main(int argc, char * argv[]) {
	unsigned int decimals[1] = {0};
	unsigned int result;
	char binary[64] = {0};
	unsigned int decimalResult[] = {0};

	// Separates ~ and shifts
	switch (argc) {
	case 3:
		binaryToDecimal(argv[2], decimals); // Converts binary string to decimal
		result = ~decimals[0];
		decimalToBinary(result, binary, strlen(argv[2])); // Converts result to binary
		printf("~%s evaluates to %s using bit strings of length %ld\n",
		argv[2], binary, strlen(argv[2]));
		binaryToDecimal(binary, decimalResult); // Converts result back to decimal
		printf("~%d evaluates to %d using unsigned %ld-bit integers\n",
		decimals[0], decimalResult[0], strlen(argv[2]));
		break;
	case 4:
		binaryToDecimal(argv[1], decimals);
		unsigned int shift = strtoul(argv[3], NULL, 10);
		char * direction;
		char binaryResult[64] = {0};
		if (argv[2][1] == 'l') {
			direction = "<<";
			result = decimals[0] << shift;
		} else {
			direction = ">>";
			result = decimals[0] >> shift;
		}

		decimalToBinary(shift, binary, strlen(argv[1])); // Converts shift amount into binary
		decimalToBinary(result, binaryResult, strlen(argv[1])); // Converts result into binary

		printf("%s %s %s evaluates to %s using bit strings of length %ld\n",
		argv[1], direction, binary, binaryResult, strlen(argv[1]));

		binaryToDecimal(binaryResult, decimalResult); // Converts result from binary back to decimal

		printf("%d %s %d evaluates to %d using unsigned %ld-bit integers\n",
		decimals[0], direction, shift, decimalResult[0], strlen(argv[1]));
		break;
	}
	return 0;
}

void binaryToDecimal(char * binary, unsigned int decimals[]) {
	long count = 0;
	int power = 1;
	for (int i = strlen(binary) - 1; i > -1; i--) {
		if (binary[i] == '1') {
			count += power;
		}
		power *= 2;
	}
	decimals[0] = count;
}
void decimalToBinary(unsigned int decimal, char binary[], int bitSize) {
	for (int i = bitSize - 1; i > -1; i--) {
		binary[i] = decimal % 2 + '0';
		decimal = decimal / 2;
	}
}
