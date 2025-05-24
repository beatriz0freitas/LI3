CC = gcc
CFLAGS = $(shell pkg-config --cflags glib-2.0) $(addprefix -I, $(shell find include -type d)) -lm -lncurses -lpanel -lform  #-Wall -Wextra -Werror -Wpedantic
LIBS = $(shell pkg-config --libs glib-2.0)

SRC_DIR = src
OBJ_DIR = objs

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS)) $(RECOMENDADOR_OBJ)

MAIN_PROGRAM = $(OBJ_DIR)/apresentacao/programa-principal.o 
TEST_PROGRAM = $(OBJ_DIR)/apresentacao/programa-testes.o
UNIT_TEST_PROGRAM = $(OBJ_DIR)/apresentacao/programa-testes-unitarios.o
INTERAT_PROGRAM = $(OBJ_DIR)/apresentacao/programa-interativo.o

RECOMENDADOR_OBJ = $(OBJ_DIR)/recomendador/recomendador.o
RECOMENDADOR_IMPL_OBJ = $(OBJ_DIR)/infra/recomendador-implementacao.o


all:programa-principal programa-testes programa-testes-unitarios programa-interativo
programa-principal: $(filter-out $(TEST_PROGRAM) $(UNIT_TEST_PROGRAM) $(INTERAT_PROGRAM) $(RECOMENDADOR_IMPL_OBJ), $(OBJS)) $(MAIN_PROGRAM)
	@echo "Linking programa-principal..."
	@$(CC) $^ $(CFLAGS) $(LIBS) -o $@ > /dev/null

programa-testes: $(filter-out $(MAIN_PROGRAM) $(UNIT_TEST_PROGRAM) $(INTERAT_PROGRAM) $(RECOMENDADOR_IMPL_OBJ), $(OBJS)) $(TEST_PROGRAM)
	@echo "Linking programa-testes..."
	@$(CC) $^ $(CFLAGS) $(LIBS) -o $@ > /dev/null

programa-testes-unitarios: $(filter-out $(MAIN_PROGRAM) $(TEST_PROGRAM) $(INTERAT_PROGRAM) $(RECOMENDADOR_IMPL_OBJ), $(OBJS)) $(UNIT_TEST_PROGRAM)
	@echo "Linking programa-testes-unitarios..."
	@$(CC) $^ $(CFLAGS) $(LIBS) -o $@ > /dev/null

programa-interativo: $(filter-out $(MAIN_PROGRAM) $(TEST_PROGRAM) $(UNIT_TEST_PROGRAM) $(RECOMENDADOR_OBJ), $(OBJS)) $(INTERAT_PROGRAM) 
	@echo "Linking programa-interativo..."
	@$(CC) $^ $(CFLAGS) $(LIBS) -o $@ > /dev/null


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g
debug: clean all

run: programa-principal
	./programa-principal dataset/com_erros input.txt

run-normal: programa-principal
	./programa-principal dataset/com_erros input.txt normal

run-testes: programa-testes
	./programa-testes dataset/com_erros input.txt resultados-esperados

run-testes-normal: programa-testes
	./programa-testes dataset/com_erros input.txt resultados-esperados normal

run-testes-grande: programa-testes
	./programa-testes dataset/com_erros_grande input-grande.txt resultados-esperados-grande

unit-tests: programa-testes-unitarios
	./programa-testes-unitarios

run-interativo: programa-interativo
	./programa-interativo

gprof: CFLAGS += -pg
gprof: clean all
	./programa-principal dataset/com_erros input.txt
	gprof programa-principal gmon.out > gprof.txt

valgrind: programa-principal
	valgrind --leak-check=summary ./programa-principal dataset/valgrind input.txt

valgrind-full: clean programa-principal
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./programa-principal dataset/valgrind input.txt
	
docs: 
	doxygen Doxyfile

clean:
	rm -rf all
	find $(OBJ_DIR) -type f ! -name 'recomendador.o' -exec rm -rf {} +
	rm -rf resultados/* 
	rm -rf gmon.out gprof.txt
	rm -rf docs

.PHONY: all clean debug run run-testes unit-tests run-iterativo gprof valgrind valgrind-full docs
