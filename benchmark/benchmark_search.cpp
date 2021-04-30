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

    // работа с набором данных
    const auto path = string(kDatasetPath);
    cout << "Path to the 'dataset/' folder: " << path << endl;


    auto input_file = ifstream(path);

    string line;
    vector<int> vector;
    DataStructure *dataStructure = new DataStructure(new Node(0, nullptr, nullptr, nullptr));
    for (int v = 0; v < 10; v++) {
        // чтение и обработка набора данных ...
        input_file = ifstream(path + "\\data" + to_string(v) + ".csv");
        while (getline(input_file, line, ',')) {
            vector.push_back(stoi(line));
            dataStructure->Insert(stoi(line));
        }
        // Контрольный тест: поиск
        // Для каждого из 10 наборов чисел вызывается метод Search 10 раз

        for (int j = 0; j < 10; j++) {

            const auto time_point_before = chrono::steady_clock::now();

            for (int i = 0; i < vector.size(); i++) {

                dataStructure->Search(vector[i]);
            }

            const auto time_point_after = chrono::steady_clock::now();


            dataStructure->Clear();

            // переводим время в наносекунды
            const auto time_diff = time_point_after - time_point_before;
            const auto time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();

            cout << time_elapsed_ns / 1000000 << endl;
        }
    }
    vector.clear();

    return 0;
}
