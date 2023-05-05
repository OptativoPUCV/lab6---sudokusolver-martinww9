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
    int used[10] = {0};

    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 10; k++) {
            used[k] = 0;
        }
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0 && used[num] == 1) {
                return 0;
            }
            used[num] = 1;
        }
    }

    for (int j = 0; j < 9; j++) {
        for (int k = 0; k < 10; k++) {
            used[k] = 0;
        }
        for (int i = 0; i < 9; i++) {
            int num = n->sudo[i][j];
            if (num != 0 && used[num] == 1) {
                return 0;
            }
            used[num] = 1;
        }
    }

    for (int bi = 0; bi < 3; bi++) {
        for (int bj = 0; bj < 3; bj++) {
            for (int k = 0; k < 10; k++) {
                used[k] = 0;
            }
            for (int i = bi*3; i < bi*3+3; i++) {
                for (int j = bj*3; j < bj*3+3; j++) {
                    int num = n->sudo[i][j];
                    if (num != 0 && used[num] == 1) {
                        return 0;
                    }
                    used[num] = 1;
                }
            }
        }
    }

    return 1;
}



List* get_adj_nodes(Node* n) {
    List* list = createList();
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                int k;
                for (k = 1; k <= 9; k++) {
                    Node* new_node = copy(n);
                    new_node->sudo[i][j] = k;
                    if (is_valid(new_node)) {
                        pushBack(list, new_node);
                    } else {
                        free(new_node);
                    }
                }
                return list;
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

Node* DFS(Node* n, int* cont) {
    Stack* S = createStack();
    push(S, n);
    while (!is_empty(S)) {
        Node* current_node = (Node*) top(S);
        pop(S);
        (*cont)++;
        if (is_final(current_node)) {
            return current_node;
        }
        List* adj_nodes = get_adj_nodes(current_node);
        Node* adj_node = NULL;
        for (Node* next_node = (Node*) front(adj_nodes); next_node != NULL; next_node = (Node*) next(adj_nodes)) {
            push(S, next_node);
        }
        free(adj_nodes);
        free(current_node);
    }
    free(S);
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