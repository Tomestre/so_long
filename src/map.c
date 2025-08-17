#include "so_long.h"

static size_t get_file_size(int fd)
{
    char buffer[1024];
    size_t total_size = 0;
    ssize_t bytes_read;

    while (1)
    {
        bytes_read = read(fd, buffer, 1024);
        if (bytes_read < 0)
        {
            perror("Error reading file size");
            exit(1); // No game resources allocated yet
        }
        if (bytes_read == 0)
            break;
        total_size += bytes_read;
    }
    return (total_size);
}

static char *read_file_part1(const char *file_path, int *fd, size_t *size)
{
    *fd = open(file_path, O_RDONLY);
    if (*fd < 0)
    {
        perror("Error opening file");
        exit(1); // No game resources allocated yet
    }
    *size = get_file_size(*fd);
    if (*size == 0)
    {
        close(*fd);
        ft_printf("Error: Empty file\n");
        exit(1); // No game resources allocated yet
    }
    close(*fd);
    *fd = open(file_path, O_RDONLY);
    if (*fd < 0)
    {
        perror("Error reopening file");
        exit(1); // No game resources allocated yet
    }
    return (NULL);
}

static char *read_file_part2(int fd, size_t size)
{
    char *buffer;
    ssize_t bytes_read;

    buffer = malloc(size + 1);
    if (!buffer)
    {
        close(fd);
        perror("Error allocating memory");
        exit(1); // No game resources allocated yet
    }
    bytes_read = read(fd, buffer, size);
    if (bytes_read < 0 || (size_t)bytes_read != size)
    {
        free(buffer);
        close(fd);
        ft_printf("Error: Failed to read bytes from file\n");
        exit(1); // No game resources allocated yet
    }
    buffer[bytes_read] = '\0';
    ft_printf("Read bytes: '%s'\n", buffer);
    close(fd);
    return (buffer);
}

char *read_file(const char *file_path)
{
    int fd;
    size_t size;
    char *buffer;

    read_file_part1(file_path, &fd, &size);
    buffer = read_file_part2(fd, size);
    return (buffer);
}

int count_lines(const char *content)
{
    int lines = 0;
    const char *ptr = content;
    ft_printf("Counting lines in: '%s'\n", content);
    while (*ptr)
    {
        if (*ptr == '\n')
            lines++;
        ptr++;
    }
    if (ptr > content && *(ptr - 1) != '\n')
        lines++;
    ft_printf("Counted %d lines\n", lines);
    return (lines);
}
