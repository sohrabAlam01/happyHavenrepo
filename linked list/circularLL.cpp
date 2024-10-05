#include<iostream>
#include<map>
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

    cout<<endl;
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

//function to check if the linked list is circular or not

bool isCircularLL(Node *head){
    //when list is empty
    if(head == NULL) return true;
    //when there is only one node pointing to itself
    if(head->next == head) return true;
    //when there is greater than one node in the linked list
    Node *ptr = head;
    while(ptr != NULL && ptr->next != head){
        ptr = ptr->next;
    }
    if(ptr == NULL) return false;
    else {
        return true;
    }

}


//approach 2: using hashmap to detect loop in the linked list

bool isItCircular(Node *ptr){

   map<Node*, bool>visited;

   while(ptr != NULL){
      if(visited[ptr] == true) return true; //loop exists
      visited[ptr] = true;
      ptr = ptr->next;
   }
   //will come out from loop and reach here only when there is null value
   return false;

}


///////////floyed warshall algorithm/////////////
/*
1.detect a loop in the LL
2. find the statring node of the loop;
3. remove the loop in the linked list
*/

//1. function to find if there exists a loop in the list and return the node at which slow and fast pointer meets


Node * floydDetectLoop(Node *head){
    if(head == NULL) return head;

    Node* slow = head;
    Node* fast = head;

    while(fast != NULL && fast->next != NULL)
    {
         fast = fast->next->next;
         slow = slow->next;
         if(slow == fast){
            return slow;
         }
    }
    return NULL;
}


//2. finding the starting node of the loop

Node * startingLoop(Node *head){
    if(head == NULL) return;
    Node *interSection = floydDetectLoop(head);

    if(interSection == NULL) return NULL; //if there is no loop then how we will find the starting node of the loop

    Node* slow = head;
    while(interSection != slow){
          slow = slow->next;
          interSection = interSection->next;
    }

    return interSection;
}


//3.removing the loop
void removeLoop(Node *head){
    Node* ptr = floydDetectLoop(head);
    if(ptr == NULL) return;  //if ptr =  null it means there is no loop in the linked list
    while(ptr->next != NULL) ptr = ptr->next;
    ptr->next = NULL;
}


int main(){

 Node* ptr = NULL;  //ptr will be pointing to any node in the circular linked list because there is no head or tail pointer in the circular linked list
 //inserting first node
 insertNode(ptr, 10);
 insertNode(ptr, 20, 10);
 insertNode(ptr, 30, 20);
 deleteNode(ptr, 30);
 print(ptr);

if(isItCircular(ptr)) cout<<"LL is a circular linked list";
else{
    cout<<"it is not a circular linked list";
}

cout<<(NULL == NULL);
    return 0;
}