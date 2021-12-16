#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BAD_NUMBER_ARGS 1

FILE *parseCommandLine(int argc, char **argv, int *bits) {
  if (argc > 2) {
    printf("Usage: %s [-b|-bits]\n", argv[0]);
    exit(BAD_NUMBER_ARGS);
  }
  if (argc == 2 && (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-bits") == 0)) {
    *bits = TRUE;
  }
	else {
    *bits = FALSE;
	}
  return stdin;
}

void printDataAsHex(unsigned char *data, size_t size) {
	//printf("Size: %ld ", size);
	if (size % 2 == 0){
		for (int i = 0; i < size; i+=2){
			printf(" %x%x", data[i], data[i+1]);
		}
	}
	else{
		for (int i = 0; i < size; i+=2){
			printf(" %x", data[i]);
			if (i != (size - 1)){
				printf("%x", data[i+1]);
			}
		}
	}

	if (size < 16){
		int spaces = (16 - size) / 2;
		for (int i = 0; i < spaces; i++){
			for (int j = 0; j < 4; j++){
				printf(" ");
			}
			printf(" ");
		}
	}
}

void printDataAsChars(unsigned char *data, size_t size) {
  for (int i = 0; i < size; i++){
		printf("%c", data[i]);
	}
}

void readAndPrintInputAsHex(FILE *input) {
  unsigned char data[16];
  int numBytesRead = fread(data, 1, 16, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x:", offset);
    offset += numBytesRead;
    printDataAsHex(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 16, input);
  }
}

void printDataAsBits(unsigned char *data, size_t size){
	//printf("Size: %ld ", size);
	char c;
	for (int i = 0; i < size; i++){
		c = data[i];
		for (int j = 0; j < 8; j++) {
			int shifted = c << j; //left shifts the binary representation of c left by j spaces
			int operated = shifted & 0x80; //bitwise and operation. after this the output is all either 0 or 128
			int bit = !!operated; //double not. first not turns 0 into 1 and 128 into 0, second turns the 1s back into 0s and the 0s (previously 128s) into 1s
      printf("%d", bit);
  	}
		printf(" ");
	}
	if (size < 6){
		int spaces = 6 - size;
		for (int i = 0; i < spaces; i++){
			for (int j = 0; j < 8; j++){
				printf(" ");
			}
			printf(" ");
		}
	}
}

void readAndPrintInputAsBits(FILE *input) {
  unsigned char data[16];
  int numBytesRead = fread(data, 1, 6, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x: ", offset);
    offset += numBytesRead;
    printDataAsBits(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 6, input);
  }
}
int main(int argc, char **argv) {
  int bits = FALSE;
  FILE *input = parseCommandLine(argc, argv, &bits);

  if (bits == FALSE) {
    readAndPrintInputAsHex(input);
  } 
	else {
    readAndPrintInputAsBits(input);
  }
  return 0;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BAD_NUMBER_ARGS 1

FILE *parseCommandLine(int argc, char **argv, int *bits) {
  if (argc > 2) {
    printf("Usage: %s [-b|-bits]\n", argv[0]);
    exit(BAD_NUMBER_ARGS);
  }
  if (argc == 2 && (strcmp(argv[1], "-b") == 0 || strcmp(argv[1], "-bits") == 0)) {
    *bits = TRUE;
  }
	else {
    *bits = FALSE;
	}
  return stdin;
}

void printDataAsHex(unsigned char *data, size_t size) {
	//printf("Size: %ld ", size);
	if (size % 2 == 0){
		for (int i = 0; i < size; i+=2){
			printf(" %02x%02x", data[i], data[i+1]);
		}
	}
	else{
		for (int i = 0; i < size; i+=2){
			printf(" %x", data[i]);
			if (i != (size - 1)){
				printf("%x", data[i+1]);
			}
		}
	}

	if (size < 16){
		int spaces = (16 - size) / 2;
		for (int i = 0; i < spaces; i++){
			for (int j = 0; j < 4; j++){
				printf(" ");
			}
			printf(" ");
		}
	}
}

void printDataAsChars(unsigned char *data, size_t size) {
  for (int i = 0; i < size; i++){
		if (data[i] >= 32 && data[i] <= 126){
			printf("%c", data[i]);
		}
		else{
			printf(".");
		}
	}
}

void readAndPrintInputAsHex(FILE *input) {
  unsigned char data[16];
  int numBytesRead = fread(data, 1, 16, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x:", offset);
    offset += numBytesRead;
    printDataAsHex(data, numBytesRead);
		if (numBytesRead != 16){
			printf("  ");
		}
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 16, input);
  }
}

void printDataAsBits(unsigned char *data, size_t size){
	//printf("Size: %ld ", size);
	char c;
	for (int i = 0; i < size; i++){
		c = data[i];
		for (int j = 0; j < 8; j++) {
			int shifted = c << j; //left shifts the binary representation of c left by j spaces
			int operated = shifted & 0x80; //bitwise and operation. after this the output is all either 0 or 128
			int bit = !!operated; //double not. first not turns 0 into 1 and 128 into 0, second turns the 1s back into 0s and the 0s (previously 128s) into 1s
      printf("%d", bit);
  	}
		printf(" ");
	}
	if (size < 6){
		int spaces = 6 - size;
		for (int i = 0; i < spaces; i++){
			for (int j = 0; j < 8; j++){
				printf(" ");
			}
			printf(" ");
		}
	}
}

void readAndPrintInputAsBits(FILE *input) {
  unsigned char data[16];
  int numBytesRead = fread(data, 1, 6, input);
  unsigned int offset = 0;
  while (numBytesRead != 0) {
    printf("%08x: ", offset);
    offset += numBytesRead;
    printDataAsBits(data, numBytesRead);
    printf("  ");
    printDataAsChars(data, numBytesRead);
    printf("\n");
    numBytesRead = fread(data, 1, 6, input);
  }
}
int main(int argc, char **argv) {
  int bits = FALSE;
  FILE *input = parseCommandLine(argc, argv, &bits);

  if (bits == FALSE) {
    readAndPrintInputAsHex(input);
  } 
	else {
    readAndPrintInputAsBits(input);
  }
  return 0;
}
}
