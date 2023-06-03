#ifndef __Board_H
#define __Board_H
#include<iostream>
#include <string>
#include "Slot.h"
#include"Player.h"

using namespace std;


class Board {
public:
	enum action { END_GAME, PLAY, PRINT_BOARD };

protected:
	int m_size;
	Slot** m_arr;
	std::string m_board_image[6][5];
	int m_slot_width;
	void init_board_image();
	static int slotindex;
public:
	Board();
	~Board();
	int size() const;
	void add_go_slot(std::string g_msg);
	void add_asset_slot(std::string city, std::string asset);
	void add_chance_slot(std::string c_msg, int num);
	void add_jail_slot(std::string j_str);
	Slot* operator[](int idx) const;
	Slot* get_Slot_data(int index) const;
	void showplayers(Player* players);
	void play(Player* players);
	void Simulator(Player* players);//simulator
	friend ostream& operator<<(ostream& os, const Board& b);
};



#endif
