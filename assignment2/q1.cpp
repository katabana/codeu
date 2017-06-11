#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int value;
    Node *parent;
    Node *left, *right;
};

Node *FindKey(Node *root, int key) {

    if(root->value == key)
        return root;

    Node *l = NULL;
    Node *r = NULL;

    if(root->left != NULL) {
        l = FindKey(root->left, key);
        if(l != NULL)
            return l;
    }
    if(root->right != NULL) {
        r = FindKey(root->right, key);
        if(r != NULL)
            return r;
    }

    return NULL;
}

void PrintAncestors(Node *root, int key) {

    if(root == NULL) {
        cout << "The tree is empty." << endl;
        return;
    }
    Node* descendant = FindKey(root, key);

    if(descendant != NULL) {
        cout << "Descendant key is "<< descendant->value <<endl;
        if(descendant->parent == NULL)
            cout<< "NULL";
        while(descendant->parent != NULL) {
            cout << descendant->parent->value << " ";
            descendant = descendant->parent;
        }
    }
    else
        cout<< "The key "<<key<<" is not present in the tree." <<endl;

}


int main () {

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

    print_ancestors(root, 5);   //lowest value in the tree
    cout<<endl;
    print_ancestors(root, 1); //lowest value in the tree
    cout<<endl;
    print_ancestors(root, 14); //leaf (but not lowest)
    cout<<endl;
    print_ancestors(root, 3); //in the middle
    cout<<endl;
    print_ancestors(root, 19);  //lowest leaf on the right
    cout<<endl;
    print_ancestors(root, 16);  //root
    cout<<endl;
    print_ancestors(root, -1);  //nonexisting value

    return 0;
}
