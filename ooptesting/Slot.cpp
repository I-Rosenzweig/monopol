#define  _CRTDBG_MAP_ALLOC
#include <iostream>
#include <string>
#include <time.h>
#include "Slot.h"
#include"Board.h"
#include "Player.h"
#include "Queue.h"//Realized as we have already done in a prior assignment

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

using namespace std;

//_____\\\slot///_________________________________________________________________
int Slot::s_counter(0);
//A static variable that counts the amount of slots and its derivatives
Slot::Slot(std::string name, std::string type) :index(s_counter + 1),myname(name),mytype(type)
//Slot constructor
{
	s_counter++;
}
int Slot::get_count() const
{
	return s_counter;
}

//______\\\Asset///___________________________________________________________________________
Asset::Asset(std::string Cityname, std::string assetname):City_name(Cityname),Ass_name(assetname),A_price(Random(100,50)),A_rent(Random(45,20)),Slot(Cityname+" "+assetname,"Asset")
//Asset constructor
{
	owner = nullptr;//at the begining of the game the asset belong to no one.
	owner_name ="";
	A_belong = 0;
}
std::string Asset:: get_name() const
//Specifically in the Asset the name consists of the name of the city and the name of the property
{
	return myname;
}
std::string Asset::get_city_name() const
//return the name of the city for example Givat Ella
{
	return City_name;
}
std::string Asset::get_ass_name() const
//return the name of the Asset, for example "home"
{
	return Ass_name;
}
std::string Asset::get_type() const
//We prepared this optionand did not use it.
//We decided to keep it in case we want to 
//upgrade the game in the future
//return the name of the Asset, for example "home"
{
	return mytype;
}
int Asset::get_index() const
{
	return index;
}
int Asset::get_price() const
//Each asset has a fixed price determined randomly at the start of the game between 50 and 150.
//This method returns the value of the property.
{
	return A_price;
}
int Asset::get_rent() const 
//Each asset has a fixed rent money determined randomly at the start of the game between 50 and 150.
//This method returns the value of the property.
{
	return A_rent;
}
bool Asset::get_is_taken() const 
//an Asset can be owned by a player.
//that method return 1 if it is owend by someone.
{
	return A_belong;
}
void Asset::set_is_taken() 
//an Asset can be bought and sold.
//that method Changes the status from associated to unassociated
{
	if(!A_belong)
		A_belong = true;
	else 
		A_belong = false;
}
Player* Asset::get_ownership() const
//that method return a pointer to the owner of that Asset.
//used to pay rent for exmple.
{
	return owner;
}
std::string Asset::get_owner_name() const
//each player has a name and so does every owner.
{
	return this->owner_name;
}
void Asset::set_ownership(Player* p)
//change the pointer to a new owner.
{
	owner = p;
	owner_name = p->get_player_name();
}
void Asset::remove_ownership()
//it is possible that the Asset will nob be owend by any one.
{
	owner = nullptr;
	owner_name = "";
	A_belong = 0;
}
bool Asset::play(Player* p)
//that method describes what happens to a player that ended his turn on Asset slot.
{
	int key =0;
	if (!this->get_is_taken())//if the asset belong to no one,
	{                         //the player get the opportunity to buy that Asset.
		cout << "welcome " << p->get_player_name() << " Would you like to buy the property? " << this->get_name() << " for " << this->get_price() << " NIS ?" << endl;
		cout << " press (1) for yes, anyother key for no. " << endl;
		cin >> key;
		if (key == 1)
		{
			p->buy_asset(this);
			return true;
		}
	}
	else if (this->get_ownership() != p)//if that asset does belong to some one and it is not you...
	{
		if (p->pay_rent(this->get_rent()))//you need to pay rent 
		{                                 
			cout << "This property belongs to " << this->owner_name << " You must pay him an amount of " << this->get_rent() << " NIS" << endl;
			//the player pay the rent and owner get the money.
			this->get_ownership()->set_player_balance(this->get_rent());
			return true;
		}
		else
			return false;//if yoe cant pay the game end
	}
	else
		return true;
}

bool Asset::playsim(Player* p, int n)
{
	int key = n;
	if (!this->get_is_taken())//if the asset belong to no one,
	{                         //the player get the opportunity to buy that Asset.
		if (key == 1)
		{
			p->buy_asset(this);
			return true;
		}
	}
	else if (this->get_ownership() != p)//if that asset does belong to some one and it is not you...
	{
		if (p->pay_rent(this->get_rent()))//you need to pay rent 
		{
			//the player pay the rent and owner get the money.
			this->get_ownership()->set_player_balance(this->get_rent());
			return true;
		}
		else
			return false;//if yoe cant pay the game end
	}
	else
		return true;
}

//GO___________________________________________________________________________
GO::GO(std::string msg ): G_message(msg), Slot("Go", "Go") { return; }//GO constructor

std::string GO::get_name() const
{
	return myname;
}
std::string GO::get_msg() const
//each GO type slot has a messege
{
	return G_message;
}
bool GO::play(Player* p)
{
	//does nothing
	return true;
}
bool GO::playsim(Player* p,int n)
{
	//does nothing
	return true;
}
std::string GO::get_type() const
{
	return mytype;
}
int GO::get_index() const
{
	return index;
}
//Jail________________________________________________________________________________
Jail::Jail(std::string msg) :J_message(msg), Slot("Jail", "Jail") { return; }//Jail constructor
std::string Jail::get_name() const
{
	return myname;
}
std::string Jail::get_msg() const
{
	return J_message;
}
std::string Jail::get_type() const
{
	return mytype;
}
int Jail::get_index() const
{
	return index;
}

bool Jail::play(Player* p)
{
	//cout << "You broke the law! You must enter the prison for one turn" << endl;
	//if the player ends his or hers turn in this slot. the jail flag change and the player losses the next turn.
	cout << this->get_msg() << endl;
	p->set_in_jail();
	return true;
}
bool Jail::playsim(Player* p, int n)
{
	return play(p);
}
//Chance________________________________________________________________________________
Chance::Chance(std::string msg,int num) :C_message(msg),C_money(num), Slot("Chance", "Chance") { return; }//Chance constructor

std::string Chance::get_name() const
{
	return myname;
}

std::string Chance::get_msg() const
{
	return C_message;
}

int Chance::get_money() const
{
	return C_money;
}

std::string Chance::get_type() const
{
	return mytype;
}
int Chance::get_index() const
{
	return index;
}

bool Chance::play(Player* p)
{
	//if the player ends his or hers turn in this slot. 
	//thay get money or have to pay money.
	cout << this->get_msg() << endl;
	p->set_player_balance(this->get_money());
	return true;
}
bool Chance::playsim(Player* p, int n)
{
	return play(p);
}
int Random(int mod, int st)
{
	int num;
	num = rand() % mod + st;
	return num;
}
int Random()
{
	int num;
	num = rand();
	return num;
}