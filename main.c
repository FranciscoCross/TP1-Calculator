#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <math.h>
#include <string.h>

#include "cdecl.h"

//Funciones en C
void printLine();
void printHeader();

int checkNumberSystem(const char *numSystem);
int checkOperation(const char *opSymbol);

int binToDec(const char *num);
void printBinResult(int dec);

//Funciones en ASM
extern int suma(int n1, int n2);  //__attribute__((cdecl));
extern int resta(int n1, int n2); //__attribute__((cdecl));

//ARGUMENTOS DE ENTRADA
//1: sistema de numeración: b - d
//2: numero 1
//3: operacion
//4: numero 2
int main(int argc, char const *argv[])
{
    if(argc < 5){
        perror("Too few argumetns\n");
        exit(EXIT_FAILURE);
    }

    int numSystem;
    int operation;
    int num1 = 0, num2 = 0;
    int result = 0;

    //printHeader();

    numSystem = checkNumberSystem(argv[1]);
    if(numSystem < 0){
        perror("Error");
        exit(EXIT_FAILURE);
    }

    operation = checkOperation(argv[3]);
    if(operation < 0){
        perror("Error");
        exit(EXIT_FAILURE);
    }

    //printf("Sistema de numeración: %d\n", numSystem);
    //printf("Operacion: %d\n", operation);

    if(numSystem){
        num1 = atoi(argv[2]);
        num2 = atoi(argv[4]);
    }
    else{
        num1 = binToDec(argv[2]);
        num2 = binToDec(argv[4]);
    }

    if(operation){
        result = suma(num1, num2);
    }
    else{
        result = resta(num1, num2);
    }

    if(numSystem){
        printf("%d\n", result);
    }
    else{
        //printf("Resultado de %s %s %s = ", argv[2], argv[3], argv[4]);
        printBinResult(result);
    }
    
    return result;
    

}

void printLine()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int i = 0;
    for (i = 0; i < w.ws_col; i++)
    {
        printf("-");
    }
    printf("\n");
}

void printHeader(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printLine();
    for(int i = 0; i < (w.ws_col / 2 - 20); i++){
        printf(" ");
    }
    printf("Bienvenido a su calculadora MULTI modulo\n");
    printLine();
}

int checkNumberSystem(const char *numSystem){
    if(*numSystem == 'd'){
        return 1;
    }
    else if(*numSystem == 'b'){
        return 0;
    }
    else{
        return -1;
    }
}

int checkOperation(const char *opSymbol){
    if(*opSymbol == '+'){
        return 1;
    }
    else if(*opSymbol == '-'){
        return 0;
    }
    else{
        return -1;
    }
}

int binToDec(const char *num){
    int lenght = strlen(num);
    int result = 0;

    for(int i = lenght - 1; i >= 0; i--){
        if(num[i] == '1'){
            result = result + pow(2, i);
        }
        else if(num[i] == '0'){
            result = result;
        }
        else{
            printf("ERROR");
            exit(0);
        }
    }

    return result;
}

//https://beginnersbook.com/2017/09/c-program-to-convert-decimal-number-to-binary-number/
void printBinResult(int dec){
    long binNum = 0;
    int rem, negate = 0, temp = 1;
    int num = dec;

    if(num < 0){
        num = num * (-1);
        negate = 1;
    }

    while(num != 0){
        rem = num % 2;
        num = num / 2;
        binNum = binNum + rem * temp;
        temp *= 10;
    }

    if(negate){
        printf("-%ld\n",binNum);    
    }
    else{
        printf("%ld\n", binNum);
    }
}