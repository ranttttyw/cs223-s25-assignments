#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct tree_node* createNode(const char* name) {
  struct tree_node* newNode = malloc(sizeof(struct tree_node));
  if (newNode == NULL) {
      perror("Failed to allocate memory");
      exit(EXIT_FAILURE);
  }
  strncpy(newNode->data.name, name, sizeof(newNode->data.name) - 1);
  newNode->data.name[sizeof(newNode->data.name) - 1] = '\0'; 
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

struct tree_node* find(const char* name, struct tree_node* root) {
  if (root == NULL) {
      return NULL;
  }
  int cmp = strcmp(name, root->data.name);
  if (cmp == 0) {
      return root;
  } else if (cmp < 0) {
      return find(name, root->left);
  } else {
      return find(name, root->right);
  }
}

struct tree_node* insert(const char* name, struct tree_node* root) {
  if (root == NULL) {
      return createNode(name);
  }
  if (strcmp(name, root->data.name) < 0) {
      root->left = insert(name, root->left);
  } else if (strcmp(name, root->data.name) > 0) {
      root->right = insert(name, root->right);
  }
  return root;
}

void clear(struct tree_node* root) {
  if (root == NULL) return;
  clear(root->left);
  clear(root->right);
  free(root);
}


void printTreeHelper(struct tree_node* root, int depth) {
  if (root == NULL) return;
  for (int i = 0; i < depth; i++) {
      printf(" ");
  }
  printf("%s\n", root->data.name);
  printTreeHelper(root->left, depth + 1);
  printTreeHelper(root->right, depth + 1);
}

void print(struct tree_node* root) {
  printTreeHelper(root, 0);
}

void printSorted(struct tree_node* root) {
  if (root == NULL) return;
  printSorted(root->left);
  printf("%s\n", root->data.name);
  printSorted(root->right);
}
