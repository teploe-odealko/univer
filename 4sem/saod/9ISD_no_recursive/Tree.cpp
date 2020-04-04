#include "Tree.h"
#include "stdlib.h"
#include <iostream>
using namespace std;

int generate_int()
{
    return rand() % 100 + 1;
}

Tree::Tree(int n_vertices)
{
    // this->n_vertices = n_vertices;
    stack = new DynamicStack();
    add_TreeNodes(&pRoot, n_vertices);
}

void Tree::add_TreeNodes(TreeNode **pCurrent, int n_vertices)
{
    int nl, nr;
    TreeNode *pTemp;
    // cout << n_vertices << endl;
    if (n_vertices == 0)
    {
        *pCurrent = NULL;
    }
    else
    {
        nl = n_vertices / 2;
        nr = n_vertices - nl - 1;
        pTemp = new TreeNode();
        pTemp->data = generate_int();
        add_TreeNodes(&(pTemp->left), nl);
        add_TreeNodes(&(pTemp->right), nr);
        *pCurrent = pTemp;
    }
}

void Tree::forward(TreeNode *pCurrent, int level)
{
    if (pCurrent != NULL)
    {
        for (int i = 0; i < level*5; i++)
            cout << " ";
        level++;
        cout << pCurrent->data << endl;
        forward(pCurrent->left, level);
        forward(pCurrent->right, level);
    }
}

void Tree::symmetric()
{
    TreeNode *pCurrent = pRoot;
    int level = -1;
    bool stop = false;
    while (!stop)
    {
        // cout << "pcur" << pCurrent->data << endl;
        while (pCurrent != NULL)
        {
            // cout << "pcur " << pCurrent->data << endl;
            stack->addItem(pCurrent, ++level);
            // cout << "Size ++++ " << stack->get_size() << endl;
            pCurrent = pCurrent->left;
        }
        
        if (stack->isEmpty())
            stop = true;
        else
        {
            for (int i = 0; i < stack->getTopPtr()->level*5 ; i++)
                cout << " ";
            pCurrent = stack->getTopPtr()->treeNode;
            cout << pCurrent->data << endl;
            level = stack->getTopPtr()->level;
            pCurrent = pCurrent->right;
            stack->removeTop();
        }
    }
    
    // if (pCurrent != NULL)
    // {
        
    //     symmetric(pCurrent->left, level+1);
    //     for (int i = 0; i < level*5; i++)
    //         cout << " ";
    //     cout << pCurrent->data << endl;
    //     symmetric(pCurrent->right, level+1);
    // }
}

void Tree::backward_symmetric(TreeNode *pCurrent, int level)
{
    if (pCurrent != NULL)
    {
        
        backward_symmetric(pCurrent->right, level+1);
        for (int i = 0; i < level*5; i++)
            cout << " ";
        cout << pCurrent->data << endl;
        backward_symmetric(pCurrent->left, level+1);
        
        
    }
}