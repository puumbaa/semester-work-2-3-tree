#pragma once

#include "node.hpp"
// Заголовочный файл с объявлением структуры данных

namespace itis {

  struct DataStructure {

    DataStructure(Node* node);
    void Clear(); // Очистка дерева

    void Insert(int k);// Вставка в дерево;

    Node *Search(int k); // Поиск в дереве;

    void *Remove(int k); // Удаление ключа из дерева

    Node *root(); // Возвращает корень дерева

    int Height(); // Возвращает высоту дерева


    ~DataStructure(); // То же самое, что Clear


   private:
    Node *root_{nullptr}; // Корень 2-3 дерева

    static Node *merge(Node *leaf); // Слияние используется при удалении;

    Node *redistribute(Node *leaf); // Перераспределение также используется при удалении;

    Node *fix(Node *leaf); // Используется после удаления для возвращения свойств дереву (использует merge или redistribute)

    Node *split(Node *item); // Метод для разделение вершины при переполнении;

    void insert(int k, Node *node); // Вспомогательная функция, используется при вставке

    void clear(Node *node); // Вспомогательная функция, используется при очистке

    Node *search(int k, Node *node); // Вспомогательная функция, используется при поиске

    Node *remove(int k, Node *node); // Вспомогательная функуция, используется при удалении

    int height(Node *node); // Вспомогательная функция, используется при вычислении высоты

    Node *findMin(Node *p); // Поиск узла с минимальным значением ключа
  };
}