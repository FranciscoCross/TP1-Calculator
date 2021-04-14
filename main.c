#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <math.h>
#include <string.h>

#include "cdecl.h"

//Funciones en C
//Para calculadora interactiva
void printLine();
void printHeader();
int getOperation();
int getNumberSystem();
int scanBin();
void printBinResult(int dec);

//Para calculadora por parametro
int checkNumberSystem(const char *numSystem);
int checkOperation(const char *opSymbol);
int binToDec(const char *num);
void printBinResultParametro(int dec);
int comprobarNumero(const char *num);

void calculadora();
void calculadoraParametro(int argc, char const *argv[]);


//Funciones en ASM
extern int suma(int n1, int n2); //__attribute__((cdecl));
extern int resta(int n1, int n2); //__attribute__((cdecl));

//ARGUMENTOS DE ENTRADA
//1: sistema de numeración: b - d
//2: numero 1
//3: operacion
//4: numero 2
int main(int argc, char const *argv[])
{

    if(argc >= 2){
        calculadoraParametro(argc, argv);
    }
    else{
        printHeader();
        while(1){
            calculadora();
        }
    }

    return EXIT_SUCCESS;
}

void calculadora(){
    int operacion = 100;
    int systemaNumeracion = 100;

    while(operacion == 100)
    {
        operacion = getOperation();
    }
    //printf("El valor de operacion es: %d\n", operacion);
    
    while(systemaNumeracion== 100)
    {
        systemaNumeracion = getNumberSystem();
    }
    //printf("El valor de systemaNumeracion es: %d\n", systemaNumeracion);

    char input1[2], input2[2], bin1[1], bin2[1];
    int num1, num2, res;

    switch (systemaNumeracion+operacion)
    {
    case 3:
        //printf("Suma Decimal\n");
        printf("Ingrese el primer numero: \n");
        fflush(stdin);
        scanf("%d", &num1);
        printf("Ingrese el segundo numero: \n");
        fflush(stdin);
        scanf("%d", &num2);
        res = suma(num1, num2);
        printf("Resultado de %d + %d = %d\n", num1, num2, res);
        break;
    case 4:
        //printf("Resta Decimal\n");
        printf("Ingrese el primer numero: \n");
        fflush(stdin);
        scanf("%d", &num1);
        printf("Ingrese el segundo numero: \n");
        fflush(stdin);
        scanf("%d", &num2);
        res = resta(num1, num2);
        printf("Resultado de %d - %d = %d\n", num1, num2, res);
        break;
    case 5:
        //printf("Suma Binaria\n");
        printf("Ingrese el primer numero: ");
        __fpurge(stdin);
        num1 = scanBin();
        printf("Ingrese el segundo numero: ");
        __fpurge(stdin);
        num2 = scanBin();
        res = suma(num1, num2);
        printf("Resultado de %d + %d = ", num1, num2);
        printBinResult(res);
        break;
    case 6:
        //printf("Resta Binaria\n");
        printf("Ingrese el primer numero: ");
        __fpurge(stdin);
        num1 = scanBin();
        printf("Ingrese el segundo numero: ");
        __fpurge(stdin);
        num2 = scanBin();
        res = resta(num1, num2);
        printf("Resultado de %d - %d = ", num1, num2);
        printBinResult(res);
        break;
    default:
        break;
    }

    printLine();
}

void calculadoraParametro(int argc, char const *argv[]){
        if(argc != 5){
        printf("ERROR\n");
        exit(0);
    }

    int numSystem;
    int operation;
    int num1 = 0, num2 = 0;
    int result = 0;

    numSystem = checkNumberSystem(argv[1]);
    if(numSystem < 0){
        printf("ERROR\n");
        exit(0);
    }

    operation = checkOperation(argv[3]);
    if(operation < 0){
        printf("ERROR\n");
        exit(0);
    }

    if(numSystem){
        num1 = comprobarNumero(argv[2]);
        num2 = comprobarNumero(argv[4]);
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
        printBinResultParametro(result);
    }
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

int getOperation()
{
    char operacionElegida[2];
    printf("Elija la operación: \n");
    printf("(+) Suma  \n");
    printf("(-) Resta \n");
    printf("(e) Salir \n");
    scanf("%s",operacionElegida);
    switch (operacionElegida[0])
    {
        case '+':
            return 0;
            break;
        case '-':
            return 1;
            break;
        case 'e':
            printf("Saliendo...\n");
            exit(0);
            break;
        default:
            printf("######-----Ingreso no valido-----######\n");
            return 100;
            break;
    } 
}

int getNumberSystem()
{
    char operationElegida[2];
    printf("Elija la operación: \n");
    printf("(b) Binario \n");
    printf("(d) Decimal \n");
    scanf("%s",operationElegida);
    switch (operationElegida[0])
    {
        case 'b':
            return 5;
            break;
        case 'd':
            return 3;
            break;
        default:
            printf("######-----Ingreso no valido-----######\n");
            return 100;
            break;
    } 
}

int scanBin()
{
    char bin; int dec = 0;
    while (bin != '\n') 
    { 
        bin=fgetc(stdin);
        if (bin == '1'){
            dec = dec * 2 + 1;
        }  
        else if (bin == '0'){
            dec *= 2;    
        } 
    } 
    printf("El valor pasado a dec es: %d\n", dec);
    return dec;
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
            continue;
        }
        else{
            printf("ERROR\n");
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
        printf("-%ldb = (%d)d\n", binNum, dec);    
    }
    else{
        printf("%ldb = (%d)d\n", binNum, dec);
    }
}

//Modificado para salida simple para los unitest
void printBinResultParametro(int dec){
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

int comprobarNumero(const char *num){
    int lenght = strlen(num);
    for(int i = lenght - 1; i >= 0; i--){
        if(num[i] >= '0' && num[i] <= '9'){
            continue;
        }
        else{
            printf("ERROR\n");
            exit(0);
        }
    }
    return atoi(num);
}