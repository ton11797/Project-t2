#ifndef SELECT_H_INCLUDED
#define SELECT_H_INCLUDED
#include "Player.h"
#include "collider.h"
#include<SFML/Graphics.hpp>
#include <iostream>
#include "object.h"

class tex
{
private:

public:
    tex();
    ~tex();
    sf::Texture textarray[10];
    sf::Texture* gettexture(int i);
};
sf::Texture* tex::gettexture(int i){
    return &textarray[i];
}
tex::tex(){
	for(int i=0;i<10;i++){
        char file[100];
        char buffer[1];
        sprintf(buffer, "%d", i);
        strcpy(file,"resource\\plant\\");
        strcat(file,buffer);
        strcat(file,".png");
		textarray[i].loadFromFile(file);
		cout<<"load "<<file<<endl;
	}
}

tex::~tex(){

}


#endif // SELECT_H_INCLUDED
