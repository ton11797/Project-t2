class inventory{
private:
	int money;
	int inv[10];
public:
	inventory();
	~inventory();
	int* getmoney();
	int* getinv();
	void setmoney(int m);

};
inventory::~inventory(){

}
inventory::inventory(){
 for(int i=0 ;i<10;i++){
    inv[i]=0;
 }
}
int* inventory::getmoney(){
	return &money;
}
void inventory::setmoney(int m){
    money = m;
}
int* inventory::getinv(){
    return inv;
}
