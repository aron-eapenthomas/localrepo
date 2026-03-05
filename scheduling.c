#include <stdio.h>
#include <string.h>
float avg_wt = 1e9;
char algorithm[100] = "None";
struct Process
{
    int at, bt, ct, wt, tat, rt, priority;
};
void FCFS(struct Process p[], int n)
{
    int i, current_time = 0;
    float total_wt = 0.0;
    for (i = 0; i < n; i++)
    {
        if (current_time < p[i].at)
        {
            current_time = p[i].at;
        }
        current_time += p[i].bt;
        p[i].ct = current_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_wt += p[i].wt;
    }
    printf("FCFS -Avg Time :%f\n", total_wt / n);
    // printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    // for (i = 0; i < n; i++)
    //     printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    if (avg_wt > (total_wt / n))
    {
        avg_wt = (total_wt / n);
        strcpy(algorithm, "FCFS");
    }
}
void round_robin(struct Process p[], int n, int quantum)
{
    int queue[100],i;
    int front = 0, rear = 0;
    int visited[100] = {0};
    int current_time = 0;
    int completed = 0;
    float total_wt = 0.0;
    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }
    while (completed < n)
    {
        if (front == rear) {
            current_time++;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= current_time && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }
        int i = queue[front++];
        if (p[i].rt > quantum)
        {
            current_time += quantum;
            p[i].rt -= quantum;
        }
        else
        {
            current_time += p[i].rt;
            p[i].rt = 0;
            p[i].ct = current_time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;

            total_wt += p[i].wt;
            completed++;
        }
        for (int j = 0; j < n; j++) {
            if (p[j].at <= current_time && !visited[j]) {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }
        if (p[i].rt > 0) {
            queue[rear++] = i;
        }
    }
    printf("Round Robin -Avg Time :%f\n", total_wt / n);
    // printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    // for (i = 0; i < n; i++)
    //     printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    if (avg_wt > (total_wt / n))
    {
        avg_wt = (total_wt / n);
        strcpy(algorithm, "Round Robin");
    }
}
void Non_preemptive_Priority(struct Process p[], int n)
{
    int is_completed[n];
    int completed = 0;
    int current_time = 0, i;
    float total_wt = 0.0;
    for (i = 0; i < n; i++)
    {
        p[i].rt = p[i].bt;
        is_completed[i] = 0;
    }
    while (completed != n)
    {
        int best_index = -1;
        int max_priority = -1;
        for (i = 0; i < n; i++)
        {
            if (p[i].at <= current_time && !is_completed[i])
            {
                if (p[i].priority > max_priority)
                {
                    max_priority = p[i].priority;
                    best_index = i;
                }
                else if (p[i].priority == max_priority)
                {
                    if (p[i].at < p[best_index].at)
                    {
                        best_index = i;
                    }
                }
            }
        }
        if (best_index == -1)
        {
            current_time++;
        }
        else
        {
            p[best_index].ct = current_time + p[best_index].bt;
            p[best_index].tat = p[best_index].ct - p[best_index].at;
            p[best_index].wt = p[best_index].tat - p[best_index].bt;
            current_time = p[best_index].ct;
            total_wt += p[best_index].wt;
            is_completed[best_index] = 1;
            completed++;
        }
    }
    printf("Non Preemptive Priority -Avg Time :%f\n", total_wt / n);
    // printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    // for (i = 0; i < n; i++)
    //     printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    if (avg_wt > (total_wt / n))
    {
        avg_wt = (total_wt / n);
        strcpy(algorithm, "Non Preemptive Priority");
    }
}
void calculateSRTF(struct Process p[], int n)
{
    int completed = 0, current_time = 0, min_rt = 1e9;
    int shortest = 0, finish_time;
    int found = 0, i;
    float total_wt = 0.0;
    for (i = 0; i < n; i++)
    {
        p[i].rt = p[i].bt;
    }
    while (completed != n)
    {
        min_rt = 1e9;
        found = 0;
        for (i = 0; i < n; i++)
        {
            if (p[i].at <= current_time && p[i].rt > 0)
            {
                if (p[i].rt < min_rt)
                {
                    min_rt = p[i].rt;
                    shortest = i;
                    found=1;
                }
                else if (p[i].rt == min_rt)
                {
                    if (p[i].at < p[shortest].at)
                    {
                        shortest = i;
                        found=1;
                    }
                }
            }
        }
        if (found == 0)
        {
            current_time++;
            continue;
        }
        p[shortest].rt--;
        if (p[shortest].rt == 0)
        {
            completed++;
            finish_time = current_time + 1;
            p[shortest].ct = finish_time;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            total_wt += p[shortest].wt;
        }
        current_time++;
    }
    printf("SRTF -Avg Time :%f\n", total_wt / n);
    // printf("\nID\tAT\tBT\tCT\tTAT\tWT\n");
    // for (i = 0; i < n; i++)
    //     printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    if (avg_wt > (total_wt / n))
    {
        avg_wt = (total_wt / n);
        strcpy(algorithm, "SRTF");
    }
}
int main()
{
    int n, i, quantum;
    struct Process p[100];
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\n--- Process %d ---\n", i);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Enter Priority: ");
        scanf("%d", &p[i].priority);
    }
    printf("\nEnter quantum Time :");
    scanf("%d", &quantum);
    // printf("\n\nProcess Data Received:\n");
    // printf("ID\tAT\tBT\tPriority\n");
    // for (i = 0; i < n; i++)
    // {
    //     printf("%d\t%d\t%d\t%d\n", i, p[i].at, p[i].bt, p[i].priority);
    // }
    FCFS(p, n);
    calculateSRTF(p, n);
    Non_preemptive_Priority(p, n);
    round_robin(p, n, quantum);
    printf("\nAlgorithm with Minimum Average waiting time :%s", algorithm);
    return 0;
}
