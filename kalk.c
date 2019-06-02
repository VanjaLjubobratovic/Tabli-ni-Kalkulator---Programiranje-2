#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Cell{
  char name[6];
  char equation[60];
  int val;
}cell;


void input_sheet(char *buffer, int n){
  
  cell *cell_array = malloc(n * sizeof(cell));
  
  for(int i = 0; i < n; i++){
    scanf(" %200[^\n]", buffer);
    //procitaj svaki red buffera do znaka '=' i popisi imena varijabli u strukture
    sscanf(buffer, "%s", cell_array[i].name);
    //popisi jednadzbe 
  }
  
  /*iteriraj kroz polje celija te izracunaj vrijednost svih celija cija jednadzba
  ne sadrzi vrijednosti ostalih celija, zatim pomocu tih vrijednosti izracunaj ostale
  celije
  
  ako cell_array[i].equation ne sadrzi slovne oznake calculate_value(%cell_array[i])
  */
  
  //free(cell_array);
}


int main() {
  int t, n;
  char *buffer;

  scanf("%d", &t);
  //i < n; 1 je samo za testne svrhe
  for(int i = 0; i < 1; i++){
    scanf("%d", &n);
    buffer = malloc(n * 200 * sizeof(char));
    input_sheet(buffer, n);
    //dodaj pozive funkcija za obradu 
    free(buffer);
  }
  
  return 0;
}