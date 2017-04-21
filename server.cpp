#include <SFML/Network.hpp>
#include<iostream>
#include<string.h>
#include<fstream>
#define CHARLEN 100
using namespace std;
//class userdb
typedef struct userdbs{
    char username[CHARLEN];
    char password[CHARLEN];
    char gamedata[CHARLEN];
}DBuser;
class userdb{
private:
    DBuser dbuser[CHARLEN];
    int numid;
public:
    userdb();
    ~userdb();
    void loaduserdb();
    int login(char *user,char *password);
    char* getgamedata(int id);
    void registe(char *username,char *password);
    void saveuserdb();
    void save(char *data,int id);
};
void userdb::save(char *data,int id){
    strcpy(dbuser[id].gamedata,data);
}
void userdb::saveuserdb(){
    ofstream userfile;
    userfile.open ("db/user.txt");
    for(int i =0;i<numid;i++){
        userfile << dbuser[i].username<<" "<<dbuser[i].password<<" "<<dbuser[i].gamedata<<endl;
    }
    userfile.close();
}
char* userdb::getgamedata(int id){
    if(id != -1)return dbuser[id].gamedata;
    return "nousername";
}
int userdb::login(char *user,char *password){
    for(int i=0;i<numid;i++){
        if(strcmp(user,dbuser[i].username)==0){
            if(strcmp(password,dbuser[i].password)==0){
                cout<<"pass ok"<<endl;
                return i;
            }else
                cout<<"user ok"<<endl;
                return -2;
            }
    }
    return -1;
}
userdb::userdb(){numid=0;}
userdb::~userdb(){}
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
            userfile >> dbuser[i].username;
            userfile >> dbuser[i].password;
            userfile >> dbuser[i].gamedata;
            i++;
        }
    }
    numid=i-1;
    userfile.close();
    cout<<"Loaded user data "<<numid+1<<" user"<<endl;
}
void userdb::registe(char *username,char *password){
    strcpy(dbuser[numid].username,username);
    strcpy(dbuser[numid].password,password);
    strcpy(dbuser[numid].gamedata,"0/0/0/0/0/0/0/0/0");
    numid++;
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
    int id;
    char username[CHARLEN],password[CHARLEN],type[CHARLEN];
    while(1){
    strcpy(username,"");
    strcpy(password,"");
    tcpsocket.waitingtcp();
    tcpsocket.receivedata();
    strcpy(type,tcpsocket.getdata());
    tcpsocket.receivedata();
    strcpy(username,tcpsocket.getdata());
    tcpsocket.receivedata();
    strcpy(password,tcpsocket.getdata());
    if(strcmp(type,"1")==0){
        id = userdata.login(username,password);
        if(id >=0 )tcpsocket.senddata(userdata.getgamedata(id));
        if(id ==-2 )tcpsocket.senddata("password worng");
        if(id ==-1 )tcpsocket.senddata("username worng");
    }
    if(strcmp(type,"2")==0){
        id = userdata.login(username,password);
        if(id == -1){
        cout<<"register new user";
        userdata.registe(username,password);
        userdata.saveuserdb();
        tcpsocket.senddata("registed");
        }else{
        tcpsocket.senddata("same username");
        }
    }
    if(strcmp(type,"3")==0){
        id = userdata.login(username,password);
        if(id >=0){
        tcpsocket.receivedata();
        userdata.save(tcpsocket.getdata(),id);
        userdata.saveuserdb();
        tcpsocket.senddata("done");
        }else{
        tcpsocket.senddata("password worng");
        }
    }

    }
    return 0;
}
