#include <stdio.h>
#include <string.h>

struct Day {
    char dayName[10];
    char tasks[3][50]; 
    int taskCount;
};

int main() {
    struct Day week[7] = {
        {"Monday", {}, 0}, {"Tuesday", {}, 0}, {"Wednesday", {}, 0},
        {"Thursday", {}, 0}, {"Friday", {}, 0}, {"Saturday", {}, 0}, {"Sunday", {}, 0}
    };

    int dayIndex, numTasks;
    char tempTask[50];
    int i, j;

    for (i = 0; i < 7; i++) {
        printf("Enter number of tasks for %s (max 3): ", week[i].dayName);
        scanf("%d", &numTasks);
        getchar(); 
        week[i].taskCount = numTasks;

        for (j = 0; j < numTasks && j < 3; j++) {
            printf("Enter task %d: ", j + 1);
            fgets(week[i].tasks[j], 50, stdin);
            week[i].tasks[j][strcspn(week[i].tasks[j], "\n")] = 0; 
        }
    }

    printf("\nWeekly Calendar:\n");
    for (i = 0; i < 7; i++) {
        printf("%s:\n", week[i].dayName);
        for (j = 0; j < week[i].taskCount; j++) {
            printf("  - %s\n", week[i].tasks[j]);
        }
    }

    return 0;
}

