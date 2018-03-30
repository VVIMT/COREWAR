# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/15 19:56:13 by fmuller           #+#    #+#              #
#    Updated: 2017/11/16 21:14:19 by fmuller          ###   ########.fr        #
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

 #===========/---------\==========#
#============| COREWAR |===========#
 #===========\---------/==========#

include				Makefile_corewar_var.txt

#~~~~~~~~| COMPILATION |~~~~~~~~#
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra
CPPFLAGS			= -I $(COREWAR_HEADER_DIR) -I $(LIBFT_PATH)$(LIBFT_HEADER_DIR) -I $(COMMON_PATH)$(COREWAR_HEADER_DIR)
LDFLAGS				= -L$(LIBFT_PATH)
LDLIBS				= -l$(LIBFT_NAME)

#~~~~~~~~~~~| OTHER |~~~~~~~~~~~#
EXT			= 0
DEBUG		= 0

.PHONY : all libft norme clean fclean re

all: $(COREWAR_NAME)

libft: $(LIBFT)

$(COREWAR_NAME): $(COREWAR_OBJ) $(LIBFT)
	@$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $(COREWAR_OBJ)
	@cp $(COREWAR_NAME) ..
	@echo "✅  $(BOLD)$(COREWAR_NAME)$(EOC)	$(GREEN)created$(EOC)"

$(COREWAR_OBJ_DIR)%.o: $(COREWAR_SRC_DIR)%.c $(COREWAR_HEADER)
	@mkdir -p $(COREWAR_OBJ_DIR)
ifeq ($(DEBUG),0)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
else
	@$(CC) -g $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
endif

$(COMMON_PATH)$(COREWAR_OBJ_DIR)%.o: $(COMMON_PATH)$(COREWAR_SRC_DIR)%.c $(COREWAR_HEADER)
	@mkdir -p $(COMMON_PATH)$(COREWAR_OBJ_DIR)
ifeq ($(DEBUG),0)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
else
	@$(CC) -g $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
endif

$(LIBFT): $(LIBFT_PATH_SRC) $(LIBFT_PATH_HEADER)
	@$(MAKE) -C $(LIBFT_PATH) DEBUG=$(DEBUG) EXT=1



norme:
	@$(MAKE) -C $(LIBFT_PATH) norme EXT=1
	@norminette $(COREWAR_HEADER) $(COREWAR_SRC)

clean:
	@rm -rf $(COREWAR_OBJ_DIR) $(COMMON_PATH)$(COREWAR_OBJ_DIR)
ifeq ($(EXT),0)
	@$(MAKE) -C $(LIBFT_PATH) $@ EXT=1
	@echo "⚠️  $(BOLD)object file$(EOC)	$(RED)removed$(EOC)"
endif

fclean: clean
	@rm -f $(COREWAR_NAME) ../$(COREWAR_NAME)
ifeq ($(EXT),0)
	@$(MAKE) -C $(LIBFT_PATH) $@ EXT=1
endif
	@echo "❌  $(BOLD)$(COREWAR_NAME)$(EOC)	$(RED)removed$(EOC)"

re : fclean all
