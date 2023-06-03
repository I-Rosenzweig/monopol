#define  _CRTDBG_MAP_ALLOC
#include "Slot.h"
#include"Board.h"
#include "Player.h"
#include <string>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

void test1()
{//testing the slot
	//Slot A;
	//cout << A.get_name() << endl;
	Asset A1;
	//cout << A.get_count()<<endl;
	Asset A2("haifa", "zoo");
	cout << A1.get_city_name() << " 2 " << A1.get_name() << " 3 " << A1.get_type() << " 4 " << A1.get_price() << " 5 " << A1.get_rent() << " 6 " << A1.get_is_taken() << " 7 " << endl;
	//cout << A.get_count() << endl;
	cout << A2.get_city_name() << " " << A2.get_name() << " " << A2.get_price() << " " << A2.get_is_taken() << " " << endl;
	//cout << A.get_count()<<endl;
	GO g1;
	cout << g1.get_name() << " " << g1.get_count() << " " << g1.get_msg() << endl;
	Jail j1;
	Chance c1("100", 100);
}
void test2()
{//testing the board and player
	Board monopoly;
	cout << monopoly;
	Player a1("itai", &monopoly, 350);
	//cout << "player id: " << a1.get_player_id() << endl << "player name: " << a1.get_player_name() << endl << "player balance: " << a1.get_player_balance() << endl << "player location: " << a1.get_player_location() << endl << "in jail? " << a1.get_in_jail() << endl;
	a1.showplayer();
	Player a2("nitzan", &monopoly,999);
	a2.showplayer();
	if (a2.set_player_balance(-1000));
	else cout << "do something else." << endl;
	a2.showplayer();
	cout<<a2.set_player_location(6)<<endl;
	a2.showplayer();
	a1.set_in_jail();
	a1.showplayer();
	a1.set_in_jail();
	a1.showplayer();
	Asset A1;
	Asset A3;
	a1.add_asset(&A1);
	a1.showplayer();
	a2.add_asset(&A1);
	a1.sell_asset();
	a1.showplayer();
	Player a3("yael", &monopoly,1000);
	a3.add_asset(&A3);
	cout << a3.get_Asset_list();
	Asset A2;
	A2.play(&a1);
	A2.play(&a2);
	A2.play(&a3);
}


void test3()
{//simulator to find problems in the code.
	time_t start_t, end_t;//to calculate the duration of the game
	double diff_t;
	time(&start_t);
	Board monopoly;
	Player players[3] = { Player("itai",&monopoly, 350),Player("nitzan",&monopoly, 350),Player("yael",&monopoly, 350) };
	monopoly.Simulator(players);
	time(&end_t);
	diff_t = difftime(end_t, start_t);
	int min = diff_t / 60;
	int sec = diff_t - min * 60;
	cout << "the game took " << min << " minutes and " << sec << "seconds" << endl;
}

void playmonopoly()
{//the game 
	time_t start_t, end_t;//to calculate the duration of the game
	double diff_t;
	time(&start_t);
	Board monopoly;
	Player players[3] = { Player("itai",&monopoly, 350),Player("nitzan",&monopoly, 350),Player("yael",&monopoly, 350) };
	monopoly.play(players);
	time(&end_t);
	diff_t = difftime(end_t, start_t);
	int min = diff_t / 60;
	int sec = diff_t - min * 60;
	cout << "the game took " << min << " minutes and " << sec << "seconds" << endl;
}
int main()
{
	//test1();	
	//test2();
	//test3();
	playmonopoly();
	cout << "Leaks: " << _CrtDumpMemoryLeaks() << endl;
	return 1;
}