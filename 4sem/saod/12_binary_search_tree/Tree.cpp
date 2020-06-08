#include "Tree.h"
#include "stdlib.h"
#include <iostream>
using namespace std;

Tree::Tree()
{
    // this->n_vertices = n_vertices;
    // add_TreeNodes(&pRoot, n_vertices);
}

void Tree::search(TreeNode *&res, TreeNode *pCurrent, int value, bool is_finded)
{
    if (pCurrent != nullptr && !is_finded)
    {
        if ((pCurrent)->data == value)
        {
            is_finded = true;
            res = pCurrent;
        }
        // cout << pCurrent->data << endl;
        search(res, (pCurrent)->left, value, is_finded);
        search(res, (pCurrent)->right, value, is_finded);
    }
}



void Changer(TreeNode*& p, TreeNode*& pTemp){
    if (p->right != nullptr)
        Changer(p->right, pTemp);
    else {
        pTemp->data = p->data;
        pTemp = p;
        p = p->left;
    }
}

void Tree::destr_vert(TreeNode *&pCurrent, int value, bool &is_finded)
{
    // is_finded = true;
    if (pCurrent == nullptr){return;}
    else if (value < pCurrent->data)
    {
        destr_vert(pCurrent->left, value, is_finded);
    }
    else if (value > pCurrent->data)
        destr_vert(pCurrent->right, value, is_finded);
    else {
        cout << pCurrent->data;
        TreeNode* pTemp;
        pTemp = pCurrent;
        if (pTemp->right == nullptr)
        {
            pCurrent = pTemp->left;
        }
            
        else if (pTemp->left == nullptr) 
        {
            pCurrent = pTemp->right;
        }
            
        else
        {
            Changer(pCurrent->left, pTemp);
            
        }
        delete pTemp;
        is_finded = true;
        
    }
    
}

void Tree::add_node_recursive(TreeNode **pCurrent, int value)
{
    if ((*pCurrent) == nullptr)
    {
        (*pCurrent) = new TreeNode();
        (*pCurrent)->data = value;
        (*pCurrent)->counter++;
    }
    else if ((*pCurrent)->data == value)
        (*pCurrent)->counter++;
    else
    {
        if ((*pCurrent)->data > value)
            add_node_recursive(&((*pCurrent)->left), value);
        else if ((*pCurrent)->data < value)
            add_node_recursive(&((*pCurrent)->right), value); 
    }
    
    
    
}

void Tree::add_node_iterative(int value)
{

    TreeNode **pCurrent = &pRoot;
    bool stop = false;

    while ((*pCurrent) != nullptr && !stop)
    {
        if ((*pCurrent)->data > value)
            (pCurrent) = &((*pCurrent)->left);
        else 
        {
            if ((*pCurrent)->data < value)
                (pCurrent) = &((*pCurrent)->right);
            else 
                stop = true;
        }    
    }
    if ((*pCurrent) == nullptr)
    {
        (*pCurrent) = (new TreeNode());
        (*pCurrent)->data = value;
        (*pCurrent)->right = nullptr;
        (*pCurrent)->left = nullptr;
    }
    (*pCurrent)->counter++;
}

void Tree::inline_out(TreeNode *pCurrent, int level)
{    
    if (pCurrent != nullptr)
    {
        inline_out(pCurrent->left, level+1);
        cout << pCurrent->data << "(" << pCurrent->counter << ") ";
        inline_out(pCurrent->right, level+1);
    }
}

void Tree::backward_symmetric(TreeNode *pCurrent, int level)
{
    if (pCurrent != nullptr)
    {
        
        backward_symmetric(pCurrent->right, level+1);
        for (int i = 0; i < level*5; i++)
            cout << " ";
        cout << pCurrent->data << endl;
        backward_symmetric(pCurrent->left, level+1);

    }
}

void Tree::destr_tree(TreeNode* pCurrent)
{
    if (pCurrent != nullptr)
    {
        destr_tree(pCurrent->left);
        destr_tree(pCurrent->right);
        cout << "Vertex " << pCurrent->data << " is removing ...\n";
        delete pCurrent;
    }
}

// Tree::~Tree()
// {
//     destr(pRoot);
//     // delete pRoot;
// }

// bool Tree::destr(int value)
// {
//     TreeNode *to_delete;
//     search(to_delete, pRoot, value, false);
//     if (to_delete == nullptr)
//         return false;
//     to_delete = nullptr;
//     return true;
    
// }