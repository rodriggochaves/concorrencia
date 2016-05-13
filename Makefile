# Compilador utilizado
CC = gcc

# Flags utilizadas
CFLAGS = -Wall -Wstrict-prototypes 

#Bibliotecas utilizadas
LIBS= -pthread

# Diretórios de código fonte e de compilação
SRC = src
INC = include
CODE = code
FILES = files

INCLUDEDIR := $(SRC)/$(INC)
SOURCEDIR := $(SRC)/$(CODE)
FILESDIR := $(SRC)/$(FILES)
BUILDDIR = build


# Nome do executavel
EXECUTABLE = shop

# Dependências .h, Códigos fonte .c e objetos .o 
DEPS = $(wildcard $(INCLUDEDIR)/*.h)
SOURCES = $(wildcard $(SOURCEDIR)/*.c)
OBJ = $(patsubst $(SOURCEDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))


# Compilação principal
all: dir | $(BUILDDIR)/$(EXECUTABLE)
	@ echo "Pronto!"
	@ echo "Utilize 'make run' para executar o programa"

dir:
	@ echo "Checando diretório de compilação"
	@ mkdir -p $(BUILDDIR)

$(BUILDDIR)/$(EXECUTABLE): $(OBJ)
	@ $(CC) $(CFLAGS) $(LIBS) -o $@ $^
	@ echo "Compilando executável"

$(BUILDDIR)/%.o : $(SOURCEDIR)/%.c $(DEPS)
	@ $(CC) $< $(CFLAGS) -c -o $@
	@ echo 'Compilando arquivo: $(patsubst $(SOURCEDIR)/%.c,%.c,$<)'

# Executa programa
run:
	$(BUILDDIR)/$(EXECUTABLE)

# Cria novo modulo de acordo com o parametro "name"
# ex: make module name=main
module:
	$(eval SFILE = $(SOURCEDIR)/$(name).c)
	$(eval INCFILE = $(INCLUDEDIR)/$(name).h)
	$(eval UPPERNAME = $(shell echo $(name) | tr '[:lower:]' '[:upper:]'))

# Cria arquivos e escreve diretivas do preprocessador
	@ echo "Criando '$(SFILE)'..."
	@ echo "#include \"../$(INC)/$(name).h\"" >> $(SFILE)
	@ echo "Criando '$(INCFILE)'..."
	@ echo "#ifndef $(UPPERNAME)_H\n#define $(UPPERNAME)_H\n\n#endif" >> $(INCFILE)

# Cria diretórios do projeto
new:
	@ echo "Criando diretório '$(SRC)'..."
	@ mkdir -p $(SRC)
	
	@ echo "Criando diretório '$(SOURCEDIR)'..."
	@ mkdir -p $(SOURCEDIR)

	@ echo "Criando diretório '$(INCLUDEDIR)'..."
	@ mkdir -p $(INCLUDEDIR)

	@ echo "Criando diretório '$(FILESDIR)'..."


# Limpa diretório de compilação
clean:
	@ rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(EXECUTABLE)
	@ echo "Limpando diretório '/build' "