#include "bsq.h"

// cc -Wall -Werror -Wextra main.c bsq.c
/*
static int bsq(t_data *data, FILE *file)
{
	data_init(data); // init structure by 0/NULL
	if (process_file(data, file) == -1)  // parsing & validation data
		return (-1);
	solver(data);
	print_map(data);
	free_map(data->map);
	return (0);
}
*/

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
		return (bsq(&data, stdin));
	}

/*
	//fprintf(stdout, "%d", argc);
	if (argc == 1)
	{
		return (init_map(&data, stdin));
	}
	i = 1;
	while (i < argc)
	{
		file = fopen(argv[i], "r");
		if (file == NULL)
		{
			// fprintf(stderr, "Error opening file '%s': errno %d\n", argv[i], errno);
			fprintf(stderr, "map error\n");
			//continue;
		}
		else
		{
			if (init_map(&data, file) == -1)
				fprintf(stderr, "map error\n");
			fclose(file);
		}
		if (i + 1 < argc)
			fprintf(stdout, "\n");
		i++;
	}
*/
	return (0);
}

/*
!!! everything should be in bsq.c
*/