#pragma once
#define Tree_h

struct TreeNode
{
    TreeNode* right;
    TreeNode* left;
    int data;
    
};

class Tree
{
private:
    // int n_vertices;
    
    void add_TreeNodes(TreeNode**, int);
    
    
public:
    TreeNode *pRoot = nullptr;
    Tree();
    ~Tree();
    void destr(TreeNode*);
    void search(TreeNode**, TreeNode*, int, bool);
    void add_node(TreeNode**, int);
    void forward(TreeNode*, int);
    void symmetric(TreeNode*, int);
    void backward_symmetric(TreeNode*, int);
    
};

