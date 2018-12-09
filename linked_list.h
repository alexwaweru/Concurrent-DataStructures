/***************************************************************************//**
  @file         linked_list.c
  @author       Waweru, Alex Njoroge
  @date         Friday,  30 November 2018
  @brief        Concurrent linked list - Routines that operate concurrently on a linked list
*******************************************************************************/


// Header files
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>
#include <stdio.h>


// basic node structure

typedef struct __node_t {
  int key;
  struct __node_t *next;
} node_t;

// basic list structure 
typedef struct __list_t {
  node_t *head;
  pthread_mutex_t lock;
} list_t;


void List_Init(list_t *L) {
  L->head = NULL;
  pthread_mutex_init(&L->lock, NULL);
  printf("list successfully initiliazed\n");
}


int List_Insert(list_t *L, int key) {
  pthread_mutex_lock(&L->lock);
  node_t *new = malloc(sizeof(node_t));
  if (new == NULL) {
    perror("malloc\n");
    pthread_mutex_unlock(&L->lock);
    printf("%d not inserted due to memory error!\n", key);
    return -1; // fail
  }
  new->key  = key;
  new->next = L->head;
  L->head   = new;
  printf("%d successfully inserted at index 0\n", key);
  pthread_mutex_unlock(&L->lock);
  return 0; // success
}


int List_Lookup(list_t *L, int key) {
  pthread_mutex_lock(&L->lock);
  node_t *curr = L->head;
  int count = 0;
  while (curr) {
    if (curr->key == key) {
      pthread_mutex_unlock(&L->lock);
      printf("%d found at index %d\n", key, count);
      return 0; // success
    }
    curr = curr->next;
    count +=1;
  }
  pthread_mutex_unlock(&L->lock);
  printf("%d not found in the list\n", key);
  return -1; // failure
}


int List_Delete(list_t *L, int key) {
  pthread_mutex_lock(&L->lock);
  node_t *prev = NULL;
  node_t *curr = L->head;
  while (curr) {
    if (curr->key == key && !prev){
      *L->head = *L->head->next;
      pthread_mutex_unlock(&L->lock);
      printf("%d deleted successfully\n", key);
      return 0; // success
    }
    if (curr->key == key) {
      prev->next = curr->next;
      pthread_mutex_unlock(&L->lock);
      printf("%d deleted successfully\n", key);
      return 0; // success
    }
    prev = curr;
    curr = curr->next;
  }
  pthread_mutex_unlock(&L->lock);
  printf("%d was not found in the list\n", key);
  return -1; // failure
}
