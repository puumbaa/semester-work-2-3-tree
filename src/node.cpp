//
// Created by user on 16.04.2021.
//
#include "node.hpp"
namespace itis {
  Node::Node(int value, Node *parent, Node *first, Node *second, Node *third, Node *fourth):
      size_(1), values{value, 0}, first_(first), second_(second),
      third_(third), fourth_(fourth), parent_(parent) {}


  bool Node::is_leaf() {  // Является ли узел листом; проверка используется при вставке и удалении.
    return (first_ == nullptr) && (second_ == nullptr) && (third_ == nullptr);
  }

bool Node::find(int value) {  //Если значение есть в верщине, возвращается true, Иначе - false
  for (int i = 0; i < size_; i ++) {
    if (values[i] == value)
      return true;
  }
  return false;
}

  void Node::swap(int &a, int &b) { // (нужна для сортировки) менять клюяи местами
    int temp = a;
    a = b;
    b = temp;
  }

  void Node::sort() { // Сортировка ключей в вершине по возрастанию
    if(size_ == 2) {
      if (values[0] > values[1])
        swap(values[0], values[1]);
    }
    if(size_ == 3) {
      if(values[0] > values[1]) {
        swap(values[0], values[1]);
      }
      if(values[0] > values[3]) {
        swap(values[0], values[3]);
      }
      if(values[2] > values[3]) {
        swap(values[2], values[3]);
      }
    }
  }

  void Node::insert_to_node(int value) {  // Вставка значение k в вершину
    values[size_] = value;
    size_++;
    sort();
  }

  void Node::remove_from_node(int value) {  // Удаляем ключ value из вершины (не из дерева)
    if (size_ >= 1 && values[0] == value) {
      values[0] = values[1];
      values[1] = 0;
      size_--;
    } else if (size_ == 2 && values[1] == value) {
      values[1] = 0;
      size_--;
    }
  }

    void Node::become_node2(int k, Node *first, Node *second) {  // Преобразовать в 2-вершину.
      size_ = 1;
      values[0] = k;
      values[1] = 0;
      first_ = first;
      second_ = second;
      third_ = nullptr;
      parent_ = nullptr;
    }






  }






}  // namespace itis