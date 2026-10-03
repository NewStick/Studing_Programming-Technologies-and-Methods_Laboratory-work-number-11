#include "connected_libraries.h"

// Создаёт C-строку из count_of_spaces пробелов
// Память выделяется через new[], освобождать нужно через delete[]
char* create_string_of_spaces(int count_of_spaces)
{
	char* result = new char[count_of_spaces + 1];

	for (int i = 0; i < count_of_spaces; ++i)
	{
		result[i] = ' ';
	}

	result[count_of_spaces] = '\0';

	return result;
}

// Печатает строку с отступом и сама освобождает память под отступ
void print_with_indent(int count_of_spaces, const char* text)
{
	char* indent = create_string_of_spaces(count_of_spaces);
	std::cout << std::endl << indent << text ;
	delete[] indent;
}