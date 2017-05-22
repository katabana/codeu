struct node{
    int val;
    node* next;
};

node *kth_element(int k, node *head) {

    //number of element on which starts 'k-th to end' fragment
    int n = length(head) - k;

    int i = 1;  //linked list element no
    node *ptr = head;
    while(i < n && ptr != NULL) {
        i++;
        ptr = ptr->next;
    }
    return ptr;
}

int length(node *head) {

    int len = 0;
    node *ptr = head;
    while(ptr != NULL) {
        len++;
        ptr = ptr->next;
    }
    return len;
}
