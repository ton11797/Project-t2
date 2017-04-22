#include "SFML/Graphics.hpp"
#include <iostream>
#include <string.h>
#include "Menu.h"
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include<fstream>
using namespace std;
class tcp
{
private:
    char data[100];
    int port;
    char ip[100];
    sf::TcpSocket socket;
    sf::Socket::Status status;
    std::size_t received;
public:
    tcp();
    void connect();
    void sent(char *dataa);
    void receive();
    char* getdata();
};
tcp::tcp()
{
    ifstream configfile;
    char temp[100];
    configfile.open("config.txt");
    if (configfile.is_open())
    {
        while (!configfile.eof())
        {
            configfile >>temp;
            configfile >> port;
            configfile >>temp;
            configfile >> ip;
        }
    }
    status = socket.connect(ip, port);
    configfile.close();
}
void tcp::connect()
{
    //status = socket.connect(ip, port);
    if (status != sf::Socket::Done)
    {
        cout<<"connect error";
    }
}
void tcp::sent(char *dataa)
{
    if (socket.send(dataa, 100) != sf::Socket::Done)
    {
        cout<<"sent error";
    }
}
void tcp::receive()
{
    if (socket.receive(data, 100, received) != sf::Socket::Done)
    {
        cout<<"sent receive";
    }
}
char* tcp::getdata()
{

    return data;
}
Menu::Menu(float width, float height)
{
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
    menu[1].setColor(sf::Color(232,163,12));
    menu[1].setString("Login");
    menu[1].setPosition(sf::Vector2f(width / 2, height /(MAX_NUMBER_OF_ITEMS + 1) * 1.1));

    menu[2].setCharacterSize(40);
    menu[2].setFont(font);
    menu[2].setStyle(sf::Text::Bold);
    menu[2].setColor(sf::Color(232,163,12));
    menu[2].setString("Ranking");
    menu[2].setPosition(sf::Vector2f(width / 2, height /(MAX_NUMBER_OF_ITEMS + 1) * 1.2));

    menu[3].setCharacterSize(40);
    menu[3].setFont(font);
    menu[3].setStyle(sf::Text::Bold);
    menu[3].setColor(sf::Color(232,163,12));
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
        menu[selectedItemIndex].setColor(sf::Color(232,163,12));
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}
void Menu::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setColor(sf::Color(232,163,12));
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(sf::Color::Red);
    }
}

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
int main()
{
    char user[100],pass[100];
    char type[100],re[100];
    tcp *tcpsocket;
    ///////////////////////
    sf::Texture texture,usertx,passtx;
    if(!texture.loadFromFile("menu.jpg"));
    if(!usertx.loadFromFile("loginuserp.png"));
    if(!passtx.loadFromFile("loginpass.png"));
    sf::Sprite background(texture);
    sf::RenderWindow window(sf::VideoMode(1500, 700), "Stardew walley!!");
    Menu menu(window.getSize().x, (window.getSize().y)/0.35);
    int n=0;
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
                    menu.MoveUp();
                    break;

                case sf::Keyboard::S:
                    menu.MoveDown();
                    break;
                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;
                case sf::Keyboard::Return:
                    switch (menu.GetPressedItem())
                    {
                    case 0:
                        std::cout << "Register button has been pressed" << std::endl;
                        getuserinput(window,user,usertx);
                        cout<<"password :"<<user<<endl;
                        getuserinput(window,pass,passtx);
                        cout<<"password :"<<pass<<endl;
                        char type[100],re[100];
                        strcpy(type,"2");
                        tcpsocket= new(tcp);
                        tcpsocket->sent(type);
                        tcpsocket->sent(user);
                        tcpsocket->sent(pass);
                        tcpsocket->receive();
                        strcpy(re,tcpsocket->getdata());
                        delete(tcpsocket);
                        cout<<re;
                        break;
                    case 1:
                        std::cout << "Login button has been pressed" << std::endl;
                        getuserinput(window,user,usertx);
                        cout<<"password :"<<user<<endl;
                        getuserinput(window,pass,passtx);
                        cout<<"password :"<<pass<<endl;
                        strcpy(type,"1");
                        tcpsocket= new(tcp);
                        tcpsocket->sent(type);
                        tcpsocket->sent(user);
                        tcpsocket->sent(pass);
                        tcpsocket->receive();
                        strcpy(re,tcpsocket->getdata());
                        delete(tcpsocket);
                        cout<<re;
                        break;
                    case 2:
                        std::cout << "Ranking button has been pressed "<< std::endl;
                        break;
                    case 3:
                        window.close();
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
        menu.draw(window);
        window.display();
    }
}
