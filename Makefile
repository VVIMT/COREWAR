# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/20 18:51:29 by fmuller           #+#    #+#              #
#    Updated: 2018/03/20 18:51:35 by fmuller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 #============/-------\============#
#=============| LIBFT |=============#
 #============\-------/============#

include				libft/Makefile_libft_var.txt

LIBFT_PATH			= $(LIBFT_DIR)

LIBFT				= $(addprefix $(LIBFT_PATH)/,lib$(LIBFT_NAME).a)
LIBFT_PATH_SRC		= $(addprefix $(LIBFT_PATH),$(LIBFT_SRC))
LIBFT_PATH_HEADER	= $(addprefix $(LIBFT_PATH),$(LIBFT_HEADER))

 #==========/------------\=========#
#===========| ASSEMBLEUR |==========#
 #==========\------------/=========#

include				asm_dir/Makefile_asm_var.txt

ASM					= $(addprefix $(ASM_DIR),$(ASM_NAME))
ASM_PATH_SRC		= $(addprefix $(ASM_DIR),$(ASM_SRC))
ASM_PATH_HEADER		= $(addprefix $(ASM_DIR),$(ASM_HEADER))

 #===========/---------\==========#
#============| COREWAR |===========#
 #===========\---------/==========#

include				corewar_dir/Makefile_corewar_var.txt

COREWAR				= $(addprefix $(COREWAR_DIR),$(COREWAR_NAME))
COREWAR_PATH_SRC	= $(addprefix $(COREWAR_DIR),$(COREWAR_SRC))
COREWAR_PATH_HEADER	= $(addprefix $(COREWAR_DIR),$(COREWAR_HEADER))


.PHONY : all asm corewar libft clean fclean re

all: $(ASM) $(COREWAR)

asm: $(ASM)

corewar: $(COREWAR)

libft: $(LIBFT)



$(ASM): $(ASM_PATH_SRC) $(ASM_PATH_HEADER) $(LIBFT)
	@$(MAKE) -C $(ASM_DIR) EXT=1

$(COREWAR): $(COREWAR_PATH_SRC) $(COREWAR_PATH_HEADER) $(LIBFT)
	@$(MAKE) -C $(COREWAR_DIR) EXT=1

$(LIBFT): $(LIBFT_PATH_SRC) $(LIBFT_PATH_HEADER)
	@$(MAKE) -C $(LIBFT_PATH) EXT=1	



norme:
	@norminette $(LIBFT_PATH_HEADER) $(LIBFT_PATH_SRC)\
				$(ASM_PATH_HEADER) $(ASM_PATH_SRC)\
				$(COREWAR_PATH_HEADER) $(COREWAR_PATH_SRC)

clean:
	@$(MAKE) -C $(ASM_DIR) $@ EXT=1
	@$(MAKE) -C $(COREWAR_DIR) $@ EXT=1
	@$(MAKE) -C $(LIBFT_PATH) $@ EXT=1
	@echo "⚠️  $(BOLD)object file$(EOC)	$(RED)removed$(EOC)"

fclean: clean
	@$(MAKE) -C $(ASM_DIR) $@ EXT=1
	@$(MAKE) -C $(COREWAR_DIR) $@ EXT=1
	@$(MAKE) -C $(LIBFT_PATH) $@ EXT=1

re: fclean all
