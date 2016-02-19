// This file includes all the functions the perform all the placing of the tetriminos on the board. 
#include "tetris.h"

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
			gameover = place_t(board, in_game);
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
