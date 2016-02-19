/* This is an ellaboration of tetris from scratch. It makes use of the gfx library developed by Prof. Doug Thain and
 * modified by Prof. Ramzi Bualuan
 * This tetris implementation was developed by Luis Prieb (lprieb@nd.edu) and Emily Anne Park (epark3@nd.edu)
 * Created on Dec 13, 2015
 * Last Updated Jan 19, 2016
 */

// Includes
#include "gfx5.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

// MACROS
#define BOX_SIZE 20 // block size
#define FONT "-sony-fixed-medium-r-normal--24-230-75-75-c-120-jisx0201.1976-0" // Change this font if necessary

// Global Enum
enum color {black, red, blue, cyan, orange, green, yellow, purple};
enum type {Z_mino = 1, J_mino, I_mino, L_mino, S_mino, O_mino, T_mino}; // Colors correspond to their type in number
																		// Z_mino is red, J_mino is blue, etc...

//Global Struct
typedef struct // defines a square in the tetris board
{
	_Bool moving;
	enum color color;
	_Bool occupied;
	int row;
	int col;
}t_element; 


typedef struct // defines a moving tetrimino 
{
	t_element *c_mino; // central mino for rotation
	t_element *mino1;
	t_element *mino2;
	t_element *mino3;
	int position;
	enum type type;
	enum color color;
}tetrimino;

typedef struct // defines a point given x and y coordinates
{
 	int x;
    int y;
}point;

typedef struct // defines square coordinate on board
{
	int row;
	int col;
}board_cor;


// Prototypes
enum type get_random_mino(); // function to create the random minos that will be played in the game
void initialize_board(t_element board[21][10]); // sets default values for the tetris board
void manage_game(t_element board[21][10], tetrimino* in_game); // Function that runs th game
_Bool place_mino(t_element board[21][10], enum type next_mino, tetrimino* in_game); // Calls appropriate function to place tetrimino at the top
																											  // Returns true if tetrimino was placed succesfully
_Bool place_z(t_element board[21][10], tetrimino* in_game); // Functions that place a specific tetrimino
_Bool place_j(t_element board[21][10], tetrimino* in_game); 
_Bool place_i(t_element board[21][10], tetrimino* in_game);
_Bool place_l(t_element board[21][10], tetrimino* in_game);
_Bool place_s(t_element board[21][10], tetrimino* in_game);
_Bool place_o(t_element board[21][10], tetrimino* in_game);
_Bool place_t(t_element board[21][10], tetrimino* in_game);
void rotate_mino(t_element board[21][10], tetrimino* in_game);	// Calls appropriate function to rotate functions
void rotate_z(t_element board[21][10], tetrimino* in_game);
void rotate_i(t_element board[21][10], tetrimino* in_game);
void rotate_s(t_element board[21][10], tetrimino* in_game);
void rotate_l(t_element board[21][10], tetrimino* in_game);
void rotate_j(t_element board[21][10], tetrimino* in_game);
void rotate_t(t_element board[21][10], tetrimino* in_game);
void clear_mino(t_element board[21][10], tetrimino* in_game); // Clears the tetrimino from the screen when tetrimino is rotated or placed in hold
void color_mino(t_element board[21][10], tetrimino* in_game);
void move_mino_left(t_element board[21][10], tetrimino* in_game);
void move_mino_right(t_element board[21][10], tetrimino* in_game);
_Bool check_mino(t_element board[21][10], tetrimino* in_game, board_cor mino);
_Bool clear_lines(t_element board[21][10], _Bool* back_to_back, int* score, int* lines_tot, int level); // Checks if a line has been filled
void clear_the_line(t_element board[21][10], int row); // Dissapeares the line when a line has been filled
void draw_grid(point top_left_cor, point bottom_right_cor); // Draws the grid  behind the game to help with visual ques
void draw_game(t_element board[21][10], point top_left_cor, point bottom_right_cor); // Draws all the tetriminos on the board
void draw_preview(enum type next_mino); // Draws the preview of the upcoming tetrimino
_Bool move_mino_down(t_element board[21][10], tetrimino* in_game); 
void display_score(int score);
void display_level(int level);
_Bool swap(t_element board[21][10], enum type *swap_mino, tetrimino* in_game, _Bool* there_is_swap); // Swaps current tetrimino with the one on hold
																								     // If there is no mino in hold, it will just store the tetrimino
void draw_hold(_Bool there_is_hold, enum type swap_mino); // Draws the tetrimino on the hold square
void my_gfx_cleararea(int x, int y, int w, int h); // the gfx library's gfx_cleararea() function was not working properly, so made our own

