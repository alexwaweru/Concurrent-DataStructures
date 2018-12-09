/*
********************************
Joshua Kasirye
Concurrent Hash Table Data Structure
OS Project
********************************
*/

//including necessary libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#include <stdio.h>
#include <unistd.h>

//threads
pthread_t thread1, thread2;

//Locks
pthread_mutex_t mutexI = PTHREAD_MUTEX_INITIALIZER; //initializing the insert lock
pthread_mutex_t mutexD = PTHREAD_MUTEX_INITIALIZER; //initializing the delete lock
#define SIZE 10

//Struct for related variables to be stored memory
struct DataItem {
   int data;  // data to be stored
   int key;   // primary key (index numbers)
};

struct DataItem* hashArray[SIZE]; //creating the hash table array
struct DataItem* dummyItem; //dummy data after delrtion
struct DataItem* item;  //item to be stored,searched for or deleted
struct DataItem* args;

//hashing function to get the index
int hashCode(int key) {
   return key % SIZE;
}

//memory searching function for the item
struct DataItem *search(int key) {
   //get the hash
   int hashIndex = hashCode(key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {
      if(hashArray[hashIndex]->key == key)
          return hashArray[hashIndex];
      //go to next cell
      ++hashIndex;
      //wrap around the table
      hashIndex %= SIZE;
   }

   return NULL;
}

//Item inserting function (int indexNumber, int value)
void insert(int key,int data) {
    pthread_mutex_lock(&mutexI);//locking the critical section

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->data = data;
   item->key = key;

   //get the hash
   int hashIndex = hashCode(key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }
   hashArray[hashIndex] = item;
   printf("%d data of item being inserted using key %d \n",data,key);

   pthread_mutex_unlock(&mutexI); //unlocking the critical section
}

//Deleting function (Item)
struct DataItem* delete1(struct DataItem* item) {
   pthread_mutex_lock(&mutexD);//locking the critical section
   int key = item->key;
   //get the hash
   int hashIndex = hashCode(key);
   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {
      if(hashArray[hashIndex]->key == key) {
         struct DataItem* temp = hashArray[hashIndex];
         //assign a dummy item at deleted position
         printf(" (%d,%d) Item deleted \n",hashArray[hashIndex]->key,hashArray[hashIndex]->data);
         hashArray[hashIndex] = dummyItem;
         return temp;
      }
      //go to next cell
      ++hashIndex;

      //wrap around the table
      hashIndex %= SIZE;
   }
   printf("Item was not deleted \n");
   pthread_mutex_unlock(&mutexD); //unlocking the critical section
   return NULL;
}

//Displaying of the table and results function
void display() {
   int i = 0;
   printf("Hash Table: {");
   //looping through the HT array
   for(i = 0; i<SIZE; i++) {
       //char *name = data;
      if(hashArray[i] != NULL)
         printf("(%d,%d)",hashArray[i]->key,hashArray[i]->data);
      else
         printf(" (NONE)");
   }
    printf("}\n");
   printf("\n");
}


