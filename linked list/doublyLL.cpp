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

   //destructor
   ~Node(){
    cout<<"Deleted data is: "<<this->data<<endl;
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

void insertAtHead(Node * &head, Node *&tail, int data){
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

//insert at any position

void insertAtPos(Node*&head, Node* &tail, int pos, int data){
    //inserting at first position
    if(pos==1) insertAtHead(head, tail, data);
    //inserting at last position
    else if(head->next == NULL) insertAtTail(tail, data);

    //inserting at middle position
    else{
        Node*ptr = head;
        Node *newNode = new Node(data);
        int i =1;
        while(i<pos-1){
           ptr=ptr->next;
           i++;
        }
        newNode->next = ptr->next;
        newNode->prev = ptr;
        ptr->next = newNode;
    }
}

//delete any node
void deleteNode(Node* &head,Node*& tail, int pos){
      //when there is only one node in the linked list
         if(pos==1 && head->next == NULL){
             delete head;
             head = NULL;
             tail = NULL;
         }
         //deleting the first position when there is more than one node in the linked list
       else if(pos == 1){
        Node *ptr = head;
        head->next->prev = NULL;
        head = head->next;
        delete ptr;
       }
       //deleting the last node
       
       else{
        Node*curr =  head;
        int i=1;
        while(i<pos-1){
            curr = curr->next;
            i++;
        }
        if(curr->next->next == NULL){
          tail = curr;
          Node *ptr = curr->next;
          curr->next = curr->next->next;
          delete ptr;
        }
        else{
            Node *ptr = curr->next;
            curr->next->next->prev = curr;
            curr->next = curr->next->next;
            delete ptr;
        }
        
       }
}

int main(){

Node *head = NULL;
Node *tail = NULL;

insertAtHead(head, tail, 40);
insertAtHead(head, tail, 30);
insertAtHead(head, tail, 20);
insertAtHead(head, tail, 10);
insertAtTail(tail, 11);
insertAtPos(head, tail, 1, 50);
insertAtPos(head, tail, 2, 60);
insertAtPos(head, tail, 4, 70);
insertAtPos(head, tail, 9, 90);
deleteNode(head, tail, 1);
deleteNode(head, tail, 3);
deleteNode(head, tail, 7);
insertAtTail(tail, 66);
print(head);



    return 0;
}