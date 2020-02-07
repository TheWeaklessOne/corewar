# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wstygg <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/07 17:17:26 by wstygg            #+#    #+#              #
#    Updated: 2020/02/07 17:17:27 by wstygg           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	corewar

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
D_FLAGS		=	-g

DELTA		=	$$(echo "$$(tput cols)-47"|bc)

LIBFT_DIR	=	libft/
LIBFT_LIB	=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	$(LIBFT_DIR)libft.h

LIBS		=	-lncurses

SRC_DIR		=	vm/
INC_DIR		=	includes/
OBJ_DIR		=	.objs/

SRC_BASE    =   arena.c         \
                args.c          \
                commands.c      \
                commands2.c     \
                cur.c           \
                cursor.c        \
                fork.c          \
                init2.c         \
                init_champion.c \
                ld_other.c      \
                main.c          \
                op_action.c     \
                op_tab.c        \
                print.c         \
                war.c           \

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
NB			=	$(words $(SRC_BASE))
INDEX		=	0

all :
	@make -C $(LIBFT_DIR)
	@make -j $(NAME)

$(NAME):		$(LIBFT_LIB) $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) \
		$(LIBS) \
		$(LIBFT_LIB) \
		$(FLAGS) $(D_FLAGS)
	@strip -x $@
	@printf "\r\033[48;5;15;38;5;25m✅ MAKE $(NAME)\033[0m\033[K\n"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval COLOR=$(shell echo $$(($(PERCENT)%35+196))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB)))))
	@printf "\r\033[38;5;11m⌛ MAKE %10.10s : %2d%% \033[48;5;%dm%*s\033[0m%*s\033[48;5;255m \033[0m \033[38;5;11m %*.*s\033[0m\033[K" $(NAME) $(PERCENT) $(COLOR) $(DONE) "" $(TO_DO) "" $(DELTA) $(DELTA) "$@"
	@$(CC) $(FLAGS) $(D_FLAGS) -MMD -c $< -o $@\
		-I $(INC_DIR)\
		-I $(LIBFT_INC)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:			cleanlib
	@rm -rf $(OBJ_DIR)
	@printf "\r\033[38;5;202m✖ clean $(NAME)\033[0m\033[K\n"

cleanlib:
	@make -C $(LIBFT_DIR) clean

fclean:			clean fcleanlib
	@rm -f $(NAME)
	@printf "\r\033[38;5;196m❌ fclean $(NAME)\033[0m\033[K\n"

fcleanlib:		cleanlib
	@make -C $(LIBFT_DIR) fclean

re:				fclean all

relib:			fcleanlib $(LIBFT_LIB)

-include $(OBJS:.o=.d)
