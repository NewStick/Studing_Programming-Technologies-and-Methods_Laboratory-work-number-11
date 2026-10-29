// ИЗ-21 - ТиМП - Лаб 1 - Вар 13 - Куприянов.cpp
// Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include "connected_libraries.h"

int main()
{
    // Устанавливаем UTF-8 для консоли Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Приветсвенная часть программы
    std::cout << std::endl << " = = = = = = = = = = = = = = = = = = = " << std::endl;
    std::cout << std::endl << "Программа: Решение лабораторной работы №1";
    std::cout << std::endl << "Разработчик: Куприянов Никита Сергеевич, ИЗ-21" << std::endl;
    std::cout << std::endl << " = = = = = = = = = = = = = = = = = = = " << std::endl << std::endl;

    // Однократный вывод описания лабораторных заданий.
    user_interface_show_task();

    std::cout << std::endl << " = = = = = = = = = = = = = = = = = = = " << std::endl << std::endl;

    // Основной цикл работы приложения.
    bool should_exit = false;

    while (!should_exit)
    {
        should_exit = user_interface_start_main();
    }

    std::cout << std::endl << "Программа завершает свою работу..." << std::endl;

    return 0;
}
