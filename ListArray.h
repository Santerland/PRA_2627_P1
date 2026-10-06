#ifndef LISTARRAY_H
#define LISTARRAY_H

#include <ostream>
#include <stdexcept>
#include "List.h"

// comentarios 200% humanos
template <typename T> 
class ListArray : public List<T> {
    private:
        T* arr;
        int max;
        int n;
        static const int MINSIZE = 2;

        void resize(int new_size) {
            // array temporal
            T* temp_arr = new T[new_size];

            // copiamos al array actual
            for (int i = 0; i < n; ++i) {
                temp_arr[i] = arr[i];
            }

            // borramos memoria
            delete[] arr;

            // actualizamos puntero
            arr = temp_arr;

            // actualizamos max
            max = new_size;
        }

    public:
        ListArray();
        ~ListArray() override;

        void insert(int pos, T e) override {
            // esta dentro de rango [0, n]?
            if (pos < 0 || pos > size()) {
                throw std::out_of_range("Posición fuera de rango");
            }

            // esta el array lleno?
            if (size() == max) {
                // el doble
                int new_capacity = (max == 0) ? MINSIZE : max * 2;
                resize(new_capacity); 
            }

            // mover elementos a la derecha
            for (int i = size(); i > pos; --i) {
                arr[i] = arr[i - 1];
            }

            // insertar
            arr[pos] = e;
            n++;
        }
        void append(T e) override {
            insert(n, e);
        }
        void prepend(T e) override {
            insert(0, e);
        }
        T remove(int pos) override {
            // esta en rango (0 y n-1)?
            if (pos < 0 || pos >= size()) {
                throw std::out_of_range("Posición fuera de rango");
            }

            // guardamos pos
            T elemento_eliminado = arr[pos];

            // mover a la izquierda
            for (int i = pos; i < size() - 1; ++i) {
                arr[i] = arr[i + 1];
            }

            n--;
            return elemento_eliminado;
        }
        T get(int pos) const override {
            // esta en rango (0 y n-1)?
            if (pos < 0 || pos >= size()) {
                throw std::out_of_range("Posición fuera de rango");
            }

            return arr[pos];
        }
        int search(T e) const override {
            for (int i = 0; i < size(); ++i) {
                if (arr[i] == e) {
                    return i; // Devolvemos primera posicion correta
                }
            }
            
            // no esta, devolvemos -1
            return -1;
        }
        bool empty() const override {
            return n == 0;
        }
        int size() const override {
            return n;
        }

        T operator[](int pos);

        friend std::ostream& operator<<(std::ostream &out, const ListArray<T>& list) {
            out << "[";
            for (int i = 0; i < list.n; i++) {
                out << list.arr[i];
                if (i < list.n - 1) {
                    out << ", ";
                }
            }
            out << "]";
            return out;
        }
};

#endif