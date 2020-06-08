#include <iostream>
#include "Tree.h"

using namespace std;

int generate_int()
{
    return rand() % 100 + 1;
}

int main(){
    // int n_vertices;
    Tree *tree = new Tree();
    int choice = 1;    

    while (choice != 0){
        cout << "\nSelect action:\n"
        "0) Exit\n"
        "1) Search for a vertex\n"
        "2) Adding a several random vertexes\n"
        "3) Adding a vertex\n"
        "4) The output of the tree\n"
        "5) The destruction of the given node\n"
        "Select: ";

        cin >> choice;
        TreeNode* search_res = nullptr;
        int insert_value;
        int search_value;
        int to_remove;
        int tree_size;
        int ch;
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
            cout << "Enter the amount of vertexes: ";
            cin >> tree_size;

            
            cout << endl <<
                "0) Iterative method\n"
                "1) Recursive method\n"
                "Select: ";
            cin >> ch;
            if (ch == 0)
            {
                for (int i = 0; i < tree_size; i++)
                    tree->add_node_iterative(generate_int());
            }
            else if (ch == 1)
                for (int i = 0; i < tree_size; i++)
                    tree->add_node_recursive(&(tree->pRoot), generate_int());
            break;


        case 3:
            
            cout << "\nEnter a value to add to the tree: ";
            cin >> insert_value;
            cout << endl <<
                "0) Iterative method\n"
                "1) Recursive method\n"
                "Select: ";
            cin >> ch;
            if (ch == 0)
                tree->add_node_iterative(insert_value);
            else if (ch == 1)
                tree->add_node_recursive(&(tree->pRoot), insert_value);

            break;

        case 4:
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
            
        case 5:
            
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