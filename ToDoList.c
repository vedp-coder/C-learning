#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TASK_LENGTH 100
#define FILENAME "tasks.txt"

// Structure for a task
struct Task {
    char description[MAX_TASK_LENGTH];
    int completed;  // 0 = incomplete, 1 = complete
};

// Function to display the menu
void displayMenu() {
    printf("\n===== To-Do List Manager =====\n");
    printf("1. Add a new task\n");
    printf("2. View all tasks\n");
    printf("3. Mark a task as completed\n");
    printf("4. Remove a task\n");
    printf("5. Save tasks to file\n");
    printf("6. Load tasks from file\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

// Function to add a new task
void addTask(struct Task tasks[], int *taskCount) {
    if (*taskCount >= MAX_TASKS) {
        printf("Error: Task limit reached!\n");
        return;
    }
    
    printf("Enter task description: ");
    getchar();  // Clear input buffer
    fgets(tasks[*taskCount].description, MAX_TASK_LENGTH, stdin);
    
    // Remove newline character if present
    size_t len = strlen(tasks[*taskCount].description);
    if (len > 0 && tasks[*taskCount].description[len-1] == '\n') {
        tasks[*taskCount].description[len-1] = '\0';
    }
    
    tasks[*taskCount].completed = 0;
    (*taskCount)++;
    printf("Task added successfully!\n");
}

// Function to display all tasks
void viewTasks(struct Task tasks[], int taskCount) {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }
    
    printf("\n===== Your Tasks =====\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. [%s] %s\n", i+1, 
               tasks[i].completed ? "X" : " ", 
               tasks[i].description);
    }
}

// Function to mark a task as completed
void markCompleted(struct Task tasks[], int taskCount) {
    int taskNumber;
    
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }
    
    viewTasks(tasks, taskCount);
    
    printf("Enter task number to mark as completed: ");
    scanf("%d", &taskNumber);
    
    if (taskNumber < 1 || taskNumber > taskCount) {
        printf("Invalid task number!\n");
        return;
    }
    
    tasks[taskNumber-1].completed = 1;
    printf("Task marked as completed!\n");
}

// Function to remove a task
void removeTask(struct Task tasks[], int *taskCount) {
    int taskNumber;
    
    if (*taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }
    
    viewTasks(tasks, *taskCount);
    
    printf("Enter task number to remove: ");
    scanf("%d", &taskNumber);
    
    if (taskNumber < 1 || taskNumber > *taskCount) {
        printf("Invalid task number!\n");
        return;
    }
    
    // Shift all tasks after the removed one
    for (int i = taskNumber - 1; i < *taskCount - 1; i++) {
        strcpy(tasks[i].description, tasks[i+1].description);
        tasks[i].completed = tasks[i+1].completed;
    }
    
    (*taskCount)--;
    printf("Task removed successfully!\n");
}

// Function to save tasks to a file
void saveToFile(struct Task tasks[], int taskCount) {
    FILE *file = fopen(FILENAME, "w");
    
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    
    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%d,%s\n", tasks[i].completed, tasks[i].description);
    }
    
    fclose(file);
    printf("Tasks saved to file successfully!\n");
}

// Function to load tasks from a file
void loadFromFile(struct Task tasks[], int *taskCount) {
    FILE *file = fopen(FILENAME, "r");
    
    if (file == NULL) {
        printf("No saved tasks file found!\n");
        return;
    }
    
    *taskCount = 0;
    char line[MAX_TASK_LENGTH + 10];  // Extra space for status flag
    
    while (fgets(line, sizeof(line), file) && *taskCount < MAX_TASKS) {
        char *statusStr = strtok(line, ",");
        char *description = strtok(NULL, "\n");
        
        if (statusStr && description) {
            tasks[*taskCount].completed = atoi(statusStr);
            strcpy(tasks[*taskCount].description, description);
            (*taskCount)++;
        }
    }
    
    fclose(file);
    printf("Tasks loaded from file successfully!\n");
}

int main() {
    struct Task tasks[MAX_TASKS];
    int taskCount = 0;
    int choice;
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                viewTasks(tasks, taskCount);
                break;
            case 3:
                markCompleted(tasks, taskCount);
                break;
            case 4:
                removeTask(tasks, &taskCount);
                break;
            case 5:
                saveToFile(tasks, taskCount);
                break;
            case 6:
                loadFromFile(tasks, &taskCount);
                break;
            case 0:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
    
    return 0;
}
