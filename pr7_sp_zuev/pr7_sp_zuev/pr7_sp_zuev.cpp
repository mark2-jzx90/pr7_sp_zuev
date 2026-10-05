// pr7_sp_zuev.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define DEBUG_MODE
using namespace std;
#include <string>
#include <fstream>
#include<sstream>


struct Car {
    string brand;
    string model;
    string number;
    double price;
    int days;
    string status;
};




int main()
{
    setlocale(NULL, "Russian");
    const int max_cars = 100;
    Car cars[max_cars];
    int carsCount = 0;

    string filename = "cars.txt";



    try {
        ifstream file{ filename };
        if (!file.is_open()) {
            throw runtime_error("Файл не существует");
        }


        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            if (carsCount >= max_cars) {
                cout << "Массив заполен";
                break;
            }
            try {
                stringstream ss(line);
                string fields[6];
                int fieldIdx = 0;

                string tempField;
                while (getline(ss, tempField, ';') && fieldIdx < 6) {
                    fields[fieldIdx] = tempField;
                    fieldIdx++;
                }
                if (fieldIdx < 6) {
                    throw runtime_error("Строка файла содержит недостаточно данных");
                }

                cars[carsCount].brand = fields[0];
                cars[carsCount].model = fields[1];
                cars[carsCount].number = fields[2];

                try {
                    cars[carsCount].price = stod(fields[3]);
                    cars[carsCount].days = stod(fields[4]);
                }
                catch (...) {
                    throw runtime_error("Числовое знчн. имеет неккоректный формат");
                }
                if (cars[carsCount].price < 0 || cars[carsCount].days < 0) {
                    throw runtime_error("Число выходит за допустимые пределы");
                }
                cars[carsCount].status = fields[5];
                carsCount++;
            }
            catch (const exception e) {
                cout << "Ошибка при разборе строки" << e.what();
            }
        }
        file.close();
#ifdef DEBUG_MODE
        cout << "откладка лол. Загружено записей: " << carsCount << endl;
#endif // DEBUG_MODE
    }
    catch (const exception e) {
        cout << "Ошибка: " << e.what();
        return 1;
    }


    int choose = 0;
    while (choose != 7) {
        cout << "1. Поиск машинкике\n";
        cout << "2. Вывод свободных машинок\n";
        cout << "3. Оформление аренды\n";
        cout << "4. Расчёт стоимости аренды\n";
        cout << "5. Возрат машинки\n";
        cout << "6. Сохранение изменений\n";
        cout << "7. Выход\n";
        cout << "ВЫБЕРИ ДЕЙСВТИИЕ вась ОТ 1 ДО 7: \n";
        cin >> choose;




        //поиск авто
        if (choose == 1) {
            string searchBrand;
            cout << "Введи марку для поиска машинки: ";
            cin >> searchBrand;
            for (int i = 0; i < carsCount; i++) {
                if (cars[i].brand == searchBrand) {
                    cout << cars[i].brand << " " << cars[i].model << " (" << cars[i].number << ") -" << cars[i].status << endl;
                }
            }
        }


        // вывод свобод автомобилей
        else if (choose == 2) {
            cout << "\nСвободные машины:\n";
            for (int i = 0; i < carsCount; i++) {
                if (cars[i].status == "Svoboden") {
                    cout << cars[i].brand << " " << cars[i].model << " [" << cars[i].number << "], Цена: " << cars[i].price << endl;
                }
            }
        }
        //оформление аренды
        else if (choose == 3) {
            string num;
            cout << "Введи гос. номер машины для аренды вась: ";
            cin >> num;
            bool found = false;
            for (int i = 0; i < carsCount; i++) {
                if (cars[i].number == num) {
                    found = true;
                    try {
                        if (cars[i].status == "Занят") {
                            throw runtime_error("Выполняемая операция невозможна (тачка уже занята)!");
                        }
                        int days;
                        cout << "На сколько дней арендуешь вась? ";
                        cin >> days;
                        if (days <= 0) {
                            throw runtime_error("Числовое значение выходит за допустимые пределы вась");
                        }

                       
                        cars[i].status = "Zanyat";
                        cars[i].days = days;
                        cout << "Успешно арендовано вась!\n";
                    }
                    catch (const exception e) {
                        cout << "Ошибка: " << e.what() << endl;
                    }
                }
            }
            if (!found) cout << "Машина с таким номером не найдена вась\n";
        }
        //стоимость аренды
        else if (choose == 4) {
            string num;
            cout << "Введи гос. номер машины для расчета цены: ";
            cin >> num;
            bool found = false;
            for (int i = 0; i < carsCount; i++) {
                if (cars[i].number == num) {
                    found = true;
                    cout << "Общая стоимость аренды: " << cars[i].price * cars[i].days << " руб.\n";
                }
            }
            if (!found) cout << "Машина не найдена вась\n";
        }
        //Возврат автомобиля
        else if (choose == 5) {
            string num;
            cout << "Введи гос. номер машины для возврата: ";
            cin >> num;
            bool found = false;
            for (int i = 0; i < carsCount; i++) {
                if (cars[i].number == num) {
                    found = true;
                    cars[i].status = "Svoboden";
                    cars[i].days = 0;
                    cout << "Машина успешно возвращена вась\n";
                }
            }
            if (!found) cout << "Машина не найдена вась\n";
        }
        //Сохранение измен в файл
        else if (choose == 6) {
            ofstream outFile(filename);
            if (outFile.is_open()) {
                for (int i = 0; i < carsCount; i++) {
                    outFile << cars[i].brand << ";" << cars[i].model << ";" << cars[i].number << ";"
                        << cars[i].price << ";" << cars[i].days << ";" << cars[i].status << "\n";
                }
                outFile.close();
                cout << "Изменения сохранены в файл вась лол!\n";
#ifdef DEBUG_MODE
                cout << "успешно записано в файл записей: " << carsCount << endl;
#endif
            }
            else {
                cout << "файл не открыт.\n";
            }
        }
    }

    return 0;
}



    


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
