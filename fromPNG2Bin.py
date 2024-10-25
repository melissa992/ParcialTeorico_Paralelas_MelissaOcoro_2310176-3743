from PIL import Image
import numpy as np
import sys
import os

IMAGE_FILE = sys.argv[1]

try:
    imagen = Image.open(IMAGE_FILE)
    imagen = imagen.convert('L')  # 'L' convierte a escala de grises
except FileNotFoundError:
    print(f"Error: El archivo {IMAGE_FILE} no se encontró.")
    sys.exit(1)
except IOError as io_err:
    print(f"Error de IO: No se puede leer el archivo {IMAGE_FILE}. Asegúrate de que es un archivo de imagen válido. Detalle: {io_err}")
    sys.exit(1)
except Exception as e:
    print(f"Error inesperado al abrir la imagen {IMAGE_FILE}: {e}")
    sys.exit(1)


    # Verificar si el archivo existe y es legible
if not os.path.isfile(IMAGE_FILE):
    print(f"Error: El archivo {IMAGE_FILE} no existe o no es legible.")
    sys.exit(1)

IMAGE_FILE = sys.argv[1]
FILENAME = os.path.splitext(IMAGE_FILE)[0]
OUTPUT_FILE = f"{FILENAME}.bin"


# Cargar la imagen y convertirla a escala de grises
imagen = Image.open(IMAGE_FILE).convert('L')  # 'L' convierte a escala de grises

# Convertir la imagen a un array de NumPy
array_imagen = np.array(imagen)

# Guardar el array como un archivo binario
array_imagen.astype('int32').tofile(OUTPUT_FILE)

