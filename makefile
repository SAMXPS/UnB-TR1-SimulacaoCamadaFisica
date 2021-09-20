CC=g++

ODIR=obj
LDIR=lib

LIBS=-lm -lncurses -lform -lmenu

DEPS = CamadaFisica.h

_OBJ = Simulacao.o CamadaFisica.o DrawUtils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST = CursesTest.o
TEST = $(patsubst %,$(ODIR)/%,$(_TEST))

$(TEST): $(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $<

$(OBJ): $(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $<

simulacao: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

curses_test: $(TEST)
	$(CC) -o $@ $^ $(LIBS)