#include <SFML/Network.hpp>
#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
typedef struct user
{
    char username[100];
    char password[100];
    char gamedata[100];
}USERDB;

void getdata(char *data,USERDB *userr,int n){
    for(int i=0;i<n;i++){
    if(strcmp(data,userr[i].username)==0){
        cout<<"test yes"<<endl;
    }
    }
}
int main()
{
    cout<<"Server starting"<<endl;
    cout<<"Loading config"<<endl;
    ifstream configfile;
    configfile.open("db/config.txt");
    char config[10][100];
    int i;
    if (configfile.is_open())
    {
        i=0;
        while (!configfile.eof())
        {
            configfile >> config[i];
            configfile >> config[i];
            i++;
        }
    }
    cout<<"Loaded config"<<endl;
    configfile.close();
    cout<<"Loading user data"<<endl;
    ifstream userfile;
    userfile.open("db/user.txt");
    struct user userdb[100];
    if (userfile.is_open())
    {
        i=0;
        while (!userfile.eof())
        {
            userfile >> userdb[i].username;
            userfile >> userdb[i].password;
            userfile >> userdb[i].gamedata;
            i++;
        }
    }
    cout<<"Loaded user data"<<endl;
    userfile.close();

    cout<<"listener port "<<atoi(config[0])<<endl;
    sf::TcpListener listener;
    if (listener.listen(atoi(config[0])) != sf::Socket::Done)
    {
        cout<<"Error listener port "<<atoi(config[0])<<endl;
    }
    while(1){
    cout<<"waiting for connection..."<<endl;
    sf::TcpSocket client;
    char data[100];
    std::size_t received;
    if (listener.accept(client) != sf::Socket::Done)
    {
    }
    cout<<"connecting "<<endl;
    if (client.receive(data, 100, received) != sf::Socket::Done)
    {
    // error...
    }
    cout << "Received " << received << " bytes"<<endl;
    char senddata[100];
    cout << "data :"<<data<<endl;
    getdata(data,userdb,i);
    if (client.send(data, 100) != sf::Socket::Done)
    {
    // error...
    }
}
    return 0;
}
