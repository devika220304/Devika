#include <stdio.h>
#include <stdlib.h>

// Structure for a threaded binary tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    int isThreaded; // Indicates if the right pointer is a thread
};

// Create a new threaded binary tree node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 0; // Initially, the right pointer is not a thread
    return newNode;
}

// Function to insert a new node into the threaded binary search tree
void insert(struct TreeNode** root, int data) {
    struct TreeNode* newNode = createNode(data);
    struct TreeNode* current = *root;
    struct TreeNode* parent = NULL;

    // Traverse the tree to find the appropriate position for insertion
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            if (current->left == NULL) {
                current->left = newNode;
                newNode->right = current; // Thread the new node to its predecessor
                newNode->isThreaded = 1;
                return;
            }
            current = current->left;
        } else {
            if (current->isThreaded == 0) {
                newNode->right = current->right; // Thread the new node to the successor of the current node
                current->right = newNode;
                current->isThreaded = 1;
                return;
            }
            current = current->right;
        }
    }

    // If the tree is empty, the new node becomes the root
    if (parent == NULL) {
        *root = newNode;
    }
}

// Function to perform in-order traversal of threaded binary search tree
void inOrder(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Find the leftmost node
    struct TreeNode* current = root;
    while (current->left != NULL) {
        current = current->left;
    }

    // Traverse the threaded tree
    while (current != NULL) {
        printf("%d ", current->data);
        // If the right pointer is a thread, move to the inorder successor
        if (current->isThreaded) {
            current = current->right;
        } else {
            // Otherwise, move to the leftmost node in the right subtree
            current = current->right;
            while (current != NULL && current->left != NULL) {
                current = current->left;
            }
        }
    }
}

int main() {
    struct TreeNode* root = NULL;
    int numNodes, data;

    printf("Threaded Binary Tree");
    printf("\nEnter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the data for each node:\n");
    for (int i = 0; i < numNodes; i++) {
        scanf("%d", &data);
        insert(&root, data);
    }

    // Perform in-order traversal
    printf("In-order traversal of threaded binary search tree: ");
    inOrder(root);
    printf("\n");

    return 0;
}
