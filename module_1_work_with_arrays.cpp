#include "connected_libraries.h"

int user_array_get_length()
{
	int array_length;

	std::cout << std::endl << "Введите длину массива";
	std::cout << std::endl << "Ввод: ";
	std::cin >> array_length;

	return array_length;
}

double user_array_get_value(int iteration_number)
{
	double user_array_value;

	std::cout << std::endl << "Введите значение для " << iteration_number << " элемента массива";
	std::cout << std::endl << "Ввод: ";
	std::cin >> user_array_value;

	return user_array_value;
}

double* user_array_create_and_get_values(int user_array_length)
{
	double* user_array = new double[user_array_length];

	for (int i = 0; i < user_array_length; i++)
	{
		user_array[i] = user_array_get_value(i);
	}

	return user_array;
}

double get_value_for_element_c()
{
	int element_c;

	std::cout << std::endl << "Введите значение для элемента C";
	std::cout << std::endl << "Ввод: ";
	std::cin >> element_c;

	return element_c;
}

void find_coordinates_and_values_more_then_element_c(double* user_array, int user_array_length, double element_c)
{
	// Выделяем память для: 
	// Счётчика найденых значений больших значения C

	int counter_for_fiend_elements = 0;

	// Реализуем цикл с перебором элементов пользовательского масисва
	// Ищеём элементы, которые больше элемента C
	// В случаях, когда элемент найден — увеличиваем значение счётчика

	for (int i = 0; i < user_array_length; i++)
	{
		if (user_array[i] > element_c )
		{
			counter_for_fiend_elements++;
		}
	}

	// Выделяем память для: 
	// 1. Массива элементов больших значения C
	// 2. Значение j для перемещения по массиву

	int* array_for_fiend_elements = new int[counter_for_fiend_elements];
	int j = 0;

	// Реализуем цикланалогичный прошлому
	// Но в этот раз сохраняем элементы в новый созданный массив
	
	for (int i = 0; i < user_array_length; i++)
	{
		if (user_array[i] > element_c)
		{
			array_for_fiend_elements[j] = user_array[i];
			j++;
		}
	}


	// Выводим полученные результаты:
	
	// 1. Полученное от пользователя значение элемента C
	std::cout << std::endl << "Ваше значение C = " << element_c;
	
	// 2. Количество найденых элементов строго больших значения элемента C
	std::cout << std::endl << "Количество элементов больших значения C: " << counter_for_fiend_elements;

	// 3. Значения найденых элементов строго больших значения элемента C
	std::cout << std::endl << "Список найденых элементов: ";

	for (int i = 0; i < counter_for_fiend_elements; i++)
	{
		std::cout << array_for_fiend_elements[i] << ", ";
	}

	// Очищаем память от созданных массивов
	delete[] array_for_fiend_elements;
	delete[] user_array;
}

void pipeline_task1_subtask1()
{
	// Задача: 
	// В одномерном массиве из N элементов 
	// Найти количество элементов больших C
	// 
	// Описание решаемой задачи по этапам:
	// 1. 
	// 2.

}