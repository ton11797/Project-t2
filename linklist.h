#include<iostream>
#include<string.h>
using namespace std;
class node{
private:
    char data[100];
    node *next;
public:
    node(char []);
    void insert(node*&);
    node* movenext();
    int shownode();


};
node::node(char x[])
{
    int stringLength = strlen(x);
    for(int i = 0; i <= (stringLength - 1); i++) {
		data[i] = x[i];
    }
    data[stringLength] = '\0';
    next=NULL;
}
void node::insert(node*& x){
     x->next=this;

     }
node* node::movenext(){
      return next;
}
int node::shownode(){
    return atoi(data);
    //cout<<data<<endl;
}
class ll
{
    private:node*head;
            int size;
    public:void addnode(node *&);
            void showall(int *);
            int getsize();
            ll();
            ~ll();
};
ll::ll(){
    head=NULL;
        size=0;

}
ll::~ll(){
          node *t=head;
          node *s=t;
    int i;
    for(i=0;i<size;i++)
    {
        delete t;
        s=s->movenext();
        t=s;
    }

}
void ll::addnode(node *&A){

          head->insert(A);
          head=A;

       size++;

 }
void ll::showall(int *a){
     node* t=head;
     int i;
     for(i=0;i<size;i++){
                a[i]= t->shownode();
                t=t->movenext();
     }
}
int ll::getsize(){
    return size;
}
