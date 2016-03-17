/*
 *	Name:	demo.c
 */

#include <ncurses.h>
#include <stdlib.h>

#define INIT_POS 14
#define MAX_LIFE 20

struct player
{
	int	x_pos,
		y_pos,
		health;
};

void		screenInit();
void		mapInit();
struct player 	*playerInit();
void 		handleInput(int , struct player *);
void		playerMove(int , int, struct player *);
void 		checkPosition(int ,int, struct player *);

int main()
{
	struct player *user;
	int input;
	screenInit();
	mapInit();
	
	user = playerInit();
	
	/* game loop */
	while ((input = getch()) != 'q') {
		handleInput(input, user);
	}
		
	endwin();
	return EXIT_SUCCESS;
}

void screenInit()
{
	initscr();
	attron(A_STANDOUT | A_BOLD | A_UNDERLINE);
	mvprintw(0, 35, "**WELCOME TO ROGUE**\n");
	attroff(A_STANDOUT | A_BOLD | A_UNDERLINE);
	noecho();
	refresh();
}

void mapInit()
{
	mvprintw(13,13, "--------");
	mvprintw(14,13, "|......|");
	mvprintw(15,13, "|......|");
	mvprintw(16,13, "|......|");
	mvprintw(17,13, "|......|");
	mvprintw(18,13, "--------");
	
	mvprintw(2,40, "--------");
	mvprintw(3,40, "|......|");
	mvprintw(4,40, "|......|");
	mvprintw(5,40, "|......|");
	mvprintw(6,40, "|......|");
	mvprintw(7,40, "--------");
	
	mvprintw(10,40, "------------");
	mvprintw(11,40, "|..........|");
	mvprintw(12,40, "|..........|");
	mvprintw(13,40, "|..........|");
	mvprintw(14,40, "|..........|");
	mvprintw(15,40, "------------");
}

struct player *playerInit()
{
	struct player *new_player = malloc(sizeof(struct player));
	if (!new_player) {
		perror("Error: Failed to allocate memory for player");
		exit(EXIT_FAILURE);
	}
	
	new_player->x_pos	= INIT_POS;
	new_player->y_pos	= INIT_POS;
	new_player->health	= MAX_LIFE;

	playerMove(INIT_POS, INIT_POS, new_player);
	
	return new_player;
}

void handleInput(int input, struct player *user)
{
	int new_y, new_x;
	
	switch (input) {
		/* move up	*/
		case 'w':
		case 'W':
		case 'i':
		case 'I':
			new_y = user->y_pos - 1; 
			new_x = user->x_pos;
			break;
			
		/* move down	*/	
		case 's':
		case 'S':
		case 'k':
		case 'K':
			new_y = user->y_pos + 1; 
			new_x = user->x_pos;
			break;
			
		/* move left	*/	
		case 'a':
		case 'A':
		case 'j':
		case 'J':
			new_y = user->y_pos; 
			new_x = user->x_pos - 1;
			break;
			
		/* move right	*/	
		case 'd':
		case 'D':
		case 'l':
		case 'L':
			new_y = user->y_pos; 
			new_x = user->x_pos + 1;
			break;
			
		default:
			break;
	}

	checkPosition(new_y, new_x, user);
}

/* collision detection	*/
void checkPosition(int y_pos, int x_pos, struct player *user)
{
	int space;

	switch(mvinch(y_pos, x_pos)) {
		/* if not wall	*/
		case '.':
			playerMove(y_pos, x_pos, user);
			break;
		default:
			move(user->y_pos, user->x_pos);
			break;
	}
}

void playerMove(int y_pos, int x_pos, struct player *user)
{
	mvprintw(user->y_pos, user->x_pos, ".");
	user->y_pos = y_pos;
	user->x_pos = x_pos;
	mvprintw(user->y_pos, user->x_pos, "@");
	move(user->y_pos, user->x_pos);
}