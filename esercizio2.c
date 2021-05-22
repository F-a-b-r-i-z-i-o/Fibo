#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <string.h>


static int n_tot;
//funzione che controlla argomento se l'argomento passato e' un numero
int isNumber(char number[]){
    int i = 0;
    for (; number[i] != '\0'; i++)
    {
        if (!isdigit(number[i]))
            return 0;
    }
    return i;
}



//funzione princiale del programma che calcola x-esimo numero di finbonacci
//richiamando ricorsivamente un nuovo processo
int fibonacci(int n){
    //dichiarazioni variabili che verranno usate succesivamente
    int fib1;
    int fib2;
    int k;
    int stato;
    int somma;
    //caso base 
    if (n==0){
        return 0;
    }else if (n==1){
        return 1;
    }
    //passo induttivo
    //faccio un fork che si occupa di calcolare(n-1)
    fib1=fork();
    if(fib1==0){
        exit(fibonacci(n-1));
    }else{
        if(fib1 < 0){
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else{
            if (waitpid(fib1, &stato, 0) == -1){
                perror("waitpid");
            }
        }
        //attendo completamento processo
    }   //controllo per catturare exit status: 
        //se exit status presente e non ci sono errori catturo
        if (WIFEXITED(stato)){ 
        k = WEXITSTATUS(stato);
        }
    //faccio un fork che si occupa di calcolare(n-2)
    fib2=fork();
    if(fib2==0){
        exit(fibonacci(n-2));
    }else{
        if(fib2 < 0){
            perror("fork");
            exit(EXIT_FAILURE);
        } else{
                if (waitpid(fib2, &stato, 0) == -1){
                    perror("waitpid");
                }
        }
    }
        //attendo completamento processo
        //controllo per catturare exit status: 
        //se exit status presente e non ci sono errori catturo
        if (WIFEXITED(stato)){ 
            somma = k + WEXITSTATUS(stato);
            }
return somma;
}

int main(int argc, char *argv[]){
    //controllo valori inseriti siano interi compresi tra 0 e 10.
    //0 e 10 inclusi.
    if (argc != 2 || !isNumber(argv[1]))
    {
        printf("**************\n");
        printf ("ATTENZIONE\n");
        printf("**************\n");
        printf("\n");
        printf("\n");
        fprintf(stderr, "Inserisci un unico argomento INTERO: %s [INT]\n", argv[0]);
        return -1;
    }
    n_tot = atoi(argv[1]);
    if(n_tot>=0 && n_tot<=10)
    {
        fprintf(stdout, "%d\n", fibonacci(n_tot));

    }
    else
    {
        printf("**************\n");
        printf ("ATTENZIONE");
        printf("**************\n");
        printf("\n");
        printf("\n");
        printf("Devi inserire un valore INTERO tra 0 e 10\n");
        printf("\n");
        printf("**************\n");
        return -1;

    }
    return 0;
}