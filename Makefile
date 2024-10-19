# Definir el compilador
CXX = g++

# Definir las banderas de compilación
CXXFLAGS = -Wall -g

# Nombre del archivo ejecutable
TARGET = Tarea-1-AATA

# Archivo fuente
SRC = Tarea-1-AATA.cpp

# Detectar si es Windows o Linux
ifeq ($(OS),Windows_NT)
    # Para Windows
    RM = del
    TARGET := $(TARGET).exe
else
    # Para Linux
    RM = rm -f
endif

# Regla principal
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Regla para limpiar
clean:
	$(RM) $(TARGET)

# Regla para ejecutar el programa
run: $(TARGET)
	./$(TARGET)
