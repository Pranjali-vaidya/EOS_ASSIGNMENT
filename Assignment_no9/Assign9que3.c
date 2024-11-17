#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>  // For fcntl()
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int ret, fd, arr[2], pipe_buffer_size;
    char buf1[32] = "god bless you!", buf2[32];
    
    ret = pipe(arr);
    if(ret < 0) {
        perror("pipe() failed");
        _exit(1);
    }
    
    pipe_buffer_size = fcntl(arr[0], F_GETFD);
    if (pipe_buffer_size == -1) {
        perror("fcntl() failed");
        close(arr[0]);
        close(arr[1]);
        _exit(1);
    }
    
    printf("Pipe buffer size: %d bytes\n", pipe_buffer_size);
    
    // Write to the pipe
    write(arr[1], buf1, sizeof(buf1));
    printf("Written to pipe: %s\n", buf1);
    
    // Read from the pipe
    read(arr[0], buf2, sizeof(buf2));
    printf("Read from pipe: %s\n", buf2);
    
    // Close the pipe
    close(arr[1]);
    close(arr[0]);

    return 0;
}

