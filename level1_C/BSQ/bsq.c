#include "bsq.h"

// cc -Wall -Werror -Wextra bsq.c

/* Initialization of structure by 0 / NULL */
void	data_init(t_data *data)
{
	data->rows = 0;
	data->columns = 0;
	data->empty = 0;
	data->obstacle = 0;
	data->full = 0;
	data->map = NULL;
}

/* Free memory allocated for the map */
void free_map(t_data *data)
{
	int i = 0;

	if (data->map == NULL)
		return ;
	while (i < data->rows)
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
}

/* Find minimum of three */
int	min3(int a, int b, int c)
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

/* Print map */
void print_map(t_data * data)
{
	int i = 0;
	while (i < data->rows)
	{
		fprintf(stdout, "%s", data->map[i]);
		fprintf(stdout, "\n");
		i++;
	}
}

/* Size of line */
size_t ft_strlen(const char *str)
{
	size_t len = 0;
	while (str[len] != '\0' && str[len] != '\n')
	{
		len++;
	}
	return len;
}

/* count columns in second line = first map line */
int save_count_columns(t_data *data, const char *line)
{
	size_t size = ft_strlen(line);
	if (size < 1)  // if only "\n"  ?????
		return -1;
	//fprintf(stdout, "Columns size: %lu characters\n", (unsigned long)size);
	data->columns = size;
	return 0;
}

/* Parsing and validation of the first line: rows, empty, obstacle, full */
int	parse_first_line(t_data *data, const char *line)
{
	int		size;
	char	empty, obstacle, full, extra;
	int		items_scanned;

	if (line == NULL)
        return -1;
	/* 
     * sscanf matches: an integer, a space, a char, a space, a char, a space, a char.
     * The final ' %c' or '%c' catches trailing characters to ensure no extra data exists.
	 * The '\n' at the end expects the newline from getline.
     */
	items_scanned = sscanf(line, "%d %c %c %c\n%c", &size, &empty, &obstacle, &full, &extra);
	if (items_scanned != 4)
		return -1;
	if (size < 1 || empty == obstacle || empty == full || obstacle == full)
		return -1;
	data->rows = size;
	data->empty = empty;
	data->obstacle = obstacle;
	data->full = full;
	/*
	fprintf(stdout, "  Rows:     %d\n", data->rows);
    fprintf(stdout, "  Obstacle: %c\n", data->obstacle);
    fprintf(stdout, "  Empty: %c\n", data->empty);
    fprintf(stdout, "  Full: %c\n", data->full);
	*/
	return 0;
}

/* Parsing and validation of the map line*/
int parse_line(t_data *data, const char *line, int row)
{
	int len = ft_strlen(line);
	if (len != data->columns)
		return -1;
	data->map[row] = calloc(data->columns + 1, sizeof(char));
	if (data->map[row] == NULL)
		return (-1);
	for(int i = 0; i < len; i++)
	{
		if(line[i] != data->empty && line[i] != data->obstacle)
			return -1;
		data->map[row][i] = line[i];
	}
	//fprintf(stdout, "%s", line);
	return 0;
}

/* Key function to process the file/map */
int	process_file(t_data *data, FILE *file)
{
	char 	*line = NULL;
	size_t 	len = 0;
	ssize_t read;

	/* 1. Read and process the first line if it exists */
	if ((read = getline(&line, &len, file)) != -1)
	{
		if (parse_first_line(data, line) == -1)
			return (free(line), -1);
	}
	else
	{
		return (free(line), -1);
	}
	//free(line);

	/* 2. Allocation memory */
	data->map = calloc(data->rows, sizeof(char *));
	if (data->map == NULL)
	{
		fprintf(stderr, "Error: Allocation\n");
		return (-1);
	}

	/* 3. Read and process map lines if they exist */
	for (int i = 0; i < data->rows; i++)
	{
		if ((read = getline(&line, &len, file)) != -1)
		{
			if (i == 0)
			{
				if (save_count_columns(data, line) == -1)
					return (free(line), -1);
			}
			if (parse_line(data, line, i) == -1)
				return (free(line), -1);
		}
		else
			return (free(line), -1);
		//free(line);
	}

    /* 5. Clean up resources */
    free(line);
    return 0;
}

int	solver(t_data *data)
{
	int max_size = 0;
	int top_x = 0;
	int left_y = 0;

	int i, j;

	int height = data->rows;
	int width = data->columns;

	int dp[height][width];
	
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if(data->map[i][j] == data->obstacle)
				dp[i][j] = 0;
			else if (i == 0 || j == 0)
				dp[i][j] = 1;
			else
				dp[i][j] = 1 + min3(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]);
			
			if (dp[i][j] > max_size)
			{
				max_size = dp[i][j];
				top_x = i - dp[i][j] + 1;
				left_y = j - dp[i][j] + 1;
			}
			j++;
		}
		i++;
	}
	if (max_size <= 0)
		return 0;
	/* Filling the map */
	i = 0;
	while (i < max_size)
	{
		j = 0;
		while (j < max_size)
		{
			data->map[i + top_x][j + left_y] = data->full;
			j++;
		}
		i++;
	}
	return 0;
}

int bsq(t_data *data, FILE *file)
{
	data_init(data); // init structure by 0/NULL
	if (process_file(data, file) == -1)  // parsing & validation data
	{
		free_map(data);
		return (-1);
	}
	if (solver(data) == -1)
	{
		free_map(data);
		return (-1);
	}
	print_map(data);
	free_map(data);
	return (0);
}

int main (int argc, char **argv)
{
	t_data	data;
	int		i;
	FILE 	*file;

	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			// call the key function with argv[i] as the input file
			file = fopen(argv[i], "r");
			if (file == NULL)
			{
				// fprintf(stderr, "Error opening file '%s': errno %d\n", argv[i], errno);
				fprintf(stderr, "map error\n");
				//continue;
			}
			else
			{
				if (bsq(&data, file) == -1)
					fprintf(stderr, "map error\n");
				fclose(file);
			}
			if (i + 1 < argc)
				fprintf(stdout, "\n");
			i++;
		}
	}
	else
	{
		// call the key function with stdin as the input stream
		//return (bsq(&data, stdin));
		if (bsq(&data, stdin) == -1)
			fprintf(stderr, "map error\n");
	}
	return (0);
}