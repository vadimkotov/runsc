#include <windows.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
	char *buffer;
	FILE *sc_fd;
	size_t file_size;
	size_t result;
	
	if (argc != 2){
		printf("Usage: %s <shellcode file>\n", argv[0]);
		return -1;
	}
	
	sc_fd = fopen(argv[1], "rb");
	if (sc_fd == NULL){
		printf("Error %d: Couldn't open file\n", GetLastError());
		return -1;
	}
	
	fseek(sc_fd, 0, SEEK_END);
	file_size = ftell(sc_fd);
	rewind(sc_fd);
	
	buffer = VirtualAlloc(NULL, file_size+1, MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE );
	if (buffer == NULL){
		printf("Error %d: Couldn't allocate memory\n", GetLastError());
		return -1;
	}
	
	buffer[0] = 0xCC;
	result = fread(&buffer[1], 1, file_size, sc_fd);
	
	printf("Allocated %d bytes at 0x%X\n", file_size, buffer);
	
	__asm call buffer;
	
	return 0;
	
}