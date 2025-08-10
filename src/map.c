// src/map.c
#include "so_long.h"

static char *read_file(const char *file_path)
{
    int fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        exit(1);
    }

    // Get file size
    off_t size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    char *buffer = malloc(size + 1);
    if (!buffer)
    {
        close(fd);
        perror("Error allocating memory");
        exit(1);
    }

    ssize_t bytes_read = read(fd, buffer, size);
    if (bytes_read < 0)
    {
        free(buffer);
        close(fd);
        perror("Error reading file");
        exit(1);
    }
    buffer[bytes_read] = '\0';
    printf("Read %zd bytes: '%s'\n", bytes_read, buffer); // Debug print
    close(fd);
    return buffer;
}

static int count_lines(const char *content)
{
    int lines = 0;
    const char *ptr = content;
    printf("Counting lines in: '%s'\n", content); // Debug print
    while (*ptr)
    {
        if (*ptr == '\n')
            lines++;
        ptr++;
    }
    if (ptr > content && *(ptr - 1) != '\n')
        lines++;
    printf("Counted %d lines\n", lines); // Debug print
    return lines;
}

// src/map.c
static char **split_map(const char *content, int rows)
{
    if (rows == 0)
    {
        fprintf(stderr, "Error: No lines in map\n");
        exit(1);
    }

    char **grid = malloc(sizeof(char *) * (rows + 1));
    if (!grid)
    {
        perror("Error allocating grid");
        exit(1);
    }

    int i = 0;
    const char *line = content;
    const char *next_line;
    while (i < rows)
    {
        next_line = strchr(line, '\n');
        size_t len;
        if (next_line)
        {
            len = next_line - line;
            if (len > 0 && line[len - 1] == '\r')
                len--; // Remove \r
        }
        else
        {
            len = strlen(line);
            if (len > 0 && line[len - 1] == '\r')
                len--; // Remove \r
        }
        grid[i] = malloc(len + 1);
        if (!grid[i])
        {
            while (i > 0)
                free(grid[--i]);
            free(grid);
            perror("Error allocating line");
            exit(1);
        }
        strncpy(grid[i], line, len);
        grid[i][len] = '\0';
        printf("Line %d: '%s'\n", i, grid[i]);
        line = next_line ? next_line + 1 : line + len;
        i++;
    }
    grid[rows] = NULL;
    return grid;
}

void read_map(const char *file_path, t_game *game)
{
    if (!strstr(file_path, ".ber"))
    {
        fprintf(stderr, "Error: File must have .ber extension\n");
        exit(1);
    }

    char *content = read_file(file_path);
    game->map.rows = count_lines(content);
    if (game->map.rows == 0)
    {
        free(content);
        fprintf(stderr, "Error: Empty map file\n");
        exit(1);
    }
    game->map.grid = split_map(content, game->map.rows);
    game->map.cols = strlen(game->map.grid[0]);
    if (game->map.cols == 0)
    {
        free_map(game);
        free(content);
        fprintf(stderr, "Error: Empty map row\n");
        exit(1);
    }
    printf("Map dimensions: %d rows x %d cols\n", game->map.rows, game->map.cols);
    free(content);
}
