#include <iostream>
#include <string>
#include <fstream>

//Хранение данных
struct Expense {
    std::string category;
    double price;
    std::string description;
    std::string date;
};

//Функция для ввода цены с проверкой
double validPrice() {
    double price;
    while (true) {
        std::cout << "Введите цену: ";
        std::cin >> price;

        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(1000000, '\n'); 
            std::cout << "Ошибка: введите корректное число.\n";
        }
        else {
            std::cin.ignore(1000, '\n'); 
            return price;
        }
    }
}

//Добавление новых расходов
void addExp(Expense* expenses, int& expCount) {
    Expense exp;

    std::cout << "Введите категорию: ";
    std::getline(std::cin, exp.category);

    exp.price = validPrice();

    std::cout << "Введите описание: ";
    std::getline(std::cin, exp.description);

    std::cout << "Введите дату: ";
    std::getline(std::cin, exp.date);

    expenses[expCount] = exp;
    expCount++;

    std::cout << "Расход добавлен.\n";
}

//Просмотр всех расходов
void checkAllExp(Expense* expenses, int expCount) {
    std::cout << "\nВсе расходы:\n";
    for (int i = 0; i < expCount; i++) {
        std::cout << "Расход: " << i + 1 << "\n";
        std::cout << "Категория: " << expenses[i].category << "\n";
        std::cout << "Цена: " << expenses[i].price << "\n";
        std::cout << "Описание: " << expenses[i].description << "\n";
        std::cout << "Дата: " << expenses[i].date << "\n";
        std::cout << "---------------------------\n";
    }
}

//Сумма всех расходов
double sumExp(Expense* expenses, int expCount) {
    long sum = 0;
    for (int i = 0; i < expCount; i++) {
        sum += expenses[i].price;
    }
    std::cout << "Сумма всех расходов: " << sum << "\n";
    return sum;
}

//Поиск по категории
void searchByCategory(Expense* expenses, int expCount) {
    bool found = false;
    std::string searchCategory;
    std::cout << "Введите категорию для поиска: ";
    std::getline(std::cin, searchCategory);
    std::cout << "\n";
    std::cout << "Поиск по категории: \n";
    for (int i = 0; i < expCount; i++) {
        if (expenses[i].category == searchCategory) {
            std::cout << "\nРасход: " << i + 1 << "\n";
            std::cout << "Категория: " << expenses[i].category << "\n";
            std::cout << "Цена: " << expenses[i].price << "\n";
            std::cout << "Описание: " << expenses[i].description << "\n";
            std::cout << "Дата: " << expenses[i].date << "\n";
            std::cout << "---------------------------\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Данная категория не найдена.\n";
    }
}

//Сохранение расходов в файл
void saveExpToFile(Expense* expenses, int expCount, const std::string& expfile) {
    std::ofstream outFile(expfile);

    if (!outFile) {
        std::cerr << "Ошибка при открытии файла для записи.\n";
        return;
    }

    for (int i = 0; i < expCount; ++i) {
        outFile << expenses[i].category << "\n"
            << expenses[i].price << "\n"
            << expenses[i].description << "\n"
            << expenses[i].date << "\n";
    }
    outFile.close();
    std::cout << "Данные успешно сохранены в файл " << expfile << ".\n";
}

//Загрузка из файла
void loadExpFromFile(Expense* expenses, int& expCount, const std::string& expfile) {
    std::ifstream inFile(expfile);

    if (!inFile) {
        std::cout << "Файл не найден или не может быть открыт. Начинаем с пустого списка.\n";
        return;
    }

    while (inFile) {
        Expense exp;
        std::getline(inFile, exp.category);
        if (exp.category.empty())
            break;

        inFile >> exp.price;
        inFile.ignore();
        std::getline(inFile, exp.description);
        std::getline(inFile, exp.date);

        expenses[expCount++] = exp;
    }

    inFile.close();
    std::cout << "Данные успешно загружены из файла " << expfile << ".\n";
}

//Удаление расхода
void delExp(Expense* expenses, int& expCount) {
    int index;
    std::cout << "Введите номер расхода для удаления (от 1 до " << expCount << "): ";
    std::cin >> index;
    std::cin.ignore();

    if (index < 1 || index > expCount) {
        std::cout << "Неверный номер расхода.\n";
        return;
    }

    for (int i = index - 1; i < expCount - 1; i++) {
        expenses[i] = expenses[i + 1];
    }
    expCount--;

    std::cout << "Расход удален.\n";
}

void bubbleSortByPriceUp(Expense* expenses, int expCount) {
    for (int i = 0; i < expCount - 1; ++i) {
        for (int j = 0; j < expCount - 1 - i; ++j) {
            if (expenses[j].price > expenses[j + 1].price) {
                std::swap(expenses[j], expenses[j + 1]);
            }
        }
    }
}

void bubbleSortByPriceDown(Expense* expenses, int expCount) {
    for (int i = 0; i < expCount - 1; ++i) {
        for (int j = 0; j < expCount - 1 - i; ++j) {
            if (expenses[j].price < expenses[j + 1].price) {
                std::swap(expenses[j], expenses[j + 1]);
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    Expense expenses[100];
    int expCount = 0;

    int choice;
    bool run = true;

    std::string expfile = "exp.txt";
    loadExpFromFile(expenses, expCount, expfile);

    while (run) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить расход\n";
        std::cout << "2. Просмотреть все расходы\n";
        std::cout << "3. Подсчитать общую сумму расходов\n";
        std::cout << "4. Поиск по категории\n";
        std::cout << "5. Сохранить данные\n";
        std::cout << "6. Удалить расход\n";
        std::cout << "7. Сортировка расходов\n"; 
        std::cout << "8. Выйти\n";
        std::cout << "Выберите действие (1-8): ";
        while (!(std::cin >> choice) || choice < 1 || choice > 8) {
            std::cin.clear(); 
            std::cin.ignore(1000, '\n'); 
            std::cout << "Неверный выбор! Пожалуйста, введите число от 1 до 8: ";
        }
        std::cin.ignore();

        switch (choice) {
        case 1:
            addExp(expenses, expCount);
            break;
        case 2:
            checkAllExp(expenses, expCount);
            break;
        case 3:
            sumExp(expenses, expCount);
            break;
        case 4:
            searchByCategory(expenses, expCount);
            break;
        case 5:
            saveExpToFile(expenses, expCount, expfile);
            break;
        case 6:
            delExp(expenses, expCount);
            saveExpToFile(expenses, expCount, expfile);
            break;
        case 7:
            int sortChoice;
            std::cout << "\nВыберите способ сортировки:\n";
            std::cout << "1. По цене (по возрастанию)\n";
            std::cout << "2. По цене (по убыванию)\n";
            std::cout << "Выберите вариант (1-2): ";

            while (!(std::cin >> sortChoice) || sortChoice < 1 || sortChoice > 2) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Неверный выбор! Пожалуйста, введите число 1 или 2: ";
            }
            switch (sortChoice) {
            case 1:
                bubbleSortByPriceUp(expenses, expCount);
                break;
            case 2:
                bubbleSortByPriceDown(expenses, expCount);
                break;
            }
            break;
        case 8:
            run = false;
            std::cout << "Выход из программы.\n";
            break;
        }
    }
    return 0;
}
