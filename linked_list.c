/***************************************************************************//**
  @file         linked_list.c
  @author       Waweru, Alex Njoroge
  @date         Friday,  30 November 2018
  @brief        Concurrent linked list - Routines that operate concurrently on a linked list
*******************************************************************************/


// Header files
#include <stdlib.h>
#include <stdbool.h>


// Node structure and all the routines that operate on the node
 struct Node
 {
     void* data;
     struct Node *prev;
     struct Node *next;
 };

void* get_data(node)
    struct Node node;
    {
        return node.data;
    }

struct Node get_next(node)
    struct Node node;
    {
        return *node.next;
    }

void set_data(node, data)
    struct Node node;
    {
        node.data = data;
    }

void set_next(node1, node2)
    struct Node node1;
    struct Node node2;
    {
        node1.next = &node2;
    }


// Linked List structure and the routines that operate on it
struct LinkedList
{
    struct Node head;
};

struct Node get_head(list)
    struct LinkedList list;
    {
        return list.head;
    }

void set_head(list, head)
    struct LinkedList list;
    struct Node head;
    {
        list.head = head;
    }

bool is_empty(list)
    struct LinkedList list;
    {
        bool flag = false;
        struct Node head = get_head(list);
        if (&head == NULL)
        {
            flag = true;
        }
        return flag;
    }

void insert(list, data)
    struct LinkedList list;
    {
        struct Node node;
        set_data(node, data);
        set_next(node, get_head(list));
        set_head(list, node);
    }

int size(list)
    struct LinkedList list;
    {
        struct Node current = get_head(list);
        int count = 0;
        while (&current != NULL)
        {
            count += 1;
            current = get_next(current);
        }
        return count;
    }

bool search(list, data)
    struct LinkedList list;
    {
        struct Node current = get_head(list);
        bool found = false;
        while ((&current != NULL) && (found == false))
        {
            if (get_data(current) == data)
            {
                found = true;
            }
            else
            {
                current = get_next(current);
            }
        }
        return found;
    }

void delete(list, data)
    struct LinkedList list;
    {
        struct Node current = get_head(list);
        struct Node previous = { 0, NULL };
        bool found = false;
        while (found == false)
        {
            if (get_data(current) == data)
            {
                found = true;
            }
            else 
            {
                previous = current;
                current = get_next(current);
            }
        }
        if (&previous == NULL)
        {
            set_head(list, get_next(current));
        }
        else
        {
            set_next(previous, get_next(current));
        }
    }