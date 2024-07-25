#pragma warning(disable : 4996)
#include<string.h>
#include "myLib.h"
#include<stdlib.h>
#include<stdlib.h>
#include<stdio.h>

String* createString(char* str)
{
	size_t length = strlen(str);
	String* string = (String*)malloc(sizeof(String));
	string->length = length;
	string->capacity = length > DEFAULT_STRING_CAPACITY ? length + 1 : DEFAULT_STRING_CAPACITY;
	string->characters = (char*)malloc(string->capacity * sizeof(char));
	memset(string->characters, '\0', string->capacity);
	// strcpy_s(string->characters, length, str);
	if (length > 0) strcpy(string->characters, str);
	return string;
}

void freeString(String* string)
{
	if (string == NULL) return;
	free(string->characters);
	free(string);
}

void dirname(String* path, String* dir)
{
	int lastPos = -1;
	// loop to find last seperator position
	for (int i = path->length; i > 0; i--)
	{
		if (path->characters[i] == PATH_SEPARATOR)
		{
			lastPos = i;
		}
	}
}

void getPath(int argc, char* argv[], String* path)
{
	if (argc == 1)
	{
		path = createString("file.txt");
		return;
	}
	if (argc == 2)
	{
		path = createString(argv[1]);
		return;
	}

	if (argc == 3) {
		char* dirname = argv[2];
		char* filename = argv[1];
		int dirLength = strlen(dirname);
		int fileLength = strlen(filename);
		int endsWithSep = dirname[dirLength - 1] == PATH_SEPARATOR ? 1 : 0;
		
		clearString(path);
		for (int i = 0; i < dirLength; i++)
		{
			addChar(path, dirname[i]);
		}
		if (!endsWithSep) addChar(path, PATH_SEPARATOR);
		for (int i = 0; i < fileLength; i++)
		{
			addChar(path, filename[i]);
		}
		return;
	}


	printf("ERROR: invalid number of args\n");
	printf("usage :-\n");
	printf("  LineEditor.exe\n");
	printf("  LineEditor.exe <filename>\n");
	printf("  LineEditor.exe <filename> <directory>\n");
	
}

void printBuffer(Buffer* buffer)
{
	int i = 0;
	for (; i < buffer->length; i++)
	{
		printf("%d%s|", i + 1, i < 9 ? "  " : " ");
		String* line = buffer->lines[i];
		printf("%s", line->characters);
		if (line->characters[line->length - 1] != '\n') printf("\n");
	}
	while (i < BUFFER_CAPACITY)
	{
		printf("%d\n", i + 1);
		i++;
	}
}

void addLineToBuffer(Buffer* buffer, String* line)
{
	if (isBufferFull(buffer))
	{
		printf("\n\nBuffer overflow");
		exit(3);
	}
	buffer->lines[buffer->length] = line;
	buffer->length += 1;
}

bool isBufferFull(Buffer* buffer)
{
	return buffer->length >= BUFFER_CAPACITY;
}

void freeBuffer(Buffer* buffer)
{
	for (int i = 0; i < buffer->length; i++)
	{
		freeString(buffer->lines[i]);
	}
	free(buffer);
}

Buffer* createBuffer()
{
	Buffer* buffer = (Buffer*)malloc(sizeof(Buffer));
	buffer->length = 0;
	return buffer;
}

void _concat_(String* source, String* newstring)
{
	int newlength = source->length + newstring->length;
	if (newlength > source->capacity)
	{
		extendString(source, newlength * 2);
	}
	strcat(source->characters, newstring);
}

void clearString(String* str)
{
	memset(str->characters, '\0', str->length);
}

void extendString(String* source, int newCapacity)
{
	if (newCapacity < source->length) {
		printf("extendString ERROR : newCapacity cannot be less than source->length");
		exit(-1);
		return;
	}
	source->capacity = newCapacity;
	char* tmp;// = (char*)realloc(source->characters, source->capacity);
	tmp = (char*)malloc(source->capacity);
	strcpy(tmp, source->characters);

	source->characters = tmp;
	for (int i = source->length; i < newCapacity; i++)
	{
		source->characters[i] = '\0';
	}
}

void readString(String* dest)
{
	char c;
	while (1)
	{
		scanf("%c", &c);
		if (c == '\n') break;
		addChar(dest, c);
	}
}

FileBuffer* createFileBuffer()
{
	FileBuffer* filebuffer = (FileBuffer*)malloc(sizeof(FileBuffer));
	filebuffer->capacity = DEFAULT_FILEBUFFER_CAPACITY;
	filebuffer->length = 0;
	filebuffer->buffers = (Buffer**)malloc(sizeof(Buffer*));
	for (int i = 0;i < filebuffer->capacity; i++)
	{
		filebuffer->buffers[i] = createBuffer();
	}
	return filebuffer;
}

void freeFileBuffer(FileBuffer* fb)
{
	for (int i = 0; i < fb->capacity; i++)
	{
		freeBuffer(fb->buffers[i]);
	}
	free(fb);
}

void addLineToFileBuffer(FileBuffer* filebuffer, String* line)
{
	Buffer** buffers = filebuffer->buffers;
	if (filebuffer->length == 0 || isBufferFull(buffers[filebuffer->length - 1]))
	{
		//filebuffer->buffers[] = (Buffer*)malloc(sizeof(Buffer));
		//buffers[filebuffer->length] = (Buffer*)malloc(sizeof(Buffer));
		filebuffer->length += 1;
	}

	if (filebuffer->length >= filebuffer->capacity)
	{
		extendFileBuffer(filebuffer, filebuffer->length * 2);
	}

	if (buffers[0]->length == 25)
	{
		;
	}
	addLineToBuffer(buffers[filebuffer->length - 1], line);
}

void extendFileBuffer(FileBuffer* filebuffer, int newcapacity)
{
	if (newcapacity < filebuffer->length)
	{
		printf("extendFileBuffer Error : newcapacity cannot be smaller than filebuffer->length");
		exit(-1);
	}
	filebuffer->capacity = newcapacity;
	Buffer** tmp = (Buffer**)realloc(filebuffer->buffers, filebuffer->capacity);
	filebuffer->buffers = tmp;
	for (int i = filebuffer->length; i < filebuffer->capacity; i++)
	{
		filebuffer->buffers[i] = (Buffer*)malloc(sizeof(Buffer));
	}
}

void printFileBuffer(FileBuffer* fb, int lines)
{
	Buffer** buffers = fb->buffers;
	int length = fb->length;
	int count = 0;
	int bufferIndex = 0;
	int lineNum;
	while (bufferIndex < fb->length && count < lines)
	{
		lineNum = count % BUFFER_CAPACITY;
		//bufferIndex = (int)(count / BUFFER_CAPACITY);
		Buffer* buffer = buffers[bufferIndex];

		printf("%d%s|", count + 1, count < 9 ? "  " : " ");
		String* line = buffer->lines[lineNum];
		printf("%s", line->characters);
		if (line->characters[line->length - 1] != '\n') printf("\n");

		if (lineNum == buffer->length - 1)
			bufferIndex++;
		count++;
	}

	if (bufferIndex < length)
	{
		printf("more line ...\n");
	}
}



void clrscr()
{
	system(CLR_CMD);
}

void saveFile(File* file)
{
	FILE* fp = fopen(file->path->characters, "w");
	if (fp == NULL)
	{
		printf("\nsaveFile Error : *fp is NULL\n");
		return;
	}
	for (int i = 0; i < file->buffer->length; i++)
	{
		Buffer* buffer = file->buffer->buffers[i];
		for (int j = 0;j < buffer->length; j++)
		{
			String* line = buffer->lines[j];
			/*for (int k = 0; k < line->length; k++)
			{

			}*/
			fprintf(fp, line->characters);
		}
	}
	fclose(fp);
}

void addChar(String* source, char c)
{
	if (source->length + 1 == source->capacity)
	{
		extendString(source, source->length * 2);
	}
	source->characters[source->length] = c;
	source->length += 1;
}


int find_substring(const char* str, const char* search) {
	int len_str = strlen(str);
	int len_search = strlen(search);

	// Handle empty search string
	if (len_search == 0) {
		return 0; // Return 0 for empty search string
	}

	// Iterate through the main string
	for (int i = 0; i <= len_str - len_search; i++) {
		// Compare substrings
		if (strncmp(str + i, search, len_search) == 0) {
			return i; // Return the starting position of the match
		}
	}

	return -1; // Not found
}

