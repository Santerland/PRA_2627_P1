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

        void insert(int pos, T e) override {
            // esta dentro de rango [0, n]?
            if (pos < 0 || pos > n) {
                throw std::out_of_range("Posición fuera de rango");
            }

            // esta al principio?
            if (pos == 0) {
                // Creamos un nuevo nodo donde next es el antiguo first y esta pasa a ser el nuevo first
                first = new Node<T>(e, first);
            } 
            // caso general
            else {
                Node<T>* prev = first;
                // desplazamos prev hasta el nodo que queremos remplazar
                for (int i = 0; i < pos - 1; ++i) {
                    prev = prev->next;
                }
                // lo mismo que con first pero con prev->next
                prev->next = new Node<T>(e, prev->next);
            }
            n++; //importante aumentar n
        }
        void append(T e) override {
            insert(n, e);
        }
        void prepend(T e) override {
            insert(0, e);
        }
        T remove(int pos) override {
            // esta en rango?
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición fuera de rango");
            }

            Node<T>* aux = nullptr; 
            T elemento_eliminado; 

            // si es el primero:
            if (pos == 0) {
                aux = first;                  
                first = first->next;          
            } 
            // caso general:
            else {
                Node<T>* prev = first;
                
                // prev apunta al nodo anterior
                for (int i = 0; i < pos - 1; ++i) {
                    prev = prev->next;
                }
                
                aux = prev->next;             // el nodo a borrar es el siguiente a prev
                prev->next = aux->next;       // conectamos prev con el siguiente de aux
            }

            elemento_eliminado = aux->data;
            // borramos el nodo despues de guardar data
            delete aux;

            n--;
            return elemento_eliminado;
        }
        T get(int pos) const override {
            // esta en rango?
            if (pos < 0 || pos >= n) {
                throw std::out_of_range("Posición fuera de rango");
            }

            Node<T>* actual = first; 
            //recoremos la lista hasta pos
            for (int i = 0; i < pos; ++i) {
                actual = actual->next;
            }

            return actual->data;
        }
        int search(T e) const override {
            Node<T>* actual = first;
            int pos = 0; // indice

            while (actual != nullptr) {
                if (actual->data == e) {
                    return pos; // la posicion
                }
                actual = actual->next;
                pos++;  
            }
            
            // no estaba en la lista
            return -1;
        }
        bool empty() const override {
            return n == 0;
        }
        int size() const override {
            return n;
        }

        T operator[](int pos) {
            return get(pos);
        }
        friend std::ostream& operator<<(std::ostream &out, const ListLinked &list) {
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

#endif //LIST_LINKED_H