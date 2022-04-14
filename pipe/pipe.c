#include "header.h"

int main()
{
    int i, j, data,
        producer, consumer;
    
    queue buffer;
    createqueue(&buffer);

    printf("Masukkan jumlah produsen : ");
    scanf("%d", &producer);
    printf("Masukkan jumlah konsumen : ");
    scanf("%d", &consumer);

    int fd[2], pid,
        pid_producer[producer],
        pid_consumer[consumer];

    if(pipe(fd) < 0)
    {
        perror("pipe");
        exit(1);
    }

    switch(pid = fork())
    {
        // Pipe error check.
        case -1:
            perror("fork");
            exit(1);
            break;
        
        case 0:
            printf("");
            int total = 0;
            for(j = 0; j < consumer; j++)
            {
                switch (pid_consumer[j] = fork())
                {
                    case -1:
                        perror("fork");
                        exit(1);
                        break;

                    case 0:
                        printf("");
                        int *temp;
                        
                        close(fd[1]);
                        read(fd[0], temp, sizeof(int));
                        printf("Konsumen %d (PID: %d) mengambil %d\n", j, getpid(), *temp);
                        total += *temp;
                        del(&buffer);   // Remove one item from queue.
                        sleep(1);
                        break;
                    
                    default:
                        break;
                }
                
                printf("Total : %d\n\n", total);
            }
            break;

        default:
            for(i = 0; i < producer; i++)
            {
                switch(pid_producer[i] = fork())
                {
                    case -1:
                        perror("fork");
                        exit(1);
                        break;

                    case 0:
                        srand(time(0));

                        close(fd[0]);
                        data = (rand() % 100);
                        printf("Produser %d (PID: %d) menulis %d\n", i, getpid(), data);
                        write(fd[1], &data, sizeof(int));
                        add(data, &buffer);  // Add one item from queue.
                        sleep(1);
                        break;
                    
                    default:
                        break;
                }
            }
            break;
    }

    return 0;
}