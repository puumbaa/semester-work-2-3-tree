#include "data_structure.hpp"
#include "iostream"

using namespace std;

namespace itis {


    DataStructure::DataStructure(Node *root) {
        root_ = root;
    }

    DataStructure::~DataStructure() {
        Clear();
    }

    void DataStructure::Clear() {
        clear(root_);
        root_ = nullptr;
    }

    void DataStructure::clear(Node *node) {
        if (node != nullptr) {
            clear(node->first);
            clear(node->second);
            clear(node->third);
            delete[] node;
        }
    }

    void DataStructure::Insert(int k) {
        if (root_ != nullptr) {
            insert(k, root_);
        } else {
            root_ = new Node(k);
        }
    }

    void DataStructure::insert(int k, Node *node) {

        if (node->is_leaf()) {
            node->insert_to_node(k);
        } else if (k <= node->key[0]) {
            insert(k, node->first);
        } else if ((node->size == 1) || ((node->size == 2) && k <= node->key[1])) {
            insert(k, node->second);
        } else {
            insert(k, node->third);
        }
        root_ = split(node);
    }

    Node *DataStructure::split(Node *item) {
        if (item->size < 3) {
            return item;
        }

        auto x = new Node(item->key[0], item->first, item->second, nullptr, nullptr,
                          item->parent);  // Создаем две новые вершины,
        auto y = new Node(item->key[2], item->third, item->fourth, nullptr, nullptr,
                          item->parent);  // которые имеют такого же родителя, как и разделяющийся элемент.
        if (x->first) {
            x->first->parent = x;  // Правильно устанавливаем "родителя" "сыновей".
        }
        if (x->second) {
            x->second->parent = x;  // После разделения, "родителем" "сыновей" является "дедушка",
        }
        if (y->first) {
            y->first->parent = y;  // Поэтому нужно правильно установить указатели.
        }
        if (y->second) {
            y->second->parent = y;
        }

        if (item->parent) {
            item->parent->insert_to_node(item->key[1]);

            if (item->parent->first == item)
                item->parent->first = nullptr;
            else if (item->parent->second == item)
                item->parent->second = nullptr;
            else if (item->parent->third == item)
                item->parent->third = nullptr;

            // Дальше происходит сортировка ключей при разделении.
            if (item->parent->first == nullptr) {
                item->parent->fourth = item->parent->third;
                item->parent->third = item->parent->second;
                item->parent->second = y;
                item->parent->first = x;
            } else if (item->parent->second == nullptr) {
                item->parent->fourth = item->parent->third;
                item->parent->third = y;
                item->parent->second = x;
            } else {
                item->parent->fourth = y;
                item->parent->third = x;
            }

            Node *tmp = item->parent;
            delete[] item;
            return tmp;
        }
        x->parent = item;  // Так как в эту ветку попадает только корень,
        y->parent = item;  // то мы "родителем" новых вершин делаем разделяющийся элемент.
        item->become_node2(item->key[1], x, y);
        return item;
    }

    Node *DataStructure::Search(int k) {
        return search(k, root_);
    }

    Node *DataStructure::search(int k, Node *node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->find(k)) {
            return node;
        }
        if (k < node->key[0]) {
            return search(k, node->first);
        }
        if (((node->size == 2) && (k < node->key[1])) || (node->size == 1)) {
            return search(k, node->second);
        }
        if (node->size == 2) {
            return search(k, node->third);
        }
        return nullptr;
    }

    void *DataStructure::Remove(int k) {
        root_ = remove(k, root_);
    }

    Node *DataStructure::remove(int k, Node *node) {
        Node *item = search(k, node);  // Ищем узел, где находится ключ k

        if (item == nullptr)
            return node;

        Node *min = nullptr;
        if (item->key[0] == k) {
            min = findMin(item->second);  // Ищем эквивалентный ключ
        } else
            min = findMin(item->third);

        if (min != nullptr) {  // Меняем ключи местами
            int &z = (k == item->key[0] ? item->key[0] : item->key[1]);
            item->swap(z, min->key[0]);
            item = min;  // Перемещаем указатель на лист, т.к. min - всегда лист
        }

        item->remove_from_node(k);  // И удаляем требуемый ключ из листа
        return fix(item);  // Вызываем функцию для восстановления свойств дерева.
    }

    Node *DataStructure::findMin(Node *node) {
        if (node == nullptr) {
            return node;
        }
        if ((node->first) == nullptr) {
            return node;
        }
        return findMin(node->first);
    }

    Node *DataStructure::fix(Node *leaf) {  // после удаления может произойти 4 случая, которые нарушат свойства дерева
        if (leaf->size == 0 && leaf->parent == nullptr) {  // Случай 0, когда удаляем единственный ключ в дереве
            delete leaf;
            return nullptr;
        }
        if (leaf->size != 0) {  // Случай 1, когда вершина, в которой удалили ключ, имела два ключа
            if (leaf->parent != nullptr) {
                return fix(leaf->parent);
            }
            return leaf;
        }

        Node *parent = leaf->parent;
        if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2) {
            leaf = redistribute(leaf);  // Случай 2, когда достаточно перераспределить ключи в дереве
        } else if (parent->size == 2 && parent->third->size == 2) {
            leaf = redistribute(leaf);  // Аналогично
        } else
            leaf = merge(
                    leaf);  // Случай 3, когда нужно произвести склеивание и пройтись вверх по дереву как минимум на еще одну вершину
        return fix(leaf);
    }

    Node *DataStructure::redistribute(Node *leaf) {
        Node *parent = leaf->parent;
        Node *first = parent->first;
        Node *second = parent->second;
        Node *third = parent->third;

        if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
            if (first == leaf) {
                parent->first = parent->second;
                parent->second = parent->third;
                parent->third = nullptr;
                parent->first->insert_to_node(parent->key[0]);
                parent->first->third = parent->first->second;
                parent->first->second = parent->first->first;

                if (leaf->first != nullptr)
                    parent->first->first = leaf->first;
                else if (leaf->second != nullptr)
                    parent->first->first = leaf->second;

                if (parent->first->first != nullptr)
                    parent->first->first->parent = parent->first;

                parent->remove_from_node(parent->key[0]);
                delete[] first;
            } else if (second == leaf) {
                first->insert_to_node(parent->key[0]);
                parent->remove_from_node(parent->key[0]);
                if (leaf->first != nullptr)
                    first->third = leaf->first;
                else if (leaf->second != nullptr)
                    first->third = leaf->second;

                if (first->third != nullptr)
                    first->third->parent = first;

                parent->second = parent->third;
                parent->third = nullptr;

                delete[] second;
            } else if (third == leaf) {
                second->insert_to_node(parent->key[1]);
                parent->third = nullptr;
                parent->remove_from_node(parent->key[1]);
                if (leaf->first != nullptr)
                    second->third = leaf->first;
                else if (leaf->second != nullptr)
                    second->third = leaf->second;

                if (second->third != nullptr)
                    second->third->parent = second;

                delete[] third;
            }
        } else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
            if (third == leaf) {
                if (leaf->first != nullptr) {
                    leaf->second = leaf->first;
                    leaf->first = nullptr;
                }

                leaf->insert_to_node(parent->key[1]);
                if (second->size == 2) {
                    parent->key[1] = second->key[1];
                    second->remove_from_node(second->key[1]);
                    leaf->first = second->third;
                    second->third = nullptr;
                    if (leaf->first != nullptr)
                        leaf->first->parent = leaf;
                } else if (first->size == 2) {
                    parent->key[1] = second->key[0];
                    leaf->first = second->second;
                    second->second = second->first;
                    if (leaf->first != nullptr)
                        leaf->first->parent = leaf;

                    second->key[0] = parent->key[0];
                    parent->key[0] = first->key[1];
                    first->remove_from_node(first->key[1]);
                    second->first = first->third;
                    if (second->first != nullptr)
                        second->first->parent = second;
                    first->third = nullptr;
                }
            } else if (second == leaf) {
                if (third->size == 2) {
                    if (leaf->first == nullptr) {
                        leaf->first = leaf->second;
                        leaf->second = nullptr;
                    }
                    second->insert_to_node(parent->key[1]);
                    parent->key[1] = third->key[0];
                    third->remove_from_node(third->key[0]);
                    second->second = third->first;
                    if (second->second != nullptr)
                        second->second->parent = second;
                    third->first = third->second;
                    third->second = third->third;
                    third->third = nullptr;
                } else if (first->size == 2) {
                    if (leaf->second == nullptr) {
                        leaf->second = leaf->first;
                        leaf->first = nullptr;
                    }
                    second->insert_to_node(parent->key[0]);
                    parent->key[0] = first->key[1];
                    first->remove_from_node(first->key[1]);
                    second->first = first->third;
                    if (second->first != nullptr)
                        second->first->parent = second;
                    first->third = nullptr;
                }
            } else if (first == leaf) {
                if (leaf->first == nullptr) {
                    leaf->first = leaf->second;
                    leaf->second = nullptr;
                }
                first->insert_to_node(parent->key[0]);
                if (second->size == 2) {
                    parent->key[0] = second->key[0];
                    second->remove_from_node(second->key[0]);
                    first->second = second->first;
                    if (first->second != nullptr)
                        first->second->parent = first;
                    second->first = second->second;
                    second->second = second->third;
                    second->third = nullptr;
                } else if (third->size == 2) {
                    parent->key[0] = second->key[0];
                    second->key[0] = parent->key[1];
                    parent->key[1] = third->key[0];
                    third->remove_from_node(third->key[0]);
                    first->second = second->first;
                    if (first->second != nullptr)
                        first->second->parent = first;
                    second->first = second->second;
                    second->second = third->first;
                    if (second->second != nullptr)
                        second->second->parent = second;
                    third->first = third->second;
                    third->second = third->third;
                    third->third = nullptr;
                }
            }
        } else if (parent->size == 1) {
            leaf->insert_to_node(parent->key[0]);

            if (first == leaf && second->size == 2) {
                parent->key[0] = second->key[0];
                second->remove_from_node(second->key[0]);

                if (leaf->first == nullptr)
                    leaf->first = leaf->second;

                leaf->second = second->first;
                second->first = second->second;
                second->second = second->third;
                second->third = nullptr;
                if (leaf->second != nullptr)
                    leaf->second->parent = leaf;
            } else if (second == leaf && first->size == 2) {
                parent->key[0] = first->key[1];
                first->remove_from_node(first->key[1]);

                if (leaf->second == nullptr)
                    leaf->second = leaf->first;

                leaf->first = first->third;
                first->third = nullptr;
                if (leaf->first != nullptr)
                    leaf->first->parent = leaf;
            }
        }
        return parent;
    }

    Node *DataStructure::merge(Node *leaf) {
        Node *parent = leaf->parent;

        if (parent->first == leaf) {
            parent->second->insert_to_node(parent->key[0]);
            parent->second->third = parent->second->second;
            parent->second->second = parent->second->first;

            if (leaf->first != nullptr)
                parent->second->first = leaf->first;
            else if (leaf->second != nullptr)
                parent->second->first = leaf->second;

            if (parent->second->first != nullptr)
                parent->second->first->parent = parent->second;

            parent->remove_from_node(parent->key[0]);
            delete parent->first;
            parent->first = nullptr;
        } else if (parent->second == leaf) {
            parent->first->insert_to_node(parent->key[0]);

            if (leaf->first != nullptr)
                parent->first->third = leaf->first;
            else if (leaf->second != nullptr)
                parent->first->third = leaf->second;

            if (parent->first->third != nullptr)
                parent->first->third->parent = parent->first;

            parent->remove_from_node(parent->key[0]);
            delete[] parent->second;
            parent->second = nullptr;
        }

        if (parent->parent == nullptr) {
            Node *tmp = nullptr;
            if (parent->first != nullptr)
                tmp = parent->first;
            else
                tmp = parent->second;
            tmp->parent = nullptr;
            delete[] parent;
            return tmp;
        }
        return parent;
    }

    Node *DataStructure::root() {
        return root_;
    }

    int DataStructure::Height() {
        return height(root_);
    }

    int DataStructure::height(Node *node) {
        if (node == nullptr) {
            return 0;
        }

        const int first_height = height(node->first);

        return first_height + 1;
    }

}  // namespace itis