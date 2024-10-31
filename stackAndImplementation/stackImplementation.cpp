#include <iostream>
using namespace std;
// implementing stack using an array
class Stack
{

public:
    int *arr;
    int size;
    int top;

    Stack(int size)
    {

        this->size = size;
        arr = new int[size];
        top = -1;
    }

    // push method

    void push(int data)
    {

        if (top < size)
        {
            top = top + 1;
            arr[top] = data;
        }
        else
        {
            cout << "stack overflow" << endl;
        }
    }

    // pop method

    void pop()
    {

        if (top >= 0)
        {
            top--;
        }
        else
        {
            cout << "Stack underflow" << endl;
        }
    }

    // returning peel element of the stack

    int peek()
    {

        if (top >= 0)
            return arr[top];
        else
            cout << "stack underflow" << endl;
    }
 
 //checking it stack is empty or not
    bool isEmpty()
    {
        if (top >= 0)
            return 0;
        else
            return 1;
    }

//printing stack

void print(){

    int temp = this->top;
    while(temp >= 0){

        cout<<this->arr[temp--];

    }
}
};




int main()
{
  
 int size = 5;
 Stack s(size);

 s.push(1);
 s.push(2);
 s.push(3);
 s.push(4);
 s.push(5);
 s.pop();

 cout<<"top element is: "<<s.peek()<<endl;
 
 s.print();

 return 0;
}