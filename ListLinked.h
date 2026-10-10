#ifndef LIST_LINKED_H
#define LIST_LINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
        Node<T>* first;
        int n;

    public:

        ListLinked() {
            first = nullptr;
            n = 0;
        }
        ~ListLinked() override {
            while (first != nullptr) {
                Node<T>* aux = first->next;
                delete first;
                first = aux;
            }
        }

        void insert(int pos, T e) override;
        void append(T e) override;
        void prepend(T e) override;
        T remove(int pos) override;
        T get(int pos) const override;
        int search(T e) const override;
        bool empty() const override;
        int size() const override;

        T operator[](int pos) {
            return get(pos);
        }
        friend std::ostream& operator<<(std::ostream &out, ListLinked &list) {
            out << "[";
            Node<T>* actual = list.first;
            while (actual != nullptr) {
                out << actual->data; // Aquí se usa el operator<< que definiste en Node
                if (actual->next != nullptr) {
                    out << ", ";
                }
                actual = actual->next;
            }
            out << "]";
            return out;
        }
    
    };

#endif LIST_LINKED_H