#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// task node definition
struct TaskNode {
    char description[1000];
    int priority;
    int is_completed;
    struct TaskNode* next_task;
};

// category node defintion

struct CategoryNode {
    char category[500];
    struct TaskNode* task_list_head; // first task inside category
    struct CategoryNode* next_category;
};

void add_category(struct CategoryNode** category_list_head);
void add_task(struct TaskNode** task_list_head, struct CategoryNode** category_list_head);
void delete_category(struct CategoryNode** category_list_head);
void delete_task(struct CategoryNode* category_list_head);
void view_category(struct CategoryNode* category_list_head);



int main(){


    struct CategoryNode* category_list_head = NULL; // Initialize head of category list
    struct TaskNode* task_list_head = NULL; // Initialize head of task list

    int selection;
    int task_count = 0;
    int category_count = 0;


    while (1)
    {
    printf("\nTo begin, follow the instructions given below, note that there will be several questions to successfully input the desired action\n");
    printf("1. Create a new category\n");
    printf("2. Create a new task\n");
    printf("3. Delete a Category\n");
    printf("4. Delete a task\n");
    printf("5. View a Category with all its tasks\n");
    printf("6. Exit\n");
    printf("\nPlease select an option: ");
    scanf("%d", &selection);
    getchar();

    
    switch(selection){

        case 1:
        add_category(&category_list_head);
        break;

        case 2:
        add_task(&task_list_head, &category_list_head);
        break;

        case 3:
        delete_category(&category_list_head);
        break;

        case 4:
        delete_task(category_list_head);
        break;

        case 5:
        view_category(category_list_head);
        break;

        case 6:
        return 0;
        
        default:
        printf("INVALID INPUT\n");
        }
    }

    printf("------------------------------------------------\n");
    
    return 0;
}

void view_category(struct CategoryNode* head) {
    char input_name[100];

    printf("Enter category name to view: ");
    scanf(" %[^\n]", input_name);  // reads full line including spaces

    struct CategoryNode* curr = head;

    while (curr != NULL) {
        if (strcmp(curr->category, input_name) == 0) {
            printf("\nCategory: %s\n", curr->category);
            
            struct TaskNode* task = curr->task_list_head;
            if (task == NULL) {
                printf("  No tasks in this category.\n\n");
                return;
            }

            // Bubble sort the tasks based on priority (higher priority first)
            struct TaskNode *i, *j;
            int temp_priority;
            char temp_description[1000];
            while (task != NULL) {
                i = task;
                while (i->next_task != NULL) {
                    if (i->priority > i->next_task->priority) {
                        // Swap tasks if out of order (higher priority first)
                        temp_priority = i->priority;
                        i->priority = i->next_task->priority;
                        i->next_task->priority = temp_priority;

                        // Swap descriptions as well
                        strcpy(temp_description, i->description);
                        strcpy(i->description, i->next_task->description);
                        strcpy(i->next_task->description, temp_description);
                    }
                    i = i->next_task;
                }
                task = task->next_task;
            }

            printf("  Tasks (sorted by priority):\n");
            task = curr->task_list_head;
            while (task != NULL) {
                printf("    - (%d) %s\n", task->priority, task->description);
                task = task->next_task;
            }
            printf("\n");
            return;
        }
        curr = curr->next_category;
    }

    printf("Category \"%s\" not found.\n\n", input_name);
}

void add_category(struct CategoryNode** category_list_head)
{
    struct CategoryNode* new_category = (struct CategoryNode*)malloc(sizeof(struct CategoryNode)); 


    if (new_category == NULL)
    {
        printf("Error, there isn't any categories!\n");
        return;
    }



    printf("What is the name of this Category?: ");
    fgets(new_category->category, sizeof(new_category->category), stdin);

    new_category->category[strcspn(new_category->category, "\n")] = 0;

    // Initialize task list head to NULL since this category starts with no tasks
    new_category->task_list_head = NULL;
    new_category->next_category = NULL;


    
    if (*category_list_head == NULL)
    {
        *category_list_head = new_category;
    }
    else{
            struct CategoryNode* temp = *category_list_head;
            while(temp->next_category != NULL)
            {
                temp = temp->next_category;
            }

            temp->next_category = new_category;
    }
    printf("\nCategory '%s' added successfully!\n", new_category->category); 

}

void add_task(struct TaskNode** unused, struct CategoryNode** category_list_head)
{
    if (*category_list_head == NULL) {
        printf("You must create a category first.\n");
        return;
    }

    struct TaskNode* new_task = malloc(sizeof(struct TaskNode));
    if (new_task == NULL) {
        printf("Memory allocation failed for new task.\n");
        return;
    }

    printf("Enter task priority (1 = High, 2 = Medium, 3 = Low): ");
    scanf("%d", &new_task->priority);
    while (new_task->priority < 1 || new_task->priority > 3) {
        printf("Invalid input. Must be 1, 2, or 3: ");
        scanf("%d", &new_task->priority);
    }
    getchar(); // consume newline

    printf("Enter task description: ");
    fgets(new_task->description, sizeof(new_task->description), stdin);
    new_task->description[strcspn(new_task->description, "\n")] = 0;
    new_task->is_completed = 0;
    new_task->next_task = NULL;

    printf("Available categories:\n");
    struct CategoryNode* current = *category_list_head;
    while (current != NULL) {
        printf("- %s\n", current->category);
        current = current->next_category;
    }

    char target_category[500];
    printf("Enter the category to assign this task to: ");
    fgets(target_category, sizeof(target_category), stdin);
    target_category[strcspn(target_category, "\n")] = 0;

    current = *category_list_head;
    while (current != NULL && strcmp(current->category, target_category) != 0) {
        current = current->next_category;
    }

    if (current == NULL) {
        printf("Category '%s' not found.\n", target_category);
        free(new_task);
        return;
    }

    if (current->task_list_head == NULL) {
        current->task_list_head = new_task;
    } else {
        struct TaskNode* temp = current->task_list_head;
        while (temp->next_task != NULL) {
            temp = temp->next_task;
        }
        temp->next_task = new_task;
    }

    printf("Task successfully added to category '%s'.\n", target_category);
}
void delete_category(struct CategoryNode** category_head_list)
{
    char deleted_category[500];
    
    struct CategoryNode* current_category = *category_head_list;
    struct CategoryNode* previous_category = NULL;



    if (current_category == NULL)
    {
        printf("Error, there aren't any categories!\n");
        return;
    }

    printf("What is the category you would like to delete?: ");

    
    
    // Get input from user and clear newline
    fgets(deleted_category, sizeof(deleted_category), stdin);
    deleted_category[strcspn(deleted_category, "\n")] = 0;  // Remove trailing newline

    // Check if the head node matches the category to delete
    if (strcmp(current_category->category, deleted_category) == 0)
    {
        *category_head_list = current_category->next_category; // Update head of the list

        // Free all tasks in the category
        struct TaskNode* current_task = current_category->task_list_head;
        while (current_task != NULL) {
            struct TaskNode* temp_task = current_task;
            current_task = current_task->next_task;
            free(temp_task);
        }

        // Free the category node itself
        free(current_category);
        printf("Category '%s' has been successfully deleted\n", deleted_category);
        return;
    }

    // Traverse to find the category to delete
    while (current_category != NULL && strcmp(current_category->category, deleted_category) != 0)
    {
        previous_category = current_category;
        current_category = current_category->next_category;
    }

    // If the category was found and it's not the head
    if (current_category != NULL)
    {
        previous_category->next_category = current_category->next_category;

        // Free all tasks in the category
        struct TaskNode* current_task = current_category->task_list_head;
        while (current_task != NULL) {
            struct TaskNode* temp_task = current_task;
            current_task = current_task->next_task;
            free(temp_task);
        }

        // Free the category node itself
        free(current_category);
        printf("Category '%s' has been successfully deleted\n", deleted_category);
    }
    else
    {
        printf("Category '%s' not found!\n", deleted_category);
    }
}

void delete_task(struct CategoryNode* category_list_head) {
    if (category_list_head == NULL) {
        printf("No categories available.\n");
        return;
    }

    char selected_category[500];
    printf("Enter the category that contains the task: ");
    fgets(selected_category, sizeof(selected_category), stdin);
    selected_category[strcspn(selected_category, "\n")] = '\0';

    // Find the category
    struct CategoryNode* category = category_list_head;
    while (category && strcmp(category->category, selected_category) != 0) {
        category = category->next_category;
    }

    if (!category) {
        printf("Category '%s' not found.\n", selected_category);
        return;
    }

    if (category->task_list_head == NULL) {
        printf("No tasks in this category.\n");
        return;
    }

    // Display tasks with numbering
    printf("Tasks in '%s':\n", category->category);
    struct TaskNode* current = category->task_list_head;
    int index = 1;
    while (current) {
        printf("%d. [%s] Priority %d\n", index, current->description, current->priority);
        current = current->next_task;
        index++;
    }

    int task_number;
    printf("Enter the number of the task to delete: ");
    scanf("%d", &task_number);
    getchar(); // Clear newline

    if (task_number < 1 || task_number >= index) {
        printf("Invalid task number.\n");
        return;
    }

    // Delete task at position task_number
    struct TaskNode* prev = NULL;
    current = category->task_list_head;
    for (int i = 1; i < task_number; i++) {
        prev = current;
        current = current->next_task;
    }

    if (prev == NULL) {
        category->task_list_head = current->next_task;
    } else {
        prev->next_task = current->next_task;
    }

    printf("Task '%s' deleted successfully.\n", current->description);
    free(current);
}
