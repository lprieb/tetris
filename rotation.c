// This file includes all the functions that rotate the tetriminos

#include "tetris.h"

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
