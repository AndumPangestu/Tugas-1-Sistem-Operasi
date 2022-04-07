#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 5

int main()
{
    int i, j,
        n, fd[2],
        x = 0, buffer[SIZE];
    
    printf("Masukkan jumlah proses : ");
    scanf("%d", &n);
    int pid[n];

    if(pipe(fd) < 0)
    {
        perror("pipe");
        exit(1);
    }

    for(i = 0; i < n; i++)
    {
        switch (pid[i] = fork())
        {
            case -1:
                perror("fork");
                exit(1);
                break;
            
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
            default:
                close(fd[1]);

                int total = 0;
                read(fd[0], buffer, sizeof(buffer));
                for(j = 0; j < SIZE; j++)
                {
                    printf("Proses membaca proses %d ke %d : %d\n", (i + 1), j, buffer[j]);
                    total += buffer[j];
                }

                printf("Total : %d\n", total);
                break;
        }
    }

    return 0;
}