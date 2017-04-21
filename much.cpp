#include <iostream>
#include <string.h>
#include "split.h"
using namespace std;
int main(int argc, char const *argv[])
{
    ll a;
    node *t;
    char wordtest[100]={'s','a','a',',','k','u','y',',','s','c','c',',','s','c',',','s','h'},data[100];
    /*for(i=1;i<4;i++) {
                       t=new node(wordtest);
                       a.addnode(t);
                       }*/

	//recive test;
    split(wordtest);
    //cout<<"type="<<test.type<<endl<<"username="<<test.username<<endl<<"password="<<test.password<<endl<<"data="<<test.data<<endl;
    /*int stringLength = strlen(wordtest);
    for(int i = 0; i <= (stringLength - 1); i++) {
		data[i] = wordtest[i];
    }
    data[stringLength]='\0';
    for(int i = 0; i <= (stringLength - 1); i++)
    {
        cout<<data[i];
    }*/
	return 0;
}
