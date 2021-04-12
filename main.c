#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

void printLine();
int getOperation();
int selOperation();

int main(int argc, char const *argv[])
{
    int funcion = 100;
    int operacion = 100;
    printLine();
    printf("Bienvenido a su calculadora MULTI modulo\n");
    printLine();
    while(funcion == 100)
    {
        funcion = getOperation();
    }
    printf("El valor de funcion es: %d\n", funcion);
    
    while(operacion== 100)
    {
        operacion = selOperation();
    }
    printf("El valor de operacion es: %d\n", operacion);
    

    switch (operacion+funcion)
    {
    case 3:
        printf("Suma Decimal\n");
        break;
    case 4:
        printf("Suma binaria\n");
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
    return 0;

}

void printLine(){
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
    char funcionElegida[2];
    printf("Elija la operación: \n");
    printf("(+) Suma  \n");
    printf("(-) Resta \n");
    printf("(e) Salir \n");
    scanf("%s",funcionElegida);
    switch (funcionElegida[0])
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

int selOperation()
{
    char operationElegida[2];
    printf("Elija la operación: \n");
    printf("(b) Binario \n");
    printf("(d) Decimal \n");
    scanf("%s",operationElegida);
    switch (operationElegida[0])
    {
        case 'b':
            printf("Eligio operacion Binaria\n");
            return 5;
            break;
        case 'd':
            printf("Eligio operacion decimal\n");
            return 3;
            break;
        default:
            printf("\n######-----Ingreso cualquier cosa-----######\n");
            return 100;
            break;
    } 
}
