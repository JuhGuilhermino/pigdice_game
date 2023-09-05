# Makefile para compilar o jogo Pig Dice

# Compilador
CXX = g++

# Opções de compilação
CXXFLAGS = -std=c++11 -Wall

# Nome do executável
EXECUTABLE = pig_dice

# Diretório onde estão os arquivos de origem
SRC_DIR = src

# Lista de arquivos de origem
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Lista de arquivos de objeto gerados
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)