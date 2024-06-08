#include <iostream>
using namespace std;

struct Node {
    string val;
    Node* next;

    Node(string _val) : val(_val), next(nullptr) {}
};

struct list {
    Node* first;
    Node* last;

    list() : first(nullptr), last(nullptr) {}

    //Не пустой?
    bool is_empty() {
        return first == nullptr;
    }

    //добавить в конец
    void push_back(string _val) {
        Node* p = new Node(_val);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }
    
    //добавить в заданный индекс (считает с нуля)
    void insert_at(int index, string _val) {

        Node* new_node = new Node(_val);
        if (index == 0) {
            if (is_empty()) {
                first = new_node;
                last = new_node;
            } else {
                new_node->next = first;
                first = new_node;
            }
            return;
        }

        Node* current = first;
        for (int i = 0; current != nullptr && i < index - 1; i++) {
            current = current->next;
        }

        if (current == nullptr) {
            // Индекс больше, чем количество элементов в списке
            delete new_node;
            return;
        }

        if (current->next == nullptr) {
            // Вставляем в конец списка
            current->next = new_node;
            last = new_node;
        } else {
            // Вставляем между узлами
            new_node->next = current->next;
            current->next = new_node;
        }
    }
    
    //добавить в начало
    void push_front(string _val) {
        Node* p = new Node(_val);
        if (is_empty()) {
            first = p;
            last = p;
        } else {
            p->next = first;
            first = p;
        }
    }

    //распечатать 
    void print() {
        if (is_empty()) return;
        Node* p = first;
        while (p) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }

    //найти узел по значению. Возвразает указатаель(!) на найденный узел или пустой указатель если не нашел
    Node* find(string _val) {
        Node* p = first;
        while (p && p->val != _val) p = p->next;
        return (p && p->val == _val) ? p : nullptr;
    }

    //удалить первый
    void remove_first() {
        if (is_empty()) return;
        Node* p = first;
        first = p->next;
        delete p;
    }

    //удалить последний
    void remove_last() {
        if (is_empty()) return;
        if (first == last) {
            remove_first();
            return;
        }
        Node* p = first;
        while (p->next != last) p = p->next;
        p->next = nullptr;
        delete last;
        last = p;
    }

    //удалить по значению
    void remove(string _val) {
        if (is_empty()) return;
        if (first->val == _val) {
            remove_first();
            return;
        }
        else if (last->val == _val) {
            remove_last();
            return;
        }
        Node* slow = first;
        Node* fast = first->next;
        while (fast && fast->val != _val) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) {
            cout << "This element does not exist" << endl;
            return;
        }
        slow->next = fast->next;
        delete fast;
    }
    
    //удалить по индексу
    void remove_at(const int index) {
        if (is_empty()) return;

        if (index == 0) {
            remove_first();
            return;
        }

        Node* current = first;
        size_t currentIndex = 0;

        while (current->next != nullptr && currentIndex < index - 1) {
            current = current->next;
            currentIndex++;
        }   

        if (currentIndex < index - 1 || current->next == nullptr) {
            return;
        }

        if (current->next == last) {
            remove_last();
            return;
        }

        Node* nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        delete nodeToDelete;
    }

    //оператор, который позвоялет обратиться к узлу по его индексу
    Node* operator[] (const int index) {
        if (is_empty()) return nullptr;
        Node* p = first;
        for (int i = 0; i < index; i++) {
            p = p->next;
            if (!p) return nullptr;
        }
        return p;
    }
    
    void update_at_index(const int index, string new_val) {

        Node* current = first;
        for (int i = 0; current != nullptr && i < index; ++i) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Error: index out of bounds." << endl;
            return;
        }

        current->val = new_val;
    }
};

int main()
{
    list l;
    cout << l.is_empty() << endl;
    l.push_back("3");
    l.push_back("123");
    l.push_back("8");
    l.print();
    cout << l.is_empty() << endl;
    
    // Поиск элемента в списке
    Node* found = l.find("123");
    if (found) {
        cout << "Element found: " << found->val << endl;
    } else {
        cout << "Element not found." << endl;
    }


    l.remove("123");
    l.print();
    l.push_back("1234");
    l.remove_first();
    l.print();
    l.remove_last();
    l.push_front("567");
    l.print();
    
    cout << l[0]->val << endl;
    
    l.insert_at(1, "000");
    l.print();
    l.remove_at(1);
    l.print();
    
    l.update_at_index(1, "10");
    l.print();
    
    
    return 0;
}