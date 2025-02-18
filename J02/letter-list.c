# include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct node{
  char c;
  struct node* next;
}; 

struct node* insert_first(char character, struct node* previousC) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->c = character;
    newNode->next = previousC;
    return newNode;
}

int main() {
  printf("Enter a word:");
  char word[31];
  scanf("%s", word);
  char removeC;
  printf("Enter a character remove:");
  scanf(" %c", &removeC);

  struct node *list;
  list = NULL;

  for (int i = strlen(word) - 1 ; i > -1; i--) {
    if (word[i] != removeC) {
      list = insert_first(word[i], list);
    }
  }

  for(struct node * n = list; n!= NULL; n = n->next) {
    printf("%c",n->c);
  }
  struct node* curr = list;
  struct node* next = NULL;
  while(curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  return 0;
  printf("/n");
}
