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

int is_valid(Node* n) {
    int used_rows[9][10] = {0};
    int used_cols[9][10] = {0};
    int used_boxes[9][10] = {0};
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                // Check row
                if (used_rows[i][num] == 1) {
                    return 0;
                } else {
                    used_rows[i][num] = 1;
                }
                
                if (used_cols[j][num] == 1) {
                    return 0;
                } else {
                    used_cols[j][num] = 1;
                }
                
                int box_idx = (i / 3) * 3 + (j / 3);
                if (used_boxes[box_idx][num] == 1) {
                    return 0;
                } else {
                    used_boxes[box_idx][num] = 1;
                }
            }
        }
    }
    
    return 1;
}


List* get_adj_nodes(Node* n){
 List* list = createList();
    int used_rows[9][10] = {0};
    int used_cols[9][10] = {0};
    int used_boxes[9][10] = {0};
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                used_rows[i][num] = 1;
                used_cols[j][num] = 1;
                int box_idx = (i/ 3) * 3 + (j / 3);
used_boxes[box_idx][num] = 1;
}
}
}

for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
        if (n->sudo[i][j] == 0) {
            for (int k = 1; k <= 9; k++) {
                if (!used_rows[i][k] && !used_cols[j][k] && !used_boxes[(i / 3) * 3 + (j / 3)][k]) {
                    Node* new_node = copy(n);
                    new_node->sudo[i][j] = k;
                    if (is_valid(new_node)) {
                        pushBack(list, new_node);
                    } else {
                        
                    }
                }
            }
        }
    }
}
    return list;
}


int is_final(Node* n){
   int i, j;
   for(i=0;i<9;i++){
      for(j=0;j<9;j++){
         if(n->sudo[i][j] == 0){
            return 0;
         }
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont){
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