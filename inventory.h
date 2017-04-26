class inventory{
private:
	int money;
	int inv[10];
public:
	inventory();
	~inventory();
	int* getmoney();
	void setmoney(int m);
};
inventory::~inventory(){

}
inventory::inventory(){

}
int* inventory::getmoney(){
	return &money;
}
void inventory::setmoney(int m){
    money = m;
}
