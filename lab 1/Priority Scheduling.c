#include<stdio.h>

struct process
{
int pid;
int bt;
int prior;
int wt;
int tt;
} p[10], temp;

int main()
{
int i, j, n, totwt = 0, tottt = 0;
float avg1, avg2;

printf("Enter the number of processes: ");
scanf("%d", &n);

for(i = 1; i <= n; i++)
{
    p[i].pid = i;

    printf("\nEnter Burst Time of Process %d: ", i);
    scanf("%d", &p[i].bt);

    printf("Enter Priority of Process %d: ", i);
    scanf("%d", &p[i].prior);
}

/* Sorting according to priority
   (Smaller priority number = Higher priority) */
for(i = 1; i < n; i++)
{
    for(j = i + 1; j <= n; j++)
    {
        if(p[i].prior > p[j].prior)
        {
            temp = p[i];
            p[i] = p[j];
            p[j] = temp;
        }
    }
}

/* Waiting Time and Turnaround Time */
p[1].wt = 0;
p[1].tt = p[1].bt;

for(i = 2; i <= n; i++)
{
    p[i].wt = p[i-1].wt + p[i-1].bt;
    p[i].tt = p[i].wt + p[i].bt;
}

printf("\n----------------------------------------------------------");
printf("\nPID\tPriority\tBT\tWT\tTT");
printf("\n----------------------------------------------------------");

for(i = 1; i <= n; i++)
{
    printf("\n%d\t%d\t\t%d\t%d\t%d",
           p[i].pid,
           p[i].prior,
           p[i].bt,
           p[i].wt,
           p[i].tt);

    totwt += p[i].wt;
    tottt += p[i].tt;
}

avg1 = (float)totwt / n;
avg2 = (float)tottt / n;

printf("\n----------------------------------------------------------");
printf("\nAverage Waiting Time = %.2f", avg1);
printf("\nAverage Turnaround Time = %.2f", avg2);


return 0;
}