#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 *
 *
 *  Tarefa em dupla. Plágios serão penalizados
 *  de maneira severa e exemplar.
 *
 *  Prazo: ver no moodle.
 *
 *  Nesta tarefa você ira receber um programa com uma
 * função para ser implementada. Você deve primeiramente
 * entender o funcionamento do programa.
 *
 * O programa escreve um conjuntos de alunos em um arquivo
 * dados.txt. Está faltando a função que faz a leitura dos
 * dados do arquivo e salva no registro.
 *
 *
 *
 *
 */


#define fname "dados.txt"

//registro aluno.
typedef struct Aluno{
    char nome[200];//
    long int ra;
    float cr;
}Aluno;

typedef struct Disciplina{
    Aluno * v[200];
    int top;//numero de alunos. começa com zero.
}Disciplina;

/**
 * construtor do registro
 */
Aluno * newAluno(char * nome, long int ra, float cr){
    Aluno * aux = (Aluno *)malloc(sizeof(Aluno));
    strcpy(aux->nome,nome);
    aux->ra = ra;
    aux->cr = cr;
    return aux;
}

Aluno * le(){
    //le um aluno do teclado e faz um return.
    char  nome[100];
    long int ra;
    float cr;
    printf("Digite o nome do aluno:");
    scanf("%s",nome);
    printf("Digite o RA:");
    scanf("%ld",&ra);
    printf("Digite o CR:");
    scanf("%f",&cr);
    return newAluno(nome,ra,cr);
    
}
void imprimeA(Aluno * a1){
    //imprime o aluno no terminal
     printf("[%s,%ld,%f]\n",a1->nome,a1->ra,a1->cr);
}
void imprimeD(Disciplina * d){
    //imprime todos os alunos da disciplina.
    // você deve chamar o método imprimeA()
    for(int aluno=0;aluno<d->top;aluno++){
        imprimeA(d->v[aluno]);
    }
    
}
void persisteD(Disciplina * d){
    //salva a disciplina num arquivo.
    //deve ser um único arquivo com toda a informação.
    //deve imprimir o número de alunos na primeira linha
    //e as informações dos alunos nas próximas linhas
    FILE * f;
    f = fopen(fname,"w");
    fprintf(f,"%d\n",d->top);
    for(int aluno=0;aluno<d->top;aluno++){
        fprintf(f,"%s\n",d->v[aluno]->nome);
        fprintf(f,"%ld\n",d->v[aluno]->ra);
        fprintf(f,"%f\n",d->v[aluno]->cr);
    }
    fclose(f);
}

void carregaD(Disciplina * d){
    FILE * f;
    f = fopen(fname,"r");
    fscanf(f,"%d",&d->top);
    for(int aluno=0;aluno<d->top;aluno++){
        fscanf(f,"%s",d->v[aluno]->nome);
        fscanf(f,"%ld",&d->v[aluno]->ra);
        fscanf(f,"%f",&d->v[aluno]->cr);
    }
    fclose(f);
}

int main(){
    FILE * f;
    int opcao,pos;
    Disciplina * d;
    f = fopen(fname,"r");
    if(f==NULL){
       //arquivo não existe. Cria arquivo com zero
        // alunos
        f = fopen(fname,"w");
        fprintf(f,"0\n");
        fclose(f);
    }
    //carrega a disciplina do arquivo para a memória.
    //você deve implementar esta função de maneira adequada.
    d = carregaD();
    
    while(opcao!=5){
        printf("1 - adicionar aluno,\n");
        printf("2 - remover aluno,\n");
        printf("3 - Listar alunos,\n");
        printf("4 - salvar,\n");
        printf("5 - sair.\n");
        scanf("%d",&opcao);
        switch (opcao) {
            case 1:
                d->v[d->top++]=le();
                break;
                
            case 2:
                printf("Digite a posicao:");
                scanf("%d",&pos);
                for(int i=pos;i<d->top-1;i++){
                    d->v[i]=d->v[i+1];
                }
                d->top--;
                
                break;
            case 3:
                imprimeD(d);
                break;
            case 4:
                persisteD(d);
                break;
                
        }
    }
    
}
