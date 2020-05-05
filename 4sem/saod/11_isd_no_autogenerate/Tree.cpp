#include "Tree.h"
#include "stdlib.h"
#include <iostream>
using namespace std;

int generate_int()
{
    return rand() % 100 + 1;
}

Tree::Tree()
{
    // this->n_vertices = n_vertices;
    // add_TreeNodes(&pRoot, n_vertices);
}

void Tree::search(TreeNode **res, TreeNode *pCurrent, int value, bool is_finded)
{
    if (pCurrent != nullptr && !is_finded)
    {
        if ((pCurrent)->data == value)
        {
            is_finded = true;
            *res = pCurrent;
        }
        // cout << pCurrent->data << endl;
        search(res, (pCurrent)->left, value, is_finded);
        search(res, (pCurrent)->right, value, is_finded);
    }
}

void Tree::add_node(TreeNode **parent_node, int value)
{
    TreeNode *new_node = new TreeNode();
    new_node->data = value;
    new_node->left = nullptr;
    new_node->right = nullptr;
    *parent_node = new_node;
}

// void Tree::add_TreeNodes(TreeNode **pCurrent, int n_vertices)
// {
//     int nl, nr;
//     TreeNode *pTemp;
//     // cout << n_vertices << endl;
//     if (n_vertices == 0)
//     {
//         *pCurrent = nullptr;
//     }
//     else
//     {
//         nl = n_vertices / 2;
//         nr = n_vertices - nl - 1;
//         pTemp = new TreeNode();
//         pTemp->data = generate_int();
//         add_TreeNodes(&(pTemp->left), nl);
//         add_TreeNodes(&(pTemp->right), nr);
//         *pCurrent = pTemp;
//     }
// }

void Tree::forward(TreeNode *pCurrent, int level)
{
    if (pCurrent != nullptr)
    {
        for (int i = 0; i < level*5; i++)
            cout << " ";
        level++;
        cout << pCurrent->data << endl;
        forward(pCurrent->left, level);
        forward(pCurrent->right, level);
    }
}

void Tree::symmetric(TreeNode *pCurrent, int level)
{    
    if (pCurrent != nullptr)
    {
        symmetric(pCurrent->left, level+1);
        for (int i = 0; i < level*5; i++)
            cout << " ";
        cout << pCurrent->data << endl;
        symmetric(pCurrent->right, level+1);
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

Tree::~Tree()
{
    destr(pRoot);
    // delete pRoot;
}

void Tree::destr(TreeNode* pCurrent)
{
    if (pCurrent != nullptr)
    {
        destr(pCurrent->left);
        destr(pCurrent->right);
        cout << "vertex " << pCurrent->data << " is removing ...\n";
        delete pCurrent;
    }
}