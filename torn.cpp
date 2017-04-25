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

using namespace std;
//function prototype
void getuserinput(sf::RenderWindow &window,char *out,sf::Texture &texture);
void waitenter(sf::RenderWindow &window,sf::Texture &texture);
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

int Menu::open(sf::RenderWindow &window,char *userin,char *passin,int *userdatain){
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
                        char type[100],re[100];
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
                        break;
                    case 3:
                        num=0;
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
        draw(window);
        window.display();
    }
    gamestart:;
    return num;
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
//end function

int main()
{
    ///////////////////////game menu//////////////////////////////
    sf::RenderWindow windowmenu(sf::VideoMode(1500, 700), "Stardew walley!!");
    Menu menu(windowmenu.getSize().x, (windowmenu.getSize().y)/0.35);
    int n=0,num=0,userdata[100];
    char user[100],pass[100];
    num = menu.open(windowmenu,user,pass,userdata);

    for(int ii=0;ii<num;ii++){
        cout<<userdata[ii]<<endl;
    }
    ///////////////////////game start//////////////////////////////
    if(num!=0){
    sf::RenderWindow window;
    int mapcheck[38][19];
     sf::Texture playertexture,bg,cat,Barn,coop;
     sf::Vector2i position;
    window.create(sf::VideoMode(1900,950)," FARM EIEI ",sf::Style::Resize|sf::Style::Close);//Style คือ รูปแบบของดด้านบนที่เราต้องการ close จะมีปุ่มปิด
    sf::Vector2u size(640,480);
    float movespeed=1;
    //window.setSize(sf::Vector2u(600,600));//set ขนาดหน้าจอที่เราต้องการให้ขึ้น ต้องใช้ Vector2u
    window.setTitle("MUCHU");//set ชื่อข้างบนที่เราจะให้ขึ้น
    window.setPosition(sf::Vector2i(0,0));//set ตำเเหน่งที่หน้าต่างวินโดจะเปิดมา ต้องใช้ vector2i
    sf::RectangleShape player(sf::Vector2f(50.0f,70.0f));
    //player.setFillColor(sf::Color::Red);
    player.setOrigin(50.0f,50.0f);
    player.setPosition(500.0f,500.0f);
    bg.loadFromFile("map.jpg");
    sf::Sprite bgg(bg);
    bgg.setTexture(bg);
    //bgg.scale(2,2);
    bgg.setPosition(0,0);
    playertexture.loadFromFile("resource/she.png");
    player.setTexture(&playertexture);
    sf::Vector2u texturesize = playertexture.getSize();
    texturesize.x /=4;
    texturesize.y /=4;
    player.setTextureRect(sf::IntRect(texturesize.x *0,texturesize.y *0,texturesize.x,texturesize.y));
    animetion animation(&playertexture,sf::Vector2u(4,4),0.3f);
    float deltatime=0.0f;
    sf::Clock clock;
    sf::Time time;
    Barn.loadFromFile("resource/Barn.png");
    int turn=0;
    coop.loadFromFile("resource/Coop.png");
    object Barnn(&Barn,sf::Vector2f(112.0f,128.0f),sf::Vector2f(1350.0f,150.0f));
    object Coop(&coop,sf::Vector2f(112.0f,128.0f),sf::Vector2f(80.0f,350.0f));
    object kop(&bg,sf::Vector2f(10.0f,1950.0f),sf::Vector2f(0.0f,0.0f));
    object kop1(&bg,sf::Vector2f(3950.0f,10.0f),sf::Vector2f(0.0f,0.0f));
    object kop2(&bg,sf::Vector2f(10.0f,1950.0f),sf::Vector2f(1900.0f,0.0f));
    object kop3(&bg,sf::Vector2f(3950.0f,10.0f),sf::Vector2f(0.0f,950.0f));


    Player player1(&playertexture,sf::Vector2u(4,4),0.3f,sf::Vector2f(500.0f,600.0f));
    Player player2(&playertexture,sf::Vector2u(4,4),0.3f,sf::Vector2f(500.0f,500.0f));
    while (window.isOpen())
    {
       deltatime=clock.restart().asSeconds();
        sf::Event Event;
        while(window.pollEvent(Event))
        {
            switch(Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    if(Event.text.unicode<128)
                    {
                        printf("%c",Event.text.unicode);
                    }
            }

        }
        player1.update(deltatime,movespeed,turn);
        Barnn.getcollider().checkcollider(player1.getcollider(),1.0f);
        Coop.getcollider().checkcollider(player1.getcollider(),1.0f);
        kop.getcollider().checkcollider(player1.getcollider(),1.0f);
        kop1.getcollider().checkcollider(player1.getcollider(),1.0f);
        kop2.getcollider().checkcollider(player1.getcollider(),1.0f);
        kop3.getcollider().checkcollider(player1.getcollider(),1.0f);
        window.clear(sf::Color(150,150,150));
        window.draw(bgg);
        Barnn.Draw(window);
        kop.Draw(window);
        kop1.Draw(window);
        kop2.Draw(window);
        kop3.Draw(window);
        Coop.Draw(window);
        player1.Draw(window);
        window.display();
        turn++;

    }
    }

    return 0;



}
