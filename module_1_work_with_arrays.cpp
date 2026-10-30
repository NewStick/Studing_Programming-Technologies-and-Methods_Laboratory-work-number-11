#include "connected_libraries.h"

// Получение длины массива от пользователя
int user_array_get_length()
{
    int array_length = 0;
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

// Получение значения одного элемента массива
double user_array_get_value(int iteration_number)
{
    double user_array_value;

    std::cout << std::endl << "Введите значение для " << iteration_number << " элемента массива";
    std::cout << std::endl << "Ввод: ";
    std::cin >> user_array_value;

    return user_array_value;
}

// Создание динамического массива и заполнение его значениями пользователя
double* user_array_create_and_get_values(int user_array_length)
{
    double* user_array = new double[user_array_length];

    for (int i = 0; i < user_array_length; i++)
    {
        user_array[i] = user_array_get_value(i + 1);
    }

    return user_array;
}

#pragma region Задание 1.1

// Получение значения элемента C
double get_value_for_element_c()
{
    double element_c;

    std::cout << std::endl << "Введите значение элемента C";
    std::cout << std::endl << "Ввод: ";
    std::cin >> element_c;

    return element_c;
}

// Найти количество и координаты элементов, больших C
void find_coordinates_and_values_greater_than_c(double* user_array, int user_array_length, double element_c)
{
    int counter_for_found_elements = 0;

    // Подсчёт количества элементов, которые больше C
    for (int i = 0; i < user_array_length; i++)
    {
        if (user_array[i] > element_c)
        {
            counter_for_found_elements++;
        }
    }

    std::cout << std::endl << "Ваше значение C = " << element_c;
    std::cout << std::endl << "Количество элементов, больших C: " << counter_for_found_elements;

    // Если подходящих элементов нет, завершаем выполнение функции
    if (counter_for_found_elements == 0)
    {
        std::cout << std::endl << "В массиве отсутствуют элементы, большие C.";
        return;
    }

    // Вывод координат и значений найденных элементов
    std::cout << std::endl << "Найденные элементы массива:";

    for (int i = 0; i < user_array_length; i++)
    {
        if (user_array[i] > element_c)
        {
            std::cout << std::endl << "Координата: " << i + 1 << "; Значение: " << user_array[i];
        }
    }

    std::cout << std::endl;
}

// Последовательность выполнения подзадачи 1.1
void pipeline_task1_subtask1()
{
    int user_array_length = user_array_get_length();
    double* user_array = user_array_create_and_get_values(user_array_length);
    double element_c = get_value_for_element_c();

    find_coordinates_and_values_greater_than_c(user_array, user_array_length, element_c);

    // Освобождение памяти, выделенной под массив
    delete[] user_array;

    return;
}

#pragma endregion

#pragma region Задание 1.2

// Получение длины массива — в массиве должно быть минимум три элемента
int user_array_get_length_for_task_1_2()
{
    int array_length = 0;

    do
    {
        std::cout << std::endl << "Введите длину массива (минимум 3 элемента)";
        std::cout << std::endl << "Ввод: ";
        std::cin >> array_length;

        if (array_length < 3)
        {
            std::cout << std::endl << "Ошибка: для выполнения подзадачи необходимо минимум 3 элемента.";
        }
    } while (array_length < 3);

    return array_length;
}

// Поиск максимального значения по модулю в массиве
double get_maximum_absolute_value(double* user_array, int user_array_length)
{
    // В качестве начального максимума берём модуль первого элемента
    double maximum_absolute_value = fabs(user_array[0]);

    for (int i = 1; i < user_array_length; i++)
    {
        // Сравнение модулей элементов массива
        if (fabs(user_array[i]) > maximum_absolute_value)
        {
            maximum_absolute_value = fabs(user_array[i]);
        }
    }

    return maximum_absolute_value;
}

// Подсчёт количества элементов с максимальным значением по модулю
int count_maximum_coordinates(double* user_array, int user_array_length, double maximum_absolute_value)
{
    int counter_for_maximum_coordinates = 0;

    for (int i = 0; i < user_array_length; i++)
    {
        if (fabs(user_array[i]) == maximum_absolute_value)
        {
            counter_for_maximum_coordinates++;
        }
    }

    return counter_for_maximum_coordinates;
}

// Вывод всех координат и значений элементов с максимальным модулем
void print_maximum_coordinates(double* user_array, int user_array_length, double maximum_absolute_value)
{
    std::cout << std::endl << "Максимальное значение по модулю: " << maximum_absolute_value;
    std::cout << std::endl << "Координаты элементов с максимальным модулем:";

    for (int i = 0; i < user_array_length; i++)
    {
        if (fabs(user_array[i]) == maximum_absolute_value)
        {
            std::cout << std::endl << "Координата: " << i + 1 << "; Значение: " << user_array[i];
        }
    }
}

// Подсчёт количества максимумов, после которых остаются минимум два элемента
int count_valid_maximum_coordinates(double* user_array, int user_array_length, double maximum_absolute_value)
{
    int counter_for_valid_coordinates = 0;

    // Последний допустимый индекс — user_array_length - 3
    // Поэтому цикл выполняется до индекса user_array_length - 3 включительно
    for (int i = 0; i < user_array_length - 2; i++)
    {
        if (fabs(user_array[i]) == maximum_absolute_value)
        {
            counter_for_valid_coordinates++;
        }
    }

    return counter_for_valid_coordinates;
}

// Получение координаты максимального элемента от пользователя
// Выбираемый элемент должен быть максимальным по модулю,
// а после него должны оставаться минимум два элемента
int user_array_get_maximum_coordinate(double* user_array, int user_array_length, double maximum_absolute_value)
{
    int selected_coordinate = 0;

    do
    {
        std::cout << std::endl << "Выберите координату максимального элемента";
        std::cout << std::endl << "Допустимые координаты: от 1 до " << user_array_length - 2;
        std::cout << std::endl << "Ввод: ";
        std::cin >> selected_coordinate;

        if (selected_coordinate < 1 || selected_coordinate > user_array_length - 2)
        {
            std::cout << std::endl << "Ошибка: выберите координату, после которой остаются минимум два элемента.";
        }
        else if (fabs(user_array[selected_coordinate - 1]) != maximum_absolute_value)
        {
            std::cout << std::endl << "Ошибка: выбранный элемент не является максимальным по модулю.";
        }

    } while (selected_coordinate < 1 || selected_coordinate > user_array_length - 2 ||
        fabs(user_array[selected_coordinate - 1]) != maximum_absolute_value);

    return selected_coordinate;
}

// Вычисление произведения элементов, расположенных после выбранного максимума
double calculate_product_after_maximum(double* user_array, int user_array_length, int maximum_coordinate)
{
    double product = 1;

    // Координата массива начинается с 1, а индекс C++ — с 0
    // Поэтому начинаем цикл с индекса, равного координате максимума
    for (int i = maximum_coordinate; i < user_array_length; i++)
    {
        product *= user_array[i];
    }

    return product;
}

// Поиск максимума, получение его координаты и вычисление произведения
void find_maximum_and_calculate_product_after_it(double* user_array, int user_array_length)
{
    // Поиск максимального значения по модулю
    double maximum_absolute_value = get_maximum_absolute_value(user_array, user_array_length);

    // Вывод всех координат элементов с максимальным модулем
    print_maximum_coordinates(user_array, user_array_length, maximum_absolute_value);

    // Проверка, есть ли хотя бы один максимум,
    // после которого остаются минимум два элемента
    int counter_for_valid_coordinates = count_valid_maximum_coordinates(
        user_array, user_array_length, maximum_absolute_value
    );

    if (counter_for_valid_coordinates == 0)
    {
        std::cout << std::endl << "Невозможно выполнить вычисление: после максимального элемента нет двух элементов." << std::endl;
        return;
    }

    // Получение координаты максимума, выбранной пользователем
    int maximum_coordinate = user_array_get_maximum_coordinate(
        user_array, user_array_length, maximum_absolute_value
    );

    // Вычисление произведения элементов после выбранного максимума
    double product = calculate_product_after_maximum(
        user_array, user_array_length, maximum_coordinate
    );

    std::cout << std::endl << "Выбранная координата максимального элемента: " << maximum_coordinate;
    std::cout << std::endl << "Произведение элементов после выбранного максимального элемента: " << product << std::endl;
}

// Последовательность выполнения подзадачи 1.2
void pipeline_task1_subtask2()
{
    int user_array_length = user_array_get_length_for_task_1_2();
    double* user_array = user_array_create_and_get_values(user_array_length);

    find_maximum_and_calculate_product_after_it(user_array, user_array_length);

    // Освобождение памяти, выделенной под массив
    delete[] user_array;

    return;
}

#pragma endregion

#pragma region Задание 1.3

// Вывод элементов массива
void print_user_array(double* user_array, int user_array_length)
{
    std::cout << std::endl << "Элементы массива:";

    for (int i = 0; i < user_array_length; i++)
    {
        std::cout << std::endl << "Координата: " << i + 1 << "; Значение: " << user_array[i];
    }

    std::cout << std::endl;
}

// Перестройка массива: сначала отрицательные элементы, затем неотрицательные
void rearrange_array_negative_and_nonnegative(double* user_array, int user_array_length)
{
    // Создание временного массива
    double* temporary_array = new double[user_array_length];

    int current_index = 0;

    // Запись отрицательных элементов
    for (int i = 0; i < user_array_length; i++)
    {
        if (user_array[i] < 0)
        {
            temporary_array[current_index] = user_array[i];
            current_index++;
        }
    }

    // Запись положительных элементов и нулей
    for (int i = 0; i < user_array_length; i++)
    {
        if (user_array[i] >= 0)
        {
            temporary_array[current_index] = user_array[i];
            current_index++;
        }
    }

    // Перенос элементов из временного массива в исходный
    for (int i = 0; i < user_array_length; i++)
    {
        user_array[i] = temporary_array[i];
    }

    // Освобождение временного массива
    delete[] temporary_array;
}

// Последовательность выполнения подзадачи 1.3
void pipeline_task1_subtask3()
{
    int user_array_length = user_array_get_length();
    double* user_array = user_array_create_and_get_values(user_array_length);

    std::cout << std::endl << "Исходный массив:";
    print_user_array(user_array, user_array_length);

    rearrange_array_negative_and_nonnegative(user_array, user_array_length);

    std::cout << std::endl << "Массив после перестановки:";
    print_user_array(user_array, user_array_length);

    // Освобождение памяти исходного массива
    delete[] user_array;

    return;
}

#pragma endregion

