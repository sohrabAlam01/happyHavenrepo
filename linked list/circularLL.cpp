#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node*next;

    //constructor
    Node(int data){
        this->data = data;
        this->next = NULL;
    }
    //destructor
    ~Node(){
        cout<<"deleted data is "<<this->data<<endl;
        this->next = NULL;
    }
};


//insert node next to a node that has data = prevData
void insertNode(Node *&ptr, int data, int prevData = 0){
    Node* newNode = new Node(data);
    Node* curr = ptr;
     //when LL is empty
     if(ptr==NULL){
       ptr = newNode;
       newNode->next = newNode;
     }
     //when list is not empty
     else{
        while(curr->data != prevData){
            curr = curr->next;
        }
        //at this moment ptr pointng to the node where next to ptr we have to insert the node
        newNode->next = curr->next;
        curr->next = newNode;
     }
}


//print function
void print(Node *ptr){
    if(ptr == NULL) return;
    Node* start = ptr;

    do{
     cout<<ptr->data<<" ";
     ptr = ptr->next;
    }while(ptr != start);
}


//deletes a Node on the basis of the containing data

void deleteNode(Node *&ptr, int data){
    Node* prev = ptr;
    Node*curr = ptr->next;
    while(curr->data != data){
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;

    //if there is only one node in the linked list
    if(curr == prev){
        ptr = NULL;
    }
    //if the node to be deleted is pointed by ptr itself
    if(ptr == curr){
        ptr = prev;  //ptr can be pointed to any node expect the node to be deleted
    }

    delete curr;
}

int main(){

 Node* ptr = NULL;  //ptr will be pointing to any node in the circular linked list because there is no head or tail pointer in the circular linked list
 //inserting first node
 insertNode(ptr, 10);
 insertNode(ptr, 20, 10);
 insertNode(ptr, 30, 20);
 deleteNode(ptr, 30);
 print(ptr);

    return 0;
}