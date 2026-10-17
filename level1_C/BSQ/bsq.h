#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

typedef struct s_data
{
	int		rows;
	int		columns;
	char	empty;
	char	obstacle;
	char	full;
	char	**map;
} t_data;

typedef struct s_bsq
{
	/* data */
} t_bsq;

int 	bsq(t_data *data, FILE *file);
void	data_init(t_data *data);
int		process_file(t_data *data, FILE *file);
int		parse_first_line(t_data *data, const char *line);
int		parse_line(t_data *data, const char *line, int row);
int		save_count_columns(t_data *data, const char *line);
void 	print_map(t_data * data);
void 	free_map(t_data *data);
int		solver(t_data *data);
int		min3(int a, int b, int c);

#endif

/*
		getline

	ssize_t getline(char **lineptr, size_t *n, FILE *stream);

	Parameters
	lineptr	-	pointer to a pointer to the initial buffer or to a null pointer
	n		-	pointer to the size of the initial buffer
	stream	-	valid input stream, opened by fopen

	Return value
	The number of characters stored in the buffer excluding the null terminator.
	On error, returns -1 and sets feof or ferror on stream.

*/
