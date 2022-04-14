#include "header.h"

int main()
{
    int i, j, k, data,
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

    int size = 2 * sizeof(int);
    void *addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int *shared = addr;

    printf("Mapped at : %p\n\n", addr);

    switch(pid = fork())
    {
        case -1:
            perror("fork");
            exit(1);
            break;
        
        case 0:
            for(i = 0; i < consumer; i++)
            {
                switch(pid_consumer[i] = fork())
                {
                    case -1:
                        perror("fork");
                        exit(1);
                        break;
                    
                    case 0:
                        printf("");
                        int temp = 0;
                        
                        printf("Konsumen %d (PID: %d) mengambil %d\n", i, getpid(), shared[0]);
                        temp += shared[0];

                        printf("Total : %d\n\n", temp);
                        sleep(1);
                        break;
                }
            }
            break;
        
        default:
            for(j = 0; j < producer; j++)
            {
                switch(pid_producer[j] = fork())
                {
                    case -1:
                        perror("fork");
                        exit(1);
                        break;

                    case 0:
                        srand(time(0));
                        shared[0] = (rand() % 100);
                        printf("Produser %d (PID: %d) menulis %d\n", j, getpid(), shared[0]);
                        sleep(1);
                        break;
                }
            }
            
            break;
            
    }

    return 0;
}