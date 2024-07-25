#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myLib.h"
#include "LineEditor.h"
#include "screens.h"
#include "test.h"
int main(int argc, char* argv[])
{
	//test_input_string();
	//return 0;
	String* path = createString("C:\\Users\\abhay\\source\\repos\\LineEditor\\LineEditor\\file.txt");
	File* file = (File*)malloc(sizeof(File));
	// for (int i = 0; i < argc; i++)
	// 	printf("%s\n", argv[i]);

	getPath(argc, argv, path);
	printf("path : %s", path->characters);

	openFile(file, path);
	start(file);

	return 0;
}

void openFile(File* file, struct String* path)
{
	file->path = path;
	file->buffer = createFileBuffer();
	file->length = 0;

	FILE* fp = fopen(file->path->characters, "r");

	if (fp == NULL) {
		fclose(fp);
		FILE* tmp = fopen(file->path->characters, "w");
		fclose(tmp);
		fp = fopen(file->path->characters, "r");
	}

	String* currLine = createString("");
	int ch;
	while ((ch = fgetc(fp)) != EOF) {
		char _ch = ch;
		file->length += 1;

		addChar(currLine, _ch);
		if (_ch == '\n')
		{
			addLineToFileBuffer(file->buffer, currLine);
			currLine = createString("");
		}
	}
	if (currLine->length > 0)
	{
		addLineToFileBuffer(file->buffer, currLine);
	}
	fclose(fp);
}

