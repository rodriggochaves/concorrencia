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
DOCS = docs
BUILD = build

INCLUDEDIR := $(SRC)/$(INC)
SOURCEDIR := $(SRC)/$(CODE)
FILESDIR := $(SRC)/$(FILES)
BUILDDIR := $(BUILD)
DOCSDIR := $(DOCS)

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
	@ echo 'Compilando o arquivo: $(patsubst $(SOURCEDIR)/%.c,%.c,$<)'

# Compilação por objeto de acordo com o parâmetro "name"

obj: $(SOURCEDIR)/$(name).c $(DEPS)
	@ $(CC) $< -c -o $(BUILDDIR)/$(name).o
	@ echo "Compilando o arquivo: $(name).c"

# Executa programa
run:
	@ echo "Abrindo executável $(EXECUTABLE)"
	@ $(BUILDDIR)/$(EXECUTABLE)

# Cria novo modulo de acordo com o parâmetro "name"
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
	@ echo "Criando diretório '$(DOCSDIR)'..."
	@ mkdir -p $(DOCSDIR)

	@ echo "Criando diretório '$(SRC)'..."
	@ mkdir -p $(SRC)
	
	@ echo "Criando diretório '$(SOURCEDIR)'..."
	@ mkdir -p $(SOURCEDIR)

	@ echo "Criando diretório '$(INCLUDEDIR)'..."
	@ mkdir -p $(INCLUDEDIR)

	@ echo "Criando diretório '$(FILESDIR)'..."
	@ mkdir -p $(FILESDIR)

	@ echo "Criando diretório '$(FILESDIR)'..."
	@ mkdir -p $(DOCS)

# Limpa diretório de compilação
clean:
	@ rm -rf $(BUILDDIR)/*
	@ echo "Limpando diretório '$(BUILDDIR)' "