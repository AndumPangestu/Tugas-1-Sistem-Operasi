#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <errno.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SIZE 5

int main()
{
    int i, j, k,
        n, size;

    printf("Masukkan jumlah proses : ");
    scanf("%d", &n);
    int pid[n];

    size = SIZE * sizeof(int);
    void *addr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    printf("Mapped at : %p\n", addr);
    int *shared = addr;

    for(i = 0; i < n; i++)
    {
        switch(pid[i] = fork())
        {
            case -1:
                perror("fork");
                exit(1);
                break;
            
            case 0:
                printf("Child process %d.\n", (i + 1));
                for(j = 0; j < SIZE; j++)
                {
                    shared[j] = (rand() % 100);
                    printf("Proses ke-%d menulis %d : %d\n", i, j, shared[j]);
                }

                break;

            default:
                printf("Parent process %d.\n", (i + 1));

                int pidWait, status;
                while(pidWait = wait(&status))
                {
                    if(pidWait == pid[i])
                    {
                        int temp = 0;
                        for(j = 0; j < SIZE; j++)
                        {
                            printf("Proses ke-%d membaca %d : %d\n", i, j, shared[j]);
                            temp += shared[j];
                        }

                        printf("Total : %d\n", temp);
                    }
                    break;

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