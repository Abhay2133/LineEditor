#pragma warning(disable : 4996)
#include "test.h"
#include "LineEditor.h"
#include "myLib.h"
#include <stdio.h>

void testAll()
{

}

void test_dirname()
{
	String* s = createString("C:\\india\\name");
	String* dir;

}

void test_input_string()
{
	String* input = createString("");
	char c;
	while (1)
	{
		scanf("%c", &c);
		if (c == '\n') break;
		addChar(input, c);
	}
	printf("\n\ninput : '%s'\n", input->characters);

}


