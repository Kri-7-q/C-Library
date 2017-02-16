#ifndef BINARYSEARCHARRAY_H
#define BINARYSEARCHARRAY_H

#include "range.h"


/**
 * ---------------------------------------------------------------------------------
 * Template class:      BinarySearchArray
 * ---------------------------------------------------------------------------------
 * Takes an array pointer which has to point to an array with objects. It must
 * not be an array of pointer.
 * The array contains objects of type T. The search funktion can take objects of any
 * data type. But class T must handle comparison of all used data types for search.
 * The objects in the array must handle operators < and ==. This is required
 * for the search within the array.
 */
template<class T>
class BinarySearchArray
{
public:
    /**
     * Constructs an initialized BinarySearchArray object.
     * It take a pointer to a sorted array. If takeOwnership
     * is set to true then the pointer is adapted and the
     * array will be deleted within the destructor of this
     * object.
     * @param array
     * @param length
     * @param takeOwnership
     */
    BinarySearchArray(T* array, const int length, bool takeOwnership = false) :
        m_array(array),
        m_length(length),
        m_hasOwnership(takeOwnership)
    {
    }

    /**
     * Destructor of BinarySearchArray.
     * If the object has taken owner ship of the array pointer
     * then the array will be deleted here.
     */
    ~BinarySearchArray()
    {
        if (m_hasOwnership) {
            delete[] m_array;
        }
    }

    // Public class methods
    template<class E>
    T* findObject(const E& searchObj) const;

private:
    T* m_array;
    int m_length;
    bool m_hasOwnership;
};






/**
 * Template member function. Can search with any data type in the array.
 * But class T must override operators == and > to handle the other
 * data type E.
 * @param searchObj         The object of type E to search for in the array.
 * @return                  A pointer to the found object of type T or null.
 */
template<class T>
template<class E>
T* BinarySearchArray<T>::findObject(const E& searchObj) const
{
    Range range(m_length);
    while (range.isValid()) {
        int index = range.median();
        if (m_array[index] > searchObj) {
            range.setEnd(index-1);
            continue;
        }
        if (m_array[index] == searchObj) {
            return &m_array[index];
        }
        // Object is greater than the object at index.
        range.setStart(index+1);
    }

    return 0;
}

#endif // BINARYSEARCHARRAY_H
