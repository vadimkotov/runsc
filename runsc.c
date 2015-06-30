// Run shellcode in the debugger
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
	FILE *pFile;
	long lSize;
	char *buffer;
	size_t result;


	if (argc!=2) {
		printf("Usage: %s <shellcode file>\n", argv[0]);
		exit(1);
	}
	
	pFile = fopen(argv[1], "rb");
	
	if (pFile==NULL){
		printf("Couldn't open file\n");
		exit(1);
	}
	
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);
	
	// Make it 1 byte bigger for the \xCC opcode
	buffer = (char *)malloc(lSize+1);
	
	if (buffer==NULL){
		printf("Couldn't allocate memory\n");
		exit(1);
	}
	
	buffer[0] = '\xCC';
	
	result = fread(&buffer[1], 1, lSize, pFile);
	
	if (result!=lSize){
		printf("Couldn't read the file");
		exit(1);
	}
	
	__asm {
		mov eax, buffer
		call eax
	}
	
	return 0;
}