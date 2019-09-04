# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/29 15:10:41 by msaliuta          #+#    #+#              #
#    Updated: 2019/09/04 18:50:13 by msaliuta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	lem-in
CMPL	=	cc
CFLG	=	$(addprefix -W, all extra error)
LIBD	=	libftprintf
BNSD	=	bonus_part
SRCD	=	src
INCD	=	inc
OBJD	=	obj
INCS	=	-I$(addprefix $(LIBD)/, $(INCD)) -I $(INCD)

SRCS	=	lem_in.c\
			algo_start.c\
			help_functs.c\
			parser.c\
			path_functs.c\
			room_functs.c\
			functs.c\

OBJS	=	$(addprefix $(OBJD)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBD)
	@$(CMPL) $(CFLG) -o $(NAME) $^ -L$(LIBD) -lft $(INCS)
	@echo " lem-in is ready"

$(OBJD)/%.o: $(SRCD)/%.c $(INCD)/lem_in.h | $(OBJD)
	@$(CMPL) $(CFLG) -o $@ -c $< $(INCS)
	@echo ".\c"

$(OBJD):
	@mkdir -p $(OBJD)
	@echo "preparing \c"

clean:
	@$(MAKE) -C $(LIBD) clean
	@rm -rf $(OBJD)

fclean: clean
	@$(MAKE) -C $(LIBD) fclean
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re bonus
