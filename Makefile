NAME = ft_select

FLAGS = -Wall #-Werror -Wextra
FLAGS += -g

SOURCES =	main.c \
			main_start_finish.c \
			terminal_changes.c \
			globals_forbidden.c \
			signals_processing.c \
			readline.c \
			args_initiation.c \
			args_position_calculation.c \
			args_processing.c \
			keys_movement_dir.c \
			keys_bs_del_select.c \
			termcap_position.c \
			termcap_underline_inverse_video.c \
			bonus_functionalities.c \
			errors_output.c \
			help_functions.c 
	
#________________________________________________________________

DIR_O = objs

DIR_S = srcs

LIB_INCLUDE_DIR = libft/includes
LIB_PRINTF_INCLUDE_DIR = libft/ft_printf/includes
LIB_HEADERS = \
        $(wildcard $(LIB_INCLUDE_DIR)/*.h) \
        $(wildcard $(LIB_PRINTF_INCLUDE_DIR)/*.h)

INCLUDE_DIR = includes

SHARED_INCLUDE_DIR = $(INCLUDE_DIR)

INCLUDES = \
		-I $(SHARED_INCLUDE_DIR) \
        -I $(LIB_INCLUDE_DIR) -I $(LIB_PRINTF_INCLUDE_DIR)

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

LIBFT = $(addsuffix .libft , libft/)

%.libft:  $(LIB_HEADERS)
	@make -C $*

LIBS_INCLUDED = -Llibft -lft

#________________________________________________________________

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo "\x1b[32;01mCompiling ft_select...\x1b[0m"
	@gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBS_INCLUDED) -ltermcap
	@echo "\x1b[32;01mFt_select is ready\x1b[0m"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.c $(wildcard $(SHARED_INCLUDE_DIR)/*.h)
	@mkdir -p $(DIR_O)
	gcc $(FLAGS) -c $(INCLUDES) -o $@ $<

clean:
	@echo "\033[34mDeleting ft_select o-files\033[0m"
	@/bin/rm -Rf $(DIR_O)
	@make clean --directory ./libft

fclean: clean
	@echo "\033[34mDeleting ft_select binary\033[0m"
	@/bin/rm -f $(NAME)
	@make fclean --directory ./libft

re:		fclean all

.PHONY: all fclean clean re
