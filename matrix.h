/*
>>>>>>>>>>> PROJETO FINAL DE PROGRAMACAO ESTRUTURADA <<<<<<<<<<<<<

Professor: 
Igor Malheiros

Alunos:
Joao Antonio Honorato | 20210026680
Maria Raquel Martinez | 20200025900

*/

#ifndef MATRIX_H
#define MATRIX_H

//>==================== Definicao da Struct: ===================

/* Campos da struck Matrix:
   > data: array unidimensional que armazena seus dados.
   > n_rows: numero de linhas.
   > n_cols: numero de colunas.
   > stride_rows: numero de elementos "pulados” no array unidimensional para acessar a próxima linha.
   > stride_cols: numero de elementos "pulados” no array unidimensional para acessar a próxima coluna.
   > offset: índice de onde devemos começar a considerar os dados do array unidimensional.
*/
typedef struct {
    int *data;
    int n_rows;
    int n_cols;
    int stride_rows;
    int stride_cols;
    int offset;
} Matrix;

//>================== Assinaturas de Funcoes: ==================

//>==================== criacao de matrizes: =================== TODAS OK

Matrix create_matrix(int *data, int n_rows, int n_cols);          
Matrix zeros_matrix(int n_rows, int n_cols);                      
Matrix full_matrix(int n_rows, int n_cols, int value);            
Matrix i_matrix(int n);              
Matrix tile_matrix(Matrix matrix, int reps);      //-----> rever tile                  

//>==================== acessar elementos: ===================== REVER     

int get_element(Matrix matrix, int ri, int ci);                   
void put_element(Matrix matrix, int ri, int ci, int elem);        
void print_matrix(Matrix matrix);                                //ok                           

//>================= manipulacao de dimensoes: ================= REVER

Matrix transpose(Matrix matrix);                                 //ok                                
Matrix reshape(Matrix matrix, int new_n_rows, int new_n_cols);   //quase  
Matrix slice(Matrix a_matrix, int rs, int re, int cs, int ce);    

//>======================== agregacao: ========================= REVER

int min(Matrix matrix);                                           
int max(Matrix matrix);                                           
int argmin(Matrix matrix);                                        
int argmax(Matrix matrix);                                        

//>================== operacoes aritmeticas: =================== REVER

Matrix add(Matrix matrix_1, Matrix matrix_2);                     
Matrix sub(Matrix matrix_1, Matrix matrix_2);                     
Matrix division(Matrix matrix_1, Matrix matrix_2);                
Matrix mul(Matrix matrix_1, Matrix matrix_2);                     

#endif