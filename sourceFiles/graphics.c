// This file contains all the functions that perform the actual drawing to the window
#include "tetris.h"

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
