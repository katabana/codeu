struct node{
    int val;
    node* next;
};

node *kth_element(int k, node *head) {

    //number of element on which starts 'k-th to end' fragment
    int n = length(head) - k;
    //not sure what to do when n <= 0
    //return what function found or do sth that shows there was an 'error'?

    int i = 1;  //linked list element no
    node *ptr = new node;
    ptr = head;
    while(i < n && ptr != NULL) {
        i++;
        ptr->next;
    }
    return ptr;
}

int length(node *head) {

    int len = 0;
    node *ptr = new node;
    ptr = head;
    while(ptr != NULL) {
        len++;
        ptr = ptr->next;
    }
    return len;
}
