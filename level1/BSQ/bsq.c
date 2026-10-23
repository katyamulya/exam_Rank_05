
#include "bsq.h"

/*
1 -> true
0 -> false

if (!smth) -> print_err
*/

// cc -Wall -Werror -Wextra bsq.c

/* Free map */
static void free_map(t_data *d)
{
    if (!d->map)
        return;
    for (int i = 0; i < d->rows; i++)
    {
        free(d->map[i]);
    }
    free(d->map);
    d->map = NULL;
}

/* Print map */
static void print_map(t_data * data)
{
	for (int i = 0; i < data->rows; i++)
	{
		fprintf(stdout, "%s", data->map[i]);
		fprintf(stdout, "\n");
	}
}

/* Find minimum of three */
static int	min3(int a, int b, int c)
{
	if (a < b)
	{
		if (a < c)
			return a;
		else
			return c;
	}
	else
	{
		if (b < c)
			return b;
		else
			return c;
	}
}

/* if character is printable */
static int if_print(char c)
{
    return (c >= 32 && c <= 126);
}

//<number of lines> <empty> <obstacle> <full>
static int parse_first_line(char *line, ssize_t len, t_data *data)
{
	if (len < 8 || line[len -1] != '\n')
		return(0);
	if (line[len - 7] != ' ' || line[len - 5] != ' ' || line[len - 3] != ' ')
		return (0);
	data->empty = line[len - 6];
	data->obst = line[len - 4];
	data->full = line[len - 2];
	if (!if_print(data->empty) || !if_print(data->obst) || !if_print(data->full)
					|| data->empty == data->obst || data->empty == data->full || data->obst == data->full)
		return (0);
	data->rows = 0;
	for (int i = 0; i < len - 7; i++)
	{
		if (line[i] < '0' || line[i] > '9')
			return (0);
		data->rows = data->rows * 10 + line[i] - '0';
	}
	return (data->rows > 0);
}


static int read_file(FILE *file, t_data *data)
{
	char *line = NULL;
	size_t cap = 0;
	ssize_t len;
	data->map = NULL;

	len = getline(&line, &cap, file);
	if (len <= 0 || !parse_first_line(line, len, data))
		return (free(line), 0);
	free(line);

	data->map = calloc(data->rows, sizeof(char *));
	if (!data->map)
		return (0);

	data->cols = -1;
	for (int i = 0; i < data->rows; i++)
	{
		line = NULL;
		cap = 0;
		len = getline(&line, &cap, file);
		if (len <= 1 || line[len - 1] != '\n')
			return (free(line), 0);
		line[--len] = '\0';
		data->map[i] = line;
		if (data->cols == -1)
			data->cols = len;
		if (len != data->cols)
			return (0);
		for (int j = 0; j < len; j++)
		{
			if (line[j] != data->empty && line[j] != data->obst)
				return (0);
		}
	}
	line = NULL;
	cap = 0;
	len = getline(&line, &cap, file);
	free(line);
	return (len == -1);
}

static int solver(t_data *data)
{
    int max_size = 0;
	int top_row = 0;
	int left_col = 0;


    int *prev = calloc(data->cols, sizeof(int));
    int *cur = calloc(data->cols, sizeof(int));
    int *tmp;

    if (!prev || !cur)
    {
        return(free(prev), free(cur), 0);
    }
	
	for (int i = 0; i < data->rows; i++)
	{
		for(int j = 0; j < data->cols; j++)
		{
			if(data->map[i][j] == data->obst)
				cur[j] = 0;
			else if (i == 0 || j == 0)
				cur[j] = 1;
			else
				cur[j] = 1 + min3(prev[j], cur[j - 1], prev[j - 1]);
			if (cur[j] > max_size)
			{
				max_size = cur[j];
				top_row = i - cur[j] + 1;
				left_col = j - cur[j] + 1;
			}
		}
        tmp = prev;
        prev = cur;
        cur = tmp;
	}
    free(prev);
    free(cur);

	/* Filling the map */
	fprintf(stdout, "max_size = %d, top = %d, left = %d\n", max_size, top_row, left_col);
	for (int i = 0; i < max_size; i++)
	{
		for (int j = 0; j < max_size; j++)
		{
			data->map[top_row + i][left_col + j] = data->full;
		}
	}
	return (1);
}

static int process(FILE *file)
{
	t_data data;

	if (!read_file(file, &data))
		return(free_map(&data), 0);
	if (!solver(&data))
		return(free_map(&data), 0);
	print_map(&data);
	free_map(&data);
	return 1;
}


int main(int argc, char **argv)
{
	FILE *file;

	if (argc < 2)
	{
		if (!process(stdin))
			fprintf(stderr, "map error\n");
	}
	for (int i = 1; i < argc; i++)
	{
		file = fopen(argv[i], "r");
		if (!file)
		{
			fprintf(stderr, "map error\n");
			if (argc > 2)
				fprintf(stdout, "\n");
			continue;
		}
		if (!process(file))
			fprintf(stderr, "map error\n");
		if (argc > 2)
				fprintf(stdout, "\n");
		fclose(file);
	}
	return (0);
}
