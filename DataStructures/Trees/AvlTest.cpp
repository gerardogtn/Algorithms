//
//  main.cpp
//  Arboles
//
//  Created by Krikor Bisdikian G. on 5/9/15.
//  Copyright © 2015 Krikor Bisdikian G. All rights reserved.
//

#include <iostream>
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include <chrono>

using namespace std;

int main(int argc, const char * argv[]) {

    srand(time(0));

    AvlTree<int> numeros;
    int random;
    int array[10];

    for(int i=0; i<100000; i++){
        random = rand();

        numeros.insert(random);


        if(i<10)
        array[i] = random;

    }



     auto begin = std::chrono::high_resolution_clock::now();
    for(int i=0; i<10; i++){
//        cout<<array[i]<<endl;
        BNode<int> * node =numeros.search(array[i]);

        if(node){
        cout<<"Encontró " << *node<<endl;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto AVL = std::chrono::duration_cast<std::chrono::microseconds>(end-begin);

    cout<<AVL.count()<<endl;

//    numeros.prettyPrint(numeros.getRoot(), 0);


    if(numeros.isAVL(numeros.getRoot()))
        cout<<"ES AVL"<<endl;
    else{
        cout<<"No es"<<endl;
    }


//    numeros.reverseInOrder();




    return 0;
}
