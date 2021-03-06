#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "site.h"
#include "utils.h"

struct node_{
	SITE *site;
	NODE *next;
};

struct list_{
	NODE *start;
	int size;
};

LIST *list_create(){
	LIST *list = malloc(sizeof(LIST));
	if(!list) return FALSE;

	list->start = NULL;
	list->size = 0;
	return list;
}

boolean list_insert_site(LIST *list, SITE *newsite){
	//in case there is no list
	if(!list) return FALSE;

	NODE *elem = malloc(sizeof(NODE));
	//if the list is empty, put the site in the start
	if(list_empty(list)){
		elem->site = newsite;
		elem->next = NULL;
		list->start = elem;
		list->size = 1;
		return TRUE;
	}

	//if the list already has content, it needs to be added by order
	elem->site = newsite;
	NODE *prior = NULL, *actual = list->start;

	//verifies if the newsite key is equal to the one of the site at list start
	if(actual && site_get_key(actual->site) == site_get_key(newsite)){
		site_delete(&newsite);
		printf("Sorry, but this site already exists\n");
		return FALSE;
	}

	//gets the position to be alocated
	while(actual && site_get_key(actual->site) < site_get_key(newsite)){
		prior = actual;
		actual = actual->next;

		//verifies if there are equal keys
		if(actual && site_get_key(actual->site) == site_get_key(newsite)){
			site_delete(&newsite);
			printf("Sorry, but this site already exists\n");
			return FALSE;
		}
	}
	
	//if is the first element
	if(actual == list->start){
		elem->next = list->start;
		list->start = elem;
	}
	//if is the last element
	else if(!actual){
		prior->next = elem;
		elem->next = NULL;
	}
	else{
		elem->next = actual;
		prior->next = elem;
	}
	list->size++;
	//site_print(elem->site);
	return TRUE;
}

boolean list_remove_site(LIST *list, int key){
	if(list == NULL) return FALSE;
	NODE *aux = malloc(sizeof(NODE));
	aux = list->start;

	for(int i = 0; i < list->size; i++){
		if(site_get_key(aux->site) == key){
			site_delete(&aux->site);
			return TRUE;
		}
		aux = aux->next;
	}
	printf("Sorry, but there is no site with this code\n");
	return FALSE;	
}

boolean list_insert_keyword(LIST *list, int key, char *keyword){
	if(list == NULL) return FALSE;
	NODE *aux = list->start;

	for(int i = 0; i < list->size; i++){
		if(site_get_key(aux->site) == key){
			//function to add a keyword in the site content
			site_add_keyword(aux->site, keyword);
			printf("New keyword added\n");
			return TRUE;
		}
		aux = aux->next;
	}
	printf("Sorry, but there is no site with this code\n");
	return FALSE;
}

boolean list_update_relevance(LIST *list, int key, int relevance){
	if(list == NULL) return FALSE;
	NODE *aux = list->start;

	for(int i = 0; i < list->size; i++){
		if(site_get_key(aux->site) == key){
			//function to access site relevance content
			site_set_relevance(aux->site, relevance);
			printf("Revelance updated with success\n");
			return TRUE;
		}
		aux = aux->next;
	}
	printf("Sorry, but there is no site with this code\n");
	return FALSE;
}

//erase the list and all its content
void list_erase(LIST **list){
	if(!list) return;

	NODE *actual = (*list)->start, *next = NULL;

	while (actual){
		next = actual->next;
		site_delete(&actual->site);
		free(actual);
		actual = next;
	}
	actual = NULL;
	free(*list);
	*list = NULL;
}

SITE *list_getsite(LIST *list, int key){
	NODE *aux = list->start;

	for(int i = 0; i < list->size; i++){
		if(site_get_key(aux->site) == key){
			return aux->site;
		}
		aux = aux->next; 
	}
	exit (-1);
}

int list_size(LIST *list){
	if(list == NULL) return FALSE;
	return list->size;
}

boolean list_empty(LIST *list){
	if(!list || !list->size) return TRUE;
	return FALSE;
}

void list_print(LIST *list){
	if(list == NULL) return;
	
	NODE *aux = malloc(sizeof(NODE));
	aux = list->start;

	while(aux){
		site_print(aux->site);
		aux = aux->next;
	}
}