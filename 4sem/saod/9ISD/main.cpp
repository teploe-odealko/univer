#include <iostream>
#include "Tree.h"

using namespace std;

int main(){
    int n_vertices;
    Tree *tree;
    
    cout << "Введите количество вершин дерева: ";
    cin >> n_vertices; 
    tree = new Tree(n_vertices);
    cout << "\nПрямой порядок" << endl;
    cout << "-----------------------\n";
    tree->forward(tree->pRoot, 0);
    cout << "-----------------------\n\n";

    cout << "\nСимметричный порядок" << endl;
    cout << "-----------------------\n";
    tree->symmetric(tree->pRoot, 0);
    cout << "-----------------------\n\n";

    cout << "\nОбратный симметричный порядок" << endl;
    cout << "-----------------------\n";
    tree->backward_symmetric(tree->pRoot, 0);
    cout << "-----------------------\n\n";

    return 0;
}