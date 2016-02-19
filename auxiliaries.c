// This files contain additional functions that help perform other actions in the game

#include "tetris.h"

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
