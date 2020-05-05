#include <iostream>
#include "Tree.h"

using namespace std;

int main(){
    // int n_vertices;
    Tree *tree = new Tree();
    int choice = 1;    

    while (choice != 0){
        cout << "\nSelect action:\n"
        "0) Exit\n"
        "1) Search for a vertex\n"
        "2) Adding a left or right child\n"
        "3) Line-by-line output of the tree\n"
        "4) The destruction of the entire tree\n"
        "Select: ";

        cin >> choice;
        TreeNode* search_res = nullptr;
        int insert_value;
        int search_value;

        switch (choice){

        case 1:
            {
            cout << "Enter the value to search for: ";
            cin >> search_value;
            tree->search(&search_res, tree->pRoot, search_value, false);
            if (search_res != nullptr)
                cout << "Item " << search_res->data << 
                " FOUND :)\n";
            else
                cout << "\nNo such item :(\n";
            
            break;
            }
        case 2:
            
            cout << "\nEnter a value to add to the tree: ";
            cin >> insert_value;
            if (tree->pRoot == nullptr)
            {
                tree->add_node(&(tree->pRoot), insert_value);
            }
            else
            {
                int direction;

                cout << "\nEnter the value to search for: ";
                cin >> search_value;
                tree->search(&search_res, tree->pRoot, search_value, false);
                if (search_res == nullptr)
                {
                    cout << "\nNo such item :(\n";
                    break;
                }
                else if (search_res->right == nullptr && search_res->left == nullptr)
                {
                    cout << endl <<
                            "0) left\n"
                            "1) right\n"
                            "select: ";
                    cin >> direction;
                    if (direction == 0)
                        tree->add_node(&(search_res->left), insert_value);
                    else if (direction == 1)
                        tree->add_node(&(search_res->right), insert_value);
                    break ;
                }
                if (search_res->left == nullptr)
                    tree->add_node(&(search_res->left), insert_value);
                else if (search_res->right == nullptr)
                    tree->add_node(&(search_res->right), insert_value);
                else
                    cout << "\nThere are no available childs\n";
            }
            break;

        case 3:
            if (tree->pRoot == nullptr)
            {
                cout << "\nThe tree is empty\n";
                break ;
            }
            int pass;
            cout << endl <<
                        "0) Direct\n"
                        "1) Symmetrical\n"
                        "2) Reverse symmetric\n"
                        "Select: ";
            cin >> pass;
            cout << "\n\n Tree:\n-----------------------\n\n"; 
            if (pass == 0)
                tree->forward(tree->pRoot, 0);
            else if (pass == 1)
                tree->symmetric(tree->pRoot, 0);
            else if (pass == 2)
                tree->backward_symmetric(tree->pRoot, 0);
            cout << "\n-----------------------\n";
            break;
            
        case 4:
            tree->destr(tree->pRoot);
            cout << "\nThe tree was successfully deleted\n";
            tree->pRoot = nullptr;
            break;
        
    
        }
    }
    return 0;
}