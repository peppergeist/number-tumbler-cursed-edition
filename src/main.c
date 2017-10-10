#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void draw_box(int x1, int x2, int y1, int y2)
{
	mvprintw(y1, x1, "+");
	mvprintw(y1, x2, "+");
	mvprintw(y2, x1, "+");
	mvprintw(y2, x2, "+");
	for (int i = x1 + 1; i < x2; ++i)
	{
		mvprintw(y1, i, "-");
		mvprintw(y2, i, "-");
	}
	for (int j = y1 + 1; j < y2; ++j)
	{
		mvprintw(j, x1, "|");
		mvprintw(j, x2, "|");
	}
}

void draw_boxed_text(int x, int y, char* str)
{
	draw_box(x - 2, x + strlen(str) + 1, y - 1, y + 1);
	mvprintw(y, x, str);
}

void draw_border()
{
	draw_box(0, 79, 0, 2);
	draw_box(0, 79, 2, 23);
	mvprintw(1, 25, "NUMBER TUMBLER - CURSED EDITION");
	refresh();
}

int get_difficulty()
{
	int diff = 0;
	draw_boxed_text(5, 5, "Enter a game difficulty, from 1 - 5: [ ]");
	while (diff < 1 || diff > 5)
	{
		char c = getch();
		if (c > '0' && c < '6')
		{
			attron(A_STANDOUT);
			mvprintw(5, 43, "%c", c);
			attroff(A_STANDOUT);
		}
	}
	return diff;
}

int main()
{
	srand(time(NULL));
	initscr();
	keypad(stdscr, TRUE);
	raw();
	curs_set(0);
	noecho();
	clear();
	bool playing = true;
	draw_border();
	while (playing)
	{
		int difficulty = get_difficulty();
	}
	return 0;
}