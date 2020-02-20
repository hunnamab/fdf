#include "fdf.h"

void    validation(char *filename)
{
    char buf[128000];
    int fd;
    int ret;
    int i;

    i = ft_strlen(filename) - 1;
    filename[i] == 'f' ? i-- : error_exit(ERR_OPEN_FILE);
    filename[i] == 'd' ? i-- : error_exit(ERR_OPEN_FILE);
    filename[i] == 'f' ? i-- : error_exit(ERR_OPEN_FILE);
    filename[i] == '.' ? i-- : error_exit(ERR_OPEN_FILE);
    i = 0;
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit(ERR_OPEN_FILE);
    ret = read(fd, buf, 128000);
    buf[ret] = '\0';
    while(buf[i])
    {
        if (!(ft_isascii(buf[i])))
            error_exit(ERR_MAP_VALID);
        i++;
    }
    close(fd);
}