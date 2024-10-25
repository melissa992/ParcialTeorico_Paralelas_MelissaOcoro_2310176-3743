#!/usr/bin/env bash
#
# Este script se encarga de invocar los tres programas que permiten la 
# conversion de un PNG a secuencia de pixeles, se procesan esos pixeles y
# posteriormente se convierte esa secuencia de pixeles a un archivo en formato
# PNG
#
# Autor: John Sanabria - john.sanabria@correounivalle.edu.co
# Fecha: 2024-08-22
#
#INPUT_PNG="1.png"
#INPUT_PNG="2.png"
#TEMP_FILE="1.bin"
#TEMP_FILE="2.bin"
#python3 fromPNG2Bin.py ${INPUT_PNG}
#./main ${TEMP_FILE}
#python3 fromBin2PNG.py ${TEMP_FILE}.new

#!/bin/bash

#!/bin/bash

#!/bin/bash

# Iterar sobre las imágenes del 1 al 18
for i in {1..18}; do
    INPUT_PNG="${i}.png"
    TEMP_FILE="${i}.bin"
    
    echo "Procesando imagen: ${INPUT_PNG}"

    # Verificar si el archivo de entrada existe
    if [[ ! -f "$INPUT_PNG" ]]; then
        echo "Error: El archivo ${INPUT_PNG} no existe."
        continue  # Saltar a la siguiente iteración del bucle
    fi

    # Ejecutar el script fromPNG2Bin.py para convertir la imagen en .bin
    python3 fromPNG2Bin.py "${INPUT_PNG}" || { echo "Error al procesar ${INPUT_PNG} con fromPNG2Bin.py"; exit 1; }

    # Ejecutar el archivo main con el archivo .bin
    ./main "${TEMP_FILE}" || { echo "Error al ejecutar ./main con ${TEMP_FILE}"; exit 1; }

    # Convertir el archivo .bin de vuelta a una imagen .png
    python3 fromBin2PNG.py "${TEMP_FILE}.new" || { echo "Error al procesar ${TEMP_FILE}.new con fromBin2PNG.py"; exit 1; }
done
