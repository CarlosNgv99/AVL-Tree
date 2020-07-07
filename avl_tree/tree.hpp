//
//  tree.hpp
//  avl_tree
//
//  Created by Carlos NG on 6/3/20.
//  Copyright © 2020 Carlos NG. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <stdio.h>
#include <string>
class Tree;
class Graph;
class Node
{
private:
    Node* right;
    Node* left;
    int FE;
    int data;
public:
    friend class Tree;
    Node(){right = nullptr; left = nullptr;};
    Node* getLeft(){return left;};
    Node* getRight(){return right;};
    void setLeft(Node* value){left = value;};
    void setRight(Node* value){right = value;};
    int getFE(){return FE;};
    void setFE(int value){FE = value;};
    int getData(){return data;};
    void setData(int data){this -> data = data;};

};

class Tree
{
private:
    Node* root;
public:
    Tree(){root = nullptr;};
    void setRoot(Node* value){root = value;};
    Node* LLRotation(Node* p, Node* aux);
    Node* RRRotation(Node* p, Node* aux);
    Node* LRRotation(Node* p, Node* aux);
    Node* RLRotation(Node* p, Node* aux);
    Node* Search(Node*, int data);
    Node* LRestructure(Node* p, int* auxValue);
    Node* RRestructure(Node* p, int* auxValue);
    void Susbstitute(Node* p, Node* aux, int* auxValue);
    void Insert(int data, Node* p, int* band);
    void Remove(Node* p, Node* pAnt, int* axuValue, int value);
    void Inorder(Node* node);
    void Inorder2(Node* node);

    Node* getRoot(){return root;};
    void graphAVL();
};

#endif /* tree_hpp */

class Graph
{
public:
    Graph();
    void graphAVL();
};
