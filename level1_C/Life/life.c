#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// cc -Wall -Werror -Wextra life.c

int count_neighbors(int r, int c, int height, int width, char board[height][width])
{
	int count = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
			{
				continue;
			}
			int neighbor_r = r + i;
			int neighbor_c = c + j;

            // Boundary check: ensure the neighbor is inside the grid
            if (neighbor_r >= 0 && neighbor_r < height && neighbor_c >= 0 && neighbor_c < width) 
			{
                if (board[neighbor_r][neighbor_c] == 1) // if neighbour alive?
				{
                    count++;
                }
			}
		}
	}
	return count;
}

int main(int argc, char **argv)
{
	if (argc != 4)
		return 1;
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int iterations = atoi(argv[3]);
	if (width <= 0 || height <= 0 || iterations < 0)
		return 1;

	char board[height][width];
	char new_board[height][width];

	// Filling the board with empty cells
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			board[i][j] = 0;
		}
	}

	// Filling the board with stdin config
	char c;
	int pen = 0, col = 0, row = 0;
	ssize_t bytes_read;
	while ((bytes_read = read(STDIN_FILENO, &c, 1)) == 1) 
	{
		if (c == 'w' && row > 0)
			row--;
		else if (c == 's' && row < height - 1)
			row++;
		else if (c == 'a' && col > 0)
			col--;
		else if (c == 'd' && col < width - 1)
			col++;
		else if (c == 'x')
			pen = !pen;

		if (pen)
			board[row][col] = 1;
		//board[row][col] = pen ? 1 : 0;
	}
	if (bytes_read == -1)
		return 1;

	// Simulating a game of life on the board
	for (int i = 0; i < iterations; i++)
	{
		for (row = 0; row < height; row ++)
		{
			for (col = 0; col < width; col++)
			{
				int neighbors = count_neighbors(row, col, height, width, board);

            	if (board[row][col] == 1)
				{
					// Any live cell with < 2 live neighbours dies
            		// Any live cell with 2 or 3 live neighbours lives on to the next generation.
            		// Any live cell with > 3 live neighbours dies
                	new_board[row][col] = (neighbors == 2 || neighbors == 3) ? 1 : 0;  // =2 or =3 -> 1, other 0
				}
				else // Any dead cell with = 3 live neighbours becomes a live cell
                	new_board[row][col] = (neighbors == 3) ? 1 : 0;  // =3 -> 1, other 0
			}
		}
		// Store the state of the last iteration, befor moving to the next
		for (int r = 0; r < height; r++) 
		{
        	for (int c = 0; c < width; c++) 
			{
            	board[r][c] = new_board[r][c];
        	}
		}
	}

    // Print the frame
    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            if (board[row][col] == 1) {
                putchar('0');
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }

	return 0;
}



/*
	read(STDIN_FILENO, &c, 1)

Read text from standard input one character at a time
Returns 1: A character was successfully read and stored in c. The loop continues.
Returns 0: End-of-File (EOF) was reached (e.g., the user pressed Ctrl+D in Linux or the input stream ended).
Returns -1: An error occurred (e.g., the input stream was interrupted).

*/
