#pragma once
// #define DynamicStack_h0

struct TreeNode
{
    TreeNode* right;
    TreeNode* left;
    int data;
    
};

struct StackNode
{
    StackNode *next;
    TreeNode *treeNode;
    int level;
};

class DynamicStack
{
private:
    int size = -1; 
    StackNode* sp = nullptr;
public:
    DynamicStack(/* args */);
    StackNode* getSp(){ return sp; };
    void addItem(TreeNode*, int);
    int get_size(){ return size; };
    void showAll();
    void removeTop();
    void addStackNode(StackNode*);
    StackNode* getTopPtr();
    bool isEmpty();
    ~DynamicStack();

};

