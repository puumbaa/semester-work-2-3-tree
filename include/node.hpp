//
// Created by user on 16.04.2021.
//
#pragma
#ifndef SEMESTER_WORK_TEMPLATE_NODE_HPP
  #define SEMESTER_WORK_TEMPLATE_NODE_HPP
#endif  //SEMESTER_WORK_TEMPLATE_NODE_HPP

namespace itis {
  struct Node {
   private:
    int size;
    int values[3];
    Node *parent_{nullptr};
    Node *first_{nullptr};
    Node *second_{nullptr};
    Node *third_{nullptr};
    Node *fourth_{nullptr};

    explicit Node (int value, Node* parent, Node* first = nullptr, Node* second = nullptr,
                  Node* third, Node* fourth );

    bool is_leaf();

    bool find(int value);

    void sort2(int &a, int &b);

    void sort3(int &a, int &b, int &c);

    void sort();

    void swap(int &a, int &b);

    void insert_to_node(int value);

    void remove_from_node(int value);

    void become_node2(int value, Node *first,Node *second);



  };
}  // namespace itis