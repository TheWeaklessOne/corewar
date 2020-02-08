SRC = assoc.c treatment.c ft_arg_o.c ft_strjoin.c print_di.c ft_printf.c \
	  ft_strnew.c  ft_strdup.c  delete.c float.c func_str.c print_p.c \
	  print_s.c ft_itoa_u.c ft_arg_xx.c print_c.c ft_arg_di.c  print_u.c \
	  print_f.c print_o.c parse.c print_perc.c  print_xx.c ft_arg_f.c

OBJ = $(SRC:.c=.o)

SRCDIR = srcs
OBJDIR = objs

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))


CFLAGS = -c -Wall -Wextra -Werror

NAME = libftprintf.a

.PHONY: all clean fclean re
	.SUFFIXES: .c .o

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
		@/bin/mkdir -p $(OBJDIR)
			@gcc $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
		@ar rcs $@ $^
			@ranlib $@
			@echo "\033[32m$(NAME) OK ! \033[0m"

clean:
		@/bin/rm -rf $(OBJDIR)
		@echo "\033[33mObject deleted\033[0m"

fclean: clean
		@/bin/rm -f $(NAME)
		@echo "\033[33mExec deleted\033[0m"

re: fclean all
