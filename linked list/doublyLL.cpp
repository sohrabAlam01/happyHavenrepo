#include<iostream>
using namespace std;

class Node{

   public:
   int data;
   Node * next;
   Node * prev;

   //constructor
   Node(int data){
    this->data = data;
    this->next = NULL;
    this->prev = NULL;
   }

};

//print function

void print(Node *head){
    Node *ptr = head;
    while(ptr!=NULL){
        cout<<ptr->data<<" ";
        ptr = ptr->next;
    }
}

//inserting at head

void insertAtHead(Node * &head,Node *&tail, int data){
    Node*temp = new Node(data);
    if(head == NULL){
        head = temp;
        tail = temp;
        return;
    }

    temp->next = head;
    head->prev = temp;
    head = temp;
}

//inserting at tail

void insertAtTail(Node*&tail, int data){
    Node *temp = new Node(data);
    temp->data = data;
    if(tail == NULL){
       tail = temp;
       return;
    }

    tail->next = temp;
    temp->prev = tail;
    tail = temp;
}




int main(){

Node *head = NULL;
Node *tail = NULL;

insertAtHead(head, tail, 10);
insertAtHead(head, tail, 20);
insertAtHead(head, tail, 30);
insertAtHead(head, tail, 40);
insertAtTail(tail, 11);
print(head);






    return 0;
}