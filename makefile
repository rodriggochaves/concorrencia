# Compilador utilizado
CC = gcc

# Flags utilizadas
CFLAGS = -Wall -Wstrict-prototypes 

#Bibliotecas utilizadas
LIBS= -pthread

# Dirtorios de código fonte e de compilação
SOURCEDIR = src/code
BUILDDIR = build

# Nome do executavel
EXECUTABLE = shop

# Dependências .h, Códigos fonte .c e objetos .o 
DEPS = $(wildcard $(SOURCEDIR)/*.h)
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

# Limpa diretório de compilação
clean:
	@ rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(EXECUTABLE)
	@ echo "Limpando diretório '/build' "