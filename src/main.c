#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void draw_box(int x1, int x2, int y1, int y2)
{
	for (int x = x1; x <= x2; ++x)
	{
		for (int y = y1; y <= y2; ++y)
		{
			if ((x == x1 && y == y1) /* "corner" case */
				|| (x == x1 && y == y2)
				|| (x == x2 && y == y1)
				|| (x == x2 && y == y2))
			{
				mvprintw(y, x, "+");
			}
			else if (x == x1 || x == x2)
			{
				mvprintw(y, x, "|");
			}
			else if (y == y1 || y == y2)
			{
				mvprintw(y, x, "-");
			}
			else
			{
				mvprintw(y, x, " ");
			}
		}
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
	while (true)
	{
		char c = getch();
		if (c == '\n' && diff > 0 && diff < 6)
		{
			break;
		}
		if (c > '0' && c < '6')
		{
			attron(A_STANDOUT);
			mvprintw(5, 43, "%c", c);
			attroff(A_STANDOUT);
			diff = c - 48;
			draw_boxed_text(9, 8, "Press 'Enter' to confirm.");
		}
		else
		{
			mvprintw(5, 43, " ");
			mvprintw(7, 7, "                              ");
			mvprintw(8, 7, "                              ");
			mvprintw(9, 7, "                              ");
		}
	}
	return diff;
}

int read_guess(int try, int diff)
{
	int digit = 0;
	int current[4] = {10, 10, 10, 10};
	while (true)
	{
		char c = getch();
		if(c >= '0' && c <= '4' + diff && digit < 4)
		{
			mvprintw(8 + try, 16 + digit, "%c", c);
			current[digit] = 0 + c - '0';
			++digit;
		}
		if ((c == 8 || c == 127) && digit > 0)
		{
			current[digit] = 10;
			mvprintw(8 + try, 15 + digit, "_");
			--digit;
		}
		if (c == '\n' && digit == 4)
		{
			break;
		}
	}
	int final = current[3] +
		10 * current[2] + 
		100 * current[1] +
		1000 * current[0];
	return final;
}

int main()
{
	srand(time(NULL));
	initscr();
	keypad(stdscr, TRUE);
	curs_set(0);
	raw();
	noecho();
	clear();
	bool playing = true;
	draw_border();
	while (playing)
	{
		/* read in difficulty */
		int difficulty = get_difficulty();
		draw_box(0, 79, 2, 23);
		draw_boxed_text(62, 5, "Difficulty:  ");
		mvprintw(5, 74, "%d", difficulty);
		draw_box(5, 56, 5, 9);
		mvprintw(6, 6, " I am thinking of a four-digit number. Each digit");
		mvprintw(7, 6, " is between 0 and %d. You have ten guesses.",
			difficulty + 4);
		mvprintw(8, 12, " Press 'Enter' to begin...");
		/* wait for player to start game */
		while (true)
		{
			if (getch() == '\n')
			{
				mvprintw(5, 5,
					"                                                       ");
				mvprintw(6, 5,
					"                                                       ");
				mvprintw(7, 5,
					"                                                       ");
				mvprintw(8, 5,
					"                                                       ");
				mvprintw(9, 5,
					"                                                       ");
				break;
			}
		}
		int tries = 0;	/* current turn */
		int total_score = 0;
		int guess[4] = {10, 10, 10, 10};	/* stores the 4-digit guess */
		int answer[4] =
		{
			rand() % (difficulty + 5),
			rand() % (difficulty + 5),
			rand() % (difficulty + 5),
			rand() % (difficulty + 5)
		};
		mvprintw(6, 5, " Turn | Your guess | My answer | Points ");
		mvprintw(7, 5, "------+------------+-----------+--------");
		for (tries = 0; tries < 10; ++tries)
		{
			mvprintw(8 + tries, 5,
				"  %2d  |    ____    |    ????   |        ", tries + 1);
			int guess_unparsed = read_guess(tries, difficulty);
			guess[0] = guess_unparsed / 1000;
			guess[1] = (guess_unparsed % 1000) / 100;
			guess[2] = (guess_unparsed % 100) / 10;
			guess[3] = guess_unparsed % 10;

			int correct = 0;
			int almost = 0;
			int incorrect = 4;
			/* we add 10 to guesses when they're hit */
			/* we subtract 10 from the code when they're hit */
			/* first check for correct digits */
			for (int i = 0; i < 4; ++i)
			{
				if (guess[i] == answer[i])
				{
					++correct;
					--incorrect;
					guess[i] = guess[i] + 10;
					answer[i] = answer[i] - 10;
				}
			}
			/* then check for almost-correct answers */
			for (int g = 0; g < 4; ++g)
			{
				for (int a = 0; a < 4; ++a)
				{
					if (guess[g] == answer[a])
					{
						++almost;
						--incorrect;
						guess[g] = guess[g] + 10;
						answer[a] = answer[a] - 10;
					}
				}
			}
			int roundscore = 25 * correct + 10 * almost;
			move(8 + tries, 29);
			for (int i = 0; i < correct; ++i)
			{
				printw("+");
			}
			for (int i = 0; i < almost; ++i)
			{
				printw("-");
			}
			for (int i = 0; i < incorrect; ++i)
			{
				printw(".");
			}
			for (int i = 0; i < 4; ++i)
			{
				if (answer[i] < 0)
				{
					answer[i] = answer[i] + 10;
				}
			}
			mvprintw(8 + tries, 38, "%4d", roundscore);
			total_score += roundscore;
		}
	}
	return 0;
}