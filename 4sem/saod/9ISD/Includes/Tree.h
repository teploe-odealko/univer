#pragma once
#define Tree_h

struct Node
{
    Node* right;
    Node* left;
    int data;
};

struct Tree
{
private:
    // int n_vertices;
    
    void add_nodes(Node**, int);
    
    
public:
    Node *pRoot = new Node();
    Tree(int);
    void forward(Node*, int);
    void symmetric(Node*, int);
    void backward_symmetric(Node*, int);
};

