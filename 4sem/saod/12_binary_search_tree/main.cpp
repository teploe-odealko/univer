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
        "2) Добавление вершины\n"
        "3) Вывод дерева\n"
        "4) Уничтожение заданной вершины\n"
        "Выбрать: ";

        cin >> choice;
        TreeNode* search_res = nullptr;
        int insert_value;
        int search_value;
        int to_remove;
        bool res;

        switch (choice){

        case 1:
            {
            cout << "Введите значение для поиска: ";
            cin >> search_value;
            tree->search(search_res, tree->pRoot, search_value, false);
            if (search_res != nullptr)
                cout << "Элемент \"" << search_res->data << 
                "\" встречается " << search_res->counter << " раз";
            else
                cout << "\nТакого элемента в дереве не найдено\n";
            
            break;
            }
        case 2:
            
            cout << "\nВведите значение для добавления в дерево: ";
            cin >> insert_value;
            int ch;
            cout << endl <<
                "0) Итеративный метод\n"
                "1) Рекурсивный метод\n"
                "Выбрать: ";
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
                cout << "\nДерево пустое\n";
                break ;
            }
            int pass;
            cout << endl <<
                        "0) В строчку\n"
                        "1) Обратный-симметричный обход\n"
                        "Выбрать: ";
            cin >> pass;
            cout << "\n\n Дерево:\n-----------------------\n\n"; 
            if (pass == 0)
                tree->inline_out(tree->pRoot, 0);
            else if (pass == 1)
                tree->backward_symmetric(tree->pRoot, 0);
            cout << "\n-----------------------\n";
            break;
            
        case 4:
            
            cout << "\nВведите значение вершины для удаления: ";
            cin >> to_remove;
            res = false;
            tree->destr_vert(tree->pRoot, to_remove, res);
            if (res)
                cout << "\nВешрина успешно удалена\n";
            else 
                cout << "\nВешрина не найдена\n";
            // tree->pRoot = nullptr;
            break;
        }
    }
    return 0;
}