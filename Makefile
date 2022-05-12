##
## EPITECH PROJECT, 2021
## mysh
## File description:
## make the mysh
##

# ----------------------------------------------------------------------------
# TARGET
NAME		=	42sh
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# COLOUR
CYAN		=	'\033[1;36m'
BLUE		=	'\033[1;34m'
GREEN 		= 	'\033[1;32m'
RED			=	'\033[1;31m'

RESET		=	'\033[0m'
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# IN-MAKEFILE SETTINGS
CURR_RULE	=	all
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# SRC
SRC_BUILTINS		:=	./src/builtins/cd.c							\
						./src/builtins/check_if_builtins.c			\
						./src/builtins/env.c						\
						./src/builtins/exec_builtins.c				\
						./src/builtins/exit.c						\
						./src/builtins/setenv.c						\
						./src/builtins/unsetenv.c

SRC_EXECOMMAND		:=	./src/execommand/execute_all.c				\
						./src/execommand/execute_command.c			\
						./src/execommand/execute_command_child.c	\
						./src/execommand/execute_command_genitor.c	\
						./src/execommand/execute_command_parsed.c

SRC_LOOP			:=	./src/loop/entry_point.c					\
						./src/loop/loop.c							\
						./src/loop/print_prompt.c

SRC_PARSECOMMAND	:=	./src/parsecommand/get_arguments_array.c	\
						./src/parsecommand/get_binary_path.c		\
						./src/parsecommand/get_file_to_input.c		\
						./src/parsecommand/get_redirect_to_file.c	\
						./src/parsecommand/parse_command.c			\
						./src/parsecommand/parse_pipe.c				\
						./src/parsecommand/parse_single_command.c	\
						./src/parsecommand/split_str.c				\
						./src/parsecommand/split_str_add_to_list.c

SRC_UTILS			:=	./src/utils/count_tokken.c					\
						./src/utils/get_colors.c					\
						./src/utils/get_env_from_dico.c				\
						./src/utils/my_puterror.c					\
						./src/utils/remove_empty_command.c			\
						./src/utils/remove_quote.c					\
						./src/utils/strsplit_not_rec.c

SRC					:=	./src/create_dict.c							\
						./src/main.c								\
						./src/help.c								\
						$(SRC_LOOP)									\
						$(SRC_PARSECOMMAND)							\
						$(SRC_UTILS)								\
						$(SRC_EXECOMMAND)							\
						$(SRC_BUILTINS)

OBJ					:=	$(SRC:%.c=%.o)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# LIB
LIB_TARGET	=	lib/libmy.a

LDFLAGS		=	-L$(dir $(LIB_TARGET)) -lmy
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# TEST
TNAME		:=	bin_test

TSRCDIR		:=	tests/unitest/

TSRC		:=	test_basic.c	\
				env.c			\
				help.c
TSRC		:=	$(addprefix $(TSRCDIR),$(TSRC))
TSRC		:= 	$(filter-out ./src/main.c,$(SRC)) $(TSRC)

TOBJ		:=	$(TSRC:%.c=%.o)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# FLAGS
CFLAGS		= 	-Iinclude/ -Ilib/include/ -Wall -Wextra -Wpedantic

TFLAGS		=	-fprofile-arcs -ftest-coverage

CR_TEST_LDFLAGS	=	-lcriterion -lgcov

FN_TEST_LDFLAGS	=	-lgcov
# ----------------------------------------------------------------------------

%.o: %.c
	@$(CC) $(CFLAGS) $^ -c -o $@
	@echo -e $(BLUE)'compil : $(notdir $^) -> $(notdir $@)'$(RESET)

# ----------------------------------------------------------------------------
# Make the mysh
.PHONY: 	all
all:		CURR_RULE = all
all:		init $(LIB_TARGET)
	@$(MAKE) $(NAME) -s
	@echo -e $(GREEN)'-> [finished]: $(NAME): all'$(RESET)

$(NAME):	CURR_RULE = $(NAME)
$(NAME): 	init $(OBJ)
	@$(CC) $(OBJ) $(MAIN_OBJ) -o $(NAME) $(LDFLAGS) $(CFLAGS)
	@echo -e $(GREEN)'-> [finished]: $(NAME): $(NAME)'$(RESET)

$(LIB_TARGET):
	@$(MAKE) -s -C $(dir $(LIB_TARGET))
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# Mr. clean
.PHONY: 	clean
clean:
	@$(RM) $(OBJ) $(TOBJ)
	@$(RM) $(TOBJ:.o=.gcno) $(TOBJ:.o=.gcda) $(OBJ:.o=.gcno) $(OBJ:.o=.gcda)
	@$(RM) vgcore.*

.PHONY: 	fclean
fclean:		CURR_RULE = fclean
fclean:		init clean
	@$(MAKE) -C $(dir $(LIB_TARGET)) fclean -s
	@$(RM) $(NAME) $(TNAME)
	@echo -e $(GREEN)'-> [finished]: $(NAME): $(CURR_RULE)'$(RESET)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# Re
.PHONY: 	re
re:		CURR_RULE = re
re:		init
	@$(MAKE) fclean -s
	@$(MAKE) all -s
	@echo -e $(GREEN)'-> [finished]: $(NAME): $(CURR_RULE)'$(RESET)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# Test
.PHONY: tests_run
tests_run: fn_tests_run

.PHONY: cr_tests_run
cr_tests_run: LDFLAGS += $(CR_TEST_LDFLAGS)
cr_tests_run: CFLAGS += $(TFLAGS)
cr_tests_run: fclean $(LIB_TARGET) $(TOBJ)
	@$(CC) $(TOBJ) -o $(TNAME) $(LDFLAGS) $(LDFLAGS) $(CFLAGS)
	@./$(TNAME)
	@gcovr --exclude tests/
	@gcovr --exclude tests/ --branch

.PHONY: fn_tests_run
fn_tests_run: LDFLAGS += $(FN_TEST_LDFLAGS)
fn_tests_run: CFLAGS += $(TFLAGS)
fn_tests_run: fclean $(LIB_TARGET) $(OBJ)
	@$(CC) $(OBJ) -o $(TNAME) $(LDFLAGS) $(CFLAGS)
	@./tests/functionaltest/fn_tests.sh ./$(TNAME)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# Prety Print
.PHONY: init
init:
	@echo -e $(CYAN)'-> [starting]: $(NAME): make $(CURR_RULE)'$(RESET)
# ----------------------------------------------------------------------------
