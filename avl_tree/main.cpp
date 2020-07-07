//
//  main.cpp
//  avl_tree
//
//  Created by Carlos NG on 6/3/20.
//  Copyright © 2020 Carlos NG. All rights reserved.
//

#include <iostream>
#include "tree.hpp"
int main() {
    Tree tree;
    int auxValue = 0;
    tree.Insert(41, tree.getRoot(), &auxValue);
    tree.Insert(23, tree.getRoot(), &auxValue);
    tree.Insert(53, tree.getRoot(), &auxValue);
    tree.Insert(55, tree.getRoot(), &auxValue);
    tree.Insert(56, tree.getRoot(), &auxValue);
    tree.Insert(22, tree.getRoot(), &auxValue);
    tree.Insert(21, tree.getRoot(), &auxValue);
    tree.Remove(tree.getRoot(), NULL, &auxValue, 22);
    tree.Inorder2(tree.getRoot());
    tree.graphAVL();
    
    
    return 0;
}
