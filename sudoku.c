#include <stdio.h>
#include <stdlib.h>
#include "list.h"



typedef struct{
   int sudo[9][9];
}Node;


Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

//Filtrar por columna y fila y el cuadrado (podemos guardar los datos de cada cuadrado);

int is_valid(Node* n){
   //int *vector_columna = (int*) calloc(sizeof(int)*9);
   //int *vector_fila = (int*) calloc(sizeof(int)*9);
/*
   int k=8,p; 
   for(p=0;p<9;p++){
      int i=3*(k/3) + (p/3) ;
      int j=3*(k%3) + (p%3) ;
      List *lista = createList();
      
      if (n->sudo[i][j] == 0) return 0;
      
    //printf("%d ",n->sudo[i][j]);
    //if(p%3 == 2) printf("\n");
   }
   
   

   */

   int i, j;
   int fila[9][10] = {0};
   int columna[9][10] = {0}; 
   int matriz3x3[3][3][10] = {0};
   

   for (i = 0; i < 9; i++) {
      for (j = 0; j < 9; j++) {
         if (n->sudo[i][j] == 0) {
            continue; 
         }
         int num = n->sudo[i][j];
         
         
         if (fila[i][num]) return 0;
         fila[i][num] = 1;
      
         if (columna[j][num]) return 0;
         columna[j][num] = 1;

         if (matriz3x3[i / 3][j / 3][num]) return 0;
         matriz3x3[i / 3][j / 3][num] = 1;
      }
   }
   return 1; 
}


List* get_adj_nodes(Node* n){
   int i,j,k;
   List* list=createList();
   for (i=0 ; i<9 ; i++){
      for (j=0 ; j<9 ; j++){
         
         if (n->sudo[i][j] == 0){
            for (k=0 ; k<9 ; k++){
               n->sudo[i][k] = k;
               Node* aux = copy(n);
               
               if (is_valid(n) == 0){
                  pushBack(list,aux);
               }
            }
         }
      }
   }
   return list;
}


int is_final(Node* n){
   for (int i=0 ; i<9 ; i++){
      for (int j=0 ; j<9 ; j++){
         if (n->sudo[i][j] == 0) return 0;
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* s = createStack();
   push(s,initial);
   while(!is_empty(s)){
      Node* n = top(s);
      pop(s);
      if (is_final(n)){
         return n;
      }
      List* list = get_adj_nodes(n);
      Node* aux = first(list);
      while(aux){
         push(s,aux);
         aux = next(list);
      }
      popFront(list);
      free(list);
      (*cont)++;
   }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/