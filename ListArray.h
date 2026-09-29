#ifndef LISTARRAY_H
#define LISTARRAY_H

#include <ostream>
#include <stdexcept>
#include "List.h"

template <typename T> 
class ListArray : public List<T> {
    private:
        T* arr;
        int max;
        int n;
        static const int MINSIZE = 10;

        void resize(int new_size);

    public:
        ListArray();
        ~ListArray() override;

        void insert(int pos, T e) override;
        void append(T e) override;
        void prepend(T e) override;
        T remove(int pos) override;
        T get(int pos) const override;
        int search(T e) const override;
        bool empty() const override;
        int size() const override;

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