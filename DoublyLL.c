#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
// Function to insert a node at the end of the list
void insertAtEnd(struct Node** head, char data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Function to delete a node from the list
void deleteNode(struct Node** head, struct Node* delNode) {
    if (*head == NULL || delNode == NULL) {
        return;
    }
    if (*head == delNode) {
        *head = delNode->next;
    }
    if (delNode->next != NULL) {
        delNode->next->prev = delNode->prev;
    }
    if (delNode->prev != NULL) {
        delNode->prev->next = delNode->next;
    }
    free(delNode);
}

// Function to display the list forward
void displayForward(struct Node* head) {
    printf("Forward: ");
    while(head!=NULL) {
        printf("%c ",head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to display the list backward
void displayBackward(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    printf("String in backward order: ");
    while (current != NULL) {
        printf("%c  " , current->data);
        current = current->prev;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove trailing newline

    // Insert each character of the string into the doubly linked list
    for (int i = 0; i < strlen(str); i++) {
        insertAtEnd(&head, str[i]);
    }

    // Display menu of operations
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Display string forward\n");
        printf("2. Display string backward\n");
        printf("3. Insert element in string\n");
        printf("4. Delete element in string\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayForward(head);
                break;
            case 2:
                displayBackward(head);
                break;
            case 3: {
                char data;
                printf("Enter the element to insert: ");
                scanf(" %c", &data);
                insertAtEnd(&head, data); // You can change this to insert at any desired position
                break;
            }
            case 4: {
                char data;
                printf("Enter the element to delete: ");
                scanf(" %c", &data);
                struct Node* current = head;
                while (current != NULL) {
                    if (current->data == data) {
                        struct Node* temp = current;
                        current = current->next;
                        deleteNode(&head, temp);
                    } else {
                        current = current->next;
                    }
                }
                break;
            }
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

return 0;
}
