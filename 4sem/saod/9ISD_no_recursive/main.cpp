#include <iostream>
#include "Tree.h"

using namespace std;

int main(){
    int n_vertices;
    Tree *tree;
    
    cout << "Enter the number of tree vertexes: ";
    cin >> n_vertices; 
    tree = new Tree(n_vertices);
    cout << "\nDirect order" << endl;
    cout << "-----------------------\n";
    tree->forward(tree->pRoot, 0);
    cout << "-----------------------\n\n";

    cout << "\nSymmetrical order" << endl;
    cout << "-----------------------\n";
    tree->symmetric();
    cout << "-----------------------\n\n";

    cout << "\nReverse symmetric order" << endl;
    cout << "-----------------------\n";
    tree->backward_symmetric(tree->pRoot, 0);
    cout << "-----------------------\n\n";

    return 0;
}