#include <iostream>
using namespace std;

class node
{
public:
    int data;
    node *next;

    // constructor
    node(int data)
    {
        this->data = data;
        this->next = NULL;
    }

    //destructor to delete an object
    ~node()
    {
     
        cout<<"destructor is called"<<endl;
       
    }
};


// insert at the beginning
void insertAtBeg(node *&head, int data)
{
    node *temp = new node(data);
    temp->next = head;
    head = temp;
}

// insert at the end
void insertAtEnd(node *&tail, int data)
{

    node *temp = new node(data);
    tail->next = temp;
    tail = temp;
}

void print(node *&head)
{
    node *temp = head;
    if (head == NULL)
        return;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
}

// insert at end using only head pointer

void insertAtEnding(node *&head, int data)
{
    node *temp = new node(data);
    if (head == NULL)
    {
        head = temp;
    }

    node *ptr = head;
    while (ptr->next != NULL)  ptr = ptr->next;
    ptr->next = temp;
   
}

//insert at mid
void insertAtMid(node * &head, int data, int pos)
{
    node *ptr = head;
    node*temp = new node(data);
    if(pos == 1){
        temp->next = head;
        head = temp;
        return;
    }
    int i=1;
    while(i<pos-1)
    {
       ptr = ptr->next;
       i++;
    } 
    temp->next = ptr->next;
    ptr->next = temp;
}

//delete node at position pos
void deleteNode(node * &head, int pos)
{
    node *ptr = head;
    if(head == NULL)
    {
       return;
    }

    //when there is only one node in the list
    if(pos == 1) 
    {
        head = head->next;
        ptr->next = NULL;
        delete ptr;
    }
    else{
        int i=1;
        node *curr = head;
        while(i<pos-1 && curr->next != NULL)
        {       
            curr = curr->next;
            i++;
        }
       ptr = curr->next;
       curr->next = curr->next->next;
       ptr->next = NULL;
        delete ptr;
    }
}

int main()
{

    node *head = new node(10);
    node *tail = head;
    node *node1 = new node(20);
    head->next = node1;
    tail = node1;
    insertAtBeg(head, 30);
    insertAtEnd(tail, 50);
    insertAtEnding(head, 60);
    insertAtMid(head, 70, 3);
    deleteNode(head, 6);

    print(head);

    return 0;
}