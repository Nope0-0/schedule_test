#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<windows.h>
using namespace std;
int totalStep,minTime;
int n,m;
int Step[105];
struct Job
{
    int machine;
    int len;
} job[105][105];
int jobEnd[105][105];
int jobStep[105];
int workTime[105];
struct Recording
{
    int start;
    int end;
    int job;
    int machine;
} best[105],now[105];
void init()
{
    totalStep=0;
    minTime = 999999999;
    memset(jobStep,0,sizeof(jobStep));
    memset(workTime,0,sizeof(workTime));
    memset(best,0,sizeof(best));
    memset(jobEnd,-1,sizeof(jobEnd));
}
void dfs(int step,int time)
{
    if (time>=minTime) return;
    if (step == totalStep)
    {
        minTime = time;
        for (int i=0; i<totalStep; i++)
            best[i]=now[i];
        /*int gantt[105][105];
        for (int i=0;i<totalStep;i++)
        {
            for (int j=best[i].start;j<best[i].end;j++)
            {
                gantt[best[i].machine][j]=best[i].job;
            }
        }
        for (int i=0;i<m;i++)
            for (int j=0;j<minTime;j++)
                printf("%d%c",gantt[i][j],j==minTime-1?'\n':' ');
            printf("\n");*/
        return;
    }

    for (int i=0; i<n; i++)
    {
        int j = jobStep[i];
        if (j >= Step[i]) continue;
        int thisMachine = job[i][j].machine;
        now[step].machine = thisMachine;
        now[step].job = i+1;
        int temp =  workTime[thisMachine];
        int beginTime = max(jobEnd[i][j-1],workTime[thisMachine]);
        now[step].start = beginTime;
        workTime[thisMachine] =beginTime + job[i][j].len;
        jobEnd[i][j] = now[step].end = workTime[thisMachine];
        jobStep[i]++;
        //printf("%d %d %d\n",step,i,j);
        dfs(step+1, max(time,workTime[thisMachine]) );
        jobStep[i]--;
        workTime[thisMachine]=temp;
    }
}
int main()
{
    printf("Input number of Job : ");
    scanf("%d",&n);
    printf("Input number of Machine : ");
    scanf("%d",&m);
    init();
    for (int i=0; i<n; i++)
    {
        printf("Input number of Job  %d  Steps : ",i);
        scanf("%d",&Step[i]);
        totalStep+=Step[i];
        for (int j=0; j<Step[i]; j++)
        {
            printf("Input which machine Work  %d  works on, and consumption time : ",j+1);
            scanf("%d%d",&job[i][j].machine,&job[i][j].len);
        }

    }

    dfs(0,0);
    printf("Minimum Time : %d\n",minTime);

    int gantt[105][105];
    for (int i=0; i<totalStep; i++)
    {
        for (int j=best[i].start; j<best[i].end; j++)
        {
            gantt[best[i].machine][j]=best[i].job;
        }
    }

    for (int i=0; i<m; i++)
        for (int j=0; j<minTime; j++)
            printf("%d%c",gantt[i][j],j==minTime-1?'\n':' ');
	system("pause");
}

/*
5
3
3
0 5
1 3
2 6
3
0 4
1 2
2 1
2
0 7
2 4
3
0 1
1 6
2 2
2
1 8
2 5
*/