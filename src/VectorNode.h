#ifndef VECTOR_NODE_H
#define VECTOR_NODE_H

namespace cs1c {
    template <class Type>
    class VectorNode {
    public:
        VectorNode();
        VectorNode(Type* p_buffer, int p_size, int p_runningCapacity);
        VectorNode* next;
        VectorNode* previous;
        Type*       arrayOfObjects;
        int         size;
        int         runningCapacity;
    }; // END - class VectorNode
    template <class Type>
    VectorNode<Type>::VectorNode()
      : next{this}, previous{this}, arrayOfObjects{nullptr}, size{0}, runningCapacity{0} {}
    template <class Type>
    VectorNode<Type>::  VectorNode(Type* p_buffer, int p_size, int p_runningCapacity)
      : next{this}, previous{this}, arrayOfObjects{p_buffer}, size{p_size}, runningCapacity{p_runningCapacity} {}
    
}

#endif 

