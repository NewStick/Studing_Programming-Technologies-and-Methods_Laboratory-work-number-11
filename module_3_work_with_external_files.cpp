
#include "connected_libraries.h"

#pragma region Функции обработки UTF-8

// Получение Unicode-кода символа из UTF-8
// Возвращает количество байтов, занимаемых символом
int utf8_get_character(
    const char* text,
    int position,
    int text_length,
    unsigned int& character
)
{
    unsigned char first_byte = (unsigned char)text[position];

    if (first_byte < 0x80)
    {
        character = first_byte;
        return 1;
    }

    if ((first_byte & 0xE0) == 0xC0 && position + 1 < text_length)
    {
        character = ((first_byte & 0x1F) << 6) |
            ((unsigned char)text[position + 1] & 0x3F);

        return 2;
    }

    if ((first_byte & 0xF0) == 0xE0 && position + 2 < text_length)
    {
        character = ((first_byte & 0x0F) << 12) |
            (((unsigned char)text[position + 1] & 0x3F) << 6) |
            ((unsigned char)text[position + 2] & 0x3F);

        return 3;
    }

    if ((first_byte & 0xF8) == 0xF0 && position + 3 < text_length)
    {
        character = ((first_byte & 0x07) << 18) |
            (((unsigned char)text[position + 1] & 0x3F) << 12) |
            (((unsigned char)text[position + 2] & 0x3F) << 6) |
            ((unsigned char)text[position + 3] & 0x3F);

        return 4;
    }

    character = 0;
    return 0;
}

// Проверка, является ли символ английской или русской буквой
bool is_supported_letter(unsigned int character)
{
    if (character >= 'A' && character <= 'Z') return true;
    if (character >= 'a' && character <= 'z') return true;

    if (character >= 0x0410 && character <= 0x044F) return true;
    if (character == 0x0401 || character == 0x0451) return true;

    return false;
}

// Преобразование заглавных английских и русских букв в строчные
unsigned int utf8_to_lower(unsigned int character)
{
    if (character >= 'A' && character <= 'Z')
    {
        return character + 32;
    }

    if (character >= 0x0410 && character <= 0x042F)
    {
        return character + 32;
    }

    if (character == 0x0401)
    {
        return 0x0451;
    }

    return character;
}

// Сравнение двух UTF-8 слов без учёта регистра
bool utf8_compare_words(const char* first_word, const char* second_word)
{
    int first_word_length = 0;
    int second_word_length = 0;

    while (first_word[first_word_length] != '\0')
    {
        first_word_length++;
    }

    while (second_word[second_word_length] != '\0')
    {
        second_word_length++;
    }

    int first_position = 0;
    int second_position = 0;

    while (
        first_position < first_word_length &&
        second_position < second_word_length
        )
    {
        unsigned int first_character = 0;
        unsigned int second_character = 0;

        int first_character_bytes = utf8_get_character(
            first_word,
            first_position,
            first_word_length,
            first_character
        );

        int second_character_bytes = utf8_get_character(
            second_word,
            second_position,
            second_word_length,
            second_character
        );

        if (first_character_bytes == 0 || second_character_bytes == 0)
        {
            return false;
        }

        first_character = utf8_to_lower(first_character);
        second_character = utf8_to_lower(second_character);

        if (first_character != second_character)
        {
            return false;
        }

        first_position += first_character_bytes;
        second_position += second_character_bytes;
    }

    return first_position == first_word_length &&
        second_position == second_word_length;
}

#pragma endregion

#pragma region Функции чтения текстового файла

// Получение пути к текстовому файлу
void user_file_get_path(char* file_path)
{
    std::cout << std::endl << "Введите путь к текстовому файлу";
    std::cout << std::endl << "Ввод: ";

    // Пропуск оставшихся пробельных символов после предыдущего ввода
    std::cin >> std::ws;
    std::cin.getline(file_path, 260);

    // Удаление кавычек в начале и конце пути
    int file_path_length = 0;

    while (file_path[file_path_length] != '\0')
    {
        file_path_length++;
    }

    if (
        file_path_length >= 2 &&
        file_path[0] == '"' &&
        file_path[file_path_length - 1] == '"'
        )
    {
        for (int i = 0; i < file_path_length - 1; i++)
        {
            file_path[i] = file_path[i + 1];
        }

        file_path[file_path_length - 2] = '\0';
    }
}

// Чтение содержимого файла в динамический символьный массив
char* user_file_read_text(const char* file_path, int& text_length)
{
    // Преобразование UTF-8 пути в UTF-16 для Windows API
    wchar_t wide_file_path[260];

    int conversion_result = MultiByteToWideChar(
        CP_UTF8,
        MB_ERR_INVALID_CHARS,
        file_path,
        -1,
        wide_file_path,
        260
    );

    if (conversion_result == 0)
    {
        std::cout << std::endl << "Ошибка: не удалось преобразовать путь к файлу.";
        text_length = -1;
        return nullptr;
    }

    // Открытие файла через Windows API
    HANDLE input_file = CreateFileW(
        wide_file_path,
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (input_file == INVALID_HANDLE_VALUE)
    {
        std::cout << std::endl << "Ошибка: не удалось открыть файл.";
        text_length = -1;
        return nullptr;
    }

    // Получение размера файла
    LARGE_INTEGER file_size;

    if (!GetFileSizeEx(input_file, &file_size))
    {
        std::cout << std::endl << "Ошибка: не удалось определить размер файла.";

        CloseHandle(input_file);
        text_length = -1;

        return nullptr;
    }

    if (file_size.QuadPart <= 0)
    {
        std::cout << std::endl << "Ошибка: файл пуст.";

        CloseHandle(input_file);
        text_length = -1;

        return nullptr;
    }

    // Проверка, помещается ли размер файла в используемый тип int
    if (file_size.QuadPart > 2147483647LL)
    {
        std::cout << std::endl << "Ошибка: размер файла слишком большой.";

        CloseHandle(input_file);
        text_length = -1;

        return nullptr;
    }

    text_length = (int)file_size.QuadPart;

    // Выделение памяти под содержимое файла
    char* file_text = new char[text_length + 1];

    DWORD bytes_read = 0;

    // Чтение содержимого файла
    BOOL read_result = ReadFile(
        input_file,
        file_text,
        (DWORD)text_length,
        &bytes_read,
        nullptr
    );

    CloseHandle(input_file);

    if (!read_result || bytes_read != (DWORD)text_length)
    {
        std::cout << std::endl << "Ошибка: не удалось полностью прочитать файл.";

        delete[] file_text;
        text_length = -1;

        return nullptr;
    }

    file_text[text_length] = '\0';

    return file_text;
}

#pragma endregion

#pragma region Функции поиска самого длинного слова

// Поиск самого длинного слова в тексте
void find_longest_word(
    const char* file_text,
    int text_length,
    char* longest_word,
    int& longest_word_length
)
{
    // Выделение памяти под текущее слово
    char* current_word = new char[text_length + 1];

    int current_word_length = 0;
    int current_word_character_count = 0;

    int current_character_position = 0;

    longest_word_length = 0;
    longest_word[0] = '\0';

    while (current_character_position < text_length)
    {
        unsigned int character = 0;

        int character_bytes = utf8_get_character(
            file_text,
            current_character_position,
            text_length,
            character
        );

        if (character_bytes == 0)
        {
            current_character_position++;
            continue;
        }

        if (is_supported_letter(character))
        {
            // Проверка доступного места в массиве
            if (current_word_length <= text_length - character_bytes)
            {
                // Копирование исходных байтов UTF-8 символа
                for (int i = 0; i < character_bytes; i++)
                {
                    current_word[current_word_length] =
                        file_text[current_character_position + i];

                    current_word_length++;
                }

                current_word_character_count++;
            }
        }
        else
        {
            // Обработка завершённого слова
            if (current_word_length > 0)
            {
                current_word[current_word_length] = '\0';

                // Проверка, является ли слово самым длинным
                if (current_word_character_count > longest_word_length)
                {
                    longest_word_length = current_word_character_count;

                    for (int i = 0; i <= current_word_length; i++)
                    {
                        longest_word[i] = current_word[i];
                    }
                }

                current_word_length = 0;
                current_word_character_count = 0;
            }
        }

        current_character_position += character_bytes;
    }

    // Проверка последнего слова, если файл заканчивается буквой
    if (current_word_length > 0)
    {
        current_word[current_word_length] = '\0';

        if (current_word_character_count > longest_word_length)
        {
            longest_word_length = current_word_character_count;

            for (int i = 0; i <= current_word_length; i++)
            {
                longest_word[i] = current_word[i];
            }
        }
    }

    // Освобождение памяти текущего слова
    delete[] current_word;
}

// Подсчёт количества вхождений самого длинного слова
int count_longest_word_occurrences(
    const char* file_text,
    int text_length,
    const char* longest_word
)
{
    char* current_word = new char[text_length + 1];

    int current_word_length = 0;
    int counter_for_occurrences = 0;

    int current_character_position = 0;

    while (current_character_position < text_length)
    {
        unsigned int character = 0;

        int character_bytes = utf8_get_character(
            file_text,
            current_character_position,
            text_length,
            character
        );

        if (character_bytes == 0)
        {
            current_character_position++;
            continue;
        }

        if (is_supported_letter(character))
        {
            // Проверка доступного места в массиве
            if (current_word_length <= text_length - character_bytes)
            {
                // Копирование исходных байтов UTF-8 символа
                for (int i = 0; i < character_bytes; i++)
                {
                    current_word[current_word_length] =
                        file_text[current_character_position + i];

                    current_word_length++;
                }
            }
        }
        else
        {
            // Проверка завершённого слова
            if (current_word_length > 0)
            {
                current_word[current_word_length] = '\0';

                if (utf8_compare_words(current_word, longest_word))
                {
                    counter_for_occurrences++;
                }

                current_word_length = 0;
            }
        }

        current_character_position += character_bytes;
    }

    // Проверка последнего слова в файле
    if (current_word_length > 0)
    {
        current_word[current_word_length] = '\0';

        if (utf8_compare_words(current_word, longest_word))
        {
            counter_for_occurrences++;
        }
    }

    // Освобождение памяти текущего слова
    delete[] current_word;

    return counter_for_occurrences;
}

#pragma endregion

#pragma region Задание 3

// Последовательность выполнения задания 3
void pipeline_task3_subtask1()
{
    char file_path[260];

    user_file_get_path(file_path);

    int text_length = 0;

    // Чтение содержимого файла
    char* file_text = user_file_read_text(file_path, text_length);

    // Проверка успешности чтения файла
    if (file_text == nullptr)
    {
        return;
    }

    // Выделение памяти под самое длинное слово
    char* longest_word = new char[text_length + 1];

    int longest_word_length = 0;

    // Поиск самого длинного слова
    find_longest_word(
        file_text,
        text_length,
        longest_word,
        longest_word_length
    );

    if (longest_word_length == 0)
    {
        std::cout << std::endl << "В файле отсутствуют слова.";
    }
    else
    {
        // Подсчёт количества вхождений найденного слова
        int counter_for_occurrences = count_longest_word_occurrences(
            file_text,
            text_length,
            longest_word
        );

        std::cout << std::endl << "Самое длинное слово: " << longest_word;
        std::cout << std::endl << "Длина слова: " << longest_word_length;
        std::cout << std::endl << "Количество вхождений: " << counter_for_occurrences;
    }

    // Освобождение выделенной памяти
    delete[] longest_word;
    delete[] file_text;

    return;
}

#pragma endregion
