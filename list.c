// list/list.c
// 
// Implementation for linked list.
//
// <Saujanya Thapaliya>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {
  node_t *current = l -> head;
  node_t *next;

  while (current != NULL){
    next = current->next;
    free(current);
    current = next;
  }

  free(l);
}

void list_print(list_t *l) {
  node_t *current = l->head;

  while (current != NULL){
    printf("%d -> ", current -> value);
    current = current->next;
  }
  printf("NULL\n");

}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 1024);
  char tbuf[20];

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) { 
  int length = 0;
  node_t *current = l -> head;

  while (current != NULL) {
    length ++;
    current = current -> next;
  }
    return length; 
}


void list_add_to_back(list_t *l, elem value) {
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = NULL;

  if (l -> head == NULL){
    l->head = new_node;
  } else {
    node_t *current = l->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
}

void list_add_to_front(list_t *l, elem value) {
     node_t* cur_node = (node_t *) malloc(sizeof(node_t));
     cur_node->value = value;
     cur_node->next = l -> head;

     l->head = cur_node;

}

void list_add_at_index(list_t *l, elem value, int index) {
  if (index < 1) {
        list_add_to_front(l, value);
        return;
    }
    
    if (index == 1) {  
        list_add_to_front(l, value);
        return;
    }

    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = NULL;

    node_t *current = l->head;
    int current_index = 1;

    while (current != NULL && current_index < index - 1) {
        current = current->next;
        current_index++;
    }

    if (current == NULL) {
        free(new_node);  
        return;
    }

    new_node->next = current->next;
    current->next = new_node;
}


elem list_remove_from_back(list_t *l) {
  if (l->head == NULL) return -1;
  node_t *current = l->head;
  node_t *prev = NULL;

  while (current->next != NULL){
    prev = current;
    current = current -> next;
  }

  elem value = current->value;
  free(current);

  if (prev== NULL){
    l->head = NULL;
  } else{
    prev->next = NULL;
  }
  return value; 
}

elem list_remove_from_front(list_t *l) { 
  if (l->head == NULL) return -1;

  node_t*to_remove = l->head;
  elem value = to_remove->value;

  l->head = l->head->next;
  free(to_remove);
  return value;
  
}

elem list_remove_at_index(list_t *l, int index) {
    if (l->head == NULL || index < 1) {
        return -1; 
    }

    node_t *current = l->head;
    elem removed_value;

    
    if (index == 1) {
        removed_value = current->value;  
        l->head = current->next;         
        free(current);                  
        return removed_value;
    }

    node_t *prev = NULL;
    int i;  

    for (i = 1; i < index && current != NULL; i++) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return -1;  
    }

    removed_value = current->value;  
    prev->next = current->next;     
    free(current);                   
    return removed_value;  
}

bool list_is_in(list_t *l, elem value) { 
  node_t *current = l->head;  
  while (current != NULL) {
    if (current->value == value) {
        return true;  
    }
    current = current->next;  
  }
    return false;  
}

elem list_get_elem_at(list_t *l, int index) {
  if (index < 1) {
        return -1; 
    }

    node_t *current = l->head;
    int current_index = 1;

    while (current != NULL) {
        if (current_index == index) {
            return current->value;  
        }
        current = current->next;
        current_index++;
    }

    return -1;  
}


int list_get_index_of(list_t *l, elem value) {
  node_t *current = l->head;
    int index = 1;

    while (current != NULL) {
        if (current->value == value) {
            return index; 
        }
        current = current->next;
        index++;  
    }
    return -1;  
}

