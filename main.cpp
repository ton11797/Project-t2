#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <fstream>
#include "Menu.h"
#include "split.h"
#include "animetion.h"
#include "object.h"
#include "Player.h"
#include "collider.h"
#include "select.h"
#include "inventory.h"
#include "gamestart.h"
using namespace std;
//function prototype
void getuserinput(sf::RenderWindow &window,char *out,sf::Texture &texture);
void waitenter(sf::RenderWindow &window,sf::Texture &texture);
void showrank(sf::RenderWindow &window,sf::Texture &texture ,char*);
//end function prototype
//class menu
Menu::Menu(float width, float height)
{
    if(!texture.loadFromFile("resource\\menu.jpg"));
    if(!usertx.loadFromFile("resource\\loginuserp.png"));
    if(!passtx.loadFromFile("resource\\loginpass.png"));
    if(!nouser.loadFromFile("resource\\nousername.png"));
    if(!passworng.loadFromFile("resource\\password wrong.png"));
    if(!sameuser.loadFromFile("resource\\username exists.png"));
    if(!registered.loadFromFile("resource\\registered.png"));
    if(!blank.loadFromFile("resource\\blank.png"));
    if(!cantconnect.loadFromFile("resource\\cantconnect.png"));
    if(!ranking.loadFromFile("resource\\rank.png"));
    background.setTexture(texture);
    if (!font.loadFromFile("arial.ttf"))
    {
        // handle error
    }
    menu[0].setCharacterSize(40);
    menu[0].setFont(font);
    menu[0].setStyle(sf::Text::Bold);
    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Register");

    menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    menu[1].setCharacterSize(40);
    menu[1].setFont(font);
    menu[1].setStyle(sf::Text::Bold);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Login");
    menu[1].setPosition(sf::Vector2f(width / 2, height /(MAX_NUMBER_OF_ITEMS + 1) * 1.1));

    menu[2].setCharacterSize(40);
    menu[2].setFont(font);
    menu[2].setStyle(sf::Text::Bold);
    menu[2].setColor(sf::Color::White);
    menu[2].setString("Ranking");
    menu[2].setPosition(sf::Vector2f(width / 2, height /(MAX_NUMBER_OF_ITEMS + 1) * 1.2));

    menu[3].setCharacterSize(40);
    menu[3].setFont(font);
    menu[3].setStyle(sf::Text::Bold);
    menu[3].setColor(sf::Color::White);
    menu[3].setString("Exit");
    menu[3].setPosition(sf::Vector2f(width / 2, height /(MAX_NUMBER_OF_ITEMS + 1) * 1.3));

    selectedItemIndex = 0;
}
Menu::~Menu()
{
}
void Menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}
void Menu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}
void Menu::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

int Menu::open(sf::RenderWindow &window,char *userin,char *passin,int *userdatain)
{
    user=userin;
    pass=passin;
    userdata=userdatain;
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    MoveUp();
                    break;
                case sf::Keyboard::S:
                    MoveDown();
                    break;
                case sf::Keyboard::Down:
                    MoveDown();
                    break;
                case sf::Keyboard::Up:
                    MoveUp();
                    break;
                case sf::Keyboard::Return:
                    switch (GetPressedItem())
                    {
                    case 0:
                        std::cout << "Register button has been pressed" << std::endl;
                        getuserinput(window,user,usertx);
                        cout<<"password :"<<user<<endl;
                        getuserinput(window,pass,passtx);
                        cout<<"password :"<<pass<<endl;
                        char type[200],re[200];
                        strcpy(type,"2");
                        if(!(strcmp(user,"")==0 || strcmp(pass,"")==0))
                        {
                            tcpsocket= new(tcp);
                            if(tcpsocket->con==1)
                            {
                                tcpsocket->sent(type);
                                tcpsocket->sent(user);
                                tcpsocket->sent(pass);
                                tcpsocket->receive();
                                strcpy(re,tcpsocket->getdata());
                                delete(tcpsocket);
                                if(strcmp(re,"0")==0)
                                {
                                    waitenter(window,sameuser);
                                }
                                else if(strcmp(re,"1")==0)
                                {
                                    waitenter(window,registered);
                                }
                                else
                                {

                                }
                            }
                            else
                            {
                                waitenter(window,cantconnect);
                            }
                        }
                        else
                        {

                            waitenter(window,blank);
                        }
                        break;
                    case 1:
                        std::cout << "Login button has been pressed" << std::endl;
                        getuserinput(window,user,usertx);
                        cout<<"password :"<<user<<endl;
                        getuserinput(window,pass,passtx);
                        cout<<"password :"<<pass<<endl;
                        strcpy(type,"1");
                        tcpsocket= new(tcp);
                        if(tcpsocket->con==1)
                        {
                            tcpsocket->sent(type);
                            tcpsocket->sent(user);
                            tcpsocket->sent(pass);
                            tcpsocket->receive();
                            strcpy(re,tcpsocket->getdata());
                            delete(tcpsocket);
                            if(strcmp(re,"0")==0)
                            {
                                waitenter(window,nouser);
                            }
                            else if(strcmp(re,"1")==0)
                            {
                                waitenter(window,passworng);
                            }
                            else
                            {
                                num=split(re,userdata);
                                goto gamestart;
                            }
                        }
                        else
                        {
                            waitenter(window,cantconnect);
                        }
                        break;
                    case 2:
                        std::cout << "Ranking button has been pressed "<< std::endl;
                        tcpsocket= new(tcp);
                        strcpy(type,"4");
                        if(tcpsocket->con==1)
                        {
                            tcpsocket->sent(type);
                            tcpsocket->sent(" ");
                            tcpsocket->sent(" ");
                            tcpsocket->receive();
                            strcpy(re,tcpsocket->getdata());
                            delete(tcpsocket);
                            cout<<re;
                            showrank(window,ranking,re);
                        }
                        else
                        {
                            waitenter(window,cantconnect);
                        }
                        break;
                    case 3:
                        num=0;
                        window.close();
                        goto endgame;
                        break;
                    }
                    break;
                }

                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        window.clear();
        window.draw(background);
        draw(window);
        window.display();
    }
gamestart:
    ;
    return num;
endgame:
    ;
    return -1;
}
//end class menu
//function
void getuserinput(sf::RenderWindow &window,char *out,sf::Texture &texture)
{
    int n=0;
    sf::String sentence;
    sf::Text username;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Sprite background(texture);
    username.setFont(font);
    username.setCharacterSize(24);
    username.setFillColor(sf::Color::White);
    while (window.isOpen()&&n==0)
    {
        sf::Event eventrg;
        while (window.pollEvent(eventrg))
        {
            switch(eventrg.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(eventrg.key.code == sf::Keyboard::Return)
                {
                    n++;
                    break;
                }
            case sf::Event::TextEntered:
                if(eventrg.text.unicode == 59 && sentence.getSize()>0)
                {
                    sentence.erase(sentence.getSize()-1,sentence.getSize());
                }
                else if((eventrg.text.unicode >= 48 && eventrg.text.unicode <= 57)||(eventrg.text.unicode >= 65 && eventrg.text.unicode <= 90)||(eventrg.text.unicode >= 97 && eventrg.text.unicode <= 122))
                {
                    sentence += static_cast<char>(eventrg.text.unicode);
                }
                username.setString(sentence);
            }
            window.clear();
            window.draw(background);
            username.setPosition(600,280);
            window.draw(username);
            window.display();
        }

    }
    strcpy(out,sentence.toAnsiString().c_str());
}

void waitenter(sf::RenderWindow &window,sf::Texture &texture)
{
    sf::Event eventrg;
    sf::Sprite background(texture);
    while (window.isOpen())
    {
        while (window.pollEvent(eventrg))
        {
            switch(eventrg.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::TextEntered:
                goto outwait;
            }
            window.clear();
            window.draw(background);
            window.display();
        }
    }
outwait:
    ;
}

void showrank(sf::RenderWindow &window,sf::Texture &texture,char* re){
    int n=0;
    sf::String sentence;
    sf::Text ranking;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Sprite background(texture);
    ranking.setFont(font);
    ranking.setString(re);
    ranking.setCharacterSize(24);
    ranking.setFillColor(sf::Color::White);
    while (window.isOpen()&&n==0)
    {
        sf::Event eventrg;
        while (window.pollEvent(eventrg))
        {
            switch(eventrg.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(eventrg.key.code == sf::Keyboard::Return)
                {
                    n++;
                    break;
                }
            }
            window.clear();
            window.draw(background);
            ranking.setPosition(600,280);
            window.draw(ranking);
            window.display();
        }

    }
}
//end function

int main()
{
    ///////////////////////game menu//////////////////////////////
    sf::RenderWindow windowmenu(sf::VideoMode(1500, 700), "Stardew walley!!");
    Menu menu(windowmenu.getSize().x, (windowmenu.getSize().y)/0.35);
    tcp *tcpsocket;
    int n=0,num=0,userdata[200];
    char user[200],pass[200],type[200],datasave[200];
    num = menu.open(windowmenu,user,pass,userdata);
    ///////////////////////game start//////////////////////////////
    if(num!=-1)
    {
        int dataint[200];
        gamestart gm;
        /*strcpy(userdata,"-1/-1/-1/-1/-1/-1/-1/-1/0/0/-1/-1/-1/-1/1/0/-1/-1/-1/-1/2/2/-1/-1/-1/-1/3/3/-1/-1/-1/-1/4/4/-1/-1");
        num=split(userdata,dataint);*/
        strcpy(datasave,gm.run(userdata));
        strcpy(type,"3");
        tcpsocket= new(tcp);
        tcpsocket->sent(type);
        tcpsocket->sent(user);
        tcpsocket->sent(pass);
        tcpsocket->sent(datasave);
        cout<<"Sent"<<datasave;
    }
    return 0;
}
