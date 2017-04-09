#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(char *name)
{
	FILE *fileIn, *fileOut;
	char *buffer;
	unsigned long fileLen;

	//Open file
	fileIn = fopen("/home/liyakamilia/Desktop/input.txt", "r"); //read input
	fileOut = fopen("/home/liyakamilia/Desktop/output.bin", "w+b");

	if (!fileIn)
	{
		fprintf(stderr, "Unable to open file %s", name);
		return;
	}
	
	//Get file length
	fseek(fileIn, 0, SEEK_END);
	fileLen = ftell(fileIn);
	fseek(fileIn, 0, SEEK_SET);

	//Allocate memory
	buffer = (char *)malloc(fileLen + 1);
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
                fclose(fileIn);
		return;
	}

	//Read file contents into buffer
	int a;
	while (fscanf(fileIn, "%d\n", buffer) != EOF) {
		fwrite(buffer, fileLen, 1, fileOut);
	}
	//fread(buffer, fileLen, 1, fileIn);
	//fwrite(buffer, fileLen, 1, fileOut);
	
	fclose(fileOut);
	fclose(fileIn);

	//Do what ever with buffer
	free(buffer);
}
