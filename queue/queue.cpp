#include<iostream>
#include<queue>
using namespace std;

//////////////////////////////////////content: queue and doubly ended queue///////////////////////////////////////////

int main(){
/*
queue<int>q;

q.push(1);
q.push(2);
q.push(3);
q.push(4);
q.push(5);

cout<<q.back()<<endl;  //last element in the queue
q.size();              //number of elements available in the queue

while(!q.empty()){
    cout<<q.front();   //first elelment in the queue
    q.pop();
}

*/

///////////////////////doubly ended queue////////////////////////////////

deque<int>d;
d.push_back(2);
d.push_front(3);

cout<<d.front()<<endl;
cout<<d.back()<<endl;

d.pop_back();
d.pop_front();

if(d.empty()) cout<<"queue is empty";
else cout<<"queue is not empty";

}