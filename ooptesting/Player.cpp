#define  _CRTDBG_MAP_ALLOC
//#include "Slot.h"
#include"Board.h"
#include "Player.h"
#include "Queue.h"
#include <string>
#include <iostream>

using namespace std;
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

int Player::p_counter(0);
bool Player::sim(0);
Player::Player(std::string myname, Board* board, int money):player_id(p_counter+1),player_name(myname),p_board(board),Asset_list(13)
{//Player constructor
	p_counter++;
	p_balance = money;
	p_location = 1;
	p_in_jail = 0;
}
int Player::get_player_id()
{
	return player_id;
}
int Player::get_players_count()
{
	return p_counter;
}

std::string Player::get_player_name()
{
	return player_name;
}

int Player::get_player_balance()
{
	return p_balance;
}

int Player::get_player_location()
{
	return p_location;
}

bool Player::get_in_jail()
{
	return p_in_jail;
}

int Player::get_number_of_assets()
{
	//each player has a list of asset.
	//that method return how many asset the player own.
	return this->Asset_list.get_size();
}

bool Player::set_player_balance(int num)
{//change the amount of money the player have
 //if for some reason that fails the game end
	if ((p_balance + num) > 0)
	{
		p_balance += num;
		return true;
	}
	else if (Asset_list.get_size() > 0)
	{//if the player dont have the money 
		//thay can sell an asset if one available
		this->sell_asset();
		return set_player_balance(num);
	}
	else return false;
}

int Player::set_player_location(int num)
{
	return p_location = ((p_location + num) % 18);
}
void Player::set_in_jail()
{
	if (!this->get_in_jail())
		p_in_jail = true;
	else
		p_in_jail = false;
}
bool Player::add_asset(Asset* s)
{//add asset to the asset list
	if (!s->get_is_taken()) {//if the asset does not owend
		if (p_balance < s->get_price())
			return false;
		else
		{
			p_balance -= s->get_price();
			Asset_list.push(s);
			s->set_ownership(this);
			s->set_is_taken();//pay the price for the asset
			return true;
		}
	}
	else return false;
}
void Player::buy_asset(Asset* s)
{
	if (!s->get_is_taken())
	{
		int key = 0;
		if (this->get_player_balance() > s->get_price())
		{
			cout << "congratulations you bought " << s->get_name() << " for " << s->get_price() << " NIS" << endl;
			this->add_asset(s);
		}
		else
		{
			cout << "Unfortunately, you do not have enough money in your account to buy " << s->get_name() << endl;
			if (this->Asset_list.get_size() > 0)
			{
				cout << "Would you like to sell a property ?" << endl;
				cout << " press (1) for yes, anyother key for no. " << endl;
				if(sim==0)
					cin >> key;
				if (key == 1||sim==1)
				{
					this->sell_asset();
					buy_asset(s);
				}
			}
			else
				return;
		}
	}
	else
	{
		cout << "this asset belong to " << s->get_owner_name() << endl;
		return;
	}
}
void Player::sell_asset()
{
	//a player can sell an asset
	//thay will be payed and the onwership will be removed
	p_balance += Asset_list.front()->get_price();
	cout << "you sold " << Asset_list.front()->get_name() << "for " << Asset_list.front()->get_price() << " NIS" << endl;
	Asset_list.front()->remove_ownership();
	Asset_list.pop();
}
bool Player::pay_rent(int amount)
{
	if (p_balance > amount)//if the slot is owne by someone else you need to pay tham
	{
		p_balance -= amount;
		return true;
	}
	else if (Asset_list.get_size() > 0)//if you dont have the money you can sell an asset if one available
	{
		this->sell_asset();
		return pay_rent(amount);
	}
	else
		return false;
}
bool Player::draw_dice()
{//return a random number between one to six
	if (!this->get_in_jail())//if the playe in jail thay losses their turn
	{
		int num = Random(6, 1);
		if (this->p_location + num > 18)
		{
			cout << "Welcome, you have completed another round. Get  350 NIS and good luck in the next round" << endl;
			this->set_player_balance(75);
		}
		set_player_location(num);
	}
	else set_in_jail();
	return true;
}

void Player::showplayer()
{//use for debuging 
	cout << "player id: " << this->get_player_id() << endl << "player name: " << this->get_player_name() << endl << "player balance: " << this->get_player_balance() << endl << "player location: " << this->get_player_location() << endl<<"number of Assets :"<<this->get_number_of_assets()<<endl<< "in jail? " << this->get_in_jail() << endl;
}
Queue Player::get_Asset_list() const
{
	return this->Asset_list;
}
ostream& operator<<(ostream& os, const Player& p)
{
	os << p.Asset_list;
	return os;
}
Player::~Player()
{
	p_counter--;
}
