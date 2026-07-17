#include<stdio.h>
struct process
{
int pid;
int bt;
int wt;
int tt;
}p[10],temp;

int main()
{
int i,j,n,totwt,tottt;
float avg1,avg2;
printf("Enter number of processes: ");
scanf("%d",&n);

for(i=1;i<=n;i++)
{
    p[i].pid=i;
    printf("Enter Burst Time: ");
    scanf("%d",&p[i].bt);
}

// Sort according to burst time
for(i=1;i<n;i++)
{
    for(j=i+1;j<=n;j++)
    {
        if(p[i].bt>p[j].bt)
        {
            temp=p[i];
            p[i]=p[j];
            p[j]=temp;
        }
    }
}

p[1].wt=0;
p[1].tt=p[1].bt;

for(i=2;i<=n;i++)
{
    p[i].wt=p[i-1].wt+p[i-1].bt;
    p[i].tt=p[i].wt+p[i].bt;
}

totwt=0;
tottt=0;

printf("\nPID\tBT\tWT\tTT\n");

for(i=1;i<=n;i++)
{
    printf("%d\t%d\t%d\t%d\n",
           p[i].pid,p[i].bt,p[i].wt,p[i].tt);

    totwt+=p[i].wt;
    tottt+=p[i].tt;
}

avg1=(float)totwt/n;
avg2=(float)tottt/n;

printf("\nAverage Waiting Time = %.2f",avg1);
printf("\nAverage Turnaround Time = %.2f",avg2);

return 0;
}