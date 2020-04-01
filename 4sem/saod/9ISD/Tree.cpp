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
    add_nodes(&pRoot, n_vertices);
}

void Tree::add_nodes(Node **pCurrent, int n_vertices)
{
    int nl, nr;
    Node *pTemp;
    // cout << n_vertices << endl;
    if (n_vertices == 0)
    {
        *pCurrent = NULL;
    }
    else
    {
        nl = n_vertices / 2;
        nr = n_vertices - nl - 1;
        pTemp = new Node();
        pTemp->data = generate_int();
        add_nodes(&(pTemp->left), nl);
        add_nodes(&(pTemp->right), nr);
        *pCurrent = pTemp;
    }
}

void Tree::forward(Node *pCurrent, int level)
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

void Tree::symmetric(Node *pCurrent, int level)
{
    if (pCurrent != NULL)
    {
        
        symmetric(pCurrent->left, level+1);
        for (int i = 0; i < level*5; i++)
            cout << " ";
        cout << pCurrent->data << endl;
        symmetric(pCurrent->right, level+1);
    }
}

void Tree::backward_symmetric(Node *pCurrent, int level)
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