#include "redblacktree.h"

// Конструктор для обычных узлов
Node::Node(int data, Node* nil)
    : data(data), color(RED), left(nil), right(nil), parent(nil) {}

// Конструктор для узлов-листьев(null) всегда чёрные
Node::Node()
    : data(0), color(BLACK), left(this), right(this), parent(this) {}

// Конструктор дерева
RedBlackTree::RedBlackTree() {
    NIL = new Node(); // Инициализируем узел-лист(null)
    root = NIL;        // Корень изначально указывает на NIL
}

// Деструктор дерева
RedBlackTree::~RedBlackTree() {
    destroyTree(root);
    delete NIL; 
    root = nullptr;
}

// Рекурсивный метод для удаления всех узлов дерева (постфиксный обход)
void RedBlackTree::destroyTree(Node* node) {
    if (node == NIL) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// Левый поворот вокруг узла x
void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NIL) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Правый поворот вокруг узла y
void RedBlackTree::rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NIL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NIL) {
        root = x;
    }
    else if (y == y->parent->left) {
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

// Большой левый поворот
void RedBlackTree::BigleftRotate(Node* x) {
    rightRotate(x->right);
    leftRotate(x);
}

// Большой правый поворот
void RedBlackTree::BigrightRotate(Node* x) {
    leftRotate(x->left);
    rightRotate(x);
}

// Вставка нового элемента в дерево
void RedBlackTree::insert(int data) {
    Node* z = new Node(data, NIL);
    Node* y = NIL;    // Инициализируем узел y как NIL, он будет родителем для нового узла z
    Node* x = root;   

    while (x != NIL) {
        y = x; 
        if (z->data < x->data) {
            x = x->left;  
        }
        else {
            x = x->right; 
        }
    }
    z->parent = y;
    if (y == NIL) {
        root = z; // Если дерево было пустым, новый узел становится корнем
    }
    else if (z->data < y->data) {
        y->left = z; // Если данные нового узла меньше данных родителя, помещаем его в левое поддерево
    }
    else {
        y->right = z; // Иначе помещаем в правое поддерево
    }
    // Инициализируем левый и правый указатели нового узла на узел `NIL` и устанавливаем цвет узла как красный
    z->left = NIL;
    z->right = NIL;
    z->color = RED;
    // Восстанавливаем свойства красно-черного дерева после вставки
    insertFixup(z);
}

// Восстановление свойств красно-черного дерева после вставки
void RedBlackTree::insertFixup(Node* z) {
    
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) { 
            Node* y = z->parent->parent->right; 

            if (y->color == RED) { // Случай 1: Дядя узла z красный
                // Перекрашиваем родителя и дядю в черный, а дедушку — в красный
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent; 
            }
            else { // Дядя узла z черный
                if (z == z->parent->right) { // Случай 2: Узел z — правый ребенок своего родителя
                    z = z->parent;          
                    leftRotate(z);          
                }
                // Случай 3: Узел z — левый ребенок своего родителя
                z->parent->color = BLACK;           
                z->parent->parent->color = RED;     // Перекрашиваем дедушку в красный
                rightRotate(z->parent->parent);      // Выполняем правый поворот вокруг дедушки
            }
        }
        else { // Симметричный случай: родитель z — правый ребенок своего родителя
            Node* y = z->parent->parent->left; 
            if (y->color == RED) { // Случай 1: Дядя узла z красный
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent; // Переходим к дедушке и продолжаем цикл
            }
            else { // Дядя узла z черный
                if (z == z->parent->left) { // Случай 2: Узел z — левый ребенок своего родителя
                    z = z->parent;          
                    rightRotate(z);         
                }
                // Случай 3: Узел z — правый ребенок своего родителя
                z->parent->color = BLACK;           
                z->parent->parent->color = RED;     // Перекрашиваем дедушку в красный
                leftRotate(z->parent->parent);       // Выполняем левый поворот вокруг дедушки
            }
        }
    }
    root->color = BLACK; // Устанавливаем цвет корня дерева в черный
}


// Поиск узла с заданным ключом
Node* RedBlackTree::search(int key) {
    Node* node = searchHelper(root, key);
    if (node == NIL) {
        cout << "Такого элемента в дереве нет" << endl;
        return nullptr;
    }
    return node;
}

// Вспомогательная функция поиска
Node* RedBlackTree::searchHelper(Node* node, int key) {
    while (node != NIL && key != node->data) {
        if (key < node->data)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

// Нахождение минимального узла в поддереве
Node* RedBlackTree::treeMinimum(Node* node) {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

// Нахождение максимального узла в поддереве
Node* RedBlackTree::treeMaximum(Node* node) {
    while (node->right != NIL) {
        node = node->right;
    }
    return node;
}

// Замена поддерева u на поддерево v
void RedBlackTree::zamena(Node* u, Node* v) {
    if (u->parent == NIL) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// Удаление узла с заданным ключом
void RedBlackTree::remove(int key) {
    Node* z = search(key);
    if (z == nullptr) return;
    deleteNodehelper(z);
}

// Вспомогательная функция удаления узла
void RedBlackTree::deleteNodehelper(Node* z) {
    Node* y = z;                       // Узел y изначально равен узлу z, который нужно удалить
    Node* x;                           // Узел x будет использоваться для фиксации дерева после удаления
    Color y_original_color = y->color; // Сохраняем оригинальный цвет узла y для дальнейшей проверки

    if (z->left == NIL) {              // Если у узла z нет левого ребенка
        x = z->right;                   
        zamena(z, z->right);        
    }
    else if (z->right == NIL) {        // Если у узла z нет правого ребенка
        x = z->left;                    
        zamena(z, z->left);         
    }
    else {                              // Если у узла z есть оба ребенка
        y = treeMinimum(z->right);      
        y_original_color = y->color;    
        x = y->right;                    

        if (y->parent == z) {            // Если преемник y является непосредственным правым ребенком z
            x->parent = y;               
        }
        else {                           // Если преемник y не является непосредственным правым ребенком z
            zamena(y, y->right);     
            y->right = z->right;         
            y->right->parent = y;        
        }

        zamena(z, y);                // Заменяем поддерево z на y
        y->left = z->left;               
        y->left->parent = y;             
        y->color = z->color;             
    }

    delete z;                            // Освобождаем память, занимаемую узлом z
    if (y_original_color == BLACK) {     // Если оригинальный цвет удаленного узла был черным
        deleteFixup(x);                  // Восстанавливаем свойства красно-черного дерева
    }
}


// Восстановление свойств красно-черного дерева после удаления
void RedBlackTree::deleteFixup(Node* x) {
    
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) { 
            Node* w = x->parent->right; // w — брат узла x (правый ребенок родителя)
            if (w->color == RED) { // Случай 1: Брат w красный
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) { // Случай 2: Оба ребенка брата черные
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) { // Случай 3: Правый ребенок брата черный, а левый красный
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                // Случай 4: Правый ребенок брата w красный
                
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else { // Симметричный случай: x — правый ребенок своего родителя
            Node* w = x->parent->left; // w — брат узла x (левый ребенок родителя)
            if (w->color == RED) { // Случай 1: Брат w красный
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);                
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) { // Случай 2: Оба ребенка брата черные
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) { // Случай 3: Левый ребенок брата черный, а правый красный
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                // Случай 4: Левый ребенок брата w красный
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    // После выхода из цикла, перекрашиваем x в черный
    x->color = BLACK;
}


// Обход in-order (симметричный обход)
void RedBlackTree::inorderHelper(Node* node) {
    if (node != NIL) {
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }
}

void RedBlackTree::inorder() {
    inorderHelper(root);
    cout << endl;
}

// Обход pre-order (прямой обход)
void RedBlackTree::preorderHelper(Node* node) {
    if (node != NIL) {
        cout << node->data << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }
}

void RedBlackTree::preorder() {
    preorderHelper(root);
    cout << endl;
}

// Обход post-order (обратный обход)
void RedBlackTree::postorderHelper(Node* node) {
    if (node != NIL) {
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->data << " ";
    }
}

void RedBlackTree::postorder() {
    postorderHelper(root);
    cout << endl;
}

// Обход level-order (обход в ширину)
void RedBlackTree::levelOrderHelper(Node* node) {
    if (node == NIL)
        return;
    queue<Node*> q;
    q.push(node);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        cout << current->data << " ";
        if (current->left != NIL)
            q.push(current->left);
        if (current->right != NIL)
            q.push(current->right);
    }
}

void RedBlackTree::levelOrder() {
    levelOrderHelper(root);
    cout << endl;
}

// Проверка свойства красных узлов
bool RedBlackTree::validateRedProperty(Node* node) {
    if (node == NIL) return true;
    if (node->color == RED) {
        if (node->left->color == RED || node->right->color == RED) {
            cout << "Нарушение свойства красных узлов в узле " << node->data << ".\n";
            return false;
        }
    }
    return validateRedProperty(node->left) && validateRedProperty(node->right);
}

// Проверка одинаковой черной высоты
bool RedBlackTree::validateBlackHeight(Node* node, int& blackHeight) {
    if (node == NIL) {
        blackHeight = 1;
        return true;
    }
    int leftBlackHeight = 0, rightBlackHeight = 0;
    if (!validateBlackHeight(node->left, leftBlackHeight))
        return false;
    if (!validateBlackHeight(node->right, rightBlackHeight))
        return false;
    if (leftBlackHeight != rightBlackHeight) {
        cout << "Нарушение черной высоты в узле " << node->data << ".\n";
        return false;
    }

    if (node->color == BLACK)
        blackHeight = leftBlackHeight + 1;
    else
        blackHeight = leftBlackHeight;

    return true;
}

// Проверка свойств дерева
bool RedBlackTree::validate() {
    return validateProperties();
}

bool RedBlackTree::validateProperties() {
    if (root == NIL) {
        return true;
    }
    if (root->color != BLACK) {
        cout << "Корень не черный.\n";
        return false;
    }
    int blackHeight = 0;
    return validateRedProperty(root) && validateBlackHeight(root, blackHeight);
}

// Вычисление высоты дерева
int RedBlackTree::treeHeight(Node* node) {
    if (node == NIL) return 0;
    int leftheight = treeHeight(node->left);
    int rightheight = treeHeight(node->right);
    return (leftheight > rightheight ? leftheight : rightheight) + 1;
}

int RedBlackTree::getHeight() {
    return treeHeight(root);
}

// Подсчет количества узлов
int RedBlackTree::countNodes(Node* node) {
    if (node == NIL) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int RedBlackTree::getNodeCount() {
    return countNodes(root);
}

// Визуальное отображение дерева
void RedBlackTree::showutil(Node* node, int space, int count) {
    if (node == NIL) return;
    space += count;
    showutil(node->right, space);
    cout << "\n";
    for (int i = count; i < space; i++) {
        cout << " ";
    }
    cout << node->data << " (" << (node->color == RED ? "Red" : "Black") << ")\n";
    showutil(node->left, space);
}

void RedBlackTree::ShowTree() {
    cout << "Вывод состояния дерева" << endl;
    showutil(root, 0);
    cout << endl << endl << endl;
}

// Нахождение преемника узла
Node* RedBlackTree::findSuccessor(Node* node) {
    if (node->right != NIL)
        return treeMinimum(node->right);
    Node* y = node->parent;
    while (y != NIL && node == y->right) {
        node = y;
        y = y->parent;
    }
    return y;
}

Node* RedBlackTree::findSuccessor(int data) {
    Node* node = search(data);
    if (node == nullptr) {
        cout << "Узел " << data << " не найден в дереве.\n";
        return nullptr;
    }
    Node* succ = findSuccessor(node);
    if (succ != NIL)
        return succ;
    else
        return nullptr;
}

// Нахождение предшественника узла
Node* RedBlackTree::findPredecessor(Node* node) {
    if (node->left != NIL)
        return treeMaximum(node->left);
    Node* y = node->parent;
    while (y != NIL && node == y->left) {
        node = y;
        y = y->parent;
    }
    return y;
}

Node* RedBlackTree::findPredecessor(int data) {
    Node* node = search(data);
    if (node == nullptr) {
        cout << "Узел " << data << " не найден в дереве.\n";
        return nullptr;
    }
    Node* pred = findPredecessor(node);
    if (pred != NIL)
        return pred;
    else
        return nullptr;
}
