import pandas as pd
import numpy as np

df = pd.read_csv('data_2.csv');
pd.DataFrame

# print("Hola mundo aquí está tú CSV")
# print(df.head());

array_1d = np.array([121.1, 122.3, 122.0, 121.0])
array_2d = np.array([[121.1, 122.3, 122.0, 121.0],[0.33, 0.25, 0.34, 0.11]])

# print(array_1d)
# print(array_2d)

# print(array_2d.shape) # (2,4) 2 filas y 4 columnas
# print(array_2d.ndim) # 2

# Matriz identidad
matriz_identidad = np.eye(4)
# print(matriz_identidad)
# Matriz 0
matriz_ceros = np.zeros((4, 4))
# print(matriz_ceros)
# Matriz 1
matriz_unos = np.ones((4, 4))
# print(matriz_unos)

# Matriz random
matriz_random = np.random.rand(4,4)
# print(matriz_random)

#Leer datos de un texto
data2 =  np.genfromtxt('texto.txt', delimiter=',')
# print(data2)

data = { 'Name': [ 'Anna ' , 'Bob ' , 'Charlie' ] , 'Age' : [28 , 32 , 25] }
df = pd.DataFrame(data)
# print(df)

df_filtrado = df[df['Age'] > 30]
# print(df_filtrado) # 1 Name Bob, Age 32

csv_monitor = pd.read_csv('data_2.csv')
# print(csv_monitor)
filtered_data = csv_monitor[(csv_monitor['current'] > 0.40)]
print(filtered_data)
filtered_data.to_csv('filtered_data.csv', index=False)

# Obtener las estadísticas básicas
statistics_summary = csv_monitor.describe()
print("Estadísticas básicas:")
print(statistics_summary)

# Calcular y mostrar la moda para cada columna
mode_current = csv_monitor['current'].mode()[0]
mode_voltage = csv_monitor['voltage'].mode()[0]
print(f"\nModa de la corriente: {mode_current}")
print(f"Moda del voltaje: {mode_voltage}")

# Calcular y mostrar la mediana para cada columna
median_current = csv_monitor['current'].median()
median_voltage = csv_monitor['voltage'].median()
print(f"\nMediana de la corriente: {median_current}")
print(f"Mediana del voltaje: {median_voltage}")

# Calcular y mostrar la varianza para cada columna
variance_current = csv_monitor['current'].var()
variance_voltage = csv_monitor['voltage'].var()
print(f"\nVarianza de la corriente: {variance_current}")
print(f"Varianza del voltaje: {variance_voltage}")

# Calcular y mostrar la desviación estándar para cada columna
std_current = csv_monitor['current'].std()
std_voltage = csv_monitor['voltage'].std()
print(f"\nDesviación estándar de la corriente: {std_current}")
print(f"Desviación estándar del voltaje: {std_voltage}")

# Calcular y mostrar la suma total de cada columna
total_sum = csv_monitor.sum()
print(f"\nSuma total de cada columna:\n{total_sum}")

# Calcular y mostrar el conteo de datos en cada columna
total_count = csv_monitor.count()
print(f"\nConteo de datos en cada columna:\n{total_count}")





