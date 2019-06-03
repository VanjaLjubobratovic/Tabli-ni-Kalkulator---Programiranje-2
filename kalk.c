#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Cell{
  char name[6];
  char equation[60];
  char operators[10]; //maybeeee
  int val; //inicijaliziraj na -1 po mogucnosti
}cell;

void calculate_known(cell *cell_array, int index){
  cell_array[index].val = atoi(cell_array[index].equation);
  printf("%s = ", cell_array[index].name);
  printf("%d\n", cell_array[index].val);
}

int calculate_value(cell *celija, int index){
  /*printf("USO ZA %d\n", index);
  printf("%s", celija->name);*/
  
 // if(strlen)
  
  
  return;
}


void input_sheet(char *buffer, int n){
  
  cell *cell_array = malloc(n * sizeof(cell));
  
  for(int i = 0; i < n; i++){
    scanf(" %6[^=]", cell_array[i].name);
    scanf("= %60[^\n]", cell_array[i].equation);
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

  
  /*iteriraj kroz polje celija te izracunaj vrijednost svih celija cija jednadzba
  ne sadrzi vrijednosti ostalih celija, zatim pomocu tih vrijednosti izracunaj ostale
  celije
  
  ako cell_array[i].equation ne sadrzi slovne oznake calculate_value(&cell_array[i])
  */
  for(int i = 0; i < n; i++){
    int explicit = 1;
    for(int j = 1; j < strlen(cell_array[i].equation); j++){
      if(isalpha(cell_array[i].equation[j])){
        explicit = 0;
        break;
      }
    }
    
    if(explicit && strlen(cell_array[i].operators) == NULL){
      calculate_known(cell_array, i);
    }
    
    /*if(explicit)  
      cell_array[i].val = calculate_value(&cell_array[i], i);*/
  }
  
  //free(cell_array);
}


int main() {
  int t, n;
  char *buffer;

  scanf("%d", &t);
  //i < n; 1 je samo za testne svrhe
  for(int i = 0; i < 1; i++){
    scanf("%d", &n);
    buffer = malloc((n + 1) * sizeof(char));
    input_sheet(buffer, n);
    //dodaj pozive funkcija za obradu 
    free(buffer);
  }
  
  return 0;
}
