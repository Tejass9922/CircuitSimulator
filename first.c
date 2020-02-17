#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <stdbool.h> 
#include <ctype.h>



typedef struct Var{

    char* s;
    int i;

}Var;

typedef struct Node {
    int*arr;
    struct Node* next;
    char* s;
    
} Node;


int get(int x, int n)
{
    int getBit;
    getBit = ((x>>n)&1);
    return getBit;
}


int main(int argc, char* argv[])
{

  char input[1000];
  //char* inputarr;
     FILE *f = fopen(argv[1], "r");
    if(f == NULL) {
        printf("error");
     }
//int data;


int i=0;

    fgets(input, 1000, f);
   
    char* token = strtok(input, " ");
    int numOfVar;
   
    while (token){
        if(token[0] >= '0' && token[0] <= '9'){
       numOfVar = token[0]- '0';
         break;
        }
       token = strtok(NULL, " \n");
    }
    Var* inputs[numOfVar];
     token = strtok(NULL, " \n");
     
   for (i=0; i<numOfVar; i++){
        Var * var = (Var*)malloc (sizeof(Var));
        inputs[i] = var; 
        inputs[i]->i = 0;
        inputs[i]->s = malloc(80);
        strcpy(inputs[i]->s,token);
         token = strtok(NULL, " \n");
   }
     
    int i1=0;

    fgets(input, 1000, f);
   
    char* token1 = strtok(input, " ");
    int numOfVars;
   
   
    while (token1){
        if(token1[0] >= '0' && token1[0] <= '9'){
       numOfVars = token1[0]- '0';
         //printf("token: %d\n", numOfVar);
         break;
        }
       token1 = strtok(NULL, " \n");
    }
    Var* outputs[numOfVar];
     token1 = strtok(NULL, " \n");
     
   for (i1=0; i1<numOfVars; i1++){
        Var  *var = (Var*)malloc (sizeof(Var));
        outputs[i1] = var;
        outputs[i1]->i = 0;
        outputs[i1]->s = malloc(80);    
        strcpy(outputs[i1]->s, token1);
       
       //printf("%s\n",outputs[i1]->s);
         token1 = strtok(NULL, " \n");
   }
   
    int exp = pow(2,numOfVar);
    Var* allpossible[exp][numOfVar+numOfVars];

    for (int i=0; i<exp; i++){
      for (int j=0; j<numOfVar; j++){
        Var  *var = (Var*)malloc (sizeof(Var));
        allpossible[i][j] = var;
        allpossible[i][j]->i = get(i,numOfVar-j-1);  
        allpossible[i][j]->s = malloc(80);
       strcpy(allpossible[i][j]->s, inputs[j]->s);
      // printf("%s", allpossible[i][j]->s);
      }  
     //printf("\n");
    }
 int totalCol = numOfVar+numOfVars;
    for (int i=0; i<exp; i++){
     for (int j=numOfVar; j<totalCol; j++){
        Var  *var = (Var*)malloc (sizeof(Var));
        allpossible[i][j] = var;
        allpossible[i][j]->i = 0;
        allpossible[i][j]->s = malloc(80);
       allpossible[i][j]->s = malloc(80);
       strcpy(allpossible[i][j]->s, outputs[j-numOfVar]->s);
     }
    }
 
  Node* head = NULL;
   
   
   
    while ((fgets(input, 1000, f))!=NULL)
    {
     char* operand = strtok(input, " "); 

     if (strcmp(operand, "NOT")!=0)
     {
     
     char* op = operand;
      operand = strtok(NULL, " \n");
      char*in1 = operand;
      operand = strtok(NULL, " \n");
      char*in2 = operand;
      operand = strtok(NULL, " \n");
      char*result = operand;
      int index1, index2, index3 = -1;
      int * inp = malloc(exp* sizeof(int));
      int* inp2 =malloc(exp* sizeof(int));
      int* res= malloc(exp* sizeof(int));

      
      
     
      if ((isupper(in1[0]))||(isupper(in2[0]))||(isupper(result[0]))){
        for (int i=0; i<totalCol; i++){
           if (strcmp(in1, allpossible[0][i]->s)==0){
            index1=i;
            for (int j=0; j<exp; j++){
              inp[j] = allpossible[j][index1]->i;
              //printf("%d\n", inp[j]);
            }
            //printf("\n");
           }
           if (strcmp(in2, allpossible[0][i]->s)==0){
            index2 = i;
            for (int j=0; j<exp; j++){
              inp2[j] = allpossible[j][index2]->i;
              // printf("%d\n", inp2[j]);
            }
           // printf("\n");
          }
          if (strcmp(result, allpossible[0][i]->s)==0){
            index3 = i;
            for (int j=0; j<exp; j++){
              res[j] = allpossible[j][index3]->i;
              // printf("%d\n", res[j]);
            }
           // printf("\n");
          }

        }
      }
      
       if (islower(in1[0])||islower(in2[0])||(islower(result[0])))
       {
         
        if (head!=NULL){
         
         Node*curr = head;
         
         while (curr!=NULL){
         // printf("%s\n", curr->s);
           if (strcmp(in1, curr->s)==0){
            
              inp = curr->arr;
              for (int i=0; i<exp; i++){
                //printf("%d",inp[i]);
              }
           }
            if (strcmp(in2, curr->s)==0){
              inp2 = curr->arr;
            }
            if (strcmp(result, curr->s)==0){
              res = curr->arr;
            }
             curr = curr->next;
         }
        }

       }

      if (strcmp(op,"AND")==0){
        for (int i=0; i<exp; i++){
          res[i] = inp[i]&inp2[i];
          //printf("%d\n", res[i]);
         
        }
       
        if(isupper(result[0])){
          for (int i=0; i<exp; i++){
            allpossible[i][index3]->i = res[i];
          }
        }
        
        else if (islower(result[0])){
          if (head==NULL){
            head = (Node*)malloc(sizeof(Node));
            head->s = malloc(80);
            strcpy(head->s, result);
            head->arr = malloc(sizeof(int)*exp);
            head->arr = res;
          }
          else{
              Node*curr = head; 
              while (curr->next!=NULL){
              if (strcmp(curr->s, result)==0){
                curr->arr = res;
                break;
              }
                curr = curr->next;
              }
             Node* thead= (Node*)malloc(sizeof(Node));
             thead->s = malloc(80);
             strcpy(thead->s, result);
             thead->arr = malloc(sizeof(int) *exp);
             thead->arr = res;
             curr->next =thead;

          }
          
         
        }
      }
      else if (strcmp(op,"OR")==0){
        int ans;
        for (int i = 0; i <exp; i++) { 
        if ((inp[i] == 0) && ((inp2[i])==0)) 
           ans = 0; 
        else
            ans = 1; 
           res[i] = ans; 
        } 
       if(isupper(result[0])){
          for (int i=0; i<exp; i++){
            allpossible[i][index3]->i = res[i];
          }
        }
        
        else if (islower(result[0])){
          if (head==NULL){
            head = (Node*)malloc(sizeof(Node));
            head->s = malloc(80);
            strcpy(head->s, result);
            head->arr = malloc(sizeof(int)*exp);
            head->arr = res;
          }
          else{
              Node*curr = head; 
              while (curr->next!=NULL){
              if (strcmp(curr->s, result)==0){
                curr->arr = res;
                break;
              }
                curr = curr->next;
              }
             Node* thead= (Node*)malloc(sizeof(Node));
             thead->s = malloc(80);
             strcpy(thead->s, result);
             thead->arr = malloc(sizeof(int) *exp);
             thead->arr = res;
             curr->next =thead;

          }
          
         
        }
      }
      else if (strcmp(op,"XOR")==0){
        
        for (int i = 0; i <exp; i++) { 
          res[i] = inp[i]^inp2[i]; 
        } 

        if(isupper(result[0])){
          for (int i=0; i<exp; i++){
            allpossible[i][index3]->i = res[i];
          }
        }
        
        else if (islower(result[0])){
          if (head==NULL){
            head = (Node*)malloc(sizeof(Node));
            head->s = malloc(80);
            strcpy(head->s, result);
            head->arr = malloc(sizeof(int)*exp);
            head->arr = res;
          }
          else{
              Node*curr = head; 
              while (curr->next!=NULL){
              if (strcmp(curr->s, result)==0){
                curr->arr = res;
                break;
              }
                curr = curr->next;
              }
             Node* thead= (Node*)malloc(sizeof(Node));
             thead->s = malloc(80);
             strcpy(thead->s, result);
             thead->arr = malloc(sizeof(int) *exp);
             thead->arr = res;
             curr->next =thead;

          }
          
         
        }
      }
      else if (strcmp(op, "NOR")==0){
         int ans;
        for (int i = 0; i < exp; i++) { 
          if ((inp[i] == 0) && (inp2[i]) == 0) 
              ans = 1; 
          else
            ans = 0; 
            res[i] = ans; 
        }
        if(isupper(result[0])){
          for (int i=0; i<exp; i++){
            allpossible[i][index3]->i = res[i];
          }
        }
        
        else if (islower(result[0])){
          if (head==NULL){
            head = (Node*)malloc(sizeof(Node));
            head->s = malloc(80);
            strcpy(head->s, result);
            head->arr = malloc(sizeof(int)*exp);
            head->arr = res;
          }
          else{
              Node*curr = head; 
              while (curr->next!=NULL){
              if (strcmp(curr->s, result)==0){
                curr->arr = res;
                break;
              }
                curr = curr->next;
              }
             Node* thead= (Node*)malloc(sizeof(Node));
             thead->s = malloc(80);
             strcpy(thead->s, result);
             thead->arr = malloc(sizeof(int) *exp);
             thead->arr = res;
             curr->next =thead;

          }
          
         
        }
      }
      else if (strcmp(op, "NAND")==0){
        int ans;
        for (int i = 0; i < exp; i++) 
        { 
            if ((inp[i]) == 1 && (inp2[i]) == 1) 
                ans = 0; 
            else
                ans = 1; 
          res[i]= ans;     
        } 
          if(isupper(result[0])){
          for (int i=0; i<exp; i++){
            allpossible[i][index3]->i = res[i];
          }
        }
        
        else if (islower(result[0])){
          if (head==NULL){
            head = (Node*)malloc(sizeof(Node));
            head->s = malloc(80);
            strcpy(head->s, result);
            head->arr = malloc(sizeof(int)*exp);
            head->arr = res;
          }
          else{
              Node*curr = head; 
              while (curr->next!=NULL){
              if (strcmp(curr->s, result)==0){
                curr->arr = res;
                break;
              }
                curr = curr->next;
              }
             Node* thead= (Node*)malloc(sizeof(Node));
             thead->s = malloc(80);
             strcpy(thead->s, result);
             thead->arr = malloc(sizeof(int) *exp);
             thead->arr = res;
             curr->next =thead;

          }
        }
      }
     

    }
    else
    {
      char*op = operand;
      operand = strtok(NULL, " \n");
      char*in1 = operand;
      operand = strtok(NULL, " \n");
      char*result = operand;

      int index1, index3= -1;
      int * inp = malloc(exp* sizeof(int));
      int* res= malloc(exp* sizeof(int));

      if ((isupper(in1[0]))||(isupper(result[0]))){
        for (int i=0; i<totalCol; i++){
           if (strcmp(in1, allpossible[0][i]->s)==0){
            index1=i;
            for (int j=0; j<exp; j++){
              inp[j] = allpossible[j][index1]->i;
              //printf("%d\n", inp[j]);
            }
            //printf("\n");
           }
           
          if (strcmp(result, allpossible[0][i]->s)==0){
            index3 = i;
            for (int j=0; j<exp; j++){
              res[j] = allpossible[j][index3]->i;
              // printf("%d\n", res[j]);
            }
           // printf("\n");
          }

        }
      }
      if (islower(in1[0])||(islower(result[0])))
      {
         
        if (head!=NULL){
         
         Node*curr = head;
         
         while (curr!=NULL){
         // printf("%s\n", curr->s);
           if (strcmp(in1, curr->s)==0){
            
              inp = curr->arr;
              for (int i=0; i<exp; i++){
                //printf("%d",inp[i]);
              }
           }
            
            if (strcmp(result, curr->s)==0){
              res = curr->arr;
            }
             curr = curr->next;
         }
        }

       }
     
      if (strcmp(op, "NOT")==0){
        for (int i=0; i<exp; i++){
          res[i] = (!(inp[i]));
        }
                  if(isupper(result[0])){
          for (int i=0; i<exp; i++){
            allpossible[i][index3]->i = res[i];
          }
        }
        
        else if (islower(result[0])){
          if (head==NULL){
            head = (Node*)malloc(sizeof(Node));
            head->s = malloc(80);
            strcpy(head->s, result);
            head->arr = malloc(sizeof(int)*exp);
            head->arr = res;
          }
          else{
              Node*curr = head; 
              while (curr->next!=NULL){
              if (strcmp(curr->s, result)==0){
                curr->arr = res;
                break;
              }
                curr = curr->next;
              }
             Node* thead= (Node*)malloc(sizeof(Node));
             thead->s = malloc(80);
             strcpy(thead->s, result);
             thead->arr = malloc(sizeof(int) *exp);
             thead->arr = res;
             curr->next =thead;

          }
        } 
      } 
      }    
    }
for (int i=0; i<exp; i++){
      for (int j=0; j<totalCol; j++){
        printf("%d ",allpossible[i][j]->i);
      }
      printf("\n");
    }
}


         