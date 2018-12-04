/***************************************************************************//**
  @file         linked_list.c
  @author       Waweru, Alex Njoroge
  @date         Friday,  30 November 2018
  @brief        Concurrent linked list Tests - Routines that test the behaviour of the concurrent linked list
*******************************************************************************/


// Header files
#include "linked_list.h"

// Structure tests
void structure_tests(){
  printf("Running linked list structure and functionalities tests...\n");
  printf("______________________________________________________________\n");
  list_t *list;
  
  // tests for List_Init function
  printf("Running tests on List_Init function...\n");
  List_Init(&list);
  assert(&list->head == NULL);
  printf("\n");

  // tests for List_Insert function
  printf("Running tests on List_Insert function...\n");
  int insert_state;
  insert_state = List_Insert(&list, 5);
  assert(insert_state == 0);
  assert(&list->head->key == 5);
  insert_state = List_Insert(&list, 10);
  assert(insert_state == 0);
  assert(&list->head->key == 10);
  insert_state = List_Insert(&list, 20);
  assert(insert_state == 0);
  assert(&list->head->key == 20);
  printf("\n");

  // tests for List_Lookup function
  printf("Running tests on List_Lookup function...\n");
  int look_up_state;
  look_up_state = List_Lookup(&list, 5);
  assert(look_up_state == 0);
  look_up_state = List_Lookup(&list, 20);
  assert(look_up_state == 0);
  look_up_state = List_Lookup(&list, 50);
  assert(look_up_state == -1);
  look_up_state = List_Lookup(&list, 4);
  assert(look_up_state == -1);
  printf("\n");

  // tests for List_Delete function
  printf("Running tests on List_Delete function...\n");
  int delete_state;
  delete_state = List_Delete(&list, 20);
  assert(delete_state == 0);
  assert(&list->head->key == 10);
  assert(List_Lookup(&list, 20) == -1);
  delete_state = List_Delete(&list, 10);
  assert(delete_state == 0);
  assert(&list->head->key == 5);
  assert(List_Lookup(&list, 10) == -1);
  delete_state = List_Delete(&list, 100);
  assert(delete_state == -1);
  printf("\n");

  printf("Structural and functional tests complete!");
}



// Unit Tests


// Concurrency tests

int main(){
  structure_tests();
}