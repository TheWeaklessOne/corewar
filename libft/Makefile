NAME		=	libft.a

CC			=	gcc
AR			=	ar -rc
MKDIR		=	mkdir -p
RM			=	/bin/rm -rf

W_FLAGS		=	-Wall -Wextra -Werror -g
D_FLAGS		=	-g
FLAGS		=	$(W_FLAGS) $(D_FLAGS)

DELTA		=	$$(echo "$$(tput cols)-47"|bc)

SRC_DIR		=
INC_DIR		=   include/
OBJ_DIR		=	.objs/

SRC_BASE	=   ft_atoi.c               \
                ft_bzero.c              \
                ft_isalnum.c            \
                ft_isalpha.c            \
                ft_isascii.c            \
                ft_isdigit.c            \
                ft_isprint.c            \
                ft_itoa.c               \
                ft_memalloc.c           \
                ft_memccpy.c            \
                ft_memchr.c             \
                ft_memcmp.c             \
                ft_memcpy.c             \
                ft_memdel.c             \
                ft_memmove.c            \
                ft_memset.c             \
                ft_putchar.c            \
                ft_putchar_fd.c         \
                ft_putendl.c            \
                ft_putendl_fd.c         \
                ft_putnbr.c             \
                ft_putnbr_fd.c          \
                ft_putstr.c             \
                ft_putstr_fd.c          \
                ft_strcat.c             \
                ft_strchr.c             \
                ft_strclr.c             \
                ft_strcmp.c             \
                ft_strcpy.c             \
                ft_strdel.c             \
                ft_strdup.c             \
                ft_strequ.c             \
                ft_striter.c            \
                ft_striteri.c           \
                ft_strjoin.c            \
                ft_strlcat.c            \
                ft_strlen.c             \
                ft_strmap.c             \
                ft_strmapi.c            \
                ft_strncat.c            \
                ft_strncmp.c            \
                ft_strncpy.c            \
                ft_strnequ.c            \
                ft_strnew.c             \
                ft_strnstr.c            \
                ft_strrchr.c            \
                ft_strsplit.c           \
                ft_strstr.c             \
                ft_strsub.c             \
                ft_strtrim.c            \
                ft_tolower.c            \
                ft_toupper.c            \
                ft_strcapitalize.c      \
                ft_strlowcase.c         \
                ft_strupcase.c          \
                ft_str_is_alpha.c       \
                ft_str_is_numeric.c     \
                ft_printf/assoc.c       \
                ft_printf/delete.c      \
                ft_printf/float.c       \
                ft_printf/ft_arg_di.c   \
                ft_printf/ft_arg_f.c    \
                ft_printf/ft_arg_o.c    \
                ft_printf/ft_arg_xx.c   \
                ft_printf/ft_itoa_u.c   \
                ft_printf/ft_printf.c   \
                ft_printf/func_str.c    \
                ft_printf/parse.c       \
                ft_printf/print_c.c     \
                ft_printf/print_di.c    \
                ft_printf/print_f.c     \
                ft_printf/print_o.c     \
                ft_printf/print_p.c     \
                ft_printf/print_perc.c  \
                ft_printf/print_s.c     \
                ft_printf/print_u.c     \
                ft_printf/print_xx.c    \
                ft_printf/treatment.c   \


SRCS		=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
NB			=	$(words $(SRC_BASE))
INDEX		=	0

all:
	@make -j $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@ranlib $(NAME)
	@# @strip -x $(NAME)
	@printf "\r\033[48;5;15;38;5;25m✅ MAKE $(NAME)\033[0m\033[K\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval COLOR=$(shell echo $$(($(PERCENT)%35+196))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB)))))
	@printf "\r\033[38;5;11m⌛ MAKE %10.10s : %2d%% \033[48;5;%dm%*s\033[0m%*s\033[48;5;255m \033[0m \033[38;5;11m %*.*s\033[0m\033[K" $(NAME) $(PERCENT) $(COLOR) $(DONE) "" $(TO_DO) "" $(DELTA) $(DELTA) "$@"
	@$(CC) $(FLAGS) -MMD -c $< -o $@\
		-I $(INC_DIR)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)
	@$(MKDIR) $(dir $(OBJS))

clean:
	@$(RM) $(OBJ_DIR)
	@printf "\r\033[38;5;202m✖ clean $(NAME)\033[0m\033[K\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "\r\033[38;5;196m❌ fclean $(NAME)\033[0m\033[K\n"

re: fclean all

.PHONY: all clean fclean re

-include $(OBJS:.o=.d)
