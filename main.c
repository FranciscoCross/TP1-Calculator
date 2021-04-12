#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

#include "cdecl.h"

//Funciones en C
void imprimirLinea();
int getOperation();
int getNumberSystem();

//Funciones en ASM
extern int suma(int n1, int n2); //__attribute__((cdecl));
extern int resta(int n1, int n2); //__attribute__((cdecl));

int main(int argc, char const *argv[])
{
    int operacion = 100;
    int systemaNumeracion = 100;
    imprimirLinea();
    printf("Bienvenido a su calculadora MULTI modulo\n");
    imprimirLinea();
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

    char input1[2], input2[2];
    int num1, num2, res;

    switch (systemaNumeracion+operacion)
    {
    case 3:
        printf("Suma Decimal\n");
        printf("Ingrese el primer numero: \n");
        fflush(stdin);
        scanf("%d", &num1);
        printf("Ingrese el segundo numero: \n");
        fflush(stdin);
        scanf("%d", &num2);
        res = suma(num1, num2);
        break;
    case 4:
        printf("Resta Decimal\n");
        printf("Ingrese el primer numero: \n");
        fflush(stdin);
        scanf("%d", &num1);
        printf("Ingrese el segundo numero: \n");
        fflush(stdin);
        scanf("%d", &num2);
        res = resta(num1, num2);
        break;
    case 5:
        printf("Resta decimal\n");
        break;
    case 6:
        printf("Resta binaria\n");
        break;

    default:
        break;
    }
    printf("El resutaldo es: %d\n", res);
    return 0;

}

void imprimirLinea(){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int i = 0;
    for(i = 0; i < w.ws_col;i++){
        printf("-");
    }
    printf("\n");
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
            printf("SOY UN +\n");
            return 0;
            break;
        case '-':
            printf("SOY UN -\n");
            return 1;
            break;
        case 'e':
            printf("ME FUI, Nos vimos gente\n");
            exit(0);
            break;
        default:
            printf("\n######-----Ingreso cualquier cosa-----######\n");
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
            printf("Eligio systemaNumeracion Binaria\n");
            return 5;
            break;
        case 'd':
            printf("Eligio systemaNumeracion decimal\n");
            return 3;
            break;
        default:
            printf("\n######-----Ingreso cualquier cosa-----######\n");
            return 100;
            break;
    } 
}
