/*----------------------------------------------
 * Author: Ranty Wang
 * Date: 4/22/2025
 * Description: My malloc
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int used;
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  // TODO: Implement malloc with a free list (See reading for details)
  if (size == 0) return NULL;

  struct chunk *prev = NULL;
  struct chunk *curr = flist;

  // Find a suitable chunk (first-fit)
  while (curr != NULL) {
    if (curr->size >= (int)size) {
      // Remove from free list
      if (prev == NULL) {
        flist = curr->next;
      } else {
        prev->next = curr->next;
      }

      curr->used = size;
      curr->next = NULL;
      return (void *)(curr + 1); // Return memory after header
    }
    prev = curr;
    curr = curr->next;
}

 // No suitable chunk found
 struct chunk *new_chunk = (struct chunk *)sbrk(sizeof(struct chunk) + size);
 if (new_chunk == (void *)-1) return NULL;

 new_chunk->size = size;
 new_chunk->used = size;
 new_chunk->next = NULL;

 return (void *)(new_chunk + 1); // Return memory after header
}

void free(void *memory) {
  // TODO: Implement malloc with a free list (See reading for details)
  if (memory == NULL) return;

  struct chunk *chunk_to_free = ((struct chunk *)memory) - 1;

  chunk_to_free->next = flist;
  flist = chunk_to_free;
}
