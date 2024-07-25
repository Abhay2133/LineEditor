#pragma once

#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#define CLR_CMD "cls"
#elif defined(__linux__) || defined(__unix__) || defined(APPLE)
#define PATH_SEPARATOR '/'
#define CLR_CMD "clear"
#else
#error "Unsupported platform"
#endif

#define bool int
#define true 1
#define false 0
#define BUFFER_CAPACITY 25
#define DEFAULT_STRING_CAPACITY 10
#define DEFAULT_FILEBUFFER_CAPACITY 5

typedef struct
{
	char* characters;
	int length;
	int capacity;
} String;

typedef struct
{
	String* lines[BUFFER_CAPACITY];
	int length;
} Buffer;

typedef struct
{
	int length;
	int capacity;
	Buffer** buffers;
} FileBuffer;

typedef struct
{
	String* path;
	//FILE* file;
	FileBuffer* buffer;
	int length;
} File;

String* createString(char*);


void dirname(String* path, String* dir);
void getPath(int argc, char* argv[], String* path);

int isDirectory(const char* path);

void start(File*);

// Buffer functions
void printBuffer(Buffer* buffer);
void addLineToBuffer(Buffer* buffer, String* line);
bool isBufferFull(Buffer* buffer);
void freeBuffer(Buffer* buffer);
Buffer* createBuffer();

// string functions
void freeString(String* string);
void _concat_(String* source, String* newstring); // append newstring in source
void addChar(String* source, char c);
void clearString(String* str);
void extendString(String* string,int);
void readString(String* dest);

// FileBuffer functions
FileBuffer* createFileBuffer();
void freeFileBuffer(FileBuffer* );
void addLineToFileBuffer(FileBuffer* buffer, String* line);
void extendFileBuffer(FileBuffer* filebuffer, int newcapacity);
void printFileBuffer(FileBuffer* fb, int lines);

// helper functions
void clrscr();
void saveFile(File* file);
int find_substring(const char* str, const char* search);