#include <iostream>
#include "OperatorsList.h"
#include "UsersList.h"
#include <string>

using namespace std;

int main(){
    int choice = 1;
    OperatorsList operatorsList;
    

    while (choice != 0)
    {
        cout << "\nВыберите действие:\n"
        "0) Выход\n"
        "1) Добавить нового оператора\n"
        "2) Добавить нового пользователя для оператора\n"
        "3) Показать весь список\n"
        "4) Удалить оператора\n"
        "5) Удалить пользователя у выбранного оператора\n"
        "6) Загрузить с файла\n"
        "7) Выгрузить в файл\n"
        "Select: ";
        cin >> choice;
        cout << endl;
        bool res;
        string operator_name, find, phone_model, last_name;
        
        switch (choice){
            int user_amount;
            
        case 1:
        {
            
            cout << "Введите название оператора: ";
            cin >> operator_name;
            cout << "Сколько пользователей у этого оператора?: ";
            cin >> user_amount;
            UsersList *sublist = new UsersList(user_amount, operator_name);
            operatorsList.add_operator(sublist);
            break;
        }
        case 2:
            if (operatorsList.isEmpty())
            {
                cout << "Пока нет ни одного оператора. Создайте или загрузите с файла\n";
            }
            else
            {
                res = false;
                cout << "\nВведите название оператора для добавления пользователя: "; 
                cin >> operator_name;
                NodeLL *pSubListNode = operatorsList.findUsersList(operator_name);

                if (pSubListNode == NULL)
                {
                    cout << "Такого оператора еще не существует!\n";
                    break;
                }
                
                UsersList *sublist = (pSubListNode->data);
                if (sublist->get_current_num_of_users() < sublist->get_max_num_of_users())
                {
                    cout << "\nВведите фамилию пользователя: ";
                    cin >> last_name;
                    cout << "\nВведите марку телефона пользователя: ";
                    cin >> phone_model;
                    sublist->add_user(last_name, phone_model);
                    res = true;
                }
                if (res) cout << "Выполнено!\n";
                else cout << "Список переполнен\n";
            }
            break;
            
        case 3:
            if (operatorsList.isEmpty())
            {
                cout << "Пока нет ни одного оператора. Создайте или загрузите с файла\n";
            }
            else
            {
                operatorsList.show_all();
                cout << endl;
            }
            break;

        case 5:

            if (!operatorsList.isEmpty()){
                cout << "\nВведите название оператора: "; 
                cin >> operator_name;
                NodeLL *pSubListNode = operatorsList.findUsersList(operator_name);

                if (pSubListNode == NULL)
                {
                    cout << "Такого оператора еще не существует!\n";
                    break;
                }
                cout << "\nФамилия пользователя для удаления: ";
                cin >> last_name;
                UsersList *sublist = (pSubListNode->data);
                res = sublist->remove_user(last_name);
                if (res) cout << "Выполнено!\n";
                else cout << "Пользователь не найден\n";

            } else {
                cout << "\nУ данного оператора пока нет ни одного пользователя\n";
            }

            break;

        case 4:

            if (!operatorsList.isEmpty())
            {
                cout << "\nВведите название оператора, которого хотите удалить: ";
                cin >> operator_name;
                res = operatorsList.remove_operator(operator_name);
                if (res) cout << "Выполнено!\n";
                else cout << "Такого оператора еще не существует\n";
            }
            else 
            {
                cout << "\nПока нет ни одного оператора. Удалять нечего\n";
            }
            break;

        case 6:
            operatorsList.from_file(operatorsList);
            break ;

        case 7:
            operatorsList.to_file();
            break;

        default:
            break;


        }
    }
    return 0;
}