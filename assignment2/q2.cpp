#include <iostream>
using namespace std;

struct Node{
    int value;
    Node *parent;
    Node *left, *right;
};

bool FindNode(Node *root, Node *to_find) {

    if(root == NULL)
        return false;

    if(root == to_find)
        return true;

    if(FindNode(root->left, to_find) || FindNode(root->right, to_find))
        return true;

    return false;
}

//O(N^2) without any additional memory or changing structure
//could be O(N) if i.e. it stores paths to nodes and then compares them
Node *FindCommonAncestor(Node *root, Node *first, Node *second) {

    if(root == NULL)
        return NULL;

    //nodes are not in the tree
    if(!FindNode(root, first) || !FindNode(root, second))
        return NULL;

    //if both are in the left tree
    if(FindNode(root->left, first) && FindNode(root->left, second))
        return FindCommonAncestor(root->left, first, second);

    //if both are in the right tree
    if(FindNode(root->right, first) && FindNode(root->right, second))
        return FindCommonAncestor(root->right, first, second);

    //if nodes are one in left, other in right tree
    else
        return root;

}


int main() {

    //creating the tree for debug and testing
    Node *root = new Node;
    root->parent = NULL;
    root->value = 16;
    root->left = new Node;
    root->left->parent = root;
    root->left->value = 9;
    root->right = new Node;
    root->right->parent = root;
    root->right->value = 18;
    root->left->left = new Node;
    root->left->left->parent = root->left;
    root->left->left->value = 3;
    root->left->left->left = new Node;
    root->left->left->left->value = 1;
    root->left->left->left->parent = root->left->left;
    root->left->left->right = new Node;
    root->left->left->right->value = 5;
    root->left->left->right->parent = root->left->left;
    root->left->right = new Node;
    root->left->right->parent = root->left;
    root->left->right->value = 14;
    root->left->right->left = NULL;
    root->left->right->right = NULL;
    root->right->left = NULL;
    root->right->right = new Node;
    root->right->right->value = 19;
    root->right->right->parent = root->right;
    root->right->right->left = NULL;
    root->right->right->right = NULL;


    cout<<"FindNode test:"<<endl;
    Node *x = new Node;
    cout<< FindNode(root, x)<<endl; //not found

    cout<<FindNode(root, root) <<endl; //found
    cout<<FindNode(root, root->left) <<endl; //found
    cout<<FindNode(root, root->right) <<endl; //found

    cout<<FindNode(root->right, root->right->right)<<endl; //found
    cout<<FindNode(root->right, root->right->left) <<endl; //not found

    cout<<"FindCommonAncestor test:" <<endl;
    //14, 5 -> found 9
    Node *a = FindCommonAncestor(root, root->left->right, root->left->left->right);
    if(a != NULL)
        cout << "Found " <<a->value<<endl;
    else cout<<"Not found" <<endl;

    //9, 5 -> found 9
    a = FindCommonAncestor(root, root->left, root->left->left->right);
    if(a != NULL)
        cout << "Found " <<a->value<<endl;
    else cout<<"Not found" <<endl;

    //18, 5 -> found 16
    a = FindCommonAncestor(root, root->right, root->left->left->right);
    if(a != NULL)
        cout << "Found " <<a->value<<endl;
    else cout<<"Not found" <<endl;

    //1, 5 -> found 3
    a = FindCommonAncestor(root, root->left->left->left, root->left->left->right);
    if(a != NULL)
        cout << "Found " <<a->value<<endl;
    else cout<<"Not found" <<endl;

    //root: 18, 19,19 -> found 18
    a = FindCommonAncestor(root->right, root->right->right, root->right->right;
    if(a != NULL)
        cout << "Found " <<a->value<<endl;
    else cout<<"Not found" <<endl;

    //not found
    Node *y = new Node;
    a = FindCommonAncestor(root, root->right, y);
    if(a != NULL)
        cout << "Found " <<a->value<<endl;
    else cout<<"Not found" <<endl;

    //not found
    y = new Node;
    a = FindCommonAncestor(root, y, y);
    if(a != NULL)
        cout << "Found " <<a->value<<endl;
    else cout<<"Not found" <<endl;

    //not found
    a = FindCommonAncestor(y, root->left, root->right);
    if(a != NULL)
        cout << "Found " <<a->value<<endl;
    else cout<<"Not found" <<endl;


    return 0;
}
