
#include <ncurses.h>
#include <unistd.h>

#define DELAY 500000
#define MODX 3
#define MODY 2
int main(int argc, char *argv[]) {
	int x = 0, y = 0;//current position of the ball
	int max_y = 0, max_x = 0;//edges of screen
	int next_y = 0, next_x = 0;//where will the ball be next?
	int direction_y = 1 * MODY, direction_x = 1 * MODX;//movement direction left to right
	int ch; //stores user input, checks for breaking char.

	initscr();//make a window, creates global variables such as stdscr behind the scenes
	noecho();//no echoing keypresses
	curs_set(FALSE);//no cursor
	nodelay(stdscr, TRUE);//getch() now working in non-blocking manner, will return ERR if no input
	keypad(stdscr, TRUE); //collect all SPECIAL keys including backspace, delete and arrow keys

	x= COLS/2;//upon initscr() these globals are declared with the size of the whole screen
	y= LINES/2;//ditto

	for(;;){
	getmaxyx(stdscr,max_y, max_x);//need to call often or else resizing the window breaks it
	clear();//Clear the whole screen

	mvprintw(y,x, "DVD");//add to print buffer
	refresh();//refresh the screen to see buffered letters

	usleep(DELAY);//USLEEP counts in microseconds, instead of seconds like SLEEP

	next_x = x + direction_x;
	next_y = y + direction_y;

	if (next_x+2 >= max_x) {//need to offset the right edge by 2 due to the length of buffer
		direction_x = -1 * MODX;//if too big, go left
	} else if (next_x < 0) {
		direction_x = 1 * MODX;//if too big, go left
	}
	x+= direction_x;

	if (next_y >= max_y) {//need to offset the right edge by 2 due to the length of buffer
		direction_y = -1 * MODY;//if too big, go left
	} else if (next_y < 0) {
		direction_y = 1 * MODY;//if too big, go left
	}

	y+= direction_y;

	if ((ch = getch()) == KEY_F(1)){//breaks if F1 is pressed. Any Ascii stuff should work though
		break;
	}


	}//end of infinite loop

	endwin();//put everything back to normal
}
