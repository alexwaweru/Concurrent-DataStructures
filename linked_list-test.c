/***************************************************************************//**
  @file         linked_list.c
  @author       Waweru, Alex Njoroge
  @date         Friday,  30 November 2018
  @brief        Concurrent linked list Tests - Routines that test the behaviour of the concurrent linked list
*******************************************************************************/


// Header files
#include "linked_list.h"

// Structure | unit tests
int structure_tests(){
  printf("running linked list structure and functionalities tests...\n");
  printf("______________________________________________________________\n");
  printf("\n");
  list_t *list;
  
  // tests for List_Init function
  printf("running tests on List_Init function...\n");
  List_Init(&list);
  assert(&list->head == NULL);
  printf("\n");

  // tests for List_Insert function
  printf("running tests on List_Insert function...\n");
  printf("note: all insertions happen at the beginning of the list\n");
  int insert_state;
  printf("\033[1;36m");
  printf("trying to insert 5 into an empty list...\n");
  printf("\033[0m");
  insert_state = List_Insert(&list, 5);
  assert(insert_state == 0);
  assert(&list->head->key == 5);
  printf("\033[1;36m");
  printf("trying to inser 10 into a list containing 5...\n");
  printf("\033[0m");
  insert_state = List_Insert(&list, 10);
  assert(insert_state == 0);
  assert(&list->head->key == 10);
  printf("\033[1;36m");
  printf("trying to inser 20 into a list containing 10 and 5...\n");
  printf("\033[0m");
  insert_state = List_Insert(&list, 20);
  assert(insert_state == 0);
  assert(&list->head->key == 20);
  printf("\n");

  // tests for List_Lookup function
  printf("running tests on List_Lookup function...\n");
  int look_up_state;
  printf("\033[1;36m");
  printf("trying to search for 5 which is at index 2 of the list...\n");
  printf("\033[0m");
  look_up_state = List_Lookup(&list, 5);
  assert(look_up_state == 0);
  printf("\033[1;36m");
  printf("trying to search for 20 which is at index 0 of the list...\n");
  printf("\033[0m");
  look_up_state = List_Lookup(&list, 20);
  assert(look_up_state == 0);
  printf("\033[1;36m");
  printf("trying to search for 50 which is not in the list...\n");
  printf("\033[0m");
  look_up_state = List_Lookup(&list, 50);
  assert(look_up_state == -1);
  printf("\033[1;36m");
  printf("trying to search for 4 which is not in the list...\n");
  printf("\033[0m");
  look_up_state = List_Lookup(&list, 4);
  assert(look_up_state == -1);
  printf("\n");

  // tests for List_Delete function
  printf("running tests on List_Delete function...\n");
  int delete_state;
  printf("\033[1;36m");
  printf("trying to delete 20 which is at index 0 of the list...\n");
  printf("\033[0m");
  delete_state = List_Delete(&list, 20);
  assert(delete_state == 0);
  assert(&list->head->key == 10);
  assert(List_Lookup(&list, 20) == -1);
  printf("\033[1;36m");
  printf("trying to delete 10 which is now at index 0 of the list...\n");
  printf("\033[0m");
  delete_state = List_Delete(&list, 10);
  assert(delete_state == 0);
  assert(&list->head->key == 5);
  assert(List_Lookup(&list, 10) == -1);
  printf("\033[1;36m");
  printf("trying to delete 100 which is not in the list...\n");
  printf("\033[0m");
  delete_state = List_Delete(&list, 100);
  assert(delete_state == -1);
  printf("\n");
  printf("structural and functional tests complete!\n");
  return 0;
}


// Concurrency tests
void test_list1(int argc, char const *argv[])
{
  printf("Thread 1\n");
  list_t *list1;
  List_Init(&list1);
  List_Insert(&list1, 5);
  List_Lookup(&list1, 5);
  List_Insert(&list1, 10);
  List_Delete(&list1, 5);
}


void test_list2(int argc, char const *argv[])
{
  printf("Thread 2\n");
  list_t *list2;
  List_Init(&list2);
  List_Insert(&list2, 10);
  List_Insert(&list2, 20);
  List_Lookup(&list2, 10);
  List_Delete(&list2, 10);
}


int main(){
  printf("\033[1;38m");
  printf("Test Results for Concurrent Linked List\n");
  printf("*********************************************\n");
  printf("\033[0m");
  //structure_tests
  structure_tests();

  //Concurrency tests
  printf("running linked list concurrency tests for insert and delete...\n");
  printf("______________________________________________________________\n");
  printf("\n");
  pthread_t p1, p2;
  printf("main: begin\n");
  pthread_create(&p1, NULL, test_list1, "A");
  pthread_create(&p2, NULL, test_list2, "B");

  // join waits for the threads to finish
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  printf("main: end\n");
  return 0;
}