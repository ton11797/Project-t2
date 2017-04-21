#include <SFML/Network.hpp>
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class tcp{
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
    void getdata();
};
tcp::tcp(){
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
    configfile.close();
    status = socket.connect(ip, port);
}
void tcp::connect(){
    if (status != sf::Socket::Done)
    {
    }
}
void tcp::sent(char *dataa){
    if (socket.send(dataa, 100) != sf::Socket::Done)
    {
    }
}
void tcp::receive(){
    if (socket.receive(data, 100, received) != sf::Socket::Done)
    {
    }
}
void tcp::getdata(){
    cout<<data;
}

class user{
public:
    char username[100];
    char password[100];
    char data[100];
    user();
    void getusername();
    void getpassword();
};
user::user(){
cout<<"username: ";
cin>>username;
cout<<"password: ";
cin>>password;
}
int main()
{
    char type[100],data[100];
    user userpacket;
    cout<<"type 1.login 2.register 3.save : ";
    cin>>type;
    if(strcmp(type,"3")==0) cin>>data;
    tcp tcpsocket;
    tcpsocket.connect();
    tcpsocket.sent(type);
    tcpsocket.sent(userpacket.username);
    tcpsocket.sent(userpacket.password);
    if(strcmp(type,"3")==0)tcpsocket.sent(data);
    tcpsocket.receive();
    tcpsocket.getdata();
}
