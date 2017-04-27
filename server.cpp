#include <SFML/Network.hpp>
#include<iostream>
#include<string.h>
#include<fstream>
#define CHARLEN 150
using namespace std;
//class userdb
int getmoney(char*);
typedef struct userdbs{
    char username[CHARLEN];
    char password[CHARLEN];
    char gamedata[CHARLEN];
    int money;
}DBuser;
class userdb{
private:
    DBuser dbuser[CHARLEN];
    char ranking[150];
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
    void showall();
    void changepass(char *user,char *password);
    void sortting();
    char* getranking();
};
char* userdb::getranking(){
    sprintf(ranking, "1.%s %d\n2.%s %d\n3.%s %d\n4.%s %d\n5.%s %d\n",dbuser[0].username,dbuser[0].money,dbuser[1].username,dbuser[1].money,dbuser[2].username,dbuser[2].money,dbuser[3].username,dbuser[3].money,dbuser[4].username,dbuser[4].money);
    return ranking;
}
void userdb::changepass(char *user,char *password){
    int i;
    for(i=0;i<numid;i++){
        if(strcmp(user,dbuser[i].username)==0){
            break;
        }
    }
    strcpy(dbuser[i].password,password);
    saveuserdb();
}
void userdb::showall(){
    for(int i=0;i<numid;i++){
        cout<<dbuser[i].username<<endl;
    }
}
void userdb::save(char *data,int id){
    strcpy(dbuser[id].gamedata,data);
    dbuser[id].money = getmoney(dbuser[id].gamedata);
}
void userdb::saveuserdb(){
    int i;
    ofstream userfile;
    userfile.open ("db/user.txt");
    for(i =0;i<numid-1;i++){
        userfile << dbuser[i].username<<" "<<dbuser[i].password<<" "<<dbuser[i].gamedata<<endl;
    }
    userfile << dbuser[i].username<<" "<<dbuser[i].password<<" "<<dbuser[i].gamedata;
    userfile.close();
}
void userdb::sortting(){
    int c;
    for(int j=0;j<numid;j++){
            c=0;
    for(int i=numid;i>0;i--){
        if(dbuser[i].money>dbuser[i-1].money){
            swap(dbuser[i].money,dbuser[i-1].money);
            swap(dbuser[i].username,dbuser[i-1].username);
            swap(dbuser[i].password,dbuser[i-1].password);
            swap(dbuser[i].gamedata,dbuser[i-1].gamedata);
            c++;
        }
    }
    if(c==0)break;
    }
    saveuserdb();
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
            dbuser[i].money = getmoney(dbuser[i].gamedata);
            i++;
        }
    }
    numid=i;
    userfile.close();
    cout<<"Loaded user data "<<numid<<" user"<<endl;
}
void userdb::registe(char *username,char *password){
    strcpy(dbuser[numid].username,username);
    strcpy(dbuser[numid].password,password);
    strcpy(dbuser[numid].gamedata,"100/0/1/2/3/4/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1/-1");
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

int getmoney(char* data){
    char temp[100]="";
    for(int i=0;i<200;i++){
        if(data[i]=='/')break;
        temp[i]=data[i];
    }
    return atoi(temp);
}
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
    userdata.sortting();
    //end loaduserdata
    //listener tcp
    int mode=1;
    char username[CHARLEN],password[CHARLEN],type[CHARLEN];
    cout<<"server mode 1.normal mode 2.admin mode [1-2]: ";
    cin>>mode;
    if(mode==1){
    normal:;
    tcp tcpsocket;
    tcpsocket.listentcp(configdata.getport());
    //waiting for connection
    int id;
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
    if(!(strcmp(username,"")==0 || strcmp(password,"")==0)){
    if(strcmp(type,"1")==0){
        id = userdata.login(username,password);
        if(id >=0 )tcpsocket.senddata(userdata.getgamedata(id));
        if(id ==-2 )tcpsocket.senddata("1");
        if(id ==-1 )tcpsocket.senddata("0");
    }

    if(strcmp(type,"2")==0){
        id = userdata.login(username,password);
        if(id == -1){
        cout<<"register new user";
        userdata.registe(username,password);
        userdata.saveuserdb();
        tcpsocket.senddata("1");
        }else{
        tcpsocket.senddata("0");
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
    if(strcmp(type,"4")==0){
        userdata.sortting();
        cout<<userdata.getranking();
        tcpsocket.senddata(userdata.getranking());
    }
    }else{
    tcpsocket.senddata("username error");
    }
    }
    }else{
        while(1){
        cout<<"      1.Show all user"<<endl<<"      2.Add user"<<endl<<"      3.Change password user"<<endl<<"      4.Remove user"<<endl<<"      5.switch to normal mode"<<endl<<"      6.Stop server"<<endl<<"input[1-6]: ";
        cin>>mode;
        switch(mode){
        case 1:userdata.showall();break;
        case 2:cout<<"Add new(username password) : ";cin>>username>>password;userdata.registe(username,password);userdata.sortting();break;
        case 3:cout<<"Change pass (username new_password) : ";cin>>username>>password;userdata.changepass(username,password);userdata.sortting();break;
        case 4:;break;
        case 5:goto normal;;break;
        case 6:return 0;
        }
        }
    }

    return 0;
}
