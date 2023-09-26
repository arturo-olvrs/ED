import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import csv
import numpy as np

# Grado del polinomio de aproximación
n=1
title = "Ordenación mediante algoritmo Burbuja. Peor caso"

def logarithmic_func(x, a, base, b):
    return a * np.log(x) / np.log(base) + b

# Listas para almacenar los datos
x = []
y = []

# Leer el archivo CSV y extraer los datos
with open('tiempos.dat', 'r') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter='\t')
    for row in csv_reader:
        if len(row) >= 2:
            x.append(int(row[0]))
            y.append(float(row[1]))

# Crear el gráfico de dispersión con puntos más pequeños (s)
plt.scatter(x, y, s=1)

# Ajuste polinómico

# Calcular la función de regresión (grado en función de n)
coefficients = np.polyfit(x, y, n)
regression_line = [sum(coefficients[i] * xi ** (n - i) for i in range(n + 1)) for xi in x]

# Formatear la ecuación de la función de regresión en notación científica personalizada
etiqueta = "$f~(x)="
for i in range(n, -1, -1):
    coef_part = f"{coefficients[n-i]:.3e}".split('e')
    etiqueta += f"{coef_part[0]} \\cdot 10^{{{coef_part[1]}}}"

    if (i!=0):
        etiqueta += "x"
        if (i!=1):
            etiqueta+="^{" + str(i) + "}"
        
        if (coefficients[n-i+1]>0):   # Si el siguiente número es negativo, no se añade el signo.
            etiqueta += "+"
etiqueta+= "$"

# Agregar la recta de regresión al gráfico
plt.plot(x, regression_line, color='red', label=etiqueta)


# Ajuste logarítmico
'''
initial_params = [1.0, 2.0, 0.0]  # Valores iniciales para a, base y b
params, covariance = curve_fit(logarithmic_func, x, y, p0=initial_params)
a, base, b = params  # Los valores ajustados de los parámetros a, base y b

etiqueta = '$'

coef_part = f"{a:.3e}".split('e')
etiqueta += f"{coef_part[0]} \\cdot 10^{{{coef_part[1]}}}"

etiqueta += '\cdot \log_{'

coef_part = f"{base:.3e}".split('e')
etiqueta += f"{coef_part[0]} \\cdot 10^{{{coef_part[1]}}}"

etiqueta += '}(x)'
if (b>=0): etiqueta += '+'

coef_part = f"{b:.3e}".split('e')
etiqueta += f"{coef_part[0]} \\cdot 10^{{{coef_part[1]}}}"

etiqueta +='$'

plt.plot(x, logarithmic_func(x, a, base, b), color='red', label=etiqueta)
'''


# Configurar etiquetas de los ejes
plt.xlabel('Tamaño del Vector')
plt.ylabel('Tiempo de Ejecución $[s]$')
plt.title(title)

# Mostrar el gráfico con la leyenda
plt.legend()

# Mostrar el gráfico
plt.show()