# TP1-Calculator
Se le pedirá al estudiante implementar una Calculadora programada en lenguaje C. Cada una de las operaciones deben estar programadas en lenguaje ASM en archivos separados, utilizando la pila para convocar, enviar parámetros y devolver resultados. La Calculadora debe permitir sumar y restar enteros y binarios, presentar el resultado de la suma, borrar lo ingresado y finalizar su ejecución.

# Modos de uso de la calculadora:

1°  Una vez tenga los archivos en su computadora con linux escribir en la consola donde se encuentra "make"

2°  Puede realizar suma o resta binaria o decimal en consola siguiendo el siguiente formato:
                        ./main tipoOperacion numero1 operando numero2
    Donde: tipoOperacion puede ser una b (para operacion binaria) o una d (para operacion decimal)
           numero1 y numero2 los numeros que desea calcular
           operando puede ser un + para suma y - para resta
    Entonces, para realizar una suma decimal por ejemplo debe escribir: ./main d 3 + 5

3°  Otra forma de usar la calculadora es simplemente ingresando "./main", de esta forma entrara a una instancia interactiva de la calculadora, donde solo debe seguir las               instrucciones que se le ofrecen  
