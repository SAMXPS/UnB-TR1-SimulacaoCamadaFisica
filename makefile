CC=g++

ODIR=obj
LDIR=lib

LIBS=-lm -lncurses

DEPS = CamadaFisica.h

_OBJ = Simulacao.o CamadaFisica.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(OBJ): $(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $<

simulacao: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)