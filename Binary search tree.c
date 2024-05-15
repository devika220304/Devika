#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a node in the binary search tree
struct TreeNode {
    char mnemonic[20];
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new node
struct TreeNode* createNode(char mnemonic[]) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    strcpy(newNode->mnemonic, mnemonic);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary search tree
struct TreeNode* insertNode(struct TreeNode* root, char mnemonic[]) {
    if (root == NULL) {
        return createNode(mnemonic);
    }

    if (strcmp(mnemonic, root->mnemonic) < 0) {
        root->left = insertNode(root->left, mnemonic);
    } else if (strcmp(mnemonic, root->mnemonic) > 0) {
        root->right = insertNode(root->right, mnemonic);
    }

    return root;
}

// Function to display the tree level-wise
void displayLevelOrder(struct TreeNode* root) {
    if (root == NULL)
        return;

    // Create an array to store nodes at each level
    struct TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* tempNode = queue[front++];
        printf("%s ", tempNode->mnemonic);

        if (tempNode->left != NULL)
            queue[rear++] = tempNode->left;
        if (tempNode->right != NULL)
            queue[rear++] = tempNode->right;
    }
}

// Function to find the height of the tree
int getHeight(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    else {
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);

        if (leftHeight > rightHeight)
            return (leftHeight + 1);
        else
            return (rightHeight + 1);
    }
}

// Function to search for a node in the tree
struct TreeNode* searchNode(struct TreeNode* root, char mnemonic[]) {
    if (root == NULL || strcmp(root->mnemonic, mnemonic) == 0)
        return root;

    if (strcmp(root->mnemonic, mnemonic) < 0)
        return searchNode(root->right, mnemonic);

    return searchNode(root->left, mnemonic);
}

int main() {
    struct TreeNode* root = NULL;

    char choice;
    char mnemonic[20];

    do {
        printf("\nBinary Search Tree:\n");
        printf("1. Insert a mnemonic\n");
        printf("2. Display level-wise\n");
        printf("3. Height of the tree\n");
        printf("4. Search a mnemonic\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printf("Enter the mnemonic to insert: ");
                scanf("%s", mnemonic);
                root = insertNode(root, mnemonic);
                break;
            case '2':
                printf("Level-wise display of the tree: ");
                displayLevelOrder(root);
                printf("\n");
                break;
            case '3':
                printf("Height of the tree: %d\n", getHeight(root));
                break;
            case '4':
                printf("Enter a mnemonic to search: ");
                scanf("%s", mnemonic);
                struct TreeNode* searchedNode = searchNode(root, mnemonic);
                if (searchedNode != NULL)
                    printf("Node found: %s\n", searchedNode->mnemonic);
                else
                    printf("Node not found.\n");
                break;
            case '5':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != '5');

    return 0;
}
