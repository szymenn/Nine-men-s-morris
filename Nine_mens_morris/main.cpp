#include "game.h"
#include <cstdlib>
#include <ctime>
#include "linked_list.cpp"

int main(int argc, char* argv[])
{
	srand(time(nullptr));
	linked_list<int> list;
	list.add(5);
	list.add(6);
	list.add(25);
	list.print();
	list.pop();
	list.pop();
	list.print();
	game game1;
	game::print_board();
	game1.start_game();
	return 0;
}
