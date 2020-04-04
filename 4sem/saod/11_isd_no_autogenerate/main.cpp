#include <iostream>
#include "Tree.h"

using namespace std;

int main(){
    // int n_vertices;
    Tree *tree = new Tree();
    int choice = 1;    

    while (choice != 0){
        cout << "\nSelect action:\n"
        "0) Выход\n"
        "1) Поиск вершины\n"
        "2) Добавление левого или правого потомка\n"
        "3) Построчный вывод дерева\n"
        "4) Уничтожение всего дерева\n"
        "Выбрать: ";

        cin >> choice;
        TreeNode* search_res = nullptr;
        int insert_value;
        int search_value;

        switch (choice){

        case 1:
            {
            cout << "Введите значение для поиска: ";
            cin >> search_value;
            tree->search(&search_res, tree->pRoot, search_value, false);
            if (search_res != nullptr)
                cout << "Элемент " << search_res->data << 
                " найден в дереве\n";
            else
                cout << "\nТакого элемента в дереве не найдено\n";
            
            break;
            }
        case 2:
            
            cout << "\nВведите значение для добавления в дерево: ";
            cin >> insert_value;
            if (tree->pRoot == nullptr)
            {
                tree->add_node(&(tree->pRoot), insert_value);
            }
            else
            {
                int direction;

                cout << "\nВведите значение для поиска: ";
                cin >> search_value;
                tree->search(&search_res, tree->pRoot, search_value, false);
                if (search_res == nullptr)
                {
                    cout << "\nТакого элемента в дереве не найдено\n";
                    break;
                }
                else if (search_res->right == nullptr && search_res->left == nullptr)
                {
                    cout << endl <<
                            "0) Влево\n"
                            "1) Вправо\n"
                            "Выбрать: ";
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
                    cout << "\nНет свободных потомков\n";
            }
            break;

        case 3:
            if (tree->pRoot == nullptr)
            {
                cout << "\nДерево пустое\n";
                break ;
            }
            int pass;
            cout << endl <<
                        "0) Прямой обход\n"
                        "1) Симметричный обход\n"
                        "2) Обратный симметричный обход\n"
                        "Выбрать: ";
            cin >> pass;
            cout << "\n\n Дерево:\n-----------------------\n\n"; 
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
            cout << "\nДерево успешно удалено\n";
            tree->pRoot = nullptr;
            break;
        
    
        }
    }
    return 0;
}