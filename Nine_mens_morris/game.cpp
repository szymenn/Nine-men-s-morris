#include "game.h"
#include <cstdio>
game::game()
= default;

void game::print_state()
{
	printf("A ------- B ------- C\n|         |         |\n|  D ---- E ---- F  |\n|  |      |      |  |\n");
	printf("|  |  G-- H --I  |  |\n|  |  |       |  |  |\nJ--K--L       M--N--O\n|  |  |       |  |  |\n");
	printf("|  |  P-- Q --R  |  |\n|  |      |      |  |\n|  S ---- T ---- U  |\n|         |         |\n");
	printf("V ------- W ------- X");
}


