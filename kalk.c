#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

typedef struct Cell{
  char name[6];
  char equation[150];
  char operators[30];
  int val; //inicijaliziraj na -1 po mogucnosti
}cell;


//FUNKCIJA ZA ABECEDNO SORTIRANJE CELIJA
/////////////////////////////////////////////////////////////////////////////////////////////////
void sort_cells(cell *cell_array, int n){
  
  cell tmp;
  
  for(int i = 0; i < n; i++){
    for(int j = 1; j < n; j++){
      if(strcmp(cell_array[j - 1].name, cell_array[j].name) > 0){
        tmp = cell_array[j - 1];
        cell_array[j - 1] = cell_array[j];
        cell_array[j] = tmp;
      }
    }
  }
}

//FUNKCIJA ZA ISPIS SVIH VARIJABLI NA LISTU
/////////////////////////////////////////////////////////////////////////////////////////////////
void print_cells(cell *cell_array, int n){
  for(int i = 0; i < n; i++){
    printf("%s = %s\n", cell_array[i].name, cell_array[i].equation);
  }
}



//IZRACUNAVANJE VRIJEDNOSTI VARIJABLE BEZ OPERATORA I NEPOZNANICA
/////////////////////////////////////////////////////////////////////////////////////////////////
void calculate_known(cell *cell_array, int index){
  cell_array[index].val = atoi(cell_array[index].equation);
}





//IZRACUNAVANJE VRIJEDNOSTI VARIJABLE BEZ NEPOZNANICA
/////////////////////////////////////////////////////////////////////////////////////////////////
void calculate_value(cell *cell_array, int index){
  
  int nums[100] = {0}, j = 0;
  
  //mice operatore iz jednadzbe
  for(int i = 0; i < strlen(cell_array[index].equation); i++){
    if(ispunct(cell_array[index].equation[i]))
      cell_array[index].equation[i] = ' ';
  }
  
  //cisti razmake
  int i, x;
  for(i=x=0; cell_array[index].equation[i]; ++i)
    if(!isspace(cell_array[index].equation[i]) || (i > 0 && !isspace(cell_array[index].equation[i - 1])))
      cell_array[index].equation[x++] = cell_array[index].equation[i];
    cell_array[index].equation[x] = '\0';
  
  //popisivanje operatora u niz cijelih brojeva
  for(int i = 0; i < strlen(cell_array[index].equation); i++){
    if(isdigit(cell_array[index].equation[i])){
      nums[j] = nums[j] * 10 + cell_array[index].equation[i] - '0';
    }
    if(isspace(cell_array[index].equation[i])){
      j++;
    }
  }
  
  for(int i = 0; i < strlen(cell_array[index].operators); i++){
    
  }
  
  
}



//IZRACUNAVANJE VRIJEDNOSTI VARIJABLE KOJA SADRZI NEPOZNANICE
/////////////////////////////////////////////////////////////////////////////////////////////////
void calculate_with_unknowns(cell *cell_array, int index){
  
}




//GLAVNA FUNKCIJA ZA OBRADU
/////////////////////////////////////////////////////////////////////////////////////////////////
void input_sheet(int n){
  
  cell *cell_array = malloc(400 * sizeof(cell));
  
  for(int i = 0; i < n; i++){
    scanf(" %6[^=]", cell_array[i].name);
    scanf("= %200[^\n]", cell_array[i].equation);
  }
  
  
  //popisivanje svih operatora u jednadzbi funkcije
  for(int i = 0; i < n; i++){
    int k = 0;
    for(int j = 0; j < strlen(cell_array[i].equation); j++){
      if(cell_array[i].equation[j] == '+' || cell_array[i].equation[j] == '*' ||
      cell_array[i].equation[j] == '/' || cell_array[i].equation[j] == '-'){
        cell_array[i].operators[k] = cell_array[i].equation[j];
        k++;
      }
    }
  }

  //pronalazak jednadzbi bez nepoznanica
  for(int i = 0; i < n; i++){
    int explicit = 1;
    for(int j = 1; j < strlen(cell_array[i].equation); j++){
      if(isalpha(cell_array[i].equation[j])){
        explicit = 0;
        break;
      }
    }
    
    //dodjela vrijednosti varijabli koju ne treba racunati
    if(explicit && strlen(cell_array[i].operators) == NULL){
      calculate_known(cell_array, i);
    }
    
    //racunanje vrijednosti varijable bez nepoznanica
    if(explicit)  
      calculate_value(cell_array, i);
  }
  
  sort_cells(cell_array, n);
  //print_cells(cell_array, n);
  
  free(cell_array);
}






/////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
  int t, n;
  char *buffer;

  scanf("%d", &t);
  //i < n; 1 je samo za testne svrhe
  for(int i = 0; i < t; i++){
    scanf("%d", &n);
    input_sheet(n);
    //dodaj pozive funkcija za obradu 
  }
  
  return 0;
}
