#include <stdio.h>      // For printf()
#include <fcntl.h>      // For open() and O_RDONLY
#include <unistd.h>     // For close()

int main()
{
    int fd;

    // Open test.txt in read-only mode
    fd = open("test.txt", O_RDONLY);

    // Check if opening failed
    if(fd == -1)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // If successful
    printf("File opened successfully.\n");

    // Close the file
    close(fd);

    return 0;
}