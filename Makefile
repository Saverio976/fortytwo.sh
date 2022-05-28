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
SRC_BUILTINS		:=	cd.c							\
						check_if_builtins.c				\
						env.c							\
						exec_builtins.c					\
						exit.c							\
						setenv.c						\
						unsetenv.c						\
						alias.c							\
						which.c
SRC_BUILTINS		:=	$(addprefix builtins/,$(SRC_BUILTINS))

SRC_EXECOMMAND		:=	execute_all.c					\
						execute_command.c				\
						execute_command_child.c			\
						execute_command_genitor.c		\
						execute_command_parsed.c
SRC_EXECOMMAND		:=	$(addprefix execommand/,$(SRC_EXECOMMAND))

SRC_LOOP			:=	entry_point.c					\
						display_utils.c					\
						action_key.c					\
						action_key_arrow.c				\
						get_line_input.c				\
						loop.c							\
						print_prompt.c
SRC_LOOP			:=	$(addprefix loop/,$(SRC_LOOP))

SRC_COMPLETE		:=	complete_this.c					\
						remove_same.c
SRC_COMPLETE		:=	$(addprefix completion/,$(SRC_COMPLETE))

SRC_PARSECOMMAND	:=	get_arguments_array.c			\
						get_binary_path.c				\
						get_file_to_input.c				\
						get_redirect_to_file.c			\
						parse_command.c					\
						parse_pipe.c					\
						parse_single_command.c			\
						split_str.c						\
						split_str_add_to_list.c			\
						clear_str.c						\
						find_word_in_str.c				\
						check_null_command.c			\
						env_value.c
SRC_PARSECOMMAND	:=	$(addprefix parsecommand/,$(SRC_PARSECOMMAND))

SRC_UTILS			:=	count_tokken.c					\
						get_colors.c					\
						get_env_from_dico.c				\
						my_puterror.c					\
						remove_empty_command.c			\
						remove_quote.c					\
						strsplit_not_rec.c				\
						correct_env.c
SRC_UTILS			:=	$(addprefix utils/,$(SRC_UTILS))

SRC_PROMPT			:=	display_prompt.c				\
						prompt_flags_char.c				\
						prompt_flags_date.c				\
						prompt_flags_history.c			\
						prompt_flags_shell.c			\
						prompt_flags_time.c				\
						prompt_flags_user.c
SRC_PROMPT			:=	$(addprefix prompt/,$(SRC_PROMPT))

SRC_HISTORY			:=	history.c						\
						get_hist_startswith.c
SRC_HISTORY			:=	$(addprefix history/,$(SRC_HISTORY))

SRC					:=	create_dict.c					\
						main.c							\
						help.c							\
						$(SRC_LOOP)						\
						$(SRC_PARSECOMMAND)				\
						$(SRC_UTILS)					\
						$(SRC_EXECOMMAND)				\
						$(SRC_BUILTINS)					\
						$(SRC_PROMPT)					\
						$(SRC_HISTORY)					\
						$(SRC_COMPLETE)
SRC					:=	$(addprefix src/,$(SRC))

OBJ					:=	$(SRC:%.c=%.o)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# LIB
LIB_TARGET	=	lib/libmy.a

LDFLAGS		=	-L$(dir $(LIB_TARGET)) -lmy -lcurses
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# TEST
TNAME		:=	bin_test

TSRCDIR		:=	tests/unitest/

TSRC		:=	test_basic.c	\
				env.c			\
				help.c			\
				my_strstrip.c
TSRC		:=	$(addprefix $(TSRCDIR),$(TSRC))
TSRC		:= 	$(filter-out src/main.c,$(SRC)) $(TSRC)

TOBJ		:=	$(TSRC:%.c=%.o)
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# FLAGS
CFLAGS		+= 	-Iinclude/ -Ilib/include/ -Wall -Wextra -Wpedantic -g3

TFLAGS		=	-fprofile-arcs -ftest-coverage

CR_TEST_LDFLAGS	=	-lcriterion -lgcov

FN_TEST_LDFLAGS	=	-lgcov
# ----------------------------------------------------------------------------

%.o: %.c
	@$(CC) $(CFLAGS) $^ -c -o $@
	@echo -e $(BLUE)'compil :'$(RESET)' $(notdir $^) -> $(notdir $@)'

# ----------------------------------------------------------------------------
# Make the mysh
.PHONY: 	all
all:		CURR_RULE = all
all:		init $(LIB_TARGET)
	@$(MAKE) COMPIL_FASTER -s -j2
ifeq ("$(wildcard $(NAME))","")
	@$(MAKE) $(NAME) -s
	@echo -e $(GREEN)'-> [finished]: $(NAME): all'$(RESET)
else
	@echo "nothing to be done"
endif

COMPIL_FASTER: $(OBJ)

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
