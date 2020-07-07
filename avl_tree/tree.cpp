//
//  tree.cpp
//  avl_tree
//
//  Created by Carlos NG on 6/3/20.
//  Copyright © 2020 Carlos NG. All rights reserved.
//

#include "tree.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

std::string str;

Node* Tree::LLRotation(Node* p, Node* aux)
{
    p -> setLeft(aux -> getRight());
    aux -> setRight(p);
    p -> setFE(0);
    return aux;
}

Node* Tree::RRRotation(Node* p, Node* aux)
{
    p -> setRight(aux -> getLeft());
    aux -> setLeft(p);
    p -> setFE(0);
    return aux;
}

Node* Tree::LRRotation(Node* p, Node* aux)
{
    Node* aux2;
    aux2 = aux -> getRight();
    p -> setLeft(aux2 -> getRight());
    aux2 -> setRight(p);
    aux -> setRight(aux2 -> getLeft());
    aux2 -> setLeft(aux);
    
    if(aux2 -> getFE() == -1){
        p -> setFE(1);
    }
    else
    {
        p -> setFE(0);
    }
    if(aux2 -> getFE() == 1)
    {
        aux -> setFE(-1);
    }
    else
    {
        aux -> setFE(0);
    }
    return aux2;
    
}

Node* Tree::RLRotation(Node* p, Node* aux)
{ // CAMBIAR ESTE
    Node* aux2;
    aux2 = aux -> getLeft();
    p -> setRight(aux2 -> getLeft());
    aux2 -> setLeft(p);
    aux -> setLeft(aux2 -> getRight());
    aux2 -> setRight(aux);
    
    if(aux2 -> getFE() == 1){
        p -> setFE(-1);
    }
    else
    {
        p -> setFE(0);
    }
    if(aux2 -> getFE() == -1)
    {
        aux -> setFE(1);
    }
    else
    {
        aux -> setFE(0);
    }
    return aux2;
}

Node* Tree::Search(Node* node, int value) // Extracted from BST
{
    if(node != nullptr)
    {
        if(value < node -> getData())
        {
            return Search(node -> getLeft(), value);
        }
        else
        {
            if(value > node -> getData())
            {
                return Search(node -> getRight(), value);
            }
            else
            {
                std::cout << "Node found: " << node -> getData() << std::endl;
                return node;
            }
        }
    }
    else
    {
        std::cout << "Node not found." << std::endl;
        return nullptr;
    }
}

void Tree::Insert(int value, Node* p, int* valueAux) // data to insert, Node to visit and aux value. (valueAux = 0)
{
    Node* aux1, *aux2;
    if(p != NULL) // verifies if pointer is not empty
    {
        if(value < p -> getData())
        {
            // starts method at left subtree.
            Insert(value, p -> getLeft(), valueAux);
            p -> setLeft(root);
            if(0 < *valueAux) // Verify if left subtree has grown.
            {
                switch(p -> getFE())
                {
                    case 1:
                    {
                        p -> setFE(0);
                        *valueAux = 0;
                        break;
                    }
                    case 0:
                    {
                        p -> setFE(-1);
                        break;
                    }
                    case -1:
                    {
                        aux1 = p -> getLeft();
                        if(aux1 -> getFE() <= 0)
                        {
                            p = LLRotation(p, aux1);
                        }
                        else
                        {
                            p = LRRotation(p, aux1);
                        }
                        p -> setFE(0);
                        *valueAux = 0;
                    }
                }
            }
        }
        else
        {
            if(value > p -> getData())
            {
                // Starts right subtree method.
                Insert(value, p -> getRight(), valueAux);
                p -> setRight(root);
                if(0 < *valueAux)
                {
                    switch(p -> getFE())
                    {
                        case -1:
                        {
                            p -> setFE(0);
                            *valueAux = 0;
                            break;
                        }
                        case 0:
                        {
                            p -> setFE(1);
                            break;
                        }
                        case 1:
                        {
                            aux1 = p -> getRight();
                            if(aux1 -> getFE() >= 0)
                            {
                                p = RRRotation(p, aux1);
                            }
                            else
                            {
                                p = RLRotation(p, aux1);
                            }
                            p -> setFE(0);
                            *valueAux = 0;
                        }
                    }
                }
            }
        }
        root = p;
    }
    else
    {
        // Inserts new node updating valueAux value and setting that the tree has grown up. Works when root is empy
        aux2 = new Node();
        aux2 -> setData(value);
        aux2 -> setFE(0);
        *valueAux = 1;
        root = aux2;
    }
}

Node* Tree::LRestructure(Node *p, int *auxValue) // Restructure left when right side got diminished
{
    Node* aux;
    if(*auxValue > 0)
    {
       switch(p -> getFE())
       {
           case -1:
               p -> setFE(0);
               break;
           case 0:
               p -> setFE(1);
               *auxValue = 0;
               break;
           case 1:
               aux = p -> getRight();
               if(aux -> getFE() >= 0) // Applies RR Rotation.
               {
                   p -> setRight(aux -> getLeft());
                   aux -> setLeft(p);
                   switch(aux -> getFE())
                   {
                       case 0:
                           p -> setFE(1);
                           aux -> setFE(-1);
                           *auxValue = 0;
                           break;
                       case 1:
                           p -> setFE(0);
                           aux -> setFE(0);
                           break;
                   }
                   p = aux;
               }
               else // Applies RL Rotation.
               {
                   p = RLRotation(p, aux);
                   p -> setFE(0);
               }
               break;
       }
    }
    return p;
}

Node* Tree::RRestructure(Node *p, int *auxValue) // Restructure tree when right side got diminished
{
    Node* aux;
    if(*auxValue > 0)
    {
       switch(p -> getFE())
       {
           case 1:
               p -> setFE(0);
               break;
           case 0:
               p -> setFE(-1);
               *auxValue = 0;
               break;
           case -1:
               aux = p -> getLeft();
               if(aux -> getFE() <= 0) // Applies LL Rotation.
               {
                   p -> setLeft(aux -> getRight());
                   aux -> setRight(p);
                   switch(aux -> getFE())
                   {
                       case 0:
                           p -> setFE(-1);
                           aux -> setFE(1);
                           *auxValue = 0;
                           break;
                       case -1:
                           p -> setFE(0);
                           aux -> setFE(0);
                           break;
                   }
                   p = aux;
               }
               else // Applies LR Rotation.
               {
                   p = LRRotation(p, aux);
                   p -> setFE(0);
               }
               break;
       }
    }
    return p;
}

void Tree::Susbstitute(Node* p, Node *aux, int *auxValue)
{ // Substitutes the deleted value for the rightmost value from the left subtree.
    if(p -> getRight() != NULL)
    {
        Susbstitute(p -> getRight(), aux, auxValue);
        if(aux -> getLeft() == NULL)
        {
            p -> setRight(NULL);
        }
        else
        {
            p -> setRight(aux -> getLeft());
        }
        p = RRestructure(p, auxValue);
    }
    else
    {
        aux -> setData(p -> getData());
        p = p -> getLeft();
        *auxValue = 1;
    }
    aux -> setLeft(p);
}

void Tree::Remove(Node *p, Node *pAnt, int *auxValue, int value)
{
    Node* aux = nullptr;
    int top = 0;
    if(p != NULL)
    {
        if(value < p -> getData())
        {
            if(*auxValue > 0)
            {
                top = 1;
            }
            else
            {
                if(*auxValue != 0)
                {
                    top = -1;
                }
            }
            *auxValue = -1;
            Remove(p -> getLeft(), p, auxValue, value);
            p = LRestructure(p, auxValue);
            if(pAnt != NULL)
            {
                switch(top)
                {
                    case -1:
                        pAnt -> setLeft(p);
                        break;
                    case 1:
                        pAnt -> setRight(p);
                        break;
                    default: break;
                }
            }
            else
            {
                root = p;
            }
        }
    
        else
        {
            if(value > p -> getData())
            {
                if(*auxValue < 0)
                {
                    top = -1;
                }
                else
                {
                    if(*auxValue != 0)
                    {
                        top = 1;
                    }
                }
                *auxValue = 1;
                Remove(p -> getRight(), p, auxValue, value);
                p = RRestructure(p, auxValue);
                if(pAnt != NULL)
                {
                    switch(top)
                    {
                        case -1:
                            pAnt -> setLeft(p);
                            break;
                        case 1:
                            pAnt -> setRight(p);
                            break;
                        default: break;
                    }
                }
                else
                {
                    root = p;
                }
            }
            else
            {
                aux = p;
                if(aux -> getRight() == NULL)
                {
                    p = aux -> getLeft();
                    if(*auxValue != 0)
                    {
                        if(*auxValue < 0)
                        {
                            pAnt -> setLeft(p);
                        }
                        else
                        {
                            pAnt -> setRight(p);
                        }
                    }
                    else
                    {
                        if(p == NULL)
                        {
                            root = NULL;
                        }
                        else
                        {
                            root = p;
                        }
                        *auxValue = 1;
                    }
                }
                else
                {
                    if(p -> getLeft() == NULL)
                    {
                        p = aux -> getRight();
                        if(*auxValue != 0)
                        {
                            if(*auxValue < 0)
                            {
                                pAnt -> setLeft(p);
                            }
                            else
                            {
                                pAnt -> setRight(p);
                            }
                        }
                        else
                        {
                            if(p == NULL)
                            {
                                root = NULL;
                            }
                            else
                            {
                                root = p;
                            }
                            *auxValue = 1;
                        }
                    }
                    else
                    {
                        Susbstitute(aux -> getLeft(), aux, auxValue);
                        p = LRestructure(p, auxValue);
                        
                        if(pAnt != NULL)
                        {
                            if(*auxValue <= 0)
                            {
                                pAnt -> setLeft(p);
                            }
                            else
                            {
                                pAnt -> setRight(p);
                            }
                        }
                        else
                        {
                            root = p;
                        }
                    }
                }
            }
        }
    }
}

void Tree::graphAVL()
{
    ofstream file;
    file.open("avl.dot", ios::out);
    str = "digraph g{ ";
    str += "node [fontname=";
    str+="\"Arial\"";
    str+="];";
    Inorder(getRoot());
    str += "}";
    file << str << endl;
    file.close();
    system("dot -Tpng avl.dot -o avl.png");
    system("avl.png");


    
}

void Tree::Inorder(Node* node)
{
    if(node != NULL)
    {
        Inorder(node -> left);
        str += to_string(node -> getData()) + "[label=" + to_string(node -> getData()) + "];";

        if(node -> getLeft()!=NULL)
        {
            str+= to_string(node -> getData()) + "->{" +to_string(node->getLeft()->getData())+"};";

        }
        if(node -> getRight()!=NULL)
        {
            str+= to_string(node -> getData()) + "->{" +to_string(node->getRight()->getData())+"};";

        }
        Inorder(node -> right);
    }
}
void Tree::Inorder2(Node* node)
{
    if(node != NULL)
    {
        Inorder2(node -> left);
        cout << node -> getData() << " " ;
        Inorder2(node -> right);
    }
}
