/*
 *	Name:	demo.c
 */

#include <ncurses.h>
#include <stdlib.h>

#define INIT_POS 14
#define MAX_LIFE 20

struct room
{
	int	x_pos,
		y_pos,
		height,
		width;
};

struct player
{
	int	x_pos,
		y_pos,
		health;
};

void		screenInit();
struct room 	**mapInit();
struct room	*roomInit(int, int, int, int);
void		drawRoom();
struct player 	*playerInit();
void 		handleInput(int , struct player *);
void		playerMove(int , int, struct player *);
void 		checkPosition(int ,int, struct player *);

int main()
{
	struct player	*user;
	int		input;

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

struct room **mapInit()
{
	struct room **rooms = malloc(sizeof(struct room) * 6);
	if (!rooms) 
		exit(EXIT_FAILURE);
	
	rooms[0] = roomInit(13, 13, 6, 8);
	drawRoom(rooms[0]);
	
	rooms[1] = roomInit(2, 40, 6, 8);
	drawRoom(rooms[1]);
	
	rooms[2] = roomInit(10, 40, 6, 12);
	drawRoom(rooms[2]);
	
	return rooms;
}

struct room *roomInit(int y_pos, int x_pos, int height, int width)
{
	struct room *new_room = malloc(sizeof(struct room));
	if (!new_room)
		exit(EXIT_FAILURE);
	
	new_room->y_pos = y_pos;
	new_room->x_pos = x_pos;
	new_room->height = height;
	new_room->width = width;
	
	return new_room;
}

void drawRoom(struct room *room)
{
	int	x,
		y;

	/* draw top and bottom	*/
	for (x = room->x_pos; x < room->x_pos + room->width; x++) {
		mvprintw(room->y_pos, x, "-");			/* top */
		mvprintw(room->y_pos + room->height, x, "-");	/* bottom */
	}

	/* draw the floor */
	for (y = room->y_pos + 1; y < room->y_pos + room->height; y++) {
		mvprintw(y, room->x_pos, "|"); 			/* left wall */
		mvprintw(y,
			 room->x_pos  + room->width - 1, "|"); 	/* right wall */
		
		for (x = room->x_pos + 1;
			x < room->x_pos + room->width - 1; x++) {
			mvprintw(y, x, ".");			/* floor */
		}
	}
}

struct player *playerInit()
{
	struct player *new_player = malloc(sizeof(struct player));
	if (!new_player)
		exit(EXIT_FAILURE);
	
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