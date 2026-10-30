
#include "connected_libraries.h"

#pragma region Функции создания и заполнения матрицы

// Получение количества строк матрицы
int user_matrix_get_rows()
{
    int matrix_rows = 0;

    do
    {
        std::cout << std::endl << "Введите количество строк матрицы";
        std::cout << std::endl << "Ввод: ";
        std::cin >> matrix_rows;

        if (matrix_rows <= 0)
        {
            std::cout << std::endl << "Ошибка: количество строк должно быть больше нуля.";
        }
    } while (matrix_rows <= 0);

    return matrix_rows;
}

// Получение количества столбцов матрицы
int user_matrix_get_columns()
{
    int matrix_columns = 0;

    do
    {
        std::cout << std::endl << "Введите количество столбцов матрицы";
        std::cout << std::endl << "Ввод: ";
        std::cin >> matrix_columns;

        if (matrix_columns <= 0)
        {
            std::cout << std::endl << "Ошибка: количество столбцов должно быть больше нуля.";
        }
    } while (matrix_columns <= 0);

    return matrix_columns;
}

// Создание динамической матрицы и заполнение её значениями
int** user_matrix_create_and_get_values(int matrix_rows, int matrix_columns)
{
    int** user_matrix = new int* [matrix_rows];

    for (int i = 0; i < matrix_rows; i++)
    {
        user_matrix[i] = new int[matrix_columns];

        for (int j = 0; j < matrix_columns; j++)
        {
            std::cout << std::endl << "Введите значение элемента [" << i + 1 << "][" << j + 1 << "]";
            std::cout << std::endl << "Ввод: ";
            std::cin >> user_matrix[i][j];
        }
    }

    return user_matrix;
}

// Освобождение памяти динамической матрицы
void user_matrix_delete(int** user_matrix, int matrix_rows)
{
    for (int i = 0; i < matrix_rows; i++)
    {
        delete[] user_matrix[i];
    }

    delete[] user_matrix;
}

#pragma endregion

#pragma region Задание 2.1

// Поиск первого столбца, содержащего хотя бы один ноль
int find_first_column_with_zero(int** user_matrix, int matrix_rows, int matrix_columns)
{
    for (int j = 0; j < matrix_columns; j++)
    {
        for (int i = 0; i < matrix_rows; i++)
        {
            if (user_matrix[i][j] == 0)
            {
                return j;
            }
        }
    }

    return -1;
}

// Вывод найденного столбца и координат нулевых элементов
void print_first_column_with_zero(int** user_matrix, int matrix_rows, int matrix_column)
{
    std::cout << std::endl << "Первый столбец, содержащий нулевой элемент: " << matrix_column + 1;
    std::cout << std::endl << "Значения найденного столбца:";

    for (int i = 0; i < matrix_rows; i++)
    {
        std::cout << std::endl << "Координата: (" << i + 1 << ", " << matrix_column + 1 << "); Значение: "
            << user_matrix[i][matrix_column];
    }

    std::cout << std::endl << "Координаты нулевых элементов:";

    for (int i = 0; i < matrix_rows; i++)
    {
        if (user_matrix[i][matrix_column] == 0)
        {
            std::cout << std::endl << "(" << i + 1 << ", " << matrix_column + 1 << ")";
        }
    }
}

// Последовательность выполнения подзадачи 2.1
void pipeline_task2_subtask1()
{
    int matrix_rows = user_matrix_get_rows();
    int matrix_columns = user_matrix_get_columns();

    int** user_matrix = user_matrix_create_and_get_values(matrix_rows, matrix_columns);

    int first_column_with_zero = find_first_column_with_zero(
        user_matrix, matrix_rows, matrix_columns
    );

    if (first_column_with_zero == -1)
    {
        std::cout << std::endl << "В матрице отсутствуют нулевые элементы.";
    }
    else
    {
        print_first_column_with_zero(user_matrix, matrix_rows, first_column_with_zero);
    }

    user_matrix_delete(user_matrix, matrix_rows);

    return;
}

#pragma endregion


#pragma region Задание 2.2

// Вычисление характеристики строки матрицы
// Характеристика — сумма отрицательных чётных элементов
int get_matrix_row_characteristic(int* matrix_row, int matrix_columns)
{
    int row_characteristic = 0;

    for (int j = 0; j < matrix_columns; j++)
    {
        if (matrix_row[j] < 0 && matrix_row[j] % 2 == 0)
        {
            row_characteristic += matrix_row[j];
        }
    }

    return row_characteristic;
}

// Вывод матрицы вместе с характеристиками строк
void print_matrix_with_characteristics(int** user_matrix, int matrix_rows, int matrix_columns)
{
    std::cout << std::endl << "Матрица:";

    for (int i = 0; i < matrix_rows; i++)
    {
        std::cout << std::endl;

        for (int j = 0; j < matrix_columns; j++)
        {
            std::cout << user_matrix[i][j] << "\t";
        }

        int row_characteristic = get_matrix_row_characteristic(
            user_matrix[i], matrix_columns
        );

        std::cout << "| Характеристика: " << row_characteristic;
    }

    std::cout << std::endl;
}

// Сортировка строк матрицы по убыванию характеристик
void sort_matrix_rows_by_characteristics(int** user_matrix, int matrix_rows, int matrix_columns)
{
    // Сортировка пузырьковым методом
    for (int i = 0; i < matrix_rows - 1; i++)
    {
        for (int j = 0; j < matrix_rows - i - 1; j++)
        {
            int first_row_characteristic = get_matrix_row_characteristic(
                user_matrix[j], matrix_columns
            );

            int second_row_characteristic = get_matrix_row_characteristic(
                user_matrix[j + 1], matrix_columns
            );

            // Перестановка строк, если характеристика первой меньше второй
            if (first_row_characteristic < second_row_characteristic)
            {
                int* temporary_row = user_matrix[j];
                user_matrix[j] = user_matrix[j + 1];
                user_matrix[j + 1] = temporary_row;
            }
        }
    }
}

// Последовательность выполнения подзадачи 2.2
void pipeline_task2_subtask2()
{
    int matrix_rows = user_matrix_get_rows();
    int matrix_columns = user_matrix_get_columns();

    int** user_matrix = user_matrix_create_and_get_values(
        matrix_rows, matrix_columns
    );

    // Вывод исходной матрицы с характеристиками строк
    std::cout << std::endl << "Исходная матрица:";
    print_matrix_with_characteristics(user_matrix, matrix_rows, matrix_columns);

    // Сортировка строк по убыванию характеристик
    sort_matrix_rows_by_characteristics(user_matrix, matrix_rows, matrix_columns);

    // Вывод отсортированной матрицы с характеристиками строк
    std::cout << std::endl << "Матрица после сортировки:";
    print_matrix_with_characteristics(user_matrix, matrix_rows, matrix_columns);

    // Освобождение памяти матрицы
    user_matrix_delete(user_matrix, matrix_rows);

    return;
}

#pragma endregion
