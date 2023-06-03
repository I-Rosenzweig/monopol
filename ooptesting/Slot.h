#ifndef __Slot_H
#define __Slot_H
#include <time.h>
#include <iostream>
#include <string>
//#include"Player.h"
//#include"Board.h"
using namespace std;
class Player;

class Slot
{//pure virtual class
protected:
	static int s_counter;
	const std::string myname;
	const std::string mytype;
	const int index;
public:
	Slot(std::string name = "Slot", std::string type = "Slot");
	virtual std::string get_name() const=0;
	virtual bool play(Player* p) = 0;
	virtual bool playsim(Player* p,int n) = 0;
	virtual std::string get_type() const=0;
	int get_count() const;
	virtual int get_index() const = 0;
	virtual ~Slot() = 0 {};

	
};
//____\\\\Asset////__________________________________________________________________________________________________
class Asset:public Slot
{
private:
	const std::string City_name, Ass_name;
	const int A_price, A_rent;
	bool A_belong;
	Player* owner;//pointer to the owner
	std::string owner_name;//the owner name
public:
	Asset(std::string Cityname="Givat_Ella",std::string assetname="home");
	std::string get_name() const;
	std::string get_city_name() const;
	std::string get_ass_name() const;
	std::string get_type() const;
	int get_index() const;
	int get_price() const;
	int get_rent() const;
	bool get_is_taken() const;
	void set_is_taken();
	Player* get_ownership() const;
	std::string get_owner_name() const;
	void set_ownership(Player* p);
	void remove_ownership();
	bool play(Player* p);
	bool playsim(Player* p, int n);

	//bool pay_rent(int amount);
	//Asset& operator=(const Asset& );
	//~Asset();

};
//____\\\\GO////________________________________________________________________________
class GO :public Slot
{
private:
	const std::string G_message;
public:
	GO(std::string msg = "GO GO GO");
	std::string get_name() const;
	std::string get_msg() const;
	std::string get_type() const;
	int get_index() const;
	bool play(Player* p);
	bool playsim(Player* p, int n);
};
//______\\\\Jail////________________________________________________________________________
class Jail :public Slot
{
private:
	const std::string J_message;
public:
	Jail(std::string msg = "nu nu nu");
	std::string get_name() const;
	std::string get_msg() const;
	std::string get_type() const;
	int get_index() const;
	bool play(Player* p);
	bool playsim(Player* p, int n);
};
//____\\\\Chance////________________________________________________________________________
class Chance :public Slot
{
private:
	const std::string C_message;
	int C_money;
public:
	Chance(std::string msg = "lucky",int num=0);
	std::string get_name() const;
	std::string get_msg() const;
	int get_money() const;
	std::string get_type() const;
	int get_index() const;
	bool play(Player* p);
	bool playsim(Player* p, int n);
};
//_____________________________________________________________________________________________
int Random(int mod, int st);
int Random();
#endif
