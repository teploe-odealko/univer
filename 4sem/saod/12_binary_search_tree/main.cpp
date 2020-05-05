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
        "2) Adding a vertex\n"
        "3) The output of the tree\n"
        "4) The destruction of the given node\n"
        "Select: ";

        cin >> choice;
        TreeNode* search_res = nullptr;
        int insert_value;
        int search_value;
        int to_remove;
        bool res;

        switch (choice){

        case 1:
            {
            cout << "Enter the value to search for: ";
            cin >> search_value;
            tree->search(search_res, tree->pRoot, search_value, false);
            if (search_res != nullptr)
                cout << "The Item \"" << search_res->data << 
                "\" occurs " << search_res->counter << " times";
            else
                cout << "\nNo such element was found in the tree :(\n";
            
            break;
            }
        case 2:
            
            cout << "\nEnter a value to add to the tree: ";
            cin >> insert_value;
            int ch;
            cout << endl <<
                "0) Iterative method\n"
                "1) Recursive method\n"
                "Select: ";
            cin >> ch;
            if (ch == 0)
                tree->add_node_iterative(insert_value);
            else if (ch == 1)
                tree->add_node_recursive(&(tree->pRoot), insert_value);
                // cout << "\nВведите значение для поиска: ";
                // cin >> search_value;
                // tree->search(&search_res, tree->pRoot, search_value, false);
                // if (search_res == nullptr)
                // {
                //     cout << "\nТакого элемента в дереве не найдено\n";
                //     break;
                // }
            //     else if (search_res->right == nullptr && search_res->left == nullptr)
            //     {
            //         cout << endl <<
            //                 "0) Влево\n"
            //                 "1) Вправо\n"
            //                 "Выбрать: ";
            //         cin >> direction;
            //         if (direction == 0)
            //             tree->add_node(&(search_res->left), insert_value);
            //         else if (direction == 1)
            //             tree->add_node(&(search_res->right), insert_value);
            //         break ;
            //     }
            //     if (search_res->left == nullptr)
            //         tree->add_node(&(search_res->left), insert_value);
            //     else if (search_res->right == nullptr)
            //         tree->add_node(&(search_res->right), insert_value);
            //     else
            //         cout << "\nНет свободных потомков\n";
            // }
            break;

        case 3:
            if (tree->pRoot == nullptr)
            {
                cout << "\nThe tree is empty\n";
                break ;
            }
            int pass;
            cout << endl <<
                        "0) in line\n"
                        "1) Reverse-symmetric\n"
                        "Select: ";
            cin >> pass;
            cout << "\n\n Tree:\n-----------------------\n\n"; 
            if (pass == 0)
                tree->inline_out(tree->pRoot, 0);
            else if (pass == 1)
                tree->backward_symmetric(tree->pRoot, 0);
            cout << "\n-----------------------\n";
            break;
            
        case 4:
            
            cout << "\nEnter the vertex value to delete: ";
            cin >> to_remove;
            res = false;
            tree->destr_vert(tree->pRoot, to_remove, res);
            if (res)
                cout << "\nVertex was successfully deleted :)\n";
            else 
                cout << "\nVertex was not found :(\n";
            // tree->pRoot = nullptr;
            break;
        }
    }
    return 0;
}