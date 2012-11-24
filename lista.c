#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define SIZE 31 // 30 znakow + /0


typedef struct element {
  char *word;
  int arity;
  struct element *next;
} element;

element *create_element(char word[]) {//funkcja lokujaca pamiec na nowy element i ->word
  element *new_element = malloc(sizeof(element));
  new_element->word = malloc(SIZE);
  
  return new_element;
}

element *delete_element(element *head, char *slowo) {
  element *current;
  element *previous;//element wskazujacy na element ktory chcemy usunac
  element *temp = create_element(slowo);
  int i=0;//licznik  petli while
  
  if(head == NULL)
    printf("Lista jest pusta\n");
  else {
    current = head;
    while(current != NULL) {
      if(strcmp(slowo, current->word) == 0) {
	if(current->arity>1) {
	  current->arity--;
	  break;
	}
	else {
	  if(i==0) { // jesli usuwamy pierwszy element
	    head=current->next;//nie przestawiamy wskaznika poprzedniego elementu
	    free(current);
	    break;
	  }
	  else {
	    
	    temp->next = previous->next;
	    previous->next = current->next;
	    free(temp->next);
	    free(temp);
	    break;
	    
	  }
	} 
      }
      i++;
      previous = current;
      current = current->next;
      
    }
  }
  return head;
}

// funkcja wciskajaca element w preznaczone dla niego miejsce
// (wg alfabetu)
void *between(element *previous, element *sequent) { 
  sequent->next = previous->next;
  previous->next = sequent;
  
  //return head;
}



void *view_element(element *head) {
  element *current;
  if(head == NULL)
    printf("Lista jest pusta\n");
  else {
    current = head;
    while (current != NULL){
      
      printf("Slowo: %s:: Krotnosc: %i\n",current->word,current->arity);
      current = current->next;
    }
  }
}


element *add_element(element *head, char *slowo) {
  // zmienne pomocnicze=====
  element *current;
  element *temp1; // zmienne pomocnicza do zamiany miejscami

  int element_exists = 0; // true lub false
  int i = 0; // licznik petli while
  // =======================
  
  
  
  // Jesli head == NULL, tzn, ze lista jest pusta.
  // Nowy element staje sie poczatkiem listy, 
  // arity = 1;
  
  if (head == NULL) {
    element *new_element = create_element(slowo);// tworzenie nowego elementu
    
    strncpy(new_element->word, slowo, SIZE);
    
    new_element->next = NULL;
    new_element->arity = 1;
    head = new_element;
  }
  else {
    
    current = head;
    
    while (current->next != NULL) {
      // Jezeli podane slowo == word z aktualnej
      // struktury, dodaj 1 do arity i przerwij
      // sprawdzanie kolejnych struktur
      if(strcmp(slowo,current->word) == 0) {// if #1
	current->arity += 1;
	element_exists = 1;
	break;
      }
      
      
      
      
      
      if(strcmp(current->next->word,slowo)>0) {// if #2
	element *new_element = create_element(slowo);
	strncpy(new_element->word, slowo, SIZE);
	new_element->arity = 1;
	
	between(current,new_element);
	element_exists = 1;
	break;
	
      }
      
      
      
      current = current->next;// przeskakuj do kolejnego dopoki kolejny
      // element nie bedzie pusty
    }
    // jezeli arity zostalo przypisane do jednej z
    // wczesniejszych struktur(patrz 1 if), nie tworzymy nowej
    // struktury, bo zastapilaby nam jedna z istniejacych.
    
    // LUB(patrz 2 if) element zostal wcisniety pomiedzy
    // istniejace juz struktury(porzadek alfabetyczny)
    // tez NIE tworzymy dodatkowej strktury na koncu
    if(element_exists == 0) {
      element *new_element = create_element(slowo);// Tworzenie nowego elementu
      
      if(strcmp(slowo,current->word) == 0) {
	current->arity += 1;
	element_exists = 1;
	
      }
      else {
	
	strncpy(new_element->word, slowo, SIZE);
	
	new_element->arity = 1;
	new_element->next = NULL;
	
	current->next = new_element;
      }
    }
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
      printf("Created by Sz. Rekawek");
      
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
      view_element(head);

      break;
    default :
      printf("Nie ma takiej pozycji w menu.\n");
    }
  }while(wybor != 0);

  return 0;
}
