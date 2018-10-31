#ifndef EX5_MTM_ARRAY_H
#define EX5_MTM_ARRAY_H

#include <utility>
#include <stdexcept>
#include <type_traits>

//exception to be thrown in the case of an attempt to compare iterators
//belonging to different arrays
class array_mismatch_exception : public std::runtime_error {
public:
    array_mismatch_exception(std::string const& message): 
    std::runtime_error(message) {}
};

//template for an array of varying type of elements and length
template <class T, int SIZE>
class Array {
//data array
    T* data;
//length of the array
    int size;
public:
//array constructor
//creates an array object, can accept an initial value as an argument
//if the array size is less than 1, throws a compilation error
    Array(T const& initial_value=T()): size(SIZE) {
        static_assert(SIZE>=1, "Size must be a positive integer");
        data = new T[SIZE];
        for (int i = 0; i < size; ++i) {
            data[i] = initial_value;
        }
    }
//array copy constructor
    Array(const Array& array): size(SIZE) {
        data = new T[SIZE];
        for (int i = 0; i < array.size; ++i) {
            data[i] = array.data[i];
        }
    }



//array destructor
//deletes the data that was stored in the array
    ~Array() {
        delete[] data;
    }
//array assignment operator
    Array& operator=(const Array& array) {
        if (this == &array) {
            return *this;
        }
        delete[] data;
        data = new T[SIZE];
        for (int i = 0; i < size; ++i) {
            data[i] = array.data[i];
        }
        return *this;
    };
//array [i] operator
//returns the ith element of the array, the element can be modified
//if the index is not in range, throws std::out_of_range
    T& operator[] (int index) {
        if (index < 0 || index >= SIZE) {
            throw std::out_of_range
            ("mtm_array::operator []: index out of range!");
        }
        return data[index];
    }
//the [i] operator that does not allow to modify the received element
//if the index is not in range, throws std::out_of_range
    const T& operator[] (int index) const {
        if (index < 0 || index >= SIZE) {
            throw std::out_of_range
            ("mtm_array::operator []: index out of range!");
        }
        return data[index];
    }
    class const_iterator;
//an iterator that allows to modify array elements
    class iterator {
        Array* array;
        int index;
//iterator is constructed by an array
        iterator (Array* array1, int index): array(array1), index(index) {}
        friend class Array;



       public:
//iterator destructor
        ~iterator() = default;
//iterator copy constructor
        iterator (const iterator&) = default;
//iterator assignment operator
        iterator& operator= (const iterator&) = default;
//iterator dereference operator
//if the index is out of range, throws std::out_of_range
        T& operator*() {
            if (index < 0 || index >= SIZE) {
                throw std::out_of_range
                ("mtm_array::operator []: index out of range!");
            }
            return array->data[index];
        }
//iterator increment operator (of type ++i)
        iterator& operator++() {
            ++index;
            return *this;
        }
//iterator increment operator (of type i++)
        iterator operator++(int) {
            iterator result = *this;
            ++*this;
            return result;
        }
//iterator comparison operator
//receives a non-const iterator, if two iterators belong to different arrays,
//throws array_mismatch_exception
        bool operator==(const iterator& i) const {
            if (array != i.array) {
                throw array_mismatch_exception
                ("Iterators over different arrays");
            }
            return index==i.index;
        }
//iterator comparison operator
//receives a const iterator, if two iterators belong to different arrays,
//throws array_mismatch_exception
        bool operator==(const const_iterator& i) const {
            if ((const Array*) array != i.array) {
                throw array_mismatch_exception
                ("Iterators over different arrays");
            }
            return index==i.index;
        }
//iterator "is not equal" operator
//receives a non-const iterator, if two iterators belong to different arrays,
//throws array_mismatch_exception
        bool operator!=(const iterator& i) const {
            return !(*this==i);
        }
//iterator "is not equal" operator
//receives a const iterator, if two iterators belong to different arrays,
//throws array_mismatch_exception
        bool operator!=(const const_iterator& i) const {
            return !(*this==i);
        }
//iterator "->" operator
//throws std::out_of_range when index is not in the range
        T* operator->() {
            if (index < 0 || index >= SIZE) {
                throw std::out_of_range
                ("mtm_array::operator []: index out of range!");
            }
            return &(array->data[index]);
        }
    };

//points to the first element
    iterator begin() {
        return iterator(this, 0);
    }
//points to after the end of the array
    iterator end() {
        return iterator(this, SIZE);
    };

//the iterator that does not allow to modify passed objects
    class const_iterator {
        const Array* array;
        int index;
//only an array can create an iterator
        const_iterator (const Array* array1, int index): 
        array(array1), index(index) {}
        friend class Array;
    public:
//iterator destructor
        ~const_iterator() = default;
//iterator copy constructor
        const_iterator (const const_iterator&) = default;

//iterator constructor receiving a non-constant iterator
        const_iterator (const iterator& iterator1): array(iterator1.array), 
        index(iterator1.index) {};
//iterator assignment operator
        const_iterator& operator= (const const_iterator&) = default;
//iterator dereference operator
//throws std::out_of_range if the index is out of range
        const T& operator*() {
            if (index < 0 || index >= SIZE) {
                throw std::out_of_range
                ("mtm_array::iterator: index out of range!");
            }
            return array->data[index];
        }
//iterator increment operator of the ++i type
        const_iterator& operator++() {
            ++index;
            return *this;
        }
//iterator increment operator of the i++ type
        const_iterator operator++(int) {
            const_iterator result = *this;
            ++*this;
            return result;
        }
//iterator comparison operator
//receives a non-const iterator, if two iterators belong to different arrays,
//throws array_mismatch_exception
        bool operator==(const const_iterator& i) const {
            if (array != i.array) {
                throw array_mismatch_exception
                ("Iterators over different arrays");
            }
            return index==i.index;
        }
//iterator comparison operator
//receives a const iterator, if two iterators belong to different arrays,
//throws array_mismatch_exception
        bool operator==(const iterator& i) const {
            if (array != (const Array*) i.array) {
                throw array_mismatch_exception
                ("Iterators over different arrays");
            }
            return index==i.index;
        }



//iterator "is not equal" operator
//receives a const iterator, if two iterators belong to different arrays,
//throws array_mismatch_exception
        bool operator!=(const const_iterator& i) const {
            return !(*this==i);
        }
//iterator "is not equal" operator
//receives a const iterator, if two iterators belong to different arrays,
//throws array_mismatch_exception
        bool operator!=(const iterator& i) const {
            return !(*this==i);
        }
//iterator "->" operator
//throws std::out_of_range when index is not in the range
//returns a pointer to the element of the array
        const T* operator->() {
            if (index < 0 || index >= SIZE) {
                throw std::out_of_range
                ("mtm_array::iterator: index out of range!");
            }
            return &(array->data[index]);
        }
    };

//points to the first element
    const_iterator begin() const {
        return const_iterator(this, 0);
    };
//points to after the end of the array
    const_iterator end() const {
        return const_iterator(this, size);
    };
};

#endif //EX5_MTM_ARRAY_H

