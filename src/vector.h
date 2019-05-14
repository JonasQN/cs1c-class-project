#ifndef VECTOR_H
#define VECTOR_H

#include "LinkedList.h"

#include <algorithm>

namespace cs1c {
    template<class T>
    class vector
    {
    public:
        class iterator {
            friend class vector;
        public:
            iterator(vector* sourceVector, VectorNode<T>* vectorNode, int index);
            T& operator*();
            iterator operator++();
            iterator operator++(int);
            bool operator==(const iterator& rhs);
            bool operator!=(const iterator& rhs);
            iterator& operator=(const iterator& rhs);

        private:
            iterator moveForward();
            vector*         m_sourceVector;
            LinkedList<T>&  m_nodeList;
            VectorNode<T>*  m_vectorNode;
            int             m_index;
        }; //END - class iterator
        class const_iterator {
            friend class vector;
        public:
            const_iterator(const vector* sourceVector, const VectorNode<T>* vectorNode, int index);
            T& operator*() const;
            const_iterator operator++();
            const_iterator operator++(int);
            bool operator==(const const_iterator& rhs) const;
            bool operator!=(const const_iterator& rhs) const;
            const_iterator& operator=(const const_iterator& rhs);
        private:
            const_iterator moveForward();
            const vector*         m_sourceVector;
            const LinkedList<T>&  m_nodeList;
            const VectorNode<T>*  m_vectorNode;
            int             m_index;
        }; //END - class iterator

        vector();
        explicit vector(int size);
        vector(const vector<T>& source); 
        vector& operator=(const vector<T>& source);
        vector(vector<T>&& source); 
        vector<T>& operator=(vector<T>&& source); 
        ~vector();
        T& operator[] (int index);
        const T& operator[] (int index) const;
        int size() const;
        int capacity() const;
        void resize(int newSize);
        void push_back(T object);
        void reserve(int newCapacity);
		iterator erase(iterator pos);

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        iterator insert(iterator position, const T& value);

    private:
        T& get(int index) const;
        T& getNextEmpty() const;
        void clearList();
        LinkedList<T> m_nodeList;
        int           m_size;
        int           m_capacity;
    }; //END - class vector
    template<class T>
    vector<T>::iterator::iterator(vector* sourceVector, VectorNode<T>* vectorNode, int index)
      : m_sourceVector(sourceVector), m_nodeList{sourceVector->m_nodeList}, m_vectorNode{vectorNode}, m_index{index} {
    }
    template<class T>
    T& vector<T>::iterator::operator*() {
        return m_vectorNode->arrayOfObjects[m_index];
    }
    template<class T>
    typename vector<T>::iterator vector<T>::iterator::operator++() {
        return moveForward();
    }
    template<class T>
    typename vector<T>::iterator vector<T>::iterator::operator++(int) {
		iterator old = *this;
		moveForward();
		return old;
    }

    template<class T>
    bool vector<T>::iterator::operator==(const iterator& rhs) { 
        return ((m_vectorNode == rhs.m_vectorNode)
                && (m_index == rhs.m_index));
    }
    template<class T>
    bool vector<T>::iterator::operator!=(const iterator& rhs) { 
        return ((m_vectorNode != rhs.m_vectorNode)
                || (m_index != rhs.m_index));
    }
    template<class T>
    typename vector<T>::iterator& vector<T>::iterator::operator=(const iterator& rhs) {
    if (this != &rhs) {
        m_sourceVector = rhs.m_sourceVector;
        m_nodeList = rhs.m_nodeList;
        m_vectorNode = rhs.m_vectorNode;
        m_index = rhs.m_index;
    }
    return *this;
    }

    template<class T>
    typename vector<T>::iterator vector<T>::iterator::moveForward() {
        int availableNodeSize = std::min(m_vectorNode->size, m_sourceVector->m_size - (m_vectorNode->runningCapacity - m_vectorNode->size));
        // If there is no more valid data in this node (we indexed through all the entries or the
        // size is less than the capacity for this node), attempt to go to the next node.
        if (++m_index >= availableNodeSize) {
            // If the vector's size is greater than the running capacity (the maximum size of the
            // vector at the end of the node), then we have another node with valid entries.
            if (m_sourceVector->m_size > m_vectorNode->runningCapacity) {
                m_vectorNode = m_vectorNode->next;
            }
            // No more valid nodes, so set the iterator to null to indicate the end.
            else {
                m_vectorNode = nullptr;
            }
            m_index = 0;
        }
        return *this;
    }
    
    /*********************************************************************************************/
    template<class T>
    vector<T>::const_iterator::const_iterator(const vector* sourceVector, const VectorNode<T>* vectorNode, int index)
      : m_sourceVector(sourceVector), m_nodeList{sourceVector->m_nodeList}, m_vectorNode{vectorNode}, m_index{index} {
    }

    template<class T>
    T& vector<T>::const_iterator::operator*() const {
        return m_vectorNode->arrayOfObjects[m_index];
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::const_iterator::operator++() {
        return moveForward();
    }


    template<class T>
    bool vector<T>::const_iterator::operator==(const const_iterator& rhs) const { 
        return ((m_vectorNode == rhs.m_vectorNode)
                && (m_index == rhs.m_index));
    }

    template<class T>
    bool vector<T>::const_iterator::operator!=(const const_iterator& rhs) const{ 
        return ((m_vectorNode != rhs.m_vectorNode)
                || (m_index != rhs.m_index));
    }

    template<class T>
    typename vector<T>::const_iterator& vector<T>::const_iterator::operator=(const const_iterator& rhs) {
    if (this != &rhs) {
        m_sourceVector = rhs.m_sourceVector;
        m_nodeList = rhs.m_nodeList;
        m_vectorNode = rhs.m_vectorNode;
        m_index = rhs.m_index;
    }
    return *this;
    }

    template<class T>
    typename vector<T>::const_iterator vector<T>::const_iterator::moveForward() {
        int availableNodeSize = std::min(m_vectorNode->size, m_sourceVector->m_size - (m_vectorNode->runningCapacity - m_vectorNode->size));
        // If there is no more valid data in this node (we indexed through all the entries or the
        // size is less than the capacity for this node), attempt to go to the next node.
        if (++m_index >= availableNodeSize) {
            // If the vector's size is greater than the running capacity (the maximum size of the
            // vector at the end of the node), then we have another node with valid entries.
            if (m_sourceVector->m_size > m_vectorNode->runningCapacity) {
                m_vectorNode = m_vectorNode->next;
            }
            // No more valid nodes, so set the iterator to null to indicate the end.
            else {
                m_vectorNode = nullptr;
            }
            m_index = 0;
        }
        return *this;
    }
    /*********************************************************************************************/

    template<class T>
    vector<T>::vector() 
      : m_nodeList{}, m_size{0}, m_capacity{0} {}

    template<class T>
    vector<T>::vector(int size)
      : m_nodeList{}, m_size{size}, m_capacity{size}  {
        T* arrayOfObjects = new T[m_capacity];
        VectorNode<T>* node = new VectorNode<T>(arrayOfObjects, m_capacity, m_capacity);
        m_nodeList.insertAtTail(node);
    }
    template<class T>
    vector<T>::vector(const vector<T>& source) 
      : m_nodeList{}, m_size{source.m_size}, m_capacity{source.m_capacity}{
        if (m_capacity > 0) {
            T* arrayOfObjects = new T[m_capacity];
            VectorNode<T>* node = new VectorNode<T>(arrayOfObjects, m_capacity, m_capacity);

            for (int index = 0; index < m_size; index++) {
                node->arrayOfObjects[index] = source[index];
            }
            m_nodeList.insertAtTail(node);
        }
    }
    template<class T>
    vector<T>& vector<T>::operator=(const vector<T>& source) {
        if (this != &source) {
            clearList();
            m_size = source.m_size;
            m_capacity = source.m_capacity;

            if (m_capacity > 0) {
                T* arrayOfObjects = new T[m_capacity];
                VectorNode<T>* node = new VectorNode<T>(arrayOfObjects, m_capacity, m_capacity);

                for (int index = 0; index < m_size; index++) {
                    node->arrayOfObjects[index] = source[index];
                }
                m_nodeList.insertAtTail(node);
            }
        }     
        return *this;
    }
    template<class T>
    vector<T>::vector(vector<T>&& source)
      : m_nodeList{}, m_size{source.m_size}, m_capacity{source.m_capacity} {
        while (!source.m_nodeList.empty()) {
            m_nodeList.insertAtTail(source.m_nodeList.removeFromHead());
        } 
    }
    template<class T>
    vector<T>& vector<T>::operator=(vector<T>&& source) {
        clearList();
        m_size = source.m_size;
        m_capacity = source.m_capacity;
        while (!source.m_nodeList.empty()) {
            m_nodeList.insertAtTail(source.m_nodeList.removeFromHead());
        } 
        return *this;
    }
    template<class T>
    vector<T>::~vector() {
        clearList();
    }
    template<class T>
    T& vector<T>::operator[] (int index) {
        return get(index);
    } 
    template<class T>
    const T& vector<T>::operator[] (int index) const {
        return const_cast<T&>(get(index));
    }
    template<class T>
    int vector<T>::size() const {
        return m_size;
    }
    template<class T>
    int vector<T>::capacity() const {
        return m_capacity;
    }
    template<class T>
    void vector<T>::resize(int newSize) {
        if (newSize > m_capacity) {
            reserve(newSize);
        }
        else if (newSize > m_size) {
            for (int index = m_size; index < newSize; index++) {
                T& uninitializeObject = get(index);
                uninitializeObject = T();
            }
        }
        m_size = newSize;
    }
    template<class T>
    void vector<T>::push_back(T object) {
        const int MIN_ALLOC_SIZE = 8;
        if (m_capacity == 0) {
            reserve(MIN_ALLOC_SIZE);
        }
        else if (m_size == m_capacity) {
            reserve(m_capacity * 2);
        }
        T& lastObject = getNextEmpty();
        lastObject = object;
        m_size++;
    }
    template<class T>
    void vector<T>::reserve(int newCapacity) {
        if(newCapacity > m_capacity) {
            int additionalCapacityNeeded = newCapacity - m_capacity;
            T* arrayOfObjects = new T[additionalCapacityNeeded];
            VectorNode<T>* node = new VectorNode<T>(arrayOfObjects, additionalCapacityNeeded, newCapacity);
            m_nodeList.insertAtTail(node);
            m_capacity = newCapacity;
        }
    }
    template<class T>
    typename vector<T>::iterator vector<T>::begin() {
        if (m_size) {
            VectorNode<T>* firstNode = m_nodeList.head();
            return iterator(this, firstNode, 0);
        }
        else {
            return iterator(this, nullptr, 0);
        }
    }
    template<class T>
    typename vector<T>::const_iterator vector<T>::begin() const {
        if (m_size) {
            VectorNode<T>* firstNode = m_nodeList.head();
            return const_iterator(this, firstNode, 0);
        }
        else {
            return const_iterator(this, nullptr, 0);
        }
    }
    template<class T>
    typename vector<T>::iterator vector<T>::end() {
        return iterator(this, nullptr, 0);        
    }
    template<class T>
    typename vector<T>::const_iterator vector<T>::end() const {
        return const_iterator(this, nullptr, 0);        
    }
    template<class T>
    typename vector<T>::iterator vector<T>::insert(iterator position, const T& value) {
        VectorNode<T>* vectorNode = position.m_vectorNode;
        int insertIndex = position.m_index + 1;
        int oldSize = vectorNode->size;
        int newSize = oldSize + 1;
        T* oldArrayOfObjects = vectorNode->arrayOfObjects;
        T* newArrayOfObjects = new T[newSize];

        for (int index = 0; index < newSize; index++) {
            if (index < insertIndex) {
                newArrayOfObjects[index] = oldArrayOfObjects[index]; 
            }
            else if (index > insertIndex) {
                newArrayOfObjects[index] = oldArrayOfObjects[index - 1]; 
            }
            else {
                newArrayOfObjects[index] = value;
            }
        }

        vectorNode->arrayOfObjects = newArrayOfObjects;
        vectorNode->size = newSize;
        delete[] oldArrayOfObjects;
        
        while (vectorNode != m_nodeList.end()) {
            vectorNode->runningCapacity++;
            vectorNode = vectorNode->next;
        }        

        m_size++;
        m_capacity++;

        return iterator(this, vectorNode, insertIndex);
    }
    template<class T>
    typename vector<T>::iterator vector<T>::erase(iterator position) {
        VectorNode<T>* vectorNode = position.m_vectorNode;
        int removeIndex = position.m_index;
        int oldSize = vectorNode->size;
        int newSize = oldSize - 1;
        T* oldArrayOfObjects = vectorNode->arrayOfObjects;
        T* newArrayOfObjects = new T[newSize];

        for (int index = 0; index < oldSize; index++) {
            if (index < removeIndex) {
                newArrayOfObjects[index] = oldArrayOfObjects[index]; 
            }
            else if (index > removeIndex) {
                newArrayOfObjects[index - 1] = oldArrayOfObjects[index]; 
            }
        }

        vectorNode->arrayOfObjects = newArrayOfObjects;
        vectorNode->size = newSize;
        
        while (vectorNode != m_nodeList.end()) {
            vectorNode->runningCapacity--;
            vectorNode = vectorNode->next;
        }        

        delete[] oldArrayOfObjects;
        if (removeIndex >= newSize) {
            removeIndex--;
        }
        m_size--;
        m_capacity--;

        return iterator(this, vectorNode, removeIndex);
    }
    template<class T>
    T& vector<T>::get(int index) const {
        VectorNode<T>* node = m_nodeList.head();
        while (node != m_nodeList.end()) {
            if (index < node->size) {
                return node->arrayOfObjects[index];
            }
            index -= node->size;
            node = node->next;
        }
        static T dummy;
        return dummy;
    } 
    template<class T>
    T& vector<T>::getNextEmpty() const {
        VectorNode<T>* node = m_nodeList.tail();
        int remainingCapacity = m_capacity - m_size;
        int index = node->size - remainingCapacity;
        return node->arrayOfObjects[index];
    }
    template<class T>
    void vector<T>::clearList() {
        while (!m_nodeList.empty()) {
            VectorNode<T>* node = m_nodeList.removeFromHead();
            delete[] node->arrayOfObjects;
            delete node;
        } 
    }
} // END - namespace cs1c

#endif  // VECTOR_H
