#include<iostream>
#include"linklist.h"
using namespace std;

split(char word[])
{
    int positioncomma[100],valueofcomma=0,positionsplit=0;
    ll A;
    node *t;

    for(int i=0;i<100;i++)
    {

        if(word[i]==',')
        {
            positioncomma[valueofcomma]=i;
            cout<<positioncomma[valueofcomma]<<endl;
            valueofcomma++;
        }
    }
    for(int i=0;i<valueofcomma+1;i++)
    {
        char copychar[100];
        for(int j=0;j<100;j++)
        {
            if(word[positionsplit]!=','&&word[positionsplit]!='\0')
            {
             copychar[j]=word[positionsplit];
             positionsplit++;
            }
            else
            {
                copychar[j]='\0';
                positionsplit+=1;
                break;

            }
        }

        t=new node(copychar);
        A.addnode(t);

    }
    A.showall();



}
