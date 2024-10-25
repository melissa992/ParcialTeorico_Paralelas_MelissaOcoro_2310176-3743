#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int NUM_THREADS = 4;

// Funciones placeholder para la carga y guardado de imágenes
void cargarImagen(int *imagen, int width, int height);
void guardarImagen(int *imagen, int width, int height);

// Función para aplicar un filtro simple
void aplicarFiltro(int *imagen, int *imagenProcesada, int width, int height);

// Función para calcular la suma de los píxeles (como una estadística)
int calcularSumaPixeles(int *imagen, int width, int height);

char *filename;

int main(int argc, char* argv[]) {
    int width = 1024, height = 1024;
    int *imagen = (int *)malloc(width * height * sizeof(int));
    int *imagenProcesada = (int *)malloc(width * height * sizeof(int));

    if (argc != 2) {
      fprintf(stderr, "Dar un nombre de archivo de entrada");
      exit(1);
    }

    filename = argv[1];
    // Cargar la imagen (no paralelizable)
    cargarImagen(imagen, width, height);

    // Aplicar filtro (paralelizable)
    aplicarFiltro(imagen, imagenProcesada, width, height);

    // Calcular suma de píxeles (parte paralelizable)
    int sumaPixeles = calcularSumaPixeles(imagenProcesada, width, height);

    printf("Suma de píxeles: %d\n", sumaPixeles);

    // Guardar la imagen (no paralelizable)
    guardarImagen(imagenProcesada, width, height);

    free(imagen);
    free(imagenProcesada);
    return 0;
}

// Carga una imagen desde un archivo binario
void cargarImagen(int *imagen, int width, int height) {
    FILE *archivo = fopen(filename, "rb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para cargar la imagen");
        return;
    }

    size_t elementosLeidos = fread(imagen, sizeof(int), width * height, archivo);
    if (elementosLeidos != width * height) {
        perror("Error al leer la imagen desde el archivo");
    }

    fclose(archivo);
}

// Guarda una imagen en un archivo binario
void guardarImagen(int *imagen, int width, int height) {
    char *output_filename;

    output_filename = (char*)malloc(sizeof(char)*(strlen(filename) + 4));
    sprintf(output_filename,"%s.new",filename);
    FILE *archivo = fopen(output_filename, "wb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para guardar la imagen");
        return;
    }

    size_t elementosEscritos = fwrite(imagen, sizeof(int), width * height, archivo);
    if (elementosEscritos != width * height) {
        perror("Error al escribir la imagen en el archivo");
    }

    fclose(archivo);
}


void aplicarFiltro(int *imagen, int *imagenProcesada, int width, int height) {
    // Definir las máscaras de Sobel para detección de bordes
    int Gx[3][3] = {{-1, 0, 1}, 
                    {-2, 0, 2}, 
                    {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, 
                    {0, 0, 0}, 
                    {1, 2, 1}};

    // Establecer el número de hilos para la ejecución paralela
    omp_set_num_threads(NUM_THREADS);

    // Paralelizar el bucle externo que recorre las filas de la imagen
    #pragma omp parallel for 
    for (int y = 1; y < height - 1; y++) {
        // Iterar sobre las columnas de la imagen, evitando los bordes
        for (int x = 1; x < width - 1; x++) {
            // Inicializar las sumas para Gx y Gy
            int sumX = 0;
            int sumY = 0;

            // Aplicar las máscaras de Sobel
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    // Multiplicar el valor del píxel por el coeficiente de la máscara
                    sumX += imagen[(y + ky) * width + (x + kx)] * Gx[ky + 1][kx + 1];
                    sumY += imagen[(y + ky) * width + (x + kx)] * Gy[ky + 1][kx + 1];
                }
            }

            // Calcular la magnitud del gradiente
            int magnitude = abs(sumX) + abs(sumY);

            // Normalizar la magnitud a un valor de 8 bits y asignar a la imagen procesada
            imagenProcesada[y * width + x] = (magnitude > 255) ? 255 : magnitude;
        }
    }
}


int calcularSumaPixeles(int *imagen, int width, int height) {
    // Inicializo la variable suma para almacenar el total de los píxeles
    int suma = 0;

    // Establezco el número de hilos a utilizar en la ejecución paralela
    omp_set_num_threads(NUM_THREADS);
    
    // Utilizo la directiva de OpenMP para paralelizar el bucle
    // La cláusula 'reduction(+:suma)' asegura que la suma se combine correctamente
    #pragma omp parallel for reduction(+:suma) 
    for (int i = 0; i < width * height; i++) {
        // Cada hilo suma el valor del píxel correspondiente al total
        suma += imagen[i];
    }

    // Retorno la suma total de todos los píxeles en la imagen
    return suma;
}
