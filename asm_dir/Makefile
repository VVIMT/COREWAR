# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/20 18:52:48 by fmuller           #+#    #+#              #
#    Updated: 2018/03/20 18:52:49 by fmuller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 #============/-------\============#
#=============| LIBFT |=============#
 #============\-------/============#

include				../libft/Makefile_libft_var.txt

LIBFT_PATH			= ../$(LIBFT_DIR)

LIBFT				= $(addprefix $(LIBFT_PATH),lib$(LIBFT_NAME).a)
LIBFT_PATH_SRC		= $(addprefix $(LIBFT_PATH),$(LIBFT_SRC))
LIBFT_PATH_HEADER	= $(addprefix $(LIBFT_PATH),$(LIBFT_HEADER))

 #==========/------------\=========#
#===========| ASSEMBLEUR |==========#
 #==========\------------/=========#

include				Makefile_asm_var.txt

#~~~~~~~~| COMPILATION |~~~~~~~~#
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra
CPPFLAGS			= -I $(ASM_HEADER_DIR) -I $(LIBFT_PATH)$(LIBFT_HEADER_DIR) -I $(COMMON_PATH)$(ASM_HEADER_DIR)
LDFLAGS				= -L$(LIBFT_PATH)
LDLIBS				= -l$(LIBFT_NAME)

#~~~~~~~~~~~| OTHER |~~~~~~~~~~~#
EXT					= 0
DEBUG				= 0

.PHONY : all libft norme clean fclean re

all: $(ASM_NAME)

libft: $(LIBFT)

$(ASM_NAME): $(ASM_OBJ) $(LIBFT)
	@$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $(ASM_OBJ)
	@cp $(ASM_NAME) ..
	@echo "✅  $(BOLD)$(ASM_NAME)$(EOC)		$(GREEN)created$(EOC)"

$(ASM_OBJ_DIR)%.o: $(ASM_SRC_DIR)%.c $(ASM_HEADER)
	@mkdir -p $(ASM_OBJ_DIR)
ifeq ($(DEBUG),0)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
else
	@$(CC) -g $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
endif

$(COMMON_PATH)$(ASM_OBJ_DIR)%.o: $(COMMON_PATH)$(ASM_SRC_DIR)%.c $(ASM_HEADER)
	@mkdir -p $(COMMON_PATH)$(ASM_OBJ_DIR)
ifeq ($(DEBUG),0)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
else
	@$(CC) -g $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
endif

$(LIBFT): $(LIBFT_PATH_SRC) $(LIBFT_PATH_HEADER)
	@$(MAKE) -C $(LIBFT_PATH) DEBUG=$(DEBUG) EXT=1



norme:
	@$(MAKE) -C $(LIBFT_PATH) norme EXT=1
	@norminette $(ASM_HEADER) $(ASM_SRC)

clean:
	@rm -rf $(ASM_OBJ_DIR) $(COMMON_PATH)$(ASM_OBJ_DIR)
ifeq ($(EXT),0)
	@$(MAKE) -C $(LIBFT_PATH) $@ EXT=1
	@echo "⚠️  $(BOLD)object file$(EOC)	$(RED)removed$(EOC)"
endif

fclean: clean
	@rm -f $(ASM_NAME) ../$(ASM_NAME)
ifeq ($(EXT),0)
	@$(MAKE) -C $(LIBFT_PATH) $@ EXT=1
endif
	@echo "❌  $(BOLD)$(ASM_NAME)$(EOC)		$(RED)removed$(EOC)"

re : fclean all
