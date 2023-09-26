#!/bin/bash

inicio=100
fin=1000000
incremento=100
archivo_busqueda=$1  # El nombre del archivo se pasa como argumento

if [ -z "$archivo_busqueda" ]; then
    echo "Uso: $0 <nombre_del_archivo_busqueda>"
    exit 1
fi

i=$inicio
echo > tiempos.dat

while [ $i -le $fin ]; do
    echo "Ejecución tam = $i"
    ./"$archivo_busqueda" $i 10000 >> tiempos.dat
    i=$((i + incremento))
done