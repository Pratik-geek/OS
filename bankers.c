#include <stdio.h>
#include <unistd.h>

struct process
{
    int id, alloc[5], max[5], need[5], finished;
} pr[10];

void display(int p, int res)
{
    printf("\n%-7s%-13s%-5s%-6s", "Pr Id", "Allocations", "Max", "Need");
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < res; j++)
        {
            printf("\n%-7d%-13d%-5d%-6d", pr[i].id, pr[i].alloc[j], pr[i].max[j], pr[i].need[j]);
        }
    }
}

void safe_sequence(int p, int ava[], int res)
{

    int sseq[p];
    int ind = 0;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < p; j++)
        {
            if (pr[j].finished == 0)
            {
                int flag = 0;
                for (int k = 0; k < res; k++)
                {
                    if (pr[j].need[k] > ava[k])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    sseq[ind] = j + 1;
                    ind++;

                    for (int l = 0; l < res; l++)
                    {
                        ava[l] += pr[j].alloc[l];
                        pr[j].finished = 1;
                    }
                }
            }
        }
    }

    printf("\nSafe sequence: \n");

    if (ind == 0)
    {
        printf("Unsafe state");
    }
    else
    {
        for (int i = 0; i < p; i++)
        {
            printf("%d", sseq[i]);
        }
        printf("\n");
    }
}

int main()
{

    int p, res, ava[3];
    printf("Enter number of processes\n");
    scanf("%d", &p);
    printf("Enter number of resources\n");
    scanf("%d", &res);

    for (int i = 0; i < p; i++)
    {
        printf("Enter process id\n");
        scanf("%d", &pr[i].id);
        pr[i].finished = 0;

        printf("Enter number of allocations A B C..\n");
        for (int j = 0; j < res; j++)
        {
            scanf("%d", &pr[i].alloc[j]);
        }
        printf("Enter number of maximum allocations A B C..\n");
        for (int j = 0; j < res; j++)
        {
            scanf("%d", &pr[i].max[j]);
            pr[i].need[j] = pr[i].max[j] - pr[i].alloc[j];
        }
    }

    printf("Enter the available number of resources A B C..\n");

    for (int j = 0; j < res; j++)
    {
        scanf("%d", &ava[j]);
    }
    display(p, res);
    safe_sequence(p, ava, res);
}