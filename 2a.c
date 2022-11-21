#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <strings.h>
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}
void merge(int arr[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1], M[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];
    int i, j, k;
    i = 0;
    j = 0;
    k = p;
    while (i < n1 && j < n2)
    {
        if (L[i] <= M[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = M[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = M[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
void menu()
{
    printf("\n\n1. NORMAL EXECUTION\n2. ORPHAN EXECUTION\n3. ZOMBIE EXECUTION\n\nENTER CHOICE : ");
}
int main(void)
{

    int n;
    printf("ENTER NUMBER OF ELEMENTS: ");
    scanf("%d", &n);
    int a[n];
    printf("ENTER ELEMENTS: ");
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
    }
    menu();
    int choice;
    scanf("%d", &choice);
    pid_t p;
    p = fork();
    switch (choice)
    {
    case 1:
        printf("\nINITIATING NORMAL EXECUTION...!!\n\n");

        if (p == 0)
        {
            //CHILD Process Execution
            printf("\nCHILD PROCESS WITH PID : %d AND PARENT ID :%d\n", getpid(), getppid());

            selectionSort(a, n);

            printf("SORTED ARRAY: ");
            printArray(a, n);

            printf("\n");
        }

        else
        {
            //Parent Process Execution
            wait(NULL);
            printf("\nPARENT PROCESS WITH PID : %d AND CHILD ID : %d\n", getpid(), p);
            mergeSort(a, 0, n - 1);

            printf("SORTED ARRAY: ");
            printArray(a, n);

            printf("\n");
        }
        break;

    case 2:
        printf("\nINITIATING ORPHAN EXECUTION...!!\n\n");

        if (p == 0)
        {
            sleep(30);
            printf("\nCHILD PROCESS WITH PID : %d AND PARENT ID : %d\n", getpid(), getppid());
            selectionSort(a, n);

            printf("SORTED ARRAY: ");
            printArray(a, n);
            system("ps -elf | grep %d");
            printf("\n");
        }

        else
        {
            //wait(NULL);
            printf("\nPARENT PROCESS WITH PID : %d AND CHILD ID : %d\n", getpid(), p);
            mergeSort(a, 0, n - 1);

            printf("SORTED ARRAY: ");
            printArray(a, n);
            //snprintf(buffer, 25, );
            system("ps -elf | grep %d");
            printf("\n");
        }
        break;
    case 3:
        printf("\nINITIATING ZOMBIE EXECUTION...!!\n\n");

        if (p == 0)
        {
            printf("\nCHILD PROCESS WITH PID : %d AND PARENT ID : %d\n", getpid(), getppid());

            selectionSort(a, n);

            printf("SORTED ARRAY: ");
            printArray(a, n);
            system("ps -aux | grep %d");

            printf("\n");
        }

        else
        {
            sleep(5);
            printf("\nPARENT PROCESS WITH PID : %d AND CHILD ID : %d\n", getpid(), p);
            mergeSort(a, 0, n - 1);

            printf("SORTED ARRAY: ");
            printArray(a, n);
            system("ps -aux | grep %d");
            printf("\n");
        }
        break;
    default:
        printf("WRONG CHOICE...!!");
        printf("\n");
        menu();
        break;
    }
}