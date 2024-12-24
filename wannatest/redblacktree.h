#pragma once
#include <iostream>
#include <queue>
#include<string>
#include<sstream>
using namespace std;
// ������������ ������ �����
enum Color { RED, BLACK };
struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
    // ����������� ��� ������� �����
    Node(int data, Node* nil);
    // ����������� ��� �����-�������(null)
    Node();
};

class RedBlackTree {
private:
    Node* root;
    Node* NIL; // ����-����(null)
    // ��������������� �������
    void destroyTree(Node* root);
    void leftRotate(Node* x);
    void rightRotate(Node* y);
    void BigleftRotate(Node* x);
    void BigrightRotate(Node* x);
    void insertFixup(Node* z);
    Node* searchHelper(Node* node, int key);
    void zamena(Node* u, Node* v);
    Node* treeMaximum(Node* node);
    Node* treeMinimum(Node* node);
    void deleteNodehelper(Node* node);
    void deleteFixup(Node* x);
    // ������ ������
    void inorderHelper(Node* node);
    void preorderHelper(Node* node);
    void postorderHelper(Node* node);
    void levelOrderHelper(Node* node);
    // �������� ������� ������
    bool validateRedProperty(Node* node);
    bool validateBlackHeight(Node* node, int& blackHeight);
    bool validateProperties();
    int treeHeight(Node* node);
    int countNodes(Node* node);
    Node* findSuccessor(Node* node);
    Node* findPredecessor(Node* node);
    void showutil(Node* node, int space, int count = 10);
public:
    // ������������ � ����������
    RedBlackTree();
    ~RedBlackTree();
    // �������� ��������
    void insert(int data);
    Node* search(int key);
    void remove(int key);
    void inorder();
    void preorder();
    void postorder();
    void levelOrder();
    bool validate();
    int getHeight();
    int getNodeCount();
    Node* findPredecessor(int data);
    Node* findSuccessor(int data);
    void ShowTree();
};
