#include<stdio.h>

struct process
{
int pid, bt, wt, tt;
};

int main()
{
struct process x[10], p[50];
int i, j, k, tot = 0, n, m;
float wttime = 0.0, tottime = 0.0, a1, a2;
printf("Enter the number of processes: ");
scanf("%d", &n);

for(i = 1; i <= n; i++)
{
    x[i].pid = i;
    printf("Enter Burst Time of Process %d: ", i);
    scanf("%d", &x[i].bt);
    tot += x[i].bt;
}

printf("Total Burst Time = %d\n", tot);

printf("Enter Time Slice: ");
scanf("%d", &m);

p[0].tt = 0;
k = 1;

while(1)
{
    int done = 1;

    for(i = 1; i <= n; i++)
    {
        if(x[i].bt > 0)
        {
            done = 0;

            p[k].pid = i;
            p[k].wt = p[k-1].tt;

            if(x[i].bt <= m)
            {
                p[k].bt = x[i].bt;
                p[k].tt = p[k].wt + x[i].bt;
                x[i].bt = 0;
            }
            else
            {
                p[k].bt = m;
                p[k].tt = p[k].wt + m;
                x[i].bt -= m;
            }

            k++;
        }
    }

    if(done)
        break;
}

printf("\nPID\tBT\tWT\tTT\n");

for(i = 1; i < k; i++)
{
    printf("%d\t%d\t%d\t%d\n",
           p[i].pid,
           p[i].bt,
           p[i].wt,
           p[i].tt);
}

/* Calculate final WT and TT of each process */
for(i = 1; i <= n; i++)
{
    int finish = 0;
    int burst = 0;

    for(j = 1; j < k; j++)
    {
        if(p[j].pid == i)
        {
            finish = p[j].tt;
            burst += p[j].bt;
        }
    }

    wttime += (finish - burst);
    tottime += finish;
}

a1 = wttime / n;
a2 = tottime / n;

printf("\nAverage Waiting Time = %.2f", a1);
printf("\nAverage Turnaround Time = %.2f", a2);


return 0;
}