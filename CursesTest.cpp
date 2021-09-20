#include <curses.h>
#include <menu.h>
#include <form.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

char *choices[] = {
    "CODIFICACAO BINARIA",
    "CODIFICACAO MANCHESTER",
    "CODIFICACAO BIPOLAR",
    "Sair",
};
char *descriptions[] = {
    "Transmitir codificacao de bits em NRZ.",
    "Transmitir clock junto com os dados.",
    "Transmitir bits 1 com dois niveis +V e -V.",
    "Fechar o programa.",
};

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

int main()
{	ITEM **my_items;
	int c;				
	MENU *my_menu;
	int n_choices, i;
	ITEM *cur_item;
    WINDOW *my_menu_win;
	
	
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	
	n_choices = ARRAY_SIZE(choices);
	my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

	for(i = 0; i < n_choices; ++i)
	        my_items[i] = new_item(choices[i], descriptions[i]);
	my_items[n_choices] = (ITEM *)NULL;

	my_menu = new_menu((ITEM **)my_items);

    /* Create the window to be associated with the menu */
    int menu_width = 72;
    my_menu_win = newwin(8, menu_width, 4, 4);
    keypad(my_menu_win, TRUE);

	/* Set main window and sub window */
    set_menu_win(my_menu, my_menu_win);
    set_menu_sub(my_menu, derwin(my_menu_win, 4, menu_width-2, 3, 1));

	/* Set menu mark to the string " * " */
    set_menu_mark(my_menu, " * ");

	/* Print a border around the main window and print a title */
    box(my_menu_win, 0, 0);
	print_in_middle(my_menu_win, 1, 0, menu_width, "Simulacao Camada Fisica", COLOR_PAIR(1));
	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, menu_width-2);
	mvwaddch(my_menu_win, 2, menu_width-1, ACS_RTEE);

	mvprintw(LINES - 2, 0, "F1 to Exit");
	refresh();

	post_menu(my_menu);
	wrefresh(my_menu_win);
	refresh();

	while((c = getch()) != KEY_F(1))
	{   
        int exit = 0;
        switch(c)
	    {	case KEY_DOWN:
		        menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
            case 10:
                exit = 1;
                break; 
		}
        wrefresh(my_menu_win);
        if (exit) break;
	}	

    ITEM *cur;
    cur = current_item(my_menu);
    short index = cur->index;
    
    const char* name = item_name(cur);
	mvprintw(LINES - 5, 0, name);
	mvprintw(LINES - 4, 0, "Opa %d", index);
    getch();


	free_item(my_items[0]);
	free_item(my_items[1]);
	free_menu(my_menu);
	endwin();
}


int forms() {	
    FIELD *field[3];
	FORM  *my_form;
	int ch;
	
	/* Initialize curses */
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/* Initialize the fields */
    // new_field(int height, int width, int toprow, int leftcol, int offscreen, int nbuffers);
	field[0] = new_field(1, 20, 4, 18, 0, 0);
	field[1] = new_field(1, 20, 6, 18, 0, 0);
	field[2] = NULL;

	/* Set field options */
	set_field_back(field[0], A_UNDERLINE); 	/* Print a line for the option 	*/
	field_opts_off(field[0], O_AUTOSKIP);  	/* Don't go to next field when this */
						/* Field is filled up 		*/
	set_field_back(field[1], A_UNDERLINE); 
	field_opts_off(field[1], O_AUTOSKIP);

	/* Create the form and post it */
	my_form = new_form(field);
	post_form(my_form);
	refresh();
	
	mvprintw(4, 10, "Value 1:");
	mvprintw(6, 10, "Value 2:");
	refresh();

	/* Loop through to get user requests */
	while((ch = getch()) != KEY_F(1))
	{	switch(ch)
		{	case KEY_DOWN:
				/* Go to next field */
				form_driver(my_form, REQ_NEXT_FIELD);
				/* Go to the end of the present buffer */
				/* Leaves nicely at the last character */
				form_driver(my_form, REQ_END_LINE);
				break;
			case KEY_UP:
				/* Go to previous field */
				form_driver(my_form, REQ_PREV_FIELD);
				form_driver(my_form, REQ_END_LINE);
				break;
            case KEY_LEFT:
                form_driver(my_form, REQ_PREV_CHAR);
                break;
            case KEY_RIGHT:
                form_driver(my_form, REQ_NEXT_CHAR);
                break;
            case KEY_BACKSPACE:
                form_driver(my_form, REQ_DEL_PREV);
                break;
			default:
				/* If this is a normal character, it gets */
				/* Printed				  */	
				form_driver(my_form, ch);
				break;
		}
	}

	/* Un post form and free the memory */
	unpost_form(my_form);
	free_form(my_form);
	free_field(field[0]);
	free_field(field[1]); 

	endwin();
	return 0;
}
