
#ifndef AvlTree_h
#define AvlTree_h

#include "BinarySearchTree.h"

template <class T>
class AvlTree : public BinarySearchTree<T>{

public:
    AvlTree(){}
    ~AvlTree();

    void l_rotation(BNode<T> * node);
    void r_rotation(BNode<T> * node);
    void lr_rotation(BNode<T> * node);
    void rl_rotation(BNode<T> * node);
    bool isAVL(BNode<T> * node);
    void insert(BNode<T> * parent, BNode<T> * node);
    void insert(T value);
    void remove(T value);

    BNode<T> * getMaxMin(BNode<T> * node) const;
    BNode<T> * getMaxMin() const;

};

template <class T>
AvlTree<T>::~AvlTree(){

}

template <class T>
bool AvlTree<T>::isAVL(BNode<T> * node){

        if (node)
        {
            if (abs(this->getBalanceFactor(node)) > 1 )
            {
                return false;
            }
            return  isAVL(node->getRight()) && isAVL(node->getLeft());
        }
        else
        {
            return true;
        }

    }

template <class T>
void AvlTree<T>::r_rotation(BNode<T> * pivot){
    //Rotar hacia la derecha al rededor del padre de node
    BNode<T> * temp = pivot->getLeft();


    if(pivot->getParent() && pivot->getInfo() <= pivot->getParent()->getInfo() ){
        pivot->getParent()->setLeft(temp);
    }else if (pivot->getParent()){
        pivot->getParent()->setRight(temp);
    }else{
        this->setRoot(temp);
    }

    temp->setParent(pivot->getParent());
    pivot->setParent(temp);

    pivot->setLeft(temp->getRight());

    temp->setRight(pivot);

    if(pivot->getLeft())
    pivot->getLeft()->setParent(pivot);

}

template <class T>
void AvlTree<T>::l_rotation(BNode<T> * pivot){
    //Rotar hacia la izquierda alrededor del padre de node
    BNode<T> * temp = pivot->getRight();

    if(pivot->getParent() && pivot->getInfo() <= pivot->getParent()->getInfo() ){
        pivot->getParent()->setLeft(temp);
    }else if (pivot->getParent()){
        pivot->getParent()->setRight(temp);
    }else{
        this->setRoot(temp);
    }

    temp->setParent(pivot->getParent());
    pivot->setParent(temp);

    pivot->setRight(temp->getLeft());

    temp->setLeft(pivot);

    if(pivot->getRight())
    pivot->getRight()->setParent(pivot);

}

template <class T>
void AvlTree<T>::lr_rotation(BNode<T> * pivot){
    //Rotar hacia la izquierda alrededor de node y rotar hacia la derecha alrededor del padre de node
     BNode<T> * temp = pivot->getRight();
    l_rotation(pivot);
    r_rotation(temp->getParent());
}

template <class T>
void AvlTree<T>::rl_rotation(BNode<T> * pivot){
    //Rotar hacia la derecha alrededor de node y rotar hacia la izquierda alrededor del padre de node
    BNode<T> * temp = pivot->getLeft();
    r_rotation(pivot);
    l_rotation(temp->getParent());
}

template <class T>
void AvlTree<T>::insert(BNode<T> * parent, BNode<T> * node){




    if (this->empty())
    {
        this->setRoot(node);

    }
    else
    {
        if(node->getInfo() < parent->getInfo())
        {

            if (parent->getLeft() == nullptr)
            {
                parent->setLeft(node);
                node->setParent(parent);

            }
            else
            {
                 insert(parent->getLeft(), node);
            }
        }
        else if(node->getInfo() > parent->getInfo())
        {
            if (parent->getRight() == nullptr)
            {
                parent->setRight(node);
                node->setParent(parent);

            }
            else
            {
                insert(parent->getRight(), node);
            }
        } else {
            return;
        }


        if(this->getBalanceFactor(parent->getParent()) == -2 && this->getBalanceFactor(parent->getParent()->getLeft())== -1){
            r_rotation(parent->getParent());
//        std::cout<<"R"<<std::endl;
        }
        if(this->getBalanceFactor(parent->getParent()) == -2 && this->getBalanceFactor(parent->getParent()->getLeft())== 1){
            lr_rotation(parent);
//        std::cout<<"LR"<<std::endl;
        }
        if(this->getBalanceFactor(parent->getParent()) == 2 && this->getBalanceFactor(parent->getParent()->getRight())== 1){
            l_rotation(parent->getParent());
//        std::cout<<"L"<<std::endl;
        }
        if( (this->getBalanceFactor(parent->getParent()) == 2 && this->getBalanceFactor(parent->getParent()->getRight())== -1)){
            rl_rotation(parent);
//        std::cout<<"RL"<<std::endl;
        }

    }

    }


template <class T>
void AvlTree<T>::insert(T value){
    BNode<T> * node = new BNode<T>(value);
     insert(this->root, node);
}

template <class T>
void AvlTree<T>::remove(T value){
    BNode<T> * node = this->search(value);

    if(node){


    BNode<T> * parent = node->getParent();
    BNode<T> * nnode = getMaxMin(node);

    if(nnode){
        nnode->setRight(node->getRight());
        if(nnode->getRight())
        nnode->getRight()->setParent(nnode);
    nnode->getParent()->setRight(nnode->getLeft());
    nnode->setParent(node->getParent());




        if(node->getLeft() == nnode){
            if(!nnode->getLeft())
            nnode->setLeft(nullptr);
        }
        else{
        nnode->setLeft(node->getLeft());
        }



    }

    if(!node->getParent()){
        BinaryTree<T>::setRoot(nnode);
    }else if(node->getInfo() <= node->getParent()->getInfo()){
        node->getParent()->setLeft(nnode);
    } else{
        node->getParent()->setRight(nnode);
    }


    delete node;


    if(this->getBalanceFactor(parent) == -2 && this->getBalanceFactor(parent->getLeft()) == -1){
        r_rotation(parent);
//        std::cout<<"R"<<std::endl;
    }
    if(this->getBalanceFactor(parent) == -2 && this->getBalanceFactor(parent->getLeft())== 1){
        lr_rotation(parent->getLeft());
//        std::cout<<"LR"<<std::endl;
    }
    if(this->getBalanceFactor(parent) == 2 && this->getBalanceFactor(parent->getRight())== 1){
        l_rotation(parent);
//        std::cout<<"L"<<std::endl;
    }
    if( (this->getBalanceFactor(parent) == 2 && this->getBalanceFactor(parent->getRight())== -1)){
        rl_rotation(parent->getRight());
//        std::cout<<"RL"<<std::endl;
    }
           parent =  parent->getParent();


        if(this->getBalanceFactor(nnode) == -2 && this->getBalanceFactor(nnode->getLeft()) == -1){
            r_rotation(nnode);
//            std::cout<<"R"<<std::endl;
        }
        if(this->getBalanceFactor(nnode) == -2 && this->getBalanceFactor(nnode->getLeft())== 1){
            lr_rotation(nnode->getLeft());
//            std::cout<<"LR"<<std::endl;
        }
        if(this->getBalanceFactor(nnode) == 2 && this->getBalanceFactor(nnode->getRight())== 1){
            l_rotation(nnode);
//            std::cout<<"L"<<std::endl;
        }
        if( (this->getBalanceFactor(nnode) == 2 && this->getBalanceFactor(nnode->getRight())== -1)){
            rl_rotation(nnode->getRight());
//            std::cout<<"RL"<<std::endl;
        }





    }

}

template <class T>
BNode<T> * AvlTree<T>::getMaxMin() const
{
    return getMaxMin(this->root);
}


template <class T>
BNode<T> * AvlTree<T>::getMaxMin(BNode<T> * node) const
{
    if (node)
        {
            BNode<T> * workingNode = node->getLeft();
            if(workingNode){
            while (workingNode->getRight() != nullptr)
                {
                    workingNode = workingNode->getRight();
                }
           return workingNode;
            }
            return nullptr;

        } else{
            return nullptr;
        }
}


#endif /* AvlTree_h */
