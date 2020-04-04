#pragma once
#define Tree_h

struct TreeNode
{
    TreeNode* right;
    TreeNode* left;
    int data;
    int counter = 0;
    
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
    void destr_vert(TreeNode*&, int, bool&);
    void search(TreeNode*&, TreeNode*, int, bool);
    void add_node_recursive(TreeNode**, int);
    void add_node_iterative(int);
    void forward(TreeNode*, int);
    void symmetric(TreeNode*, int);
    void backward_symmetric(TreeNode*, int);
    void inline_out(TreeNode*, int);
    void destr_tree(TreeNode*);
    
};

