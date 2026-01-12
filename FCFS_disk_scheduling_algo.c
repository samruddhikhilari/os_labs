#include <stdio.h>
#include <stdlib.h>

void fcfs(int requests[], int n, int head)
{
    int total_movement = 0;

    printf("Order of disk access:\n");
    printf("%d -> ", head); // Starting head position

    for (int i = 0; i < n; i++)
    {
        total_movement += abs(requests[i] - head);
        head = requests[i];
        printf("%d%s", head, (i == n - 1) ? "\n" : " -> ");
    }

    printf("Total head movement: %d\n", total_movement);
}

int main()
{
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 53;

    printf("Initial head position: %d\n", head);
    fcfs(requests, n, head);

    return 0;
}
