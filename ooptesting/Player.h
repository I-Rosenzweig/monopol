#ifndef __Player_H
#define __Player_H
#include <iostream>
#include <string>
#include "Queue.h"
//#include "Board.h"
//#include "Slot.h
class Asset;
class Board;
class Queue;

using namespace std;
class Player
{
private:
	static bool sim;//ment for us to run a simulator.
	static int p_counter;
	const unsigned player_id;
	const std::string player_name;
	int p_balance;
	int p_location;
	bool p_in_jail;
	const Board* p_board;
	Queue Asset_list;
public:
	void onsim() { sim = true; }//activ smulator 
	void offsim() { sim = false; }//deactiv smulator 
	Player(std::string myname="", Board* board=nullptr, int money=0);
	int get_player_id();
	int get_players_count();
	std::string get_player_name();
	int get_player_balance();
	int get_player_location();
	bool get_in_jail();
	int get_number_of_assets();
	bool set_player_balance(int num);
	int set_player_location(int num);
	void set_in_jail();
	bool add_asset(Asset* s);
	void buy_asset(Asset* s);
	void sell_asset();
	bool pay_rent(int amount);
	bool draw_dice();
	void showplayer();
	Queue get_Asset_list()const;
	friend ostream& operator<<(ostream& os, const Player& p);//print the Asset list.
	~Player();
};

#endif