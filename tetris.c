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

_Bool place_mino(t_element board[21][10], enum type next_mino, tetrimino* in_game) // Calls appropriate place function
{
	_Bool gameover;
	switch(next_mino)
	{
		case 1:
			gameover = place_z(board, in_game);
			break;
		case 2:
			gameover = place_j(board, in_game);
			break;
		case 3:
			gameover = place_i(board, in_game);
			break;
		case 4:
			gameover = place_l(board, in_game);
			break;
		case 5:
			gameover = place_s(board, in_game);
			break;
		case 6:
			gameover = place_o(board, in_game);
			break;
		case 7:
			gameover = place_z(board, in_game);
			break;
			
	}
	
	return gameover;
	
}

_Bool place_z(t_element board[21][10], tetrimino* in_game)
{	
	int gameover = 0;
	
	in_game->mino1 = &board[1][3];
	in_game->mino2 = &board[1][4];
	in_game->c_mino = &board[2][4];
	in_game->mino3 = &board[2][5];
	
	in_game->mino1->color = red;
	in_game->mino2->color = red;
	in_game->mino3->color = red;
	in_game->c_mino->color = red;
	
	in_game->type = Z_mino;
	in_game->color = red;
	
	// Check if there is a piece there already
	if(in_game->mino1->occupied == 0 &&
	   in_game->mino2->occupied == 0 &&
	   in_game->mino3->occupied == 0 &&
	   in_game->c_mino->occupied == 0)
	{
		in_game->mino1->occupied = 1;
		in_game->mino2->occupied = 1;
		in_game->mino3->occupied = 1;
		in_game->c_mino->occupied = 1;
	}
	else
	{
		gameover = 1; // If piece overlaps another, game ends
	}
	   
	
	in_game->position = 1;
	
	return gameover;
	
}

_Bool place_j(t_element board[21][10], tetrimino* in_game)
{
	int gameover = 0;
	
	in_game->mino1 = &board[1][3];
	in_game->mino2 = &board[1][5];
	in_game->c_mino = &board[1][4];
	in_game->mino3 = &board[2][5];
	
	in_game->mino1->color = blue;
	in_game->mino2->color = blue;
	in_game->mino3->color = blue;
	in_game->c_mino->color = blue;
	
	in_game->type = J_mino;
	in_game->color = blue;
	
	// Check if there is a piece there already
	if(in_game->mino1->occupied == 0 &&
	   in_game->mino2->occupied == 0 &&
	   in_game->mino3->occupied == 0 &&
	   in_game->c_mino->occupied == 0)
	{
		in_game->mino1->occupied = 1;
		in_game->mino2->occupied = 1;
		in_game->mino3->occupied = 1;
		in_game->c_mino->occupied = 1;
	}
	else
	{
		gameover = 1;
	}
	
	in_game->position = 1;
	
	return gameover;
	
}

_Bool place_i(t_element board[21][10], tetrimino* in_game)
{
	int gameover = 0;
	
	in_game->mino1 = &board[1][3];
	in_game->mino2 = &board[1][4];
	in_game->c_mino = &board[1][5];
	in_game->mino3 = &board[1][6];
	
	in_game->mino1->color = cyan;
	in_game->mino2->color = cyan;
	in_game->mino3->color = cyan;
	in_game->c_mino->color = cyan;
	
	in_game->type = I_mino;
	in_game->color = cyan;
	
	// Check if there is a piece there already
	if(in_game->mino1->occupied == 0 &&
	   in_game->mino2->occupied == 0 &&
	   in_game->mino3->occupied == 0 &&
	   in_game->c_mino->occupied == 0)
	{
		in_game->mino1->occupied = 1;
		in_game->mino2->occupied = 1;
		in_game->mino3->occupied = 1;
		in_game->c_mino->occupied = 1;
	}
	else
	{
		gameover = 1;
	}
	
	in_game->position = 1;
	
	return gameover;
}

_Bool place_l(t_element board[21][10], tetrimino* in_game)
{
	int gameover = 0;
	
	in_game->mino1 = &board[1][5];
	in_game->mino2 = &board[1][3];
	in_game->c_mino = &board[1][4];
	in_game->mino3 = &board[2][3];
	
	in_game->mino1->color = orange;
	in_game->mino2->color = orange;
	in_game->mino3->color = orange;
	in_game->c_mino->color = orange;
	
	in_game->type = L_mino;
	in_game->color = orange;
	
	// Check if there is a piece there already
	if(in_game->mino1->occupied == 0 &&
	   in_game->mino2->occupied == 0 &&
	   in_game->mino3->occupied == 0 &&
	   in_game->c_mino->occupied == 0)
	{
		in_game->mino1->occupied = 1;
		in_game->mino2->occupied = 1;
		in_game->mino3->occupied = 1;
		in_game->c_mino->occupied = 1;
	}
	else
	{
		gameover = 1;
	}
	
	in_game->position = 1;
	
	return gameover;
}

_Bool place_s(t_element board[21][10], tetrimino* in_game)
{
	int gameover = 0;
	
	in_game->mino1 = &board[1][5];
	in_game->mino2 = &board[1][4];
	in_game->c_mino = &board[2][4];
	in_game->mino3 = &board[2][3];
	
	in_game->mino1->color = green;
	in_game->mino2->color = green;
	in_game->mino3->color = green;
	in_game->c_mino->color = green;
	
	in_game->type = S_mino;
	in_game->color = green;
	
	// Check if there is a piece there already
	if(in_game->mino1->occupied == 0 &&
	   in_game->mino2->occupied == 0 &&
	   in_game->mino3->occupied == 0 &&
	   in_game->c_mino->occupied == 0)
	{
		in_game->mino1->occupied = 1;
		in_game->mino2->occupied = 1;
		in_game->mino3->occupied = 1;
		in_game->c_mino->occupied = 1;
	}
	else
	{
		gameover = 1;
	}
	
	in_game->position = 1;
	
	return gameover;
}

_Bool place_o(t_element board[21][10], tetrimino* in_game)
{
	int gameover = 0;

	in_game->mino1 = &board[1][4];
	in_game->mino2 = &board[1][5];
	in_game->c_mino = &board[2][4];
	in_game->mino3 = &board[2][5];
	
	in_game->mino1->color = yellow;
	in_game->mino2->color = yellow;
	in_game->mino3->color = yellow;
	in_game->c_mino->color = yellow;
	
	in_game->type = O_mino;
	in_game->color = yellow;
	
	// Check if there is a piece there already
	if(in_game->mino1->occupied == 0 &&
	   in_game->mino2->occupied == 0 &&
	   in_game->mino3->occupied == 0 &&
	   in_game->c_mino->occupied == 0)
	{
		in_game->mino1->occupied = 1;
		in_game->mino2->occupied = 1;
		in_game->mino3->occupied = 1;
		in_game->c_mino->occupied = 1;
	}
	else
	{
		gameover = 1;
	}
	
	in_game->position = 1;
	
	return gameover;
}

_Bool place_t(t_element board[21][10], tetrimino* in_game)
{
	int gameover = 0;
	
	in_game->mino1 = &board[1][3];
	in_game->mino2 = &board[2][4];
	in_game->c_mino = &board[1][4];
	in_game->mino3 = &board[1][5];
	
	in_game->mino1->color = purple;
	in_game->mino2->color = purple;
	in_game->mino3->color = purple;
	in_game->c_mino->color = purple;
	
	in_game->type = T_mino;
	in_game->color = purple;
	
	// Check if there is a piece there already
	if(in_game->mino1->occupied == 0 &&
	   in_game->mino2->occupied == 0 &&
	   in_game->mino3->occupied == 0 &&
	   in_game->c_mino->occupied == 0)
	{
		in_game->mino1->occupied = 1;
		in_game->mino2->occupied = 1;
		in_game->mino3->occupied = 1;
		in_game->c_mino->occupied = 1;
	}
	else
	{
		gameover = 1;
	}
	
	in_game->position = 1;
	
	return gameover;
}

void rotate_mino(t_element board[21][10], tetrimino* in_game) // Calls appropriate rotation function
{
	switch(in_game->type)
	{
		case Z_mino:
			rotate_z(board, in_game);
			break;
		case J_mino:
			rotate_j(board, in_game);
			break;
		case I_mino:
			rotate_i(board, in_game);
			break;
		case L_mino:
			rotate_l(board, in_game);
			break;
		case S_mino:
			rotate_s(board, in_game);
			break;
		case O_mino:
			// No rotation for O
			break;
		case T_mino:
			rotate_t(board, in_game);
			break;
	}
}
void rotate_z(t_element board[21][10], tetrimino* in_game)
{
	int mino1_row, mino1_col, mino2_row, mino2_col, mino3_row, mino3_col;
	// Note, c-mino doesn't change position when rotation
	
	switch(in_game->position)
	{
		case 1:
			// Check if you are able to rotate
			if(!(board[mino1_row = in_game->mino1->row][mino1_col = in_game->mino1->col + 2].occupied)&& 
			   !(board[mino3_row = in_game->mino3->row + 1][mino3_col = in_game->mino3->col - 1].occupied))
			{
				// Calculate new Positions
				mino2_row = in_game->mino3->row;
				mino2_col = in_game->mino3->col;
				
				// Clear mino
				clear_mino(board, in_game); 
				
				// Set new positions
				in_game->mino1 = &board[mino1_row][mino1_col];
				in_game->mino2 = &board[mino2_row][mino2_col];
				in_game->mino3 = &board[mino3_row][mino3_col];
				
				color_mino(board, in_game);
				in_game->position = 2;
			}
			break;
		case 2:
			// Check if you are able to rotate
			// Check Bounds
			if((mino3_col = in_game->mino3->col - 1) >= 0)
			{
				// Check if there are other pieces in the way
				if(!(board[mino1_row = in_game->mino1->row + 2][mino1_col = in_game->mino1->col].occupied)&& 
				   !(board[mino3_row = in_game->mino3->row - 1][mino3_col].occupied))
				{
					// Calculate new Positions
					mino2_row = in_game->mino3->row;
					mino2_col = in_game->mino3->col;
				
					// Clear mino
					clear_mino(board, in_game); 
				
					// Set new positions
					in_game->mino1 = &board[mino1_row][mino1_col];
					in_game->mino2 = &board[mino2_row][mino2_col];
					in_game->mino3 = &board[mino3_row][mino3_col];
				
					color_mino(board, in_game);
					in_game->position = 3;
				}
			}
			break;
		case 3:
			// Check if you are able to rotate
			if(!(board[mino1_row = in_game->mino1->row][mino1_col = in_game->mino1->col - 2].occupied)&& 
			   !(board[mino3_row = in_game->mino3->row - 1][mino3_col = in_game->mino3->col + 1].occupied))
			{
				// Calculate new Positions
				mino2_row = in_game->mino3->row;
				mino2_col = in_game->mino3->col;
				
				// Clear mino
				clear_mino(board, in_game); 
				
				// Set new positions
				in_game->mino1 = &board[mino1_row][mino1_col];
				in_game->mino2 = &board[mino2_row][mino2_col];
				in_game->mino3 = &board[mino3_row][mino3_col];
				
				color_mino(board, in_game);
				in_game->position = 4;
			}
			break;
					
		case 4:
			// Check if you are able to rotate.
			if((mino3_col = in_game->mino3->col + 1) <= 9)
			{
				if(!(board[mino1_row = in_game->mino1->row - 2][mino1_col = in_game->mino1->col].occupied)&& 
				   !(board[mino3_row = in_game->mino3->row + 1][mino3_col].occupied))
				{
					// Calculate new Positions
					mino2_row = in_game->mino3->row;
					mino2_col = in_game->mino3->col;
				
					// Clear mino
					clear_mino(board, in_game); 
				
					// Set new positions
					in_game->mino1 = &board[mino1_row][mino1_col];
					in_game->mino2 = &board[mino2_row][mino2_col];
					in_game->mino3 = &board[mino3_row][mino3_col];
				
					color_mino(board, in_game);
					in_game->position = 1;
				}
			}
			break;
	} // Close Switch
}

void rotate_i(t_element board[21][10], tetrimino* in_game) 
{
	int mino1_row, mino1_col, mino2_row, mino2_col, mino3_row, mino3_col, c_mino_row, c_mino_col;
	
	switch(in_game->position)
	{
		case 1:
			// Check if you are able to rotate
			if(!(board[mino1_row = in_game->mino1->row + 2][mino1_col = in_game->mino1->col + 2].occupied) && 
			   !(board[mino2_row = in_game->mino2->row + 1][mino2_col = in_game->mino2->col + 1].occupied) &&
			   !(board[mino3_row = in_game->mino3->row - 1][mino3_col = in_game->mino3->col - 1].occupied))
			{
				
				// Clear mino
				clear_mino(board, in_game); 
				
				// Set new positions
				in_game->mino1 = &board[mino1_row][mino1_col];
				in_game->mino2 = &board[mino2_row][mino2_col];
				in_game->mino3 = &board[mino3_row][mino3_col];
				
				color_mino(board, in_game);
				in_game->position = 2;
			}
			break;
		case 2:
			// Check if you are able to rotate while calculating new position
			if(((mino3_col = in_game->mino3->col - 2) >= 0) && ((mino1_col = in_game->mino1->col + 1) <= 9))
			{
				if(!(board[mino1_row = in_game->mino1->row - 1][mino1_col].occupied) && 
				   !(board[c_mino_row = in_game->c_mino->row + 1][c_mino_col = in_game->c_mino->col - 1].occupied) &&
				   !(board[mino3_row = in_game->mino3->row + 2][mino3_col].occupied))
				{
				
					// Clear mino
					clear_mino(board, in_game); 
				
					// Set new positions
					in_game->mino1 = &board[mino1_row][mino1_col];
					in_game->c_mino = &board[c_mino_row][c_mino_col];
					in_game->mino3 = &board[mino3_row][mino3_col];
				
					color_mino(board, in_game);
					in_game->position = 3;
				}
			}
			break;
		case 3:
			// Check if you are able to rotate
			if(!(board[mino1_row = in_game->mino1->row - 2][mino1_col = in_game->mino1->col - 2].occupied) && 
			   !(board[mino2_row = in_game->mino2->row - 1][mino2_col = in_game->mino2->col - 1].occupied) &&
			   !(board[mino3_row = in_game->mino3->row + 1][mino3_col = in_game->mino3->col + 1].occupied))
			{
				
				// Clear mino
				clear_mino(board, in_game); 
				
				// Set new positions
				in_game->mino1 = &board[mino1_row][mino1_col];
				in_game->mino2 = &board[mino2_row][mino2_col];
				in_game->mino3 = &board[mino3_row][mino3_col];
				
				color_mino(board, in_game);
				in_game->position = 4;
			}
			break;
					
		case 4:
			// Check if you are able to rotate
            if(((mino1_col = in_game->mino1->col - 1) >= 0) && ((mino3_col = in_game->mino3->col + 2) <= 9))
            {
              if(!(board[mino1_row = in_game->mino1->row + 1][mino1_col].occupied) && 
                   !(board[c_mino_row = in_game->c_mino->row - 1][c_mino_col = in_game->c_mino->col + 1].occupied) &&
                   !(board[mino3_row = in_game->mino3->row - 2][mino3_col].occupied))
                {

                  // Clear mino
                  clear_mino(board, in_game); 

                  // Set new positions
                  in_game->mino1 = &board[mino1_row][mino1_col];
                  in_game->c_mino = &board[c_mino_row][c_mino_col];
                  in_game->mino3 = &board[mino3_row][mino3_col];

                  color_mino(board, in_game);
                  in_game->position = 1;
                }
            }
            break;
	}

}

void rotate_s(t_element board[21][10], tetrimino* in_game)
{
	int mino1_row, mino1_col, mino2_row, mino2_col, mino3_row, mino3_col;
	// Note, c-mino doesn't change position when rotation
	
	switch(in_game->position)
	{
		case 1:
			// Check if you are able to rotate
			if(!(board[mino1_row = in_game->mino1->row + 2][mino1_col = in_game->mino1->col].occupied)&& 
			   !(board[mino2_row = in_game->mino2->row + 1][mino2_col = in_game->mino2->col + 1].occupied))
			{
				// Calculate new Positions
				mino3_row = in_game->mino2->row;
				mino3_col = in_game->mino2->col;
				
				// Clear mino
				clear_mino(board, in_game); 
				
				// Set new positions
				in_game->mino1 = &board[mino1_row][mino1_col];
				in_game->mino2 = &board[mino2_row][mino2_col];
				in_game->mino3 = &board[mino3_row][mino3_col];
				
				color_mino(board, in_game);
				in_game->position = 2;
			}
			break;
		case 2:
			// Check if you are able to rotate
    	if((mino1_col = in_game->mino1->col - 2) >= 0)
      	{
			if(!(board[mino1_row = in_game->mino1->row][mino1_col].occupied)&& 
			   !(board[mino2_row = in_game->mino2->row + 1][mino2_col = in_game->mino2->col - 1].occupied))
			{
				// Calculate new Positions
				mino3_row = in_game->mino2->row;
				mino3_col = in_game->mino2->col;
				
				// Clear mino
				clear_mino(board, in_game); 
				
				// Set new positions
				in_game->mino1 = &board[mino1_row][mino1_col];
				in_game->mino2 = &board[mino2_row][mino2_col];
				in_game->mino3 = &board[mino3_row][mino3_col];
				
				color_mino(board, in_game);
				in_game->position = 3;
			}
      }
			break;
		case 3:
			// Check if you are able to rotate
			if(!(board[mino1_row = in_game->mino1->row - 2][mino1_col = in_game->mino1->col].occupied)&& 
			   !(board[mino2_row = in_game->mino2->row - 1][mino2_col = in_game->mino2->col - 1].occupied))
			{
				// Calculate new Positions
				mino3_row = in_game->mino2->row;
				mino3_col = in_game->mino2->col;
				
				// Clear mino
				clear_mino(board, in_game); 
				
				// Set new positions
				in_game->mino1 = &board[mino1_row][mino1_col];
				in_game->mino2 = &board[mino2_row][mino2_col];
				in_game->mino3 = &board[mino3_row][mino3_col];
				
				color_mino(board, in_game);
				in_game->position = 4;
			}
			break;
					
		case 4:
		// Check if you are able to rotate
            if((mino1_col = in_game->mino1->col + 2) <= 9)
            { 
            	if(!(board[mino1_row = in_game->mino1->row][mino1_col].occupied)&& 
                 !(board[mino2_row = in_game->mino2->row - 1][mino2_col = in_game->mino2->col + 1].occupied))
              	{
                	// Calculate new Positions
                	mino3_row = in_game->mino2->row;
                	mino3_col = in_game->mino2->col;

                	// Clear mino
                	clear_mino(board, in_game); 

                	// Set new positions
                	in_game->mino1 = &board[mino1_row][mino1_col];
                	in_game->mino2 = &board[mino2_row][mino2_col];
                	in_game->mino3 = &board[mino3_row][mino3_col];

                	color_mino(board, in_game);
                	in_game->position = 1;
            	}
            }
			break;
	} // Close Switch
}

void rotate_t(t_element board[21][10], tetrimino* in_game)
{
	int mino1_row, mino1_col, mino2_row, mino2_col, mino3_row, mino3_col;

	switch(in_game->position)
	{
		case 1:
    	// Check if you are able to rotate
			if(!(board[mino1_row = in_game->mino1->row - 1][mino1_col = in_game->mino1->col + 1].occupied))
			{
                  // Calculate new positions
                  mino3_row = in_game->mino2->row;
                  mino3_col = in_game->mino2->col;
                  mino2_row = in_game->mino1->row;
                  mino2_col = in_game->mino1->col;
                  
                  // Clear_mino
                  clear_mino(board, in_game);
                  
                  // Set new positions
                  in_game->mino1 = &board[mino1_row][mino1_col];
                  in_game->mino2 = &board[mino2_row][mino2_col];
                  in_game->mino3 = &board[mino3_row][mino3_col];

                  color_mino(board, in_game);
                  in_game->position=2;
            }
				break;
		case 2:
        	// Check if you are able to rotate (must be within boundaries of the board)
        	if((mino1_col = in_game->mino1->col +1 ) <= 9)
        	{
        		if(!board[mino1_row = in_game->mino1->row + 1][mino1_col].occupied)
                {
                	// Calculate new positions
                  	mino2_row=in_game->mino1->row;
                  	mino2_col=in_game->mino1->col;
                  	mino3_row=in_game->mino2->row;
                  	mino3_col=in_game->mino2->col;
                  	
                  	// Clear mino
                  	clear_mino(board, in_game);
                  	
                  	// Set new positions
                  	in_game->mino1 = &board[mino1_row][mino1_col];
                  	in_game->mino2 = &board[mino2_row][mino2_col];
                  	in_game->mino3 = &board[mino3_row][mino3_col];
                  	
                  	color_mino(board, in_game);
					in_game->position=3;
                }
            }
            break;
		case 3:
      		if(!board[mino1_row = in_game->mino1->row + 1][mino1_col = in_game->mino1->col - 1].occupied)
            {
            	// Calculate new positions
              	mino2_row = in_game->mino1->row;
              	mino2_col = in_game->mino1->col;
              	mino3_row = in_game->mino2->row;
              	mino3_col = in_game->mino2->col;
              
              	// Clear mino
              	clear_mino(board, in_game);
              	
              	// Set new positions
                in_game->mino1 = &board[mino1_row][mino1_col];
                in_game->mino2 = &board[mino2_row][mino2_col];
                in_game->mino3 = &board[mino3_row][mino3_col];
              
              	color_mino(board, in_game);
				in_game->position=4;
				break;
            }
		case 4:
			if( ((mino1_col = in_game->mino1->col - 1)>=0) ){
				if(!board[mino1_row = in_game->mino1->row - 1][mino1_col].occupied)
                {
                	// Calculate new positions
                    mino2_row = in_game->mino1->row;
                    mino2_col = in_game->mino1->col;
                    mino3_row = in_game->mino2->row;
                    mino3_col = in_game->mino2->col;
                  	
                  	// Clear mino
                  	clear_mino(board, in_game);
                  	
                    // Set new positions
                    in_game->mino1 = &board[mino1_row][mino1_col];
                    in_game->mino2 = &board[mino2_row][mino2_col];
                    in_game->mino3 = &board[mino3_row][mino3_col];
                  
                  	color_mino(board, in_game);
					in_game->position=1;
                }
            }
				break;
  } // Close switch
}

void rotate_l(t_element board[21][10], tetrimino* in_game)
{
	int mino1_row, mino1_col, mino2_row, mino2_col, mino3_row, mino3_col;

  	switch(in_game->position){
    	case 1:
    		if(!board[mino2_row = in_game->mino2->row - 1][mino2_col = in_game->mino2->col + 1].occupied &&
               !board[mino1_row = in_game->mino1->row + 1][mino1_col = in_game->mino1->col - 1].occupied &&
               !board[mino3_row = in_game->mino3->row - 2][mino3_col = in_game->mino3->col].occupied)
            {
            	// Clear mino
              	clear_mino(board, in_game);
            
              	// Set new positions
                in_game->mino1 = &board[mino1_row][mino1_col];
                in_game->mino2 = &board[mino2_row][mino2_col];
                in_game->mino3 = &board[mino3_row][mino3_col];

                color_mino(board, in_game);
                in_game->position=2;
            }
      		break;
		case 2:
      		if( (mino2_col = in_game->mino2->col + 1) <=9 )
            {
            	if(!board[mino1_row = in_game->mino1->row - 1][mino1_col = in_game->mino1->col - 1].occupied &&
                   !board[mino2_row = in_game->mino2->row + 1][mino2_col].occupied &&
                   !board[mino3_row = in_game->mino3->row][mino3_col = in_game->mino3->col + 2].occupied)
                {
                	// Clear mino
                  	clear_mino(board, in_game);
                    
                    // Set new positions
                    in_game->mino1 = &board[mino1_row][mino1_col];
                    in_game->mino2 = &board[mino2_row][mino2_col];
                    in_game->mino3 = &board[mino3_row][mino3_col];

                    color_mino(board, in_game);
                    in_game->position=3;
                }
            }
      		break;
      	case 3:
      		if(!board[mino1_row = in_game->mino1->row - 1][mino1_col = in_game->mino1->col + 1].occupied &&
               !board[mino2_row = in_game->mino2->row + 1][mino2_col = in_game->mino2->col - 1].occupied &&
               !board[mino3_row = in_game->mino3->row + 2][mino3_col = in_game->mino3->col].occupied)
            {
            	// Clear mino
              	clear_mino(board, in_game);
              
                // Set new positions
                in_game->mino1 = &board[mino1_row][mino1_col];
                in_game->mino2 = &board[mino2_row][mino2_col];
                in_game->mino3 = &board[mino3_row][mino3_col];

                color_mino(board, in_game);
                in_game->position = 4;
            } //close if
      		break;
      	case 4:
      		if( (mino2_col = in_game->mino2->col - 1) >=0 )
            {
            	if(!board[mino1_row = in_game->mino1->row + 1][mino1_col = in_game->mino1->col + 1].occupied &&
                   !board[mino2_row = in_game->mino2->row - 1][mino2_col].occupied &&
                   !board[mino3_row = in_game->mino3->row][mino3_col = in_game->mino3->col - 2].occupied)
                {
                	// Clear mino
                  	clear_mino(board, in_game);
                  
                    // Set new positions
                    in_game->mino1 = &board[mino1_row][mino1_col];
                    in_game->mino2 = &board[mino2_row][mino2_col];
                    in_game->mino3 = &board[mino3_row][mino3_col];

                    color_mino(board, in_game);
                    in_game->position = 1;
                }
            }
    } // close switch
} // close function

void rotate_j(t_element board[21][10], tetrimino* in_game)
{
	int mino1_row, mino1_col, mino2_row, mino2_col, mino3_row, mino3_col;

  	switch(in_game->position){
    	case 1:
    		if(!board[mino1_row = in_game->mino1->row - 1][mino1_col = in_game->mino1->col + 1].occupied &&
               !board[mino2_row = in_game->mino2->row + 1][mino2_col = in_game->mino2->col - 1].occupied &&
               !board[mino3_row = in_game->mino3->row][mino3_col = in_game->mino3->col - 2].occupied)
            {
            	// Clear mino
              	clear_mino(board, in_game);
            
              	// Set new positions
                in_game->mino1 = &board[mino1_row][mino1_col];
                in_game->mino2 = &board[mino2_row][mino2_col];
                in_game->mino3 = &board[mino3_row][mino3_col];

                color_mino(board, in_game);
                in_game->position=2;
            }
      		break;
		case 2:
      		if( (mino1_col = in_game->mino1->col + 1) <=9 )
            {
            	if(!board[mino1_row = in_game->mino1->row + 1][mino1_col].occupied &&
                   !board[mino2_row = in_game->mino2->row - 1][mino2_col = in_game->mino2->col - 1].occupied &&
                   !board[mino3_row = in_game->mino3->row - 2][mino3_col = in_game->mino3->col].occupied)
                {
                	// Clear mino
                  	clear_mino(board, in_game);
                    
                    // Set new positions
                    in_game->mino1 = &board[mino1_row][mino1_col];
                    in_game->mino2 = &board[mino2_row][mino2_col];
                    in_game->mino3 = &board[mino3_row][mino3_col];

                    color_mino(board, in_game);
                    in_game->position=3;
                }
            }
      		break;
      	case 3:
      		if(!board[mino1_row = in_game->mino1->row + 1][mino1_col = in_game->mino1->col - 1].occupied &&
               !board[mino2_row = in_game->mino2->row - 1][mino2_col = in_game->mino2->col + 1].occupied &&
               !board[mino3_row = in_game->mino3->row][mino3_col = in_game->mino3->col + 2].occupied)
            {
            	// Clear mino
              	clear_mino(board, in_game);
              
                // Set new positions
                in_game->mino1 = &board[mino1_row][mino1_col];
                in_game->mino2 = &board[mino2_row][mino2_col];
                in_game->mino3 = &board[mino3_row][mino3_col];

                color_mino(board, in_game);
                in_game->position=4;
            } //close if
      		break;
      	case 4:
      		if( (mino1_col = in_game->mino1->col -1) >=0 )
            {
            	if(!board[mino1_row = in_game->mino1->row - 1][mino1_col].occupied &&
                   !board[mino2_row = in_game->mino2->row + 1][mino2_col = in_game->mino2->col + 1].occupied &&
                   !board[mino3_row = in_game->mino3->row + 2][mino3_col = in_game->mino3->col].occupied)
                {
                	// Clear mino
                  	clear_mino(board, in_game);
                  
                    // Set new positions
                    in_game->mino1 = &board[mino1_row][mino1_col];
                    in_game->mino2 = &board[mino2_row][mino2_col];
                    in_game->mino3 = &board[mino3_row][mino3_col];

                    color_mino(board, in_game);
                    in_game->position=1;
                }
            }
    } // close switch
} // close function

void move_mino_left(t_element board[21][10], tetrimino* in_game)
{
	board_cor mino1, mino2, mino3, c_mino;
  
    // Calculate New positions
    mino1.row = in_game->mino1->row;
    mino1.col = in_game->mino1->col - 1;
    mino2.row = in_game->mino2->row;
    mino2.col = in_game->mino2->col - 1;
    mino3.row = in_game->mino3->row;
    mino3.col = in_game->mino3->col - 1;
    c_mino.row = in_game->c_mino->row;
    c_mino.col = in_game->c_mino->col - 1;
    if((mino1.col >= 0) && (mino2.col >= 0) && (mino3.col >= 0) && (c_mino.col >=0))// Check border first to avoid extra unnecessary checks
    {
        if(check_mino(board, in_game, mino1) && check_mino(board, in_game, mino2) && // Check each mino
        check_mino(board, in_game, mino3) && check_mino(board, in_game, c_mino))
		{
              // Clear board location
              clear_mino(board, in_game);

              // Set New position
              in_game->mino1 = &board[mino1.row][mino1.col];
              in_game->mino2 = &board[mino2.row][mino2.col];
              in_game->mino3 = &board[mino3.row][mino3.col];
              in_game->c_mino = &board[c_mino.row][c_mino.col];

              // Color Board
              color_mino(board, in_game);
		}	
    }
}

void move_mino_right(t_element board[21][10], tetrimino* in_game)
{
	board_cor mino1, mino2, mino3, c_mino;
	
	// Check if the location is occupied and if it goes out of bounds
    // Check Bounds
  
    // Calculate New positions
    mino1.row = in_game->mino1->row;
    mino1.col = in_game->mino1->col + 1;
    mino2.row = in_game->mino2->row;
    mino2.col = in_game->mino2->col + 1;
    mino3.row = in_game->mino3->row;
    mino3.col = in_game->mino3->col + 1;
    c_mino.row = in_game->c_mino->row;
    c_mino.col = in_game->c_mino->col + 1;
    if((mino1.col <= 9) && (mino2.col <= 9) && (mino3.col <= 9) && (c_mino.col <= 9)) // Check border first to avoid extra unnecessary checks
    {
        if(check_mino(board, in_game, mino1) && check_mino(board, in_game, mino2) && // Check each mino
        check_mino(board, in_game, mino3) && check_mino(board, in_game, c_mino))
    
		{
              // Clear board location
              clear_mino(board, in_game);

              // Set New position
              in_game->mino1 = &board[mino1.row][mino1.col];
              in_game->mino2 = &board[mino2.row][mino2.col];
              in_game->mino3 = &board[mino3.row][mino3.col];
              in_game->c_mino = &board[c_mino.row][c_mino.col];

              // Color Board
              color_mino(board, in_game);
		}	
    }
}
               

_Bool move_mino_down(t_element board[21][10], tetrimino* in_game)
{
	_Bool placed;
	board_cor mino1, mino2, mino3, c_mino;
	// Calculate new positions
	mino1.row = in_game->mino1->row + 1;
	mino1.col = in_game->mino1->col;
	mino2.row = in_game->mino2->row + 1;
	mino2.col = in_game->mino2->col;
	mino3.row = in_game->mino3->row + 1;
	mino3.col = in_game->mino3->col;
	c_mino.row = in_game->c_mino->row + 1;
	c_mino.col = in_game->c_mino->col;
	
  	if( check_mino(board, in_game, mino1) && check_mino(board, in_game, mino2) && // Check each mino
        check_mino(board, in_game, mino3) && check_mino(board, in_game, c_mino) &&
       (mino1.row < 21) && (mino2.row < 21) && (mino3.row < 21) && (c_mino.row < 21)) // Check borders. 
  	{
    	// Clear board location
	   	clear_mino(board, in_game);
	   	
	   	// Set New position
	   	in_game->mino1 = &board[mino1.row][mino1.col];
		in_game->mino2 = &board[mino2.row][mino2.col];
		in_game->mino3 = &board[mino3.row][mino3.col];
		in_game->c_mino = &board[c_mino.row][c_mino.col];
      
        // Color Board
      	color_mino(board, in_game);
      
    	placed = 0;
  	}
	else
    {
     	placed = 1; 
    }
	return placed;
}

_Bool check_mino(t_element board[21][10], tetrimino* in_game, board_cor mino)
{
	_Bool result;

	result = !((board[mino.row][mino.col].occupied) && // Check if position is occupied
		 !(mino.row == in_game->mino1->row && mino.col == in_game->mino1->col) &&
         !(mino.row == in_game->mino2->row && mino.col == in_game->mino2->col) && // If it is occupied, its ok if belongs to the same piece
         !(mino.row == in_game->mino3->row && mino.col == in_game->mino3->col) &&
         !(mino.row == in_game->c_mino->row && mino.col == in_game->c_mino->col)) ;
	
	return result;
}
               

void clear_mino(t_element board[21][10], tetrimino* in_game)
{
	in_game->mino1->color = black;
	in_game->mino2->color = black;
	in_game->mino3->color = black;
	in_game->c_mino->color = black;
  
  	in_game->mino1->occupied = 0;
	in_game->mino2->occupied = 0;
	in_game->mino3->occupied = 0;
	in_game->c_mino->occupied = 0;
}



void color_mino(t_element board[21][10], tetrimino* in_game)
{
	enum color current;
	
	current = in_game->color;
	
	board[in_game->mino1->row][in_game->mino1->col].color = current;
	board[in_game->mino2->row][in_game->mino2->col].color = current;
	board[in_game->mino3->row][in_game->mino3->col].color = current;
	board[in_game->c_mino->row][in_game->c_mino->col].color = current;
  
  	in_game->mino1->occupied = 1;
	in_game->mino2->occupied = 1;
	in_game->mino3->occupied = 1;
	in_game->c_mino->occupied = 1;
}
                          
_Bool clear_lines(t_element board[21][10], _Bool* back_to_back, int* score, int* lines_tot, int level)
{
	int row, col, lines;
	_Bool update_score, to_clear;
  	lines = 0;
  	update_score = 0;
  	for(row = 1 ; row <= 20; row++)
    {
      	to_clear = 1;
		for(col = 0; col <= 9; col++)
        {
        	if(!board[row][col].occupied)
           	{
				to_clear = 0;
           	}
        }
        if(to_clear)
        {
         	clear_the_line(board, row);
         	update_score = 1;
            lines++;
        }
    }
  	switch(lines)
  	{
  	    case 1:
  	        *score = *score + (100*level);
  	        break;
  	    case 2:
  	        *score = *score + (300*level);
  	        break;
  	    case 3:
  	        *score = *score + (500*level);
  	        break;
  	}
  	if(*back_to_back)
  	{
  	    if(lines == 4)
  	    {
  	        *score = *score + (1200*level);
  	    }
  	    else
  	    {
  	        back_to_back = 0;
  	    }
  	}
  	else
  	{
  	    if(lines == 4)
  	    {
  	        *score = *score + (800*level);
  	        *back_to_back = 1;
  	    }
  	}

    (*lines_tot) += lines;
  	return update_score;
}

void clear_the_line(t_element board[21][10], int row)
{
  	// Change the row to black
  	int c, r;
  	for(c=0;c<=9;c++){
		board[row][c].color = black;
      	board[row][c].occupied = 0; // There's nothing there now
    }
  	
  	// Shift all the pieces above the cleared line by 1 row (so that the pieces fall down)
  	for(r= row - 1; r >= 0; r--) // For the rows above the cleared row
    {
    	for(c=0;c<=9;c++)
        {
  			if(board[r][c].occupied) // If there is a block
    		{
            	// Color bottom block
              	board[r+1][c].color = board[r][c].color;
                board[r+1][c].occupied = 1;
                
                //Clear top one
              	board[r][c].color = black;
                board[r][c].occupied = 0;
            }
        }
    }
}

void draw_grid(point top_left_cor, point bottom_right_cor)
{
	int i, j;
  	gfx_color(130,130,130); // gray
  	for(i=top_left_cor.x; i<=bottom_right_cor.x; i+=BOX_SIZE)
    {
    	for(j=top_left_cor.y; j<=bottom_right_cor.y; j+=BOX_SIZE)
        {
        	gfx_line(top_left_cor.x,j,bottom_right_cor.x,j); // Draw horizontal lines
        }
        gfx_line(i,top_left_cor.y,i,bottom_right_cor.y); // Draw vertical lines
    }
}

  
void draw_preview(enum type next_mino)
{
    int width, height;
  
    point box_top_left_corner;
  
    box_top_left_corner.x = 13*BOX_SIZE;
    box_top_left_corner.y = 4*BOX_SIZE;
    
    my_gfx_cleararea(box_top_left_corner.x, box_top_left_corner.y, 5*BOX_SIZE, 4*BOX_SIZE); // Clear just the box containing the preview
    
  	gfx_color(130,130,130); //gray
  	gfx_line(box_top_left_corner.x, box_top_left_corner.y, box_top_left_corner.x, box_top_left_corner.y + 4*BOX_SIZE); // left 
  	gfx_line(box_top_left_corner.x + 5*BOX_SIZE, box_top_left_corner.y, box_top_left_corner.x + 5*BOX_SIZE, box_top_left_corner.y + 4*BOX_SIZE); // right 
  	gfx_line(box_top_left_corner.x, box_top_left_corner.y + 4*BOX_SIZE, box_top_left_corner.x + 5*BOX_SIZE, box_top_left_corner.y + 4*BOX_SIZE); // bottom
  	gfx_line(box_top_left_corner.x, box_top_left_corner.y, box_top_left_corner.x + 5*BOX_SIZE, box_top_left_corner.y); //top
  	gfx_text(box_top_left_corner.x, box_top_left_corner.y - BOX_SIZE, "NEXT:"); //next
  
    switch(next_mino)
    {
     	case 1:
		    // Draw Z_mino
		    gfx_color(255,88,88);
		    gfx_fill_rectangle(box_top_left_corner.x + BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 2*BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 2*BOX_SIZE, box_top_left_corner.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 3*BOX_SIZE, box_top_left_corner.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    break;
        case 2:
		    // Draw J_mino
		    gfx_color(60,87,141);
		    gfx_fill_rectangle(box_top_left_corner.x + BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 2*BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 3*BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 3*BOX_SIZE, box_top_left_corner.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    break;
        case 3:
       		// Draw I_mino
		    gfx_color(118,222,243);
		    gfx_fill_rectangle(box_top_left_corner.x + 0.5*BOX_SIZE, box_top_left_corner.y + 1.5*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 1.5*BOX_SIZE, box_top_left_corner.y + 1.5*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 2.5*BOX_SIZE, box_top_left_corner.y + 1.5*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 3.5*BOX_SIZE, box_top_left_corner.y + 1.5*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    break;
        case 4:
       		// Draw L_mino
		    gfx_color(250,132,81);
		    gfx_fill_rectangle(box_top_left_corner.x + BOX_SIZE, box_top_left_corner.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 2*BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 3*BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    break;
        case 5:
		    // Draw S_mino
		    gfx_color(88,166,104);
		    gfx_fill_rectangle(box_top_left_corner.x + BOX_SIZE, box_top_left_corner.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 2*BOX_SIZE, box_top_left_corner.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 2*BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 3*BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    break;
        case 6:
		    // Draw O_mino
		    gfx_color(249,233,130);
		    gfx_fill_rectangle(box_top_left_corner.x + 1.5*BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 2.5*BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 1.5*BOX_SIZE, box_top_left_corner.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 2.5*BOX_SIZE, box_top_left_corner.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    break;
        case 7:
		    // Draw T_mino
		    gfx_color(154,122,191);
		    gfx_fill_rectangle(box_top_left_corner.x + BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 2*BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 2*BOX_SIZE, box_top_left_corner.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    gfx_fill_rectangle(box_top_left_corner.x + 3*BOX_SIZE, box_top_left_corner.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
		    break;
    }
  	gfx_flush();
}

void draw_game(t_element board[21][10], point top_left_cor, point bottom_right_cor)
{
  	int r, c;
    int width, height;
    width = bottom_right_cor.x - top_left_cor.x;
	height = bottom_right_cor.y - top_left_cor.y;
    my_gfx_cleararea( top_left_cor.x, top_left_cor.y, width, height ); // Clear part of the screen
    
    draw_grid(top_left_cor, bottom_right_cor);
    
  	for(r=0; r<=20; r++)
    {
    	for(c=0; c<=9; c++)
        {
        	if(board[r][c].occupied)
            {
                switch(board[r][c].color)
                {
                    case red:
                        gfx_color(255,88,88);
                        gfx_fill_rectangle(top_left_cor.x + BOX_SIZE*c, top_left_cor.y + BOX_SIZE*r,BOX_SIZE,BOX_SIZE);
                        break;
                    case blue:
                        gfx_color(60,87,141);
                        gfx_fill_rectangle(top_left_cor.x + BOX_SIZE*c, top_left_cor.y + BOX_SIZE*r,BOX_SIZE,BOX_SIZE);
                        break;
                    case cyan:
                        gfx_color(118,222,243);
                        gfx_fill_rectangle(top_left_cor.x + BOX_SIZE*c, top_left_cor.y + BOX_SIZE*r,BOX_SIZE,BOX_SIZE);
                        break;
                    case orange:
                        gfx_color(250,132,81);
                        gfx_fill_rectangle(top_left_cor.x + BOX_SIZE*c, top_left_cor.y + BOX_SIZE*r,BOX_SIZE,BOX_SIZE);
                        break;
                    case green:
                        gfx_color(88,166,104);
                        gfx_fill_rectangle(top_left_cor.x + BOX_SIZE*c, top_left_cor.y + BOX_SIZE*r,BOX_SIZE,BOX_SIZE);
                        break;
                    case yellow:
                        gfx_color(249,233,130);
                        gfx_fill_rectangle(top_left_cor.x + BOX_SIZE*c, top_left_cor.y + BOX_SIZE*r,BOX_SIZE,BOX_SIZE);
                        break;
                    case purple:
                        gfx_color(154,122,191);
                        gfx_fill_rectangle(top_left_cor.x + BOX_SIZE*c, top_left_cor.y + BOX_SIZE*r,BOX_SIZE,BOX_SIZE);
                        break;
                } //end switch
            }
        }
    }
    gfx_flush(); // Flush to screen
}

void display_score(int score)
{
    char score_string[20];
    my_gfx_cleararea(0,0,12*BOX_SIZE, 2*BOX_SIZE);
    gfx_color(148,56,92);
    sprintf(score_string, "%d", score);
    gfx_text(2*BOX_SIZE, 1.5*BOX_SIZE, score_string);
}

void display_level(int level)
{
  	my_gfx_cleararea(13*BOX_SIZE, 0, 6*BOX_SIZE, 2*BOX_SIZE);
  	char level_string[20];
  	gfx_color(34,202,51);
  	sprintf(level_string, "LEVEL %d", level);
  	gfx_text(13*BOX_SIZE, 1.5*BOX_SIZE, level_string);
}

_Bool swap(t_element board[21][10], enum type *swap_mino, tetrimino* in_game, _Bool* there_is_swap)
{
    enum type temp_mino;
    _Bool gameover;

    if(*there_is_swap)
    {
      	temp_mino = in_game->type;
        clear_mino(board, in_game); 
     	gameover = place_mino(board, *swap_mino, in_game);
        color_mino(board, in_game);
        *swap_mino = temp_mino;
    }
    else
    {
     	*swap_mino = in_game->type;
        clear_mino(board, in_game); 
        gameover = place_mino(board, get_random_mino(), in_game);
        *there_is_swap = 1;
    }
    return gameover;

}

void draw_hold(_Bool there_is_hold, enum type swap_mino)
{
 	// Draw Box and title
  	point hold_top_left;
  	hold_top_left.x = 13*BOX_SIZE;
    hold_top_left.y = 12*BOX_SIZE;
	my_gfx_cleararea(hold_top_left.x, hold_top_left.y, 5*BOX_SIZE, 4*BOX_SIZE);

  	gfx_color(130,130,130); //gray
  	gfx_line(hold_top_left.x, hold_top_left.y, hold_top_left.x, hold_top_left.y + 4*BOX_SIZE); // left 
  	gfx_line(hold_top_left.x + 5*BOX_SIZE, hold_top_left.y, hold_top_left.x + 5*BOX_SIZE, hold_top_left.y + 4*BOX_SIZE); // right 
  	gfx_line(hold_top_left.x, hold_top_left.y + 4*BOX_SIZE, hold_top_left.x + 5*BOX_SIZE, hold_top_left.y + 4*BOX_SIZE); // bottom
  	gfx_line(hold_top_left.x, hold_top_left.y, hold_top_left.x + 5*BOX_SIZE, hold_top_left.y); //top
  	gfx_text(hold_top_left.x, hold_top_left.y - 0.9*BOX_SIZE, "HOLD:"); //hold:
  	
	if(there_is_hold)
    {
    	// draw what is in swap_mino
        switch(swap_mino)
        {
            case 1:
                // Draw Z_mino
                gfx_color(255,88,88);
                gfx_fill_rectangle(hold_top_left.x + BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 2*BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 2*BOX_SIZE, hold_top_left.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 3*BOX_SIZE, hold_top_left.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                break;
            case 2:
                // Draw J_mino
                gfx_color(60,87,141);
                gfx_fill_rectangle(hold_top_left.x + BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 2*BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 3*BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 3*BOX_SIZE, hold_top_left.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                break;
            case 3:
                // Draw I_mino
                gfx_color(118,222,243);
                gfx_fill_rectangle(hold_top_left.x + 0.5*BOX_SIZE, hold_top_left.y + 1.5*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 1.5*BOX_SIZE, hold_top_left.y + 1.5*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 2.5*BOX_SIZE, hold_top_left.y + 1.5*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 3.5*BOX_SIZE, hold_top_left.y + 1.5*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                break;
            case 4:
                // Draw L_mino
                gfx_color(250,132,81);
                gfx_fill_rectangle(hold_top_left.x + BOX_SIZE, hold_top_left.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 2*BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 3*BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                break;
            case 5:
                // Draw S_mino
                gfx_color(88,166,104);
                gfx_fill_rectangle(hold_top_left.x + BOX_SIZE, hold_top_left.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 2*BOX_SIZE, hold_top_left.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 2*BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 3*BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                break;
            case 6:
                // Draw O_mino
                gfx_color(249,233,130);
                gfx_fill_rectangle(hold_top_left.x + 1.5*BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 2.5*BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 1.5*BOX_SIZE, hold_top_left.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 2.5*BOX_SIZE, hold_top_left.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                break;
            case 7:
                // Draw T_mino
                gfx_color(154,122,191);
                gfx_fill_rectangle(hold_top_left.x + BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 2*BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 2*BOX_SIZE, hold_top_left.y + 2*BOX_SIZE, BOX_SIZE, BOX_SIZE);
                gfx_fill_rectangle(hold_top_left.x + 3*BOX_SIZE, hold_top_left.y + BOX_SIZE, BOX_SIZE, BOX_SIZE);
                break;
          } // close switch
          gfx_flush();
    }
}

void my_gfx_cleararea(int x, int y, int w, int h)
{
   
    gfx_color(0, 0, 0);
    gfx_fill_rectangle(x, y, w, h);
    
    return;
}
