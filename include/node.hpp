//
// Created by user on 16.04.2021.
//
#pragma
#ifndef SEMESTER_WORK_TEMPLATE_NODE_HPP
  #define SEMESTER_WORK_TEMPLATE_NODE_HPP
#endif  //SEMESTER_WORK_TEMPLATE_NODE_HPP

namespace itis {
  struct node {
   private:
    int size;  // количество занятых ключей
    int key[3];
    node *first;   // *first <= key[0];
    node *second;  // key[0] <= *second < key[1];
    node *third;   // key[1] <= *third < key[2];
    node *fourth;  // kye[2] <= *fourth.
    node *parent;  //Указатель на родителя нужен для того, потому что адрес корня может меняться при удалении


    node *insert(node *p, int k) {  // вставка ключа k в дерево с корнем p; всегда возвращаем корень дерева, т.к. он может меняться
      if (!p) return new node(k);  // если дерево пусто, то создаем первую 2-3-вершину (корень)

      if (p->is_leaf()) p->insert_to_node(k);
      else if (k <= p->key[0])  insert(p->first, k);

      else if ((p->size == 1) || ((p->size == 2) && k <= p->key[1]))   insert(p->second, k);

      else insert(p->third, k);

      return split(p);
    }

    bool find(int k) {  // Этот метод возвращает true, если ключ k находится в вершине, иначе false.
      for (int i = 0; i < size; ++i)
        if (key[i] == k) return true;
      return false;
    }

    void swap(int &x, int &y) {
      int r = x;
      x = y;
      y = r;
    }

    void sort2(int &x, int &y) {
      if (x > y)
        swap(x, y);
    }

    void sort3(int &x, int &y, int &z) {
      if (x > y)
        swap(x, y);
      if (x > z)
        swap(x, z);
      if (y > z)
        swap(y, z);
    }

    void sort() {  // Ключи в вершинах должны быть отсортированы
      if (size == 1) return;
      if (size == 2)
        sort2(key[0], key[1]);
      if (size == 3)
        sort3(key[0], key[1], key[2]);
    }

    void insert_to_node(int k) {  // Вставляем ключ k в вершину (не в дерево)
      key[size] = k;
      size++;
      sort();
    }

    void remove_from_node(int k) {  // Удаляем ключ k из вершины (не из дерева)
      if (size >= 1 && key[0] == k) {
        key[0] = key[1];
        key[1] = key[2];
        size--;
      } else if (size == 2 && key[1] == k) {
        key[1] = key[2];
        size--;
      }
    }

    void become_node2(int k, node *first_, node *second_) {  // Преобразовать в 2-вершину.
      key[0] = k;
      first = first_;
      second = second_;
      third = nullptr;
      fourth = nullptr;
      parent = nullptr;
      size = 1;
    }

    bool is_leaf() {  // Является ли узел листом; проверка используется при вставке и удалении.
      return (first == nullptr) && (second == nullptr) && (third == nullptr);
    }

   public:
    // Создавать всегда будем вершину только с одним ключом
    node(int k)
        : size(1), key{k, 0, 0}, first(nullptr), second(nullptr), third(nullptr), fourth(nullptr), parent(nullptr) {}

    node(int k, node *first_, node *second_, node *third_, node *fourth_, node *parent_)
        : size(1), key{k, 0, 0}, first(first_), second(second_), third(third_), fourth(fourth_), parent(parent_) {}

    node *split(node *item);
    node *search(node *p, int k);
    node *search_min(node *p);
    node *remove(node *p, int k);
    node *fix(node *leaf);
    node *redistribute(node *leaf);
    node *merge(node *leaf);

    friend node *split(node *item);  // Метод для разделение вершины при переполнении;
    friend node *insert(node *p, int k);  // Вставка в дерево;
    friend node *search(node *p, int k);  // Поиск в дереве;
    friend node *search_min(node *p);     // Поиск минимального элемента в поддереве;
    friend node *merge(node *leaf);       // Слияние используется при удалении;
    friend node *redistribute(node *leaf);  // Перераспределение также используется при удалении;
    friend node *fix(
        node *leaf);  // Используется после удаления для возвращения свойств дереву (использует merge или redistribute)
    friend node *remove(node *p, int k);  // Собственно, из названия понятно;
  };
}  // namespace itis