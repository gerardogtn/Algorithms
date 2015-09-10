#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "BinaryTree.h"

template <class T>
class BinarySearchTree: public BinaryTree<T> {


public:
    BinarySearchTree();
    ~BinarySearchTree();

    BNode<T> * search(const T value) const;
    BNode<T> * search(const T value, BNode<T> * node) const;
};

template <class T>
BinarySearchTree<T>::BinarySearchTree() : BinaryTree<T>(){}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{

}

template <class T>
BNode<T> * BinarySearchTree<T>::search(const T value) const{
    return search(value, this->root);

}

template <class T>
BNode<T> * BinarySearchTree<T>::search(const T value, BNode<T> * node)const {
    if (node == nullptr)
    {
        return nullptr;
    }
    else {
        T value2 = node->getInfo();
        if (value == value2)
        {
            return node;
        }
        else if (value < value2)
        {
            return search(value, node->getLeft());
        }
        else {
            return search(value, node->getRight());
        }
    }
}





#endif /* BinarySearchTree_h */
