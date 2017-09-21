# Carpeta temporal donde guardar la compilación de cada archivo
TMPDIR := ./tmp
# Bandera de inclusión de directorio de bibliotecas
LDFLAGS := -L./

# Archivos fuentes (.c)
SOURCES := $(wildcard src/*.c)

# Archivos header (.h)
INCLUDE :=  -I./include

#Compilación principal: La regla all. Esta regla genera que se compilen los dos ejecutables
all: clean coordinador comparador

# Primera compilación: La regla coordinador. Esta regla se encarga de verificar la existencia de los archivos necesarios para compilar el programa coordinador.
# Luego realiza la compilación.
coordinador: $(SOURCES)
	gcc -o coordinador $(LDFLAGS) $(INCLUDE) mainCoordinador.c $(SOURCES)

# Segunda compilación: La regla comparador. Esta regla se encarga de verificar la existencia de los archivos necesarios para compilar el programa comparador.
# Luego realiza la compilación.
comparador: $(SOURCES)
	gcc -o comparador $(LDFLAGS) $(INCLUDE) mainComparador.c $(SOURCES)

# Regla de limpieza: Esta regla se encarga de limpiar los archivos ejecutables que se encuentran en el directorio principal, para poder crearlos nuevamente.
clean:
	@rm comparador
	@rm coordinador
