#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "VectorNode.h"

namespace cs1c {

    template <class Type>
    class LinkedList {
    public:
        LinkedList();
        ~LinkedList();
        void insertAtTail(VectorNode<Type>* node);
        VectorNode<Type>* removeFromHead();
        void remove(VectorNode<Type>* node);
        bool empty() const;
        VectorNode<Type>* head() const;
        VectorNode<Type>* tail() const;
        VectorNode<Type>* end() const;
        VectorNode<Type>* start() const;
    private:

        VectorNode<Type>* m_listHead;    
    }; // END - class LinkedList 
    

        template <class Type>
        LinkedList<Type>::LinkedList() 
          : m_listHead(new VectorNode<Type>()) {
        }
        
        //! A destructor.
        template <class Type>
        LinkedList<Type>::~LinkedList() {
            delete m_listHead;
        }

        template <class Type>
        void LinkedList<Type>::insertAtTail(VectorNode<Type>* node) {
            VectorNode<Type>* oldLastNode = m_listHead->previous;

            oldLastNode->next = node;
            node->next = m_listHead;
            node->previous = oldLastNode;
            m_listHead->previous = node;
        }


        template <class Type>
        VectorNode<Type>* LinkedList<Type>::removeFromHead() {
            VectorNode<Type>* nodeToRemove = m_listHead->next;
            VectorNode<Type>* newNextNode = nodeToRemove->next;

            m_listHead->next = newNextNode;
            newNextNode->previous = m_listHead;

            nodeToRemove->next = nodeToRemove;
            nodeToRemove->previous = nodeToRemove;

            return nodeToRemove;
        }

        template <class Type>
        void LinkedList<Type>::remove(VectorNode<Type>* nodeToRemove) {
            VectorNode<Type>* nextNode = nodeToRemove->next;
            VectorNode<Type>* previousNode = nodeToRemove->previous;

            previousNode->next = nextNode;
            nextNode->previous = previousNode;

            nodeToRemove->next = nodeToRemove;
            nodeToRemove->previous = nodeToRemove;
        }


        template <class Type>
        bool LinkedList<Type>::empty() const {
            return (m_listHead->next == m_listHead);
        }


        template <class Type>
        VectorNode<Type>* LinkedList<Type>::head() const {
            return m_listHead->next;
        }

        template <class Type>
        VectorNode<Type>* LinkedList<Type>::tail() const {
            return m_listHead->previous;
        }


        template <class Type>
        VectorNode<Type>* LinkedList<Type>::end() const {
            return m_listHead;
        }

        template <class Type>
        VectorNode<Type>* LinkedList<Type>::start() const {
            return m_listHead;
        }
} // END - namespace cs1c

#endif 

