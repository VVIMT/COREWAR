# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 15:26:47 by fmuller           #+#    #+#              #
#    Updated: 2018/03/05 20:14:00 by fmuller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include		Makefile_libft_var.txt

#~~~~~~~~| COMPILATION |~~~~~~~~#
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
CPPFLAGS 	= -I $(LIBFT_HEADER_DIR)

#~~~~~~~~~~~~| NAME |~~~~~~~~~~~#
NAME		= libft.a

#~~~~~~~~~~~| OTHER |~~~~~~~~~~~#
EXT			= 0
DEBUG		= 0

.PHONY: all norme clean fclean re

all: $(NAME)

$(NAME): $(LIBFT_OBJ)
	@ar rc $@ $^
	@ranlib $@
	@echo "✅  $(BOLD)$(NAME)$(EOC)	$(GREEN)created$(EOC)"

$(LIBFT_OBJ_DIR)%.o: $(LIBFT_SRC_DIR)%.c $(LIBFT_HEADER)
	@mkdir -p $(LIBFT_OBJ_DIR)ft_printf $(LIBFT_OBJ_DIR)get_next_line
ifeq ($(DEBUG),0)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
else
	@$(CC) -g $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
endif




norme:
	@norminette $(LIBFT_SRC)
	@norminette $(LIBFT_HEADER)

clean:
	@rm -rf $(LIBFT_OBJ_DIR)
ifeq ($(EXT),0)
	@echo "⚠️  $(BOLD)object file$(EOC)	$(RED)removed$(EOC)"
endif

fclean: clean
	@rm -f $(NAME)
	@echo "❌  $(BOLD)$(NAME)$(EOC)	$(RED)removed$(EOC)"

re: fclean all
