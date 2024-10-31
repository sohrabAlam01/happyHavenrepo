#include<iostream>
#include<stack>
using namespace std;

int main(){

stack<int>s;

//push
s.push(1);
s.push(2);
s.push(3);
s.push(4);
//pop
s.pop();

//printint the stack
while(!s.empty()){
                           //3
 cout<<s.top()<<"\n";      //2
 s.pop();                  //1

}

//getting size of the stack
cout<<"size of the stack is: "<<s.size()<<endl;

}