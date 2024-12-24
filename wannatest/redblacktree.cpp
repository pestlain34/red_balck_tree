#include "redblacktree.h"

// ����������� ��� ������� �����
Node::Node(int data, Node* nil)
    : data(data), color(RED), left(nil), right(nil), parent(nil) {}

// ����������� ��� �����-�������(null) ������ ������
Node::Node()
    : data(0), color(BLACK), left(this), right(this), parent(this) {}

// ����������� ������
RedBlackTree::RedBlackTree() {
    NIL = new Node(); // �������������� ����-����(null)
    root = NIL;        // ������ ���������� ��������� �� NIL
}

// ���������� ������
RedBlackTree::~RedBlackTree() {
    destroyTree(root);
    delete NIL; 
    root = nullptr;
}

// ����������� ����� ��� �������� ���� ����� ������ (����������� �����)
void RedBlackTree::destroyTree(Node* node) {
    if (node == NIL) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// ����� ������� ������ ���� x
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

// ������ ������� ������ ���� y
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

// ������� ����� �������
void RedBlackTree::BigleftRotate(Node* x) {
    rightRotate(x->right);
    leftRotate(x);
}

// ������� ������ �������
void RedBlackTree::BigrightRotate(Node* x) {
    leftRotate(x->left);
    rightRotate(x);
}

// ������� ������ �������� � ������
void RedBlackTree::insert(int data) {
    Node* z = new Node(data, NIL);
    Node* y = NIL;    // �������������� ���� y ��� NIL, �� ����� ��������� ��� ������ ���� z
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
        root = z; // ���� ������ ���� ������, ����� ���� ���������� ������
    }
    else if (z->data < y->data) {
        y->left = z; // ���� ������ ������ ���� ������ ������ ��������, �������� ��� � ����� ���������
    }
    else {
        y->right = z; // ����� �������� � ������ ���������
    }
    // �������������� ����� � ������ ��������� ������ ���� �� ���� `NIL` � ������������� ���� ���� ��� �������
    z->left = NIL;
    z->right = NIL;
    z->color = RED;
    // ��������������� �������� ������-������� ������ ����� �������
    insertFixup(z);
}

// �������������� ������� ������-������� ������ ����� �������
void RedBlackTree::insertFixup(Node* z) {
    
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) { 
            Node* y = z->parent->parent->right; 

            if (y->color == RED) { // ������ 1: ���� ���� z �������
                // ������������� �������� � ���� � ������, � ������� � � �������
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent; 
            }
            else { // ���� ���� z ������
                if (z == z->parent->right) { // ������ 2: ���� z � ������ ������� ������ ��������
                    z = z->parent;          
                    leftRotate(z);          
                }
                // ������ 3: ���� z � ����� ������� ������ ��������
                z->parent->color = BLACK;           
                z->parent->parent->color = RED;     // ������������� ������� � �������
                rightRotate(z->parent->parent);      // ��������� ������ ������� ������ �������
            }
        }
        else { // ������������ ������: �������� z � ������ ������� ������ ��������
            Node* y = z->parent->parent->left; 
            if (y->color == RED) { // ������ 1: ���� ���� z �������
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent; // ��������� � ������� � ���������� ����
            }
            else { // ���� ���� z ������
                if (z == z->parent->left) { // ������ 2: ���� z � ����� ������� ������ ��������
                    z = z->parent;          
                    rightRotate(z);         
                }
                // ������ 3: ���� z � ������ ������� ������ ��������
                z->parent->color = BLACK;           
                z->parent->parent->color = RED;     // ������������� ������� � �������
                leftRotate(z->parent->parent);       // ��������� ����� ������� ������ �������
            }
        }
    }
    root->color = BLACK; // ������������� ���� ����� ������ � ������
}


// ����� ���� � �������� ������
Node* RedBlackTree::search(int key) {
    Node* node = searchHelper(root, key);
    if (node == NIL) {
        cout << "������ �������� � ������ ���" << endl;
        return nullptr;
    }
    return node;
}

// ��������������� ������� ������
Node* RedBlackTree::searchHelper(Node* node, int key) {
    while (node != NIL && key != node->data) {
        if (key < node->data)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

// ���������� ������������ ���� � ���������
Node* RedBlackTree::treeMinimum(Node* node) {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

// ���������� ������������� ���� � ���������
Node* RedBlackTree::treeMaximum(Node* node) {
    while (node->right != NIL) {
        node = node->right;
    }
    return node;
}

// ������ ��������� u �� ��������� v
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

// �������� ���� � �������� ������
void RedBlackTree::remove(int key) {
    Node* z = search(key);
    if (z == nullptr) return;
    deleteNodehelper(z);
}

// ��������������� ������� �������� ����
void RedBlackTree::deleteNodehelper(Node* z) {
    Node* y = z;                       // ���� y ���������� ����� ���� z, ������� ����� �������
    Node* x;                           // ���� x ����� �������������� ��� �������� ������ ����� ��������
    Color y_original_color = y->color; // ��������� ������������ ���� ���� y ��� ���������� ��������

    if (z->left == NIL) {              // ���� � ���� z ��� ������ �������
        x = z->right;                   
        zamena(z, z->right);        
    }
    else if (z->right == NIL) {        // ���� � ���� z ��� ������� �������
        x = z->left;                    
        zamena(z, z->left);         
    }
    else {                              // ���� � ���� z ���� ��� �������
        y = treeMinimum(z->right);      
        y_original_color = y->color;    
        x = y->right;                    

        if (y->parent == z) {            // ���� �������� y �������� ���������������� ������ �������� z
            x->parent = y;               
        }
        else {                           // ���� �������� y �� �������� ���������������� ������ �������� z
            zamena(y, y->right);     
            y->right = z->right;         
            y->right->parent = y;        
        }

        zamena(z, y);                // �������� ��������� z �� y
        y->left = z->left;               
        y->left->parent = y;             
        y->color = z->color;             
    }

    delete z;                            // ����������� ������, ���������� ����� z
    if (y_original_color == BLACK) {     // ���� ������������ ���� ���������� ���� ��� ������
        deleteFixup(x);                  // ��������������� �������� ������-������� ������
    }
}


// �������������� ������� ������-������� ������ ����� ��������
void RedBlackTree::deleteFixup(Node* x) {
    
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) { 
            Node* w = x->parent->right; // w � ���� ���� x (������ ������� ��������)
            if (w->color == RED) { // ������ 1: ���� w �������
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) { // ������ 2: ��� ������� ����� ������
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) { // ������ 3: ������ ������� ����� ������, � ����� �������
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                // ������ 4: ������ ������� ����� w �������
                
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        }
        else { // ������������ ������: x � ������ ������� ������ ��������
            Node* w = x->parent->left; // w � ���� ���� x (����� ������� ��������)
            if (w->color == RED) { // ������ 1: ���� w �������
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);                
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) { // ������ 2: ��� ������� ����� ������
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) { // ������ 3: ����� ������� ����� ������, � ������ �������
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                // ������ 4: ����� ������� ����� w �������
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    // ����� ������ �� �����, ������������� x � ������
    x->color = BLACK;
}


// ����� in-order (������������ �����)
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

// ����� pre-order (������ �����)
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

// ����� post-order (�������� �����)
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

// ����� level-order (����� � ������)
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

// �������� �������� ������� �����
bool RedBlackTree::validateRedProperty(Node* node) {
    if (node == NIL) return true;
    if (node->color == RED) {
        if (node->left->color == RED || node->right->color == RED) {
            cout << "��������� �������� ������� ����� � ���� " << node->data << ".\n";
            return false;
        }
    }
    return validateRedProperty(node->left) && validateRedProperty(node->right);
}

// �������� ���������� ������ ������
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
        cout << "��������� ������ ������ � ���� " << node->data << ".\n";
        return false;
    }

    if (node->color == BLACK)
        blackHeight = leftBlackHeight + 1;
    else
        blackHeight = leftBlackHeight;

    return true;
}

// �������� ������� ������
bool RedBlackTree::validate() {
    return validateProperties();
}

bool RedBlackTree::validateProperties() {
    if (root == NIL) {
        return true;
    }
    if (root->color != BLACK) {
        cout << "������ �� ������.\n";
        return false;
    }
    int blackHeight = 0;
    return validateRedProperty(root) && validateBlackHeight(root, blackHeight);
}

// ���������� ������ ������
int RedBlackTree::treeHeight(Node* node) {
    if (node == NIL) return 0;
    int leftheight = treeHeight(node->left);
    int rightheight = treeHeight(node->right);
    return (leftheight > rightheight ? leftheight : rightheight) + 1;
}

int RedBlackTree::getHeight() {
    return treeHeight(root);
}

// ������� ���������� �����
int RedBlackTree::countNodes(Node* node) {
    if (node == NIL) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int RedBlackTree::getNodeCount() {
    return countNodes(root);
}

// ���������� ����������� ������
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
    cout << "����� ��������� ������" << endl;
    showutil(root, 0);
    cout << endl << endl << endl;
}

// ���������� ��������� ����
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
        cout << "���� " << data << " �� ������ � ������.\n";
        return nullptr;
    }
    Node* succ = findSuccessor(node);
    if (succ != NIL)
        return succ;
    else
        return nullptr;
}

// ���������� ��������������� ����
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
        cout << "���� " << data << " �� ������ � ������.\n";
        return nullptr;
    }
    Node* pred = findPredecessor(node);
    if (pred != NIL)
        return pred;
    else
        return nullptr;
}
