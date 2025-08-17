#include "so_long.h"

static char **allocate_grid(int rows)
{
    char **grid;

    if (rows == 0)
    {
        ft_printf("Error: No lines in map\n");
        exit(1); // No game resources allocated yet, so exit is fine
    }
    grid = malloc(sizeof(char *) * (rows + 1));
    if (!grid)
    {
        perror("Error allocating grid");
        exit(1); // No game resources allocated yet
    }
    return (grid);
}

static void split_line(const char *line, char **grid, int i)
{
    const char *next_line;
    size_t len;

    next_line = ft_strchr(line, '\n');
    if (next_line)
    {
        len = next_line - line;
        if (len > 0 && line[len - 1] == '\r')
            len--;
    }
    else
    {
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\r')
            len--;
    }
    grid[i] = malloc(len + 1);
    if (!grid[i])
    {
        while (i > 0)
            free(grid[--i]);
        free(grid);
        perror("Error allocating line");
        exit(1); // No game resources allocated yet
    }
    ft_strncpy(grid[i], line, len);
    grid[i][len] = '\0';
    ft_printf("Line %d: '%s'\n", i, grid[i]);
}

static char **split_map(const char *content, int rows)
{
    char **grid;
    int i;
    const char *line;

    grid = allocate_grid(rows);
    i = 0;
    line = content;
    while (i < rows)
    {
        split_line(line, grid, i);
        line = ft_strchr(line, '\n');
        line = line ? line + 1 : line + ft_strlen(line);
        i++;
    }
    grid[rows] = NULL;
    return (grid);
}

void read_map(const char *file_path, t_game *game)
{
    char *content;

    if (!ft_strstr(file_path, ".ber"))
    {
        ft_printf("Error: File must have .ber extension\n");
        exit(1); // No game resources allocated yet
    }
    content = read_file(file_path);
    game->map.rows = count_lines(content);
    if (game->map.rows == 0)
    {
        free(content);
        ft_printf("Error: Empty map file\n");
        free_game(game); // Clean up game
        exit(1);
    }
    game->map.grid = split_map(content, game->map.rows);
    game->map.cols = ft_strlen(game->map.grid[0]);
    if (game->map.cols == 0)
    {
        free_game(game); // Clean up game (includes map)
        free(content);
        ft_printf("Error: Empty map row\n");
        exit(1);
    }
    free(content);
}
