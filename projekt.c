#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
  char name[10];
  char equation[200];
  int solved;
  int val;
}cell;


//PROVJERAVA JE LI VARIJABLA
/////////////////////////////////////////////////////////////////////////////////////////////////
int is_var(char *string){
  int is = 0;
  for(int i = 0; i < strlen(string); i++){
    if(isalpha(string[i])){
      is = 1;
      break;
    }
  }
  return is;
}



//IZBACUJE NEPOTREBNE RAZMAKE
/////////////////////////////////////////////////////////////////////////////////////////////////
void one_space(cell *cell_array, int index){
  int i, j;
  for(i=j=0; cell_array[index].equation[i]; i++)
    if(!isspace(cell_array[index].equation[i]) || (i > 0 && !isspace(cell_array[index].equation[i - 1])))
      cell_array[index].equation[j++] = cell_array[index].equation[i];
    cell_array[index].equation[j] = '\0';
}




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
    printf("%s = %d\n", cell_array[i].name, cell_array[i].val);
  }
  printf("\n");
}



//ODREDJUJE OPERATOR IZ STRINGA
/////////////////////////////////////////////////////////////////////////////////////////////////
int find_operator(char *oper){
  for(int i = 0; i < strlen(oper); i++){
    if(*(oper + i) == '+') return 1;
    if(*(oper + i) == '-') return 2;
    if(*(oper + i) == '*') return 3;
    if(*(oper + i) == '/') return 4;
  }
  
  return 0;
}



//IZRACUNAVANJE VRIJEDNOSTI VARIJABLE BEZ OPERATORA I NEPOZNANICA
/////////////////////////////////////////////////////////////////////////////////////////////////
void calculate_known(cell *cell_array, int index){
  cell_array[index].val = atoi(cell_array[index].equation);
  cell_array[index].solved = 1;
}


//PRONALAZI VARIJABLU PO IMENU TE AKO JE IZRACUNATA VRACA VRIJEDNOST
/////////////////////////////////////////////////////////////////////////////////////////////////
int find_var(cell *cell_array, char key[], int n){
  for(int i = 0; i < n; i++){
    if(strcmp(cell_array[i].name, key) == 0){
        return cell_array[i].val;
    }
  }
  return 0;
}

//TRAZI VARIJABLU PO IMENU TE PROVJERAVA JE LI RIJESENA
/////////////////////////////////////////////////////////////////////////////////////////////////
int is_solved(cell *cell_array, char key[], int n){
  for(int i = 0; i < n; i++){
    if(strcmp(cell_array[i].name, key) == 0){
        if(cell_array[i].solved == 0)
          return 1;
    }
  }
  return 0;
}


int is_num(char *string){
	for(int i = 0; i < strlen(string); i++){
		if(isdigit(string[i])){
			continue;
		}
		return 1;
	}
	return 0;
}


//IZRACUNAVANJE VRIJEDNOSTI VARIJABLE
/////////////////////////////////////////////////////////////////////////////////////////////////
void calculate_value(cell *cell_array, int index, int n){
  
  
  int offset = 0, count;
  char operand1[10], operand2[10], buffer[10], rez_str[10];
  int op1, op2, rez;
  
  while(sscanf(cell_array[index].equation + offset, " %[^' '] %n", buffer, &count) > 0){
    if(find_operator(buffer) == 3 || find_operator(buffer) == 4){
      sscanf(cell_array[index].equation + offset + strlen(buffer), " %s", operand2);
      if(is_var(operand1)){
        if(is_solved(cell_array, operand1, n))
          op1 = find_var(cell_array, operand1, n);
        else return;
        
      } else if(is_num(operand1)){
      	op1 = atoi(operand1);	
	  }
      
      if(is_var(operand2)){
        if(is_solved(cell_array, operand2, n))
          op2 = find_var(cell_array, operand2, n);
        else return;
      } else if(is_num(operand2)){
      	op2 = atoi(operand2);
	  } 
      
      if(find_operator(buffer) == 3) rez = op1 * op2;
      if(find_operator(buffer) == 4) rez = op1 / op2;
      
      sprintf(rez_str, "%d", rez);
      for(int i = 0; i < strlen(buffer) + strlen(operand1) + strlen(operand2) + 2; ++i){
        cell_array[index].equation[offset + i - strlen(operand1) - strlen(buffer)] = ' ';
      }
      strncpy(cell_array[index].equation + offset - strlen(operand1) - strlen(buffer), rez_str,
      strlen(rez_str));
      
      one_space(cell_array, index);
      return;
    }
    offset += count;
    strcpy(operand1, buffer);
  }
  offset = 0;
  
  while(sscanf(cell_array[index].equation + offset, " %[^' '] %n", buffer, &count) > 0){
    if(find_operator(buffer) == 1 || find_operator(buffer) == 2){
      sscanf(cell_array[index].equation + offset + strlen(buffer), " %s", operand2);
      if(is_var(operand1)){
        if(is_solved(cell_array, operand1, n))
          op1 = find_var(cell_array, operand1, n);
        else return;
        
      } else if(is_num(operand1)){
      	op1 = atoi(operand1);
	  } 
      
      if(is_var(operand2)){
        if(is_solved(cell_array, operand2, n))
          op2 = find_var(cell_array, operand2, n);
        else return;
      } else if(is_num(operand2)){
      	op2 = atoi(operand2);
	  } 
      
      if(find_operator(buffer) == 1) rez = op1 + op2;
      if(find_operator(buffer) == 2) rez = op1 - op2;
      
      sprintf(rez_str, "%d", rez);
      for(int i = 0; i < strlen(buffer) + strlen(operand1) + strlen(operand2) + 2; ++i){
        cell_array[index].equation[offset + i - strlen(operand1) - strlen(buffer)] = ' ';
      }
      strncpy(cell_array[index].equation + offset - strlen(operand1) - strlen(buffer), rez_str,
      strlen(rez_str));
      
      one_space(cell_array, index);
      return;
    }
    offset += count;
    strcpy(operand1, buffer);
  }
  offset = 0;
  
  sscanf(cell_array[index].equation, " %s", buffer);
  if(is_var(buffer)){
    if(is_solved(cell_array, buffer, n)){
      cell_array[index].val = find_var(cell_array, buffer, n);
      cell_array[index].solved = 1;
      return;
    }
  } 
  if(is_num(buffer)){
    cell_array[index].val = atoi(buffer);
    cell_array[index].solved = 1;
    return;
  }
}


//FUNKCIJA ZA OBRADU LISTA
/////////////////////////////////////////////////////////////////////////////////////////////////
void input_sheet(int n){
  
  cell *cell_array = malloc(400 * sizeof(cell));
  int num_solved = 0;
  
  for(int i = 0; i < n; i++){
    scanf(" %6[^=]", cell_array[i].name);
    scanf("= %200[^\n]", cell_array[i].equation);
  }

  do{
    
    for(int i = 0; i < n; i++){
    if(cell_array[i].solved)
      continue;
    else calculate_value(cell_array, i, n);
    
    
    num_solved = 0;
    for (int i = 0; i < n; ++i){
			if(cell_array[i].solved){
				num_solved++;
				printf("SOLVED : %d\n", num_solved);
			}
		}
  }
} while(num_solved < n);
  
  
  sort_cells(cell_array, n);
  print_cells(cell_array, n);
  
  free(cell_array);
}




/////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
  int t, n;

  scanf("%d", &t);
  for(int i = 0; i < t; i++){
    scanf("%d", &n);
    input_sheet(n);
  }
  
  return 0;
}