#include <fstream>//
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds
#include <sstream>      // stringstream
#include <vector>
#include "data_structure.hpp"

// подключаем вашу структуру данных
#include "Node.hpp"

using namespace std;
using namespace itis;

// абсолютный путь до набора данных и папки проекта
static constexpr auto kDatasetPath = string_view{PROJECT_DATASET_DIR};
static constexpr auto kProjectPath = string_view{PROJECT_SOURCE_DIR};

int main() {

//    // Tip 1: входные аргументы позволяют более гибко контролировать работу вашей программы.
//    // Можете передать путь до входного/выходного тестового файла в качестве аргумента программы.
//
//    for (int index = 0; index < argc; index++) {
//        cout << "Arg: " << argv[index] << '\n';
//    }

    // Tip 2: для перевода строки в число можете использовать функцию stoi (string to integer)

    // можете использовать функционал класса stringstream для обработки строки
//    auto ss = stringstream("0 1 2");  // передаете строку (входной аргумент или строку из файла) и обрабатываете ее
//
//    int number = 0;
//    ss >> number;  // number = 0
//    ss >> number;  // number = 1
//    ss >> number;  // number = 2

    // работа с набором данных
    const auto path = string(kDatasetPath);
    cout << "Path to the 'dataset/' folder: " << path << endl;


    auto input_file = ifstream(path);

    string line;
    vector<int> vector;
    DataStructure *dataStructure = new DataStructure(new Node(0, nullptr, nullptr, nullptr));

    // чтение и обработка набора данных ...
    for (int v = 0; v < 10; v++) {
        input_file = ifstream(path + "\\data" + to_string(v) + ".csv");
        while (getline(input_file, line, ',')) {
            vector.push_back(stoi(line));
            dataStructure->Insert(stoi(line));
        }




        // Контрольный тест: операции добавления, удаления, поиска и пр. над структурой данных



        //создать файл csv и через новую строку туда пушить

        // Tip 3: время работы программы (или участка кода) можно осуществить
        // как изнутри программы (std::chrono), так и сторонними утилитами




        for (int j = 0; j < 10; j++) {

            const auto time_point_before = chrono::steady_clock::now();

            for (int i = 0; i < vector.size(); i++) {

                dataStructure->Remove(vector[i]);
            }


            // здесь находится участок кода, время которого необходимо замерить

            const auto time_point_after = chrono::steady_clock::now();

            // переводим время в наносекунды

            dataStructure->Clear();

            const auto time_diff = time_point_after - time_point_before;
            const auto time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();

            //cout << "Time elapsed (ns): " << time_elapsed_ns << '\n';
            cout << time_elapsed_ns / 1000000 << endl;
        }
    }
    vector.clear();

    return 0;
}
