#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include "animetion.h"
#include "object.h"
#include "Player.h"
#include "collider.h"
#include "select.h"
#include "Menu.h"
#include "inventory.h"
#include "gamestart.h"
#include "split.h"
using namespace std;
int main()
{
    char username[200];
    char password[200];
    char data[200];
    int dataint[200],num;
    gamestart gm;
    strcpy(data,"-1/-1/-1/-1/-1/-1/-1/-1/0/0/-1/-1/-1/-1/1/0/-1/-1/-1/-1/2/2/-1/-1/-1/-1/3/3/-1/-1/-1/-1/4/4/-1/-1");
    num=split(data,dataint);
    for(int i=0;i<num;i++){
        cout<<dataint[i]<<endl;
    }
    cout<<endl<<"save "<<gm.run(dataint);
    return 0;
}
