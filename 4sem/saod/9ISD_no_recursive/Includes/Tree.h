#pragma once
#define Tree_h
#include "DynamicStack.h"



struct Tree
{
private:
    // int n_vertices;
    
    void add_TreeNodes(TreeNode**, int);
    DynamicStack *stack;
    
    
public:
    TreeNode *pRoot = new TreeNode();
    Tree(int);
    void forward(TreeNode*, int);
    void symmetric();
    void backward_symmetric(TreeNode*, int);
    
};

