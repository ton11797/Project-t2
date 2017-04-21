#include <SFML/Network.hpp>
#include<iostream>
#include<string.h>
#include<fstream>
#define CHARLEN 100
using namespace std;
//class userdb
class userdb{
private:
    char username[CHARLEN];
    char password[CHARLEN];
    char gamedata[CHARLEN];
public:
    void loaduserdb();
};
void userdb::loaduserdb(){
    ifstream userfile;
    cout<<"Loading user data"<<endl;
    userfile.open("db/user.txt");
    int i;
    if (userfile.is_open())
    {
        i=0;
        while (!userfile.eof())
        {
            userfile >> username;
            userfile >> password;
            userfile >> gamedata;
            i++;
        }
    }
    userfile.close();
    cout<<"Loaded user data"<<endl;
}
//end class userdb
//class configdb
class configdb{
private:
    int port;
public:
    void loadconfig();
    int getport();
};
int configdb::getport(){
    return port;
}
void configdb::loadconfig(){
    ifstream configfile;
    char temp[CHARLEN];
    cout<<"Loading config"<<endl;
    configfile.open("db/config.txt");
    int i;
    if (configfile.is_open())
    {
        i=0;
        while (!configfile.eof())
        {
            configfile >>temp;
            configfile >> port;
            i++;
        }
    }
    configfile.close();
    cout<<"Loaded config"<<endl;
}
//end class configdb
//class tcp
class tcp{
private:
    char data[CHARLEN];
    sf::TcpListener listener;
    sf::TcpSocket client;
    size_t received;
public:
    void listentcp(int port);
    void waitingtcp();
    void receivedata();
    void senddata(char *sdata);
    char* getdata();
};
char* tcp::getdata(){
    return data;
}
void tcp::listentcp(int port){
    cout<<"listener port "<<port<<endl;
    if (listener.listen(port) != sf::Socket::Done)
    {
        cout<<"Error listener port "<<port<<endl;
    }
}
void tcp::waitingtcp(){
    cout<<"waiting for connection..."<<endl;
    if (listener.accept(client) != sf::Socket::Done)
    {
    }
    cout<<"connected "<<endl;
}
void tcp::receivedata(){
    if (client.receive(data, CHARLEN, received) != sf::Socket::Done)
    {
    // error...
    }
     cout << "Received " << received << " bytes"<<endl;
     cout << "data :"<<data<<endl;
}
void tcp::senddata(char *sdata){
    if (client.send(sdata, CHARLEN) != sf::Socket::Done)
    {
    // error...
    }
}

//end class tcp
int main()
{
    cout<<"Server starting"<<endl;
    //object config
    configdb configdata;
    configdata.loadconfig();
    //end loadcconfig
    //object userdb
    userdb userdata;
    userdata.loaduserdb();
    //end loaduserdata
    //listener tcp
    tcp tcpsocket;
    tcpsocket.listentcp(configdata.getport());
    //waiting for connection
    while(1){
    tcpsocket.waitingtcp();
    tcpsocket.receivedata();
    tcpsocket.senddata(tcpsocket.getdata());
}
    return 0;
}
