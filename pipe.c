#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SIZE 5

int main()
{
    // Declare variable.
    int i, j,                 // Iteration.
        n, fd[2],             // Total process, pipe.
        buffer[SIZE];         // Buffer.
    
    // Input total process.
    printf("Masukkan jumlah proses : ");
    scanf("%d", &n);
    int pid[n];

    // Pipe error check.
    if(pipe(fd) < 0)
    {
        perror("pipe");
        exit(1);
    }

    // Looping process.
    for(i = 0; i < n; i++)
    {
        // Fork.
        switch (pid[i] = fork())
        {
            // Pipe error check.
            case -1:
                perror("fork");
                exit(1);
                break;
            
            // Child process.
            case 0:
                close(fd[0]);

                int fill[SIZE];
                for(j = 0; j < SIZE; j++)
                {
                    fill[j] = (rand() % 100);
                }

                write(fd[1], fill, sizeof(fill));
                for(j = 0; j < SIZE; j++)
                {
                    printf("Proses menulis proses %d ke %d : %d\n", (i + 1), j, fill[j]);
                }
                break;
            
            // Parent process.
            default:
                close(fd[1]);

                // Wait until child process done.
                int pidWait, status;
                while(pidWait = wait(&status))
                {
                    if(pidWait == pid[i])
                    {
                        int total = 0;
                        read(fd[0], buffer, sizeof(buffer));
                        for(j = 0; j < SIZE; j++)
                        {
                            printf("Proses membaca proses %d ke %d : %d\n", (i + 1), j, buffer[j]);
                            total += buffer[j];
                        }
    
                        printf("Total : %d\n", total);
                    }
                    break;

                    // Error check.
                    if((pidWait == (-1)) && (errno != EINTR))
                    {
                        perror("wait");
                        exit(1);
                    }
                }
        }
    }

    return 0;
}