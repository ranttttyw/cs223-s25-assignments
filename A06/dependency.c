#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DEPENDENCIES 100

struct tree_node {
    char *filename;
    char *dependencies[MAX_DEPENDENCIES];
    int dep_count;
    struct tree_node *left;
    struct tree_node *right;
};

struct tree_node* createNode(const char* filename) {
    struct tree_node* node = malloc(sizeof(struct tree_node));
    if (!node) {
        perror("malloc failed");
        exit(1);
    }
    node->filename = strdup(filename);
    node->dep_count = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void addDependency(struct tree_node *node, const char *dependency) {
    if (node->dep_count < MAX_DEPENDENCIES) {
        node->dependencies[node->dep_count++] = strdup(dependency);
    }
}

void parseDependencies(const char* filename, struct tree_node* node) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror(filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *include = strstr(line, "#include");
        if (include) {
            char dependency[256];
            if (sscanf(include, "#include \"%255[^\"]\"", dependency) == 1 ||
                sscanf(include, "#include <%255[^>]>", dependency) == 1) {
                addDependency(node, dependency);
            }
        }
    }
    fclose(file);
}

struct tree_node* insert(struct tree_node* root, const char* filename) {
    if (root == NULL) {
        struct tree_node* node = createNode(filename);
        parseDependencies(filename, node);
        return node;
    }

    int cmp = strcmp(filename, root->filename);
    if (cmp < 0) {
        root->left = insert(root->left, filename);
    } else if (cmp > 0) {
        root->right = insert(root->right, filename);
    }
    return root;
}

struct tree_node* find(struct tree_node* root, const char* filename) {
    if (root == NULL) return NULL;

    int cmp = strcmp(filename, root->filename);
    if (cmp == 0) return root;
    if (cmp < 0) return find(root->left, filename);
    return find(root->right, filename);
}

void printSorted(struct tree_node* root) {
    if (root == NULL) return;
    printSorted(root->left);
    printf("%s\n", root->filename);
    printSorted(root->right);
}

void showDependencies(struct tree_node* node) {
    if (node->dep_count == 0) {
        printf("%s has no dependencies\n", node->filename);
        return;
    }

    printf("%s has the following dependencies\n", node->filename);
    for (int i = 0; i < node->dep_count; i++) {
        printf("  %s\n", node->dependencies[i]);
    }
}

void freeTree(struct tree_node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);

    for (int i = 0; i < root->dep_count; i++) {
        free(root->dependencies[i]);
    }
    free(root->filename);
    free(root);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <files>\n", argv[0]);
        return 1;
    }

    struct tree_node* root = NULL;

    // Process files from command line
    int validFileCount = 0;
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file) {
            fclose(file);
            root = insert(root, argv[i]);
            validFileCount++;
        } else {
            fprintf(stderr, "Skipping invalid file: %s\n", argv[i]);
        }
    }

    printf("Processing %d files\n", validFileCount);

    // Command loop
    char command[256];
    while (1) {
        printf("$ ");  
        if (!fgets(command, sizeof(command), stdin)) {
            break;
        }

        // Remove newline at the end if present
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "quit") == 0) {
            break;
        } else if (strcmp(command, "list") == 0) {
            printSorted(root);
        } else {
            struct tree_node* node = find(root, command);
            if (node) {
                showDependencies(node);
            } else {
                printf("%s not found\n", command);
            }
        }
    }

    freeTree(root);
    return 0;
}
