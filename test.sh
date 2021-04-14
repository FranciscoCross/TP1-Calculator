#!/bin/bash

assert_equals () {
  if [ "$1" = "$2" ]; then
    echo -e "$Green $Check_Mark Prueba Pasada $Color_Off"
  else
    echo -e "$Red  Fallo $Color_Off"
    echo -e "$Red  Salida: $1  Esperado: $2 $Color_Off"
    Errors=$((Errors  + 1))
    exit 1
  fi
}

response=$(./main d  2 + 2)
assert_equals "$response" 4

response=$(./main d  2 - 2)
assert_equals "$response" 0

response=$(./main d  2 - 4)
assert_equals "$response" -2

response=$(./main b  11 + 11)
assert_equals "$response" 110

response=$(./main b  11 + 0)
assert_equals "$response" 11

response=$(./main b  11 - 1)
assert_equals "$response" 10

response=$(./main b  11 - 11)
assert_equals "$response" 0

response=$(./main b  1 - 101)
assert_equals "$response" -100

response=$(./main b  12 - 11)
assert_equals "$response" ERROR

response=$(./main b  a - 11)
assert_equals "$response" ERROR

response=$(./main d  4  11)
assert_equals "$response" ERROR

response=$(./main d  4 + 4 + 4)
assert_equals "$response" ERROR