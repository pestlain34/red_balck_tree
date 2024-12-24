#include "redblacktree.h"
void printMenu() {
    cout << "\n--- Меню ---\n";
    cout << "1. Вставить элементы\n";
    cout << "2. Найти элемент\n";
    cout << "3. Удалить элемент\n";
    cout << "4. Показать дерево\n";
    cout << "5. Обход дерева (Inorder, Preorder, Postorder, Level-order)\n";
    cout << "6. Найти преемника и предшественника\n";
    cout << "7. Проверить свойства дерева\n";
    cout << "8. Вычислить высоту и количество узлов\n";
    cout << "9. Выход\n";
    cout << "Выберите действие: ";
}
int main() {
    setlocale(LC_ALL, "ru");
    RedBlackTree tree;
    int choice;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1: { // Вставить элементы
            cout << "Введите элементы через пробел: ";
            string input;
            int value;
            cin.ignore(); // чтобы проигнорировать символ новой строки после предыдущего ввода
            getline(cin, input); // получаем строку ввода
            stringstream ss(input); // создаем поток из строки
            while (ss >> value){
                tree.insert(value);
                cout << "Элемент " << value << " вставлен.\n";
            }
            break;
        }

        case 2: { // Найти элемент
            int key;
            cout << "Введите элемент для поиска: ";
            cin >> key;
            Node* found = tree.search(key);
            if (found)
                cout << "Элемент " << key << " найден.\n";
            else
                cout << "Элемент " << key << " не найден.\n";
            break;
        }

        case 3: { // Удалить элемент
            int key;
            cout << "Введите элемент для удаления: ";
            cin >> key;
            tree.remove(key);
            cout << "Элемент " << key << " удалён.\n";
            break;
        }

        case 4: { // Показать дерево
            cout << "\nВизуальное представление дерева:\n";
            tree.ShowTree();
            break;
        }

        case 5: { // Обход дерева
            cout << "\nОбход Inorder: ";
            tree.inorder();
            cout << "Обход Preorder: ";
            tree.preorder();
            cout << "Обход Postorder: ";
            tree.postorder();
            cout << "Обход Level-order: ";
            tree.levelOrder();
            break;
        }

        case 6: { // Найти преемника и предшественника
            int key;
            cout << "Введите элемент: ";
            cin >> key;
            Node* succ = tree.findSuccessor(key);
            Node* pred = tree.findPredecessor(key);
            if (succ)
                cout << "Преемник: " << succ->data << "\n";
            else
                cout << "Преемника нет.\n";
            if (pred)
                cout << "Предшественник: " << pred->data << "\n";
            else
                cout << "Предшественника нет.\n";
            break;
        }

        case 7: { // Проверить свойства дерева
            cout << "\nПроверка свойств дерева: ";
            if (tree.validate())
                cout << "Дерево является валидным чёрно-красным деревом.\n";
            else
                cout << "Дерево НЕ является валидным чёрно-красным деревом.\n";
            break;
        }

        case 8: { // Вычислить высоту и количество узлов
            cout << "\nВысота дерева: " << tree.getHeight() << "\n";
            cout << "Количество узлов: " << tree.getNodeCount() << "\n";
            break;
        }

        case 9: { // Выход
            cout << "Выход из программы.\n";
            break;
        }

        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 9);

    return 0;
}
