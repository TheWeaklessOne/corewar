# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djoye <djoye@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/06 12:56:38 by djoye             #+#    #+#              #
#    Updated: 2020/02/06 14:45:20 by djoye            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ASM_SRC = asm_source
COREWAR_SRC = corewar_source

FLAGS = -Wall -Wextra -Werror

LIBFT_PATH = libft/libft.a
LIBFT = libft
HEADERS = -I includes/

ASM_SRC_NAMES = asm.c assembly.c create_file.c errors.c free.c parse.c validation.c

ASM_SRC_FOLDER = asm
ASM_OBJ_FOLDER = asm/obj

ASM_SRC_CODE = $(addprefix $(ASM_SRC_FOLDER)/, $(ASM_SRC_NAMES))
ASM_OBJ = $(addprefix $(ASM_OBJ_FOLDER)/, $(ASM_SRC_NAMES:.c=.o))

COREWAR_SRC_NAMES = arena.c args.c	commands.c commands2.c commands3.c \
					cur.c cursor.c init2.c init_champion.c main.c op_action.c \
					op_tab.c print.c war.c

COREWAR_SRC_FOLDER = vm
COREWAR_OBJ_FOLDER = vm/obj

COREWAR_SRC_CODE = $(addprefix $(COREWAR_SRC_FOLDER)/, $(COREWAR_SRC_NAMES))
COREWAR_OBJ = $(addprefix $(COREWAR_OBJ_FOLDER)/, $(COREWAR_SRC_NAMES:.c=.o))

all: $(LIBFT_PATH) $(ASM) $(LIBFT_PATH) $(COREWAR)

$(ASM_OBJ_FOLDER)/%.o: $(ASM_SRC_FOLDER)/%.c
	mkdir -p $(ASM_OBJ_FOLDER)
	gcc $(FLAGS) $(HEADERS) -c $< -o $@

$(ASM_LIBFT_PATH):
	make -C $(ASM_LIBFT)

$(ASM): $(ASM_OBJ)
	gcc $(ASM_OBJ) $(HEADERS) -L. $(LIBFT_PATH) -o $(ASM)

$(COREWAR_OBJ_FOLDER)/%.o: $(COREWAR_SRC_FOLDER)/%.c
	mkdir -p $(COREWAR_OBJ_FOLDER)
	gcc $(FLAGS) $(HEADERS) -c $< -o $@

$(LIBFT_PATH):
	make -C $(LIBFT)

$(COREWAR): $(COREWAR_OBJ)
	gcc $(COREWAR_OBJ) $(HEADERS) -L. $(LIBFT_PATH) -o $(COREWAR) -lncurses

clean:
	make clean -C $(ASM_SRC)
	make clean -C $ (COREWAR_SRC)

fclean: clean
	make fclean -C $(ASM_SRC)
	make fclean -C $(COREWAR_SRC)
	/bin/rm -f $(ASM)
	/bin/rm -f $(COREWAR)

re: fclean all