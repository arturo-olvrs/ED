#!/bin/bash

inicio=100
fin=100000
incremento=500

if [[ $# -ne 1 ]]; then
    echo "Uso: $0 <nombre_ejecutable>"
    exit 1
fi


ejecutable=$1  # El nombre del archivo se pasa como argumento
nfils=300
ncols=300

nreps=1
img_orig=./codigo/img/shuffle_9973.pgm
img_dest=./codigo/expected/nreps.pgm

i=$inicio
echo > tiempos.dat

while [ $i -le $fin ]; do
    echo "Ejecución tam = $i"

    echo -ne "$i \t" >> tiempos.dat
    "$ejecutable" "$img_orig" "$img_dest" $i >> tiempos.dat
    i=$((i + incremento))
done