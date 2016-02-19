// These file includes the functions that perform the movements of the tetriminos
#include "tetris.h"

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

_Bool check_mino(t_element board[21][10], tetrimino* in_game, board_cor mino) // Checks a partiluar mino of a tetrimino to see if it is allowed to move in the desired direction.
{
	_Bool result;

	result = !((board[mino.row][mino.col].occupied) && // Check if position is occupied
		 !(mino.row == in_game->mino1->row && mino.col == in_game->mino1->col) &&
         !(mino.row == in_game->mino2->row && mino.col == in_game->mino2->col) && // If it is occupied, its ok if belongs to the same piece
         !(mino.row == in_game->mino3->row && mino.col == in_game->mino3->col) &&
         !(mino.row == in_game->c_mino->row && mino.col == in_game->c_mino->col)) ;
	
	return result;
}
