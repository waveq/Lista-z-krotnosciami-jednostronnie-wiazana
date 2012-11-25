#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 31 

typedef struct element {
	char *word;
	int arity;
	struct element *next;
} element;

element *create_element(char *slowo) {	// Funkcja lokujaca pamiec na nowy element i ->word
	element *new_element = malloc(sizeof(element));
	new_element->word = malloc(SIZE);
	
	strncpy(new_element->word,slowo,30);
	new_element->arity = 1;
	new_element->next=NULL;
  
	return new_element;
}

element *delete_element(element *head, char *slowo) {
  	element *current;
  	element *previous=NULL;//element wskazujacy na element ktory chcemy usunac
  
  	if(head == NULL) {
		printf("Lista jest pusta.\n");
		return head;
	}
	else {
    	current = head;
    	while(current != NULL) {
			if(strcmp(slowo, current->word) == 0) {
				if(current->arity>1) {
			 	 	current->arity--;
			  	return head;
				}
				else {
		  			if(previous==NULL) { 	// Jesli usuwany jest pierwszy element,
						head=current->next; // wskaznik poprzednika nie jest przestawiany
					}
		 			else {
		   				previous->next = current->next;
		  			}
		  			free(current->word);
		  			free(current);
		  			return head;
				} 
 	     	}
 	     	previous = current;
 	     	current = current->next;
      
		}
	}
	printf("Nie ma takiego slowa.\n");
  	return head;
}

void *view_list(element *head) {
	element *current;
	if(head == NULL)
		printf("Lista jest pusta.\n");
	else {
		current = head;
		while (current != NULL){
      		printf("Slowo: %s:: Krotnosc: %i.\n",current->word,current->arity);
      		current = current->next;
    	}
  	}
}


element *add_element(element *head, char *slowo) {
	element *previous=NULL;
	element *current; 
  	element *new_element;
  
  	// Jesli head == NULL, tzn, ze lista jest pusta.
  	// Nowy element staje sie poczatkiem listy.
	if (head == NULL) {
    	element *new_element = create_element(slowo);// tworzenie nowego elementu
    	head = new_element;
  	}
  	else {
    
    	current = head;
    	while (current != NULL) {
      		// Jezeli podane slowo == word z aktualnej
      		// struktury, dodaj 1 do arity i przerwij
      		// sprawdzanie kolejnych struktur.
      		if(strcmp(slowo,current->word) == 0) {	// if #1
			current->arity += 1;
			return head;
      		}
    
    		// Jezeli element zostal wcisniety pomiedzy
    		// istniejace juz struktury(porzadek alfabetyczny)
    		// przerwij sprawdzanie kolejnych struktur.
    		if(strcmp(current->word,slowo)>0) {		// if #2
    			new_element = create_element(slowo);
				new_element->next = current;
				
				if (previous == NULL) 
					head = new_element;	
				else 
					previous->next = new_element;			
				return head; 
			}
			
     		previous=current;		// przeskakuj, az current
      		current = current->next;// nie bedzie pusty.
      								
    	}	// Koniec while
    	// Wszystkie poprzednie elementy sa rozne lub mniejsze alfabetycznie
    	// od slowa, tworzona jest wiec nowa struktura na koncu.
		previous->next = create_element(slowo);
    } 	
  	return head;
}


int main() {
  	int wybor;
  	char slowo[SIZE];
  	element *head = NULL;
  	do{
		printf(".-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-.\n");
    	printf("            ..::MENU::..\n");
    	printf("0 - Zakonczenie programu\n");
    	printf("1 - Dopisanie wyrazu\n");
    	printf("2 - Usuniecie wyrazu\n");
    	printf("3 - Wyswietlenie zawartosci listy\n");
    	printf(".-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-.\n");
    	scanf("%i",&wybor);
    
    	switch(wybor) {
    		case 0 :
      			printf("Created by Sz. Rekawek.");
      			
      			break;
    		case 1 : 
      			printf("Jakie slowo chcesz dodac?");
      			scanf("%s",slowo);
      			head=add_element(head, slowo);
      
      			break;
    		case 2 :
      			printf("Jakie slowo chcesz usunac?");
      			scanf("%s",slowo);
      			head=delete_element(head, slowo);
      			
      			break;
    		case 3 :
      			view_list(head);

      			break;
    		default :
      			printf("Nie ma takiej pozycji w menu.\n");
    	}
  	}while(wybor != 0);

  	return 0;
}
