#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int my_cat(const char* const filename)
{
    int fd;

    if (filename == NULL)
    {
        fd = STDIN_FILENO;    
    }
    else
    {
        fd = open(filename, O_RDONLY);
        if (fd == -1) return 1;
    }

    // Lecture par blocs
    char buffer[BUFFER_SIZE];
    ssize_t nb_bytes_read;
    ssize_t nb_bytes_wrote;

    while((nb_bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        if (nb_bytes_read == -1) return 1; // erreur de read

        nb_bytes_wrote = write(STDOUT_FILENO, buffer, nb_bytes_read);

        if (nb_bytes_wrote == -1) return 1; // erreur de write
        if (nb_bytes_wrote != nb_bytes_read) return 1;
    }
    
    if (close(fd) == -1) return 1;

    return 0;
}