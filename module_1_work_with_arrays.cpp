#include "connected_libraries.h"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Функции для создания и заполнения одномерного массива
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int user_array_get_length()
{
    int array_length;

    do
    {
        std::cout << std::endl << "Введите длину массива";
        std::cout << std::endl << "Ввод: ";
        std::cin >> array_length;

        if (array_length <= 0)
        {
            std::cout << std::endl << "Ошибка: длина массива должна быть больше нуля.";
        }

    } while (array_length <= 0);

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
        user_array[i] = user_array_get_value(i + 1);
    }

    return user_array;
}

double get_value_for_element_c()
{
    double element_c;

    std::cout << std::endl << "Введите значение элемента C";
    std::cout << std::endl << "Ввод: ";
    std::cin >> element_c;

    return element_c;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Задание 1.1. Поиск элементов, больших C
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void find_coordinates_and_values_greater_than_c(double* user_array, int user_array_length, double element_c)
{
    int counter_for_found_elements = 0;

    // Подсчитываем количество элементов, больших C.
    for (int i = 0; i < user_array_length; i++)
    {
        if (user_array[i] > element_c)
        {
            counter_for_found_elements++;
        }
    }

    std::cout << std::endl << "Ваше значение C = " << element_c;
    std::cout << std::endl << "Количество элементов, больших C: " << counter_for_found_elements;

    if (counter_for_found_elements == 0)
    {
        std::cout << std::endl << "В массиве отсутствуют элементы, большие C.";
        return;
    }

    // Выводим координаты и значения найденных элементов.
    std::cout << std::endl << "Найденные элементы массива:";

    for (int i = 0; i < user_array_length; i++)
    {
        if (user_array[i] > element_c)
        {
            std::cout << std::endl << "Координата: " << i + 1;
            std::cout << std::endl << "Значение: " << user_array[i];
        }
    }
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Последовательное выполнение подзадачи 1.1
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void pipeline_task1_subtask1()
{
    // 1. Получаем размер массива.
    int user_array_length = user_array_get_length();

    // 2. Создаём массив и заполняем его значениями пользователя.
    double* user_array = user_array_create_and_get_values(user_array_length);

    // 3. Получаем значение C.
    double element_c = get_value_for_element_c();

    // 4. Находим и выводим количество, координаты и значения элементов, больших C.
    find_coordinates_and_values_greater_than_c(user_array, user_array_length, element_c);

    // 5. Освобождаем выделенную память.
    delete[] user_array;

    return;
}

void pipeline_task1_subtask2()
{
    std::cout << std::endl << "Подзадача 1.2 пока не реализована.";
}

void pipeline_task1_subtask3()
{
    std::cout << std::endl << "Подзадача 1.3 пока не реализована.";
}