#define  _CRTDBG_MAP_ALLOC
#include "Slot.h"
#include"Board.h"
#include "Player.h"
#include "Queue.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include<fstream>//write and read from files.
using namespace std;

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#define breadth 30

int Board::slotindex(0);//count the number of Board game 
string center(int width, const string& str) {
	//yael's master masterpiece
	int len = str.length();
	if (width < len) { return str; }

	int diff = width - len;
	int pad1 = diff / 2;
	int pad2 = diff - pad1;
	return string(pad1, ' ') + str + string(pad2, ' ');
}

void draw_edge_line(int width, const string* line)
{
	//yael's master masterpiece
	cout << "|" << string((width) * 5 + 4, '-') << "|" << endl;
	cout << "|" << string((width) * 5 + 4, ' ') << "|" << endl;
	cout << "|";
	for (int col = 0; col < 5; col++)
		cout << center(width, line[col]) << "|";
	cout << endl;
	cout << "|" << string((width) * 5 + 4, ' ') << "|" << endl;
	cout << "|" << string((width) * 5 + 4, '-') << "|" << endl;
}

void draw_inner_line(int width, const string* line, bool last)
{
	//yael's master masterpiece
	cout << "|" << string(width * 5 + 4, ' ') << "|" << endl;
	cout << "|" << center(width, line[0]) << "|";
	cout << string(width * 3 + 2, ' ') << "|";
	cout << center(width, line[4]) << "|" << endl;
	cout << "|" << string(width * 5 + 4, ' ') << "|" << endl;
	if (!last)
	{
		cout << "|" << string(width, '-') << "|" << string((width * 3 + 3), ' ');
		cout << string(width, '-') << "|" << endl;
	}
}


ostream& operator<<(ostream& os, const Board& b)
{
	//yael's master masterpiece
	draw_edge_line(b.m_slot_width, b.m_board_image[0]);
	for (int row = 1; row < 5; row++)
		draw_inner_line(b.m_slot_width, b.m_board_image[row], row == 4);
	draw_edge_line(b.m_slot_width, b.m_board_image[5]);
	return os;
}

void Board::init_board_image()
{
	//yael's master masterpiece
	m_board_image[0][0] = m_arr[9]->get_name();
	m_board_image[0][1] = m_arr[10]->get_name();
	m_board_image[0][2] = m_arr[11]->get_name();
	m_board_image[0][3] = m_arr[12]->get_name();
	m_board_image[0][4] = m_arr[13]->get_name();
	m_board_image[1][0] = m_arr[8]->get_name();
	m_board_image[1][1] = "";
	m_board_image[1][2] = "";
	m_board_image[1][3] = "";
	m_board_image[1][4] = m_arr[14]->get_name();
	m_board_image[2][0] = m_arr[7]->get_name();
	m_board_image[2][1] = "";
	m_board_image[2][2] = "";
	m_board_image[2][3] = "";
	m_board_image[2][4] = m_arr[15]->get_name();
	m_board_image[3][0] = m_arr[6]->get_name();
	m_board_image[3][1] = "";
	m_board_image[3][2] = "";
	m_board_image[3][3] = "";
	m_board_image[3][4] = m_arr[16]->get_name();
	m_board_image[4][0] = m_arr[5]->get_name();
	m_board_image[4][1] = "";
	m_board_image[4][2] = "";
	m_board_image[4][3] = "";
	m_board_image[4][4] = m_arr[17]->get_name();
	m_board_image[5][0] = m_arr[4]->get_name();
	m_board_image[5][1] = m_arr[3]->get_name();
	m_board_image[5][2] = m_arr[2]->get_name();
	m_board_image[5][3] = m_arr[1]->get_name();
	m_board_image[5][4] = m_arr[0]->get_name();

	m_slot_width = 0;
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 5; col++)
			if (m_board_image[row][col].size() > m_slot_width)
				m_slot_width = m_board_image[row][col].size();
	}
	m_slot_width += 2;
}

Board::Board()
{
	srand(time(NULL));
	m_size = 0;
	m_arr = nullptr;
	m_arr = new Slot * [18];//workes onley for a board in spacific size
	add_go_slot("GO!");
	add_asset_slot("Jerusalem", "zoo");
	add_asset_slot("Jerusalem", "David_tower");
	add_asset_slot("Jerusalem", "Western_wall");
	add_jail_slot("JAIL! Wait 1 turn");

	add_asset_slot("Tel_Aviv", "Hilton");
	int num = rand() % 1000 + 500;
	add_chance_slot("You won the lottery", num);
	add_asset_slot("Tel_Aviv", "Azrieli");
	add_asset_slot("Tel_Aviv", "Habima");
	num = rand() % 200 + 100;
	add_chance_slot("You have to pay the IRS", -num);

	add_asset_slot("Carmiel", "Rocks_park");
	num = rand() % 70 + 30;
	add_chance_slot("Congratulations to your birthday, get a bouquet", num);
	add_asset_slot("Carmiel", "Big");
	add_asset_slot("Carmiel", "Ort_Braude");

	add_asset_slot("Eilat", "Dolpin_reef");
	add_asset_slot("Eilat", "Kings_town");
	add_asset_slot("Eilat", "Ramon_airport");
	add_asset_slot("Eilat", "Almog_beach");
	init_board_image();
}
int Board::size() const
{
	return m_size;
}

void Board::add_go_slot(std::string g_msg)
{
	m_arr[slotindex] = new GO(g_msg);
	slotindex++;
}
void Board::add_asset_slot(std::string city, std::string asset)
{
	m_arr[slotindex] = new Asset(city,asset);
	slotindex++;
}
void Board::add_chance_slot(std::string c_msg, int num)
{
	m_arr[slotindex] = new Chance(c_msg,num);
	slotindex++;
}
void Board::add_jail_slot(std::string j_msg)
{
	m_arr[slotindex] = new Jail(j_msg);
	slotindex++;
}
Slot* Board::operator[](int idx)const
{
	return m_arr[idx];
}
Slot* Board::get_Slot_data(int index) const
{
	return m_arr[index];
}
void write(std::string str, int width)
{//function helper 
		cout << str;
		for (int j = str.length(); j < width; j++)
			cout << " ";
		cout << "|";
}
void Board::showplayers(Player* players)
{//show all he player status.
	for (int i = 0; i < players->get_players_count(); i++)
		write("player name: " + players[i].get_player_name(), breadth);
	cout << endl;
	for (int i = 0; i < players->get_players_count(); i++)
		write("player balance: " + to_string(players[i].get_player_balance()), breadth);
	cout << endl;
	for (int i = 0; i < players->get_players_count(); i++)
		write("player location: " + to_string(players[i].get_player_location()), breadth);
	cout << endl;
	for (int i = 0; i < players->get_players_count(); i++)
		write("is the player in jail?: " + to_string(players[i].get_in_jail()), breadth);
	cout << endl; 
	for (int i = 0; i < players->get_players_count(); i++)
		for (int j = 0; j < breadth +(players->get_players_count()-1); j++)
			cout << "_";
	cout << endl;

}
void Board::play(Player* players)
{//the game is self
	bool flag = true;//the game will continue as long as flag=true
	int stop;
	int index = 0;
	int key;
	while (flag)
	{
		system("CLS");// with the begining of each turn we refresh the display.
		cout << *this;
		this->showplayers(players);
		cout << endl;
		key = NULL;
		cout << "it is " << players[index].get_player_name() << " turn" << endl;
		cout << players[index]<<endl;
		if (players[index].get_in_jail())//if the player is in jail the turn ended
			players[index].set_in_jail();//end we resete the jail flag for next turn.
		std::cout << "To roll the dice (1)" << std::endl;
		std::cout << "To end the game press (2)" << std::endl;
		cin >> key;
		switch (key)
		{
		case 1:
			cout << players[index].get_player_name() << " move from " << players[index].get_player_location();
			players[index].draw_dice();
			cout<< " to " << players[index].get_player_location()<<endl;
			if (this->m_arr[players[index].get_player_location()]->play(&players[index]))//activate the slot properise
				flag = true;
			else
				flag = false;
			break;
		case 2:
			cout << "you choose to end the game "<<endl;
			flag = false;
			break;
		}
		index = (index + 1) % players->get_players_count();//change the pointer to the nex player.
		cout << endl;
		cout << endl;
		std::cout << "to end your turn press any key" << std::endl;
		cin >> stop;//separate turns in the game
		if (stop);
	}
}
void Board::Simulator(Player* players)
{//the game is self
	std::ofstream myfile("results.csv", ios::app);
	players->onsim();
	bool flag = true;//the game will continue as long as flag=true
	int index = 0;
	time_t start_t, end_t;//to calculate the duration of the game
	double diff_t;
	time(&start_t);
	for (int i = 0; i < 3; i++)
		myfile << players[i].get_player_name() << ", ";
	myfile << endl;
	while (flag)
	{
		
		if (players[index].get_in_jail())//if the player is in jail the turn ended
			players[index].set_in_jail();//end we resete the jail flag for next turn.
		players[index].draw_dice();	
		if (this->m_arr[players[index].get_player_location()]->playsim(&players[index],1))//activate the slot properise
				flag = true;
		else
				flag = false;
		index = (index + 1) % players->get_players_count();//change the pointer to the nex player.
		time(&end_t);
		diff_t = difftime(end_t, start_t);
		int min = diff_t / 60;
		int sec = diff_t - min * 60;
		string titel[3];
		
		for (int i = 0; i < 3; i++)
			myfile << players[i].get_player_balance() << ", ";
		myfile << min << ", " << sec;
		myfile << endl;
	}
	myfile.close();//colse the file
}
Board::~Board()
{
	for (int i = 0; i < 18; i++)
		if (m_arr[i] != nullptr)
		{
			delete m_arr[i];
			slotindex--;
		}
	delete[] m_arr;
}

