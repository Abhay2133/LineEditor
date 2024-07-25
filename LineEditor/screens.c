#pragma warning(disable : 4996)
#include"myLib.h"
#include "screens.h"
#include<stdlib.h>

void start(File* file)
{

	int choice;

	clrscr();
	printf("filepath : \"%s\"\n\n", file->path->characters);
	printFileBuffer(file->buffer, 10);//BUFFER_CAPACITY* file->buffer->length);

	printf("\n\n Enter your Choice ( in interger ) :-\n\n");
	printf("1.) View File\n");
	printf("2.) Insert Line\n");
	printf("3.) Edit Line\n");
	printf("4.) Delete Line\n");
	printf("5.) Search File\n");
	printf("6.) Save File\n");
	printf("7.) Exit\n");
	printf("\n >> ");

	scanf("%d", &choice);

	switch (choice)
	{

	case 1: viewScreen(file);break;
	case 2: insertScreen(file); break;
	case 3: editScreen(file); break;
	case 4: deleteScreen(file);break;
	case 5: searchScreen(file); break;
	case 6: saveScreen(file); break;
	case 7: return;

	default:
		start(file);
		/*exit(0);*/
	}
}

void insertScreen(File* file)
{

	int choice; // insertMODE : 1 -> before , 2 -> after
	int lineNum;
	String* newString = createString("");
	int pos;

	clrscr();
	printf("filepath : \"%s\"\n\n", file->path->characters);
	printFileBuffer(file->buffer, 10);

	printf("\n\n Enter your Choice ( in interger ) :-\n\n");
	printf("1.) Insert before line\n");
	printf("2.) Insert after line\n");
	printf("3.) Home\n");
	printf("4.) Exit\n");
	printf("\n >> ");

	scanf("%d", &choice);
	switch (choice)
	{

	case 1: break;
	case 2: break;
	case 3: start(file); break;
	case 4: return;
	default:
		insertScreen(file);
	}

	printf("\n Enter the line number no. : ");
	scanf("%d", &lineNum);

	printf("\n type the new line : ");
	char _c; scanf("%c", &_c); // flushing previous buffer from input
	readString(newString);
	addChar(newString, '\n');

	if (choice == 1)
	{
		pos = lineNum;
	}
	else if (choice == 2)
	{
		pos = lineNum + 1;
	}

	String* tmpString = createString("");
	addLineToFileBuffer(file->buffer, tmpString);

	for (int i = file->buffer->length - 1; i >= 0; i--)
	{
		bool breakMe = false;
		Buffer* buf = file->buffer->buffers[i];
		if (buf->length == 1) continue; // only when the tmp string creates a new buffer
		int j = buf->length - 1;
		if (i == file->length - 1) j = buf->length - 2;
		for (int j = buf->length - 1; j >= 0; j--)
		{
			int lineNum = BUFFER_CAPACITY * i + j + 1;
			String* line = buf->lines[j];

			// condition to push last element to start of next buffer
			if (j == BUFFER_CAPACITY - 1)
			{
				file->buffer->buffers[i + 1]->lines[0] = line;
			}
			else
			{
				file->buffer->buffers[i]->lines[j + 1] = line;
			}

			if (lineNum == pos)
			{
				file->buffer->buffers[i]->lines[j] = newString;
				breakMe = true;
				break;
			}
		}
		if (breakMe) break;
	}
	freeString(tmpString);

	printf("\n -- New line inserted at pos : %d --", pos);
	printf("\n\n Enter your choice :- \n\n");
	printf("1.) Insert more\n");
	printf("2.) Home\n");
	printf("3.) Exit\n");
	printf(" >> ");

	scanf("%d", &choice);
	switch (choice)
	{
	case 1: insertScreen(file); break;
	case 2: start(file); break;
	case 3: return;
	default: insertScreen(file);
	}
}

void deleteScreen(File* file)
{

	int choice; // insertMODE : 1 -> before , 2 -> after
	int lineNum;
	String* newString = createString("");
	int pos;

	clrscr();
	printf("filepath : \"%s\"\n\n", file->path->characters);
	printFileBuffer(file->buffer, 10);

	printf("\n\n Enter your Choice ( in interger ) :-\n\n");
	printf("1.) Proceed to Delete a Line\n");
	printf("2.) Home\n");
	printf("3.) Exit\n");
	printf("\n >> ");

	scanf("%d", &choice);
	switch (choice)
	{

	case 1: break;
	case 2: start(file); break;
	case 3: return;
	default:
		deleteScreen(file);
	}

	printf("\n Enter the line number no. : ");
	scanf("%d", &lineNum);

	int bufferIndex = lineNum / BUFFER_CAPACITY;
	int linePos = lineNum - 1 % BUFFER_CAPACITY;


	for (int i = bufferIndex; i < file->buffer->length; i++)
	{
		bool breakMe = false;
		Buffer* buf = file->buffer->buffers[i];
		int j = i == bufferIndex ? linePos : 0;

		for (; j < buf->length; j++)
		{
			if (i == file->buffer->length - 1 && j == buf->length - 1) {
				break;
			}
			String* nextLine;
			if (j == BUFFER_CAPACITY - 1)
			{
				nextLine = file->buffer->buffers[i + 1]->lines[0];
			}
			else
			{
				nextLine = buf->lines[j + 1];
			}
			buf->lines[j] = nextLine;
		}
		if (breakMe) break;
	}

	Buffer* lastBuffer = file->buffer->buffers[file->buffer->length - 1];
	lastBuffer->length -= 1;
	if (lastBuffer->length == 0)
	{
		file->buffer->length -= 1;
	}

	//	freeString(tmpString);

	printf("\n -- line at pos '%d' is deleted --", lineNum);
	printf("\n\n Enter your choice :- \n\n");
	printf("1.) Delete more Lines\n");
	printf("2.) Home\n");
	printf("3.) Exit\n");
	printf(" >> ");

	scanf("%d", &choice);
	switch (choice)
	{
	case 1: deleteScreen(file); break;
	case 2: start(file); break;
	case 3: return;
	default: deleteScreen(file);
	}

}

void searchScreen(File* file)
{
	int choice; // insertMODE : 1 -> before , 2 -> after
	String* newString = createString("");
	String* _line = NULL;

	clrscr();
	printf("filepath : \"%s\"\n\n", file->path->characters);
	printFileBuffer(file->buffer, 10);

	printf("\n\n Enter your Choice ( in interger ) :-\n\n");
	printf("1.) Proceed to Search\n");
	printf("2.) Home\n");
	printf("3.) Exit\n");
	printf("\n >> ");

	scanf("%d", &choice);
	switch (choice)
	{

	case 1: break;
	case 2: start(file); break;
	case 3: return;
	default:
		searchScreen(file);
	}

	printf("\n type the search string : ");

	char _c; scanf("%c", &_c);
	readString(newString);
	//addChar(newString, '\n');

	int loc[] = { -1, -1 }; // x,y
	for (int i = 0; i < file->buffer->length;i++)
	{
		Buffer* buf = file->buffer->buffers[i];
		bool breakMe = false;
		for (int j = 0; j < buf->length; j++)
		{
			String* line = buf->lines[j];
			int posX = find_substring(line->characters, newString->characters);
			if (posX != -1)
			{
				_line = line;
				loc[0] = posX;
				loc[1] = i * BUFFER_CAPACITY + j + 1;
				breakMe = true;
				break;
			}
		}
		if (breakMe) break;
	}

	if (loc[0] != -1)
	{
		int charNum = loc[0];
		int lineNum = loc[1];
		printf(
			"\nThe search string '%s' found at line number '%d' in position '%d'",
			newString->characters,
			lineNum,
			charNum
		);
		printf("\n\n%d |%s", lineNum, _line->characters);
		if (_line->characters[_line->length-1] != '\n') printf("\n");
		for (int i = 0; i < charNum + (lineNum > 9 ? 4 : 3); i++) printf(" ");
		printf("^\n");
	}
	else
	{
		printf("\n ---- The search string '%s' not found ! ---- \n ");
	}

	printf("\n\n Enter your choice :- \n\n");
	printf("1.) Search Again \n");
	printf("2.) Home\n");
	printf("3.) Exit\n");
	printf(" >> ");

	scanf("%d", &choice);
	switch (choice)
	{
	case 1: searchScreen(file); break;
	case 2: start(file); break;
	case 3: return;
	default: searchScreen(file);
	}
}

void editScreen(File* file)
{

	int choice; // insertMODE : 1 -> before , 2 -> after
	String* newString = createString("");
	int lineNum;

	clrscr();
	printf("filepath : \"%s\"\n\n", file->path->characters);
	printFileBuffer(file->buffer, 10);

	printf("\n\n Enter your Choice ( in interger ) :-\n\n");
	printf("1.) Proceed to Edit\n");
	printf("2.) Home\n");
	printf("3.) Exit\n");
	printf("\n >> ");

	scanf("%d", &choice);
	switch (choice)
	{

	case 1: break;
	case 2: start(file); break;
	case 3: return;
	default:
		editScreen(file);
	}

	printf("\nEdit line number : ");
	scanf("%d", &lineNum);

	printf("type new line : ");
	char _c; scanf("%c", &_c);
	readString(newString);
	addChar(newString, '\n');

	int bufferIndex = lineNum / BUFFER_CAPACITY;
	int linePos = lineNum - 1 % BUFFER_CAPACITY;

	String* oldString = file->buffer->buffers[bufferIndex]->lines[linePos];
	file->buffer->buffers[bufferIndex]->lines[linePos] = newString;

	printf("\n --- line number %d is edited --- \n");
	printf(" old : '%s'\n", oldString->characters);
	printf(" new : '%s'\n", newString->characters);

	freeString(oldString);

	printf("\n\n Enter your choice :- \n\n");
	printf("1.) Edit more\n");
	printf("2.) Home\n");
	printf("3.) Exit\n");
	printf(" >> ");

	scanf("%d", &choice);
	switch (choice)
	{
	case 1: editScreen(file); break;
	case 2: start(file); break;
	case 3: return;
	default: editScreen(file);
	}

}

void viewScreen(File* file)
{
	int choice;

	clrscr();
	printf("filepath : \"%s\"\n\n", file->path->characters);
	printFileBuffer(file->buffer, BUFFER_CAPACITY * file->buffer->length);

	printf("\n\n Enter your Choice ( in interger ) :-\n\n");
	printf("1.) HOME\n");
	printf("2.) EXIT\n >> ");

	scanf("%d", &choice);
	switch (choice)
	{
	case 1: start(file); break;
	case 2: return; break;
	default: viewScreen(file);
	}
}

void saveScreen(File* file)
{
	int choice;

	clrscr();
	printf("filepath : \"%s\"\n\n", file->path->characters);
	printFileBuffer(file->buffer, BUFFER_CAPACITY * file->buffer->length);

	printf("\n\n Do you wanna save the file( in interger ) :-\n\n");
	printf("1.) Yes\n");
	printf("2.) No\n >> ");

	scanf("%d", &choice);
	if (choice == 1)
	{
		saveFile(file);
		printf("\n --- FILE SAVED --- \n");
	}

	printf("\n\n Enter your Choice ( in interger ) :-\n\n");
	printf("1.) HOME\n");
	printf("2.) EXIT\n >> ");

	scanf("%d", &choice);
	switch (choice)
	{
	case 1: start(file); break;
	case 2: return; break;
	default: viewScreen(file);
	}
}
