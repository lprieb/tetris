/* This is an ellaboration of tetris from scratch. It makes use of the gfx library developed by Prof. Doug Thain and
 * modified by Prof. Ramzi Bualuan
 * This tetris implementation was developed by Luis Prieb (lprieb@nd.edu) and Emily Anne Park (epark3@nd.edu)
 * Created on Dec 13, 2015
 * Last Updated Jan 15, 2016
 */


#include "gfx5.h"
#include "tetris.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>


int main(void)
{
	// Declare Variables
	t_element board[21][10];
	tetrimino in_game;
	
	// Seed Random Number generator
	srand(time(NULL));

	initialize_board(board);
	manage_game(board, &in_game);
}

enum type get_random_mino()
{
	int i;	
	
	return (rand() % 7 + 1); // gets casted to an enum type
}

void initialize_board(t_element board[21][10])
{
	int row, col;
	
	for(row = 0; row < 21; row++)
	{
		for(col = 0; col < 10; col++)
		{
			board[row][col].moving = 0;
			board[row][col].color = black;
			board[row][col].row = row;
			board[row][col].col = col;
			board[row][col].occupied = 0;	
		}
	}
}

void manage_game(t_element board[21][10], tetrimino* in_game)
{
	_Bool gameover, placed, back_to_back, to_update_score, there_is_swap, quit;
	int input, score, x_size, y_size, level, lines;
	struct timeval start, current;
    double time_dif_max, temp_time_dif_max, time_diff, pause_temp_time;
  	point top_left_cor, bottom_right_cor;
    enum type swap_mino = 0;
	enum type next_mino = get_random_mino();
	in_game->type = get_random_mino();
	
	gameover = 0;
	lines = 0;
	score = 0;
	back_to_back = 0;
	to_update_score = 0;
    level =  1;
    there_is_swap = 0; // Initially there is not piece to swap with;
	quit = 0;
	pause_temp_time = 0;
  
    //Initialize screen
    x_size = 21*BOX_SIZE; 
    y_size = 25*BOX_SIZE;
	gfx_open(x_size, y_size, "Tetris");
    gfx_changefont(FONT); // Font can be changed if necessary
    gfx_clear(); // Clear screen
	
	// Define coordinates for board
    top_left_cor.x = 2*BOX_SIZE;
    top_left_cor.y = 2*BOX_SIZE;
    bottom_right_cor.x = 12*BOX_SIZE;
    bottom_right_cor.y = 23*BOX_SIZE;
    
    // Prepare for the game
	draw_grid(top_left_cor, bottom_right_cor);
    draw_hold(there_is_swap, swap_mino);
	display_score(score);
  	display_level(level);
    time_dif_max = 1000.0; // in ms
						   // This variable defines the level's natural speed at moving the piece down
    temp_time_dif_max = time_dif_max; // The temp_time... will be the one used in the actual game movement
                                      // The temp_time... can change if the user presses soft-drop or hard-drop
  
	while(!gameover && !quit)
	{
		gameover = place_mino(board, next_mino, in_game);
		next_mino = get_random_mino();
        draw_preview(next_mino);
        draw_game(board, top_left_cor, bottom_right_cor);
		placed = 0; // variable to determine if the piece has been placed and the next piece needs to processed
		gettimeofday(&start,NULL);
		gettimeofday(&current, NULL); // initialize value to avoid using without initialization
		temp_time_dif_max = time_dif_max;
		while(!placed && !gameover && !quit)
		{
			switch(gfx_event_waiting())
			{
				case 0: // Catches mouse click and does nothing
					break;
				case 1: // In case of key press
				    input = gfx_wait();
				    if(input == 'R') // Maps to up-arrow in keyboard
				    {
					    rotate_mino(board, in_game);
                      	draw_game(board, top_left_cor, bottom_right_cor);
				    }
				    else if(input == 'Q') // Maps to left-arrow
				    {
					    move_mino_left(board, in_game);
                        draw_game(board, top_left_cor, bottom_right_cor);
				    }
				    else if(input == 'S') // Maps to right-arrow
				    {
					    move_mino_right(board, in_game);
                        draw_game(board, top_left_cor, bottom_right_cor);
				    }
				    else if(input == 'T') // Maps to down_arrow
				    {
					    temp_time_dif_max = 50;
				    }
				    else if(input == ' ') // If you hit space
				    {
				        temp_time_dif_max = 0;
				    }
                    else if(input == 'z') // This swaps the tetrimino
                    {
                     	gameover = swap(board, &swap_mino, in_game, &there_is_swap);
                     	draw_game(board, top_left_cor, bottom_right_cor);
                        draw_hold(there_is_swap, swap_mino);
                    }
                    else if(input == 'p')
                    {
                      	pause_temp_time += 1000*(current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec)/1000.0; // Saves the time that has transitioned
																															// Prevents player from cheating by constantly pressing pause
                        gfx_color(255,255,255); // white
                        gfx_text(5.5*BOX_SIZE, 12*BOX_SIZE, "PAUSE");
						gfx_wait(); // catches release of key
                    	while(gfx_wait() != 'p')
                        ; // Do nothing, just wait
						draw_game(board, top_left_cor, bottom_right_cor);
                        gettimeofday(&start, NULL); // Get new reference point after pause ends
                    }
                    else if(input == 'q')
                    {
                    	quit = 1;
                    }
				    break;
				case 2: // in case of key release
				    input = gfx_wait();
				    if(input == 'T') // Releasing key stops soft-drop
				    {
				        temp_time_dif_max = time_dif_max;
				    }
				    break;
				default: // If anything else is pressed it catches the event
				    gfx_wait();
				    break;
			}
		
		    gettimeofday(&current, NULL);
		    time_diff = 1000*(current.tv_sec - start.tv_sec) + (current.tv_usec - start.tv_usec)/1000.0 + pause_temp_time ; // in ms
																															// measures how much time has passed since piece last moved down
		    
		    if(time_diff>= temp_time_dif_max)
		    {
			    placed = move_mino_down(board, in_game);
                draw_game(board, top_left_cor, bottom_right_cor);
                gettimeofday(&start, NULL);
                pause_temp_time = 0;
		    }
		}
		
		// Perform checks after piece has been placed
	    if(!gameover)
        {
       		to_update_score = clear_lines(board, &back_to_back, &score, &lines, level); // Checks and clear lines and updates score database
       		if(to_update_score)
       		{
       		    to_update_score = 0;
       		    display_score(score); // new score is displayed
       		}
       		
        }

        if((lines >= 10) && (level < 11))
        {
             	level++;
             	display_level(level);
                lines = 0;
                if(level <= 10)
                {
                	time_dif_max -= 100;
                }
                else
                {
                 	time_dif_max = 50;  // time between every move down of piece will decrease by 100 ms until you reach lvl 10
										// At lvl 10 time between every piece move down is just set to 50ms
                }
        }
	} // End while. Game Ends

    while(!quit) // When game ends, display gameover and wait for user to press q
    {
    	gfx_color(255,255,255);
    	gfx_text(4.7*BOX_SIZE, 12*BOX_SIZE, "GAMEOVER");
        if(gfx_wait() == 'q')
        {
            quit = 1;
        }
    }
}

