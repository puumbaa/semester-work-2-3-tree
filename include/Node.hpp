#pragma once
#ifndef SEMESTER_WORK_TEMPLATE_NODE_H
#define SEMESTER_WORK_TEMPLATE_NODE_H
#endif

namespace itis {


    struct Node {
        int size;
        int key[3];
        Node *first{nullptr};
        Node *second{nullptr};
        Node *third{nullptr};
        Node *fourth{nullptr};
        Node *parent{nullptr};

        bool find(int k); // поиск ключа в вершине

        static void swap(int &x, int &y); // вспомогательная операция, используется в сортировке

        static void sort2(int &x, int &y); // вспомогательная операция, используется в сортировке

        static void sort3(int &x, int &y, int &z); // вспомогательная операция, используется в сортировке

        void sort(); // сортировка ключей в вершине

        void insert_to_node(int k); // вставка ключа в вершину

        void remove_from_node(int k); // удаление ключа из вершины

        void become_node2(int k, Node *first_, Node *second_); // преобразование в 2-вершину

        bool is_leaf() const; // является ли вершина листом

        explicit Node(int k, Node *first_ = nullptr, Node *second_ = nullptr, Node *third_ = nullptr,
                      Node *fourth_ = nullptr, Node *parent_ = nullptr);

    };


}