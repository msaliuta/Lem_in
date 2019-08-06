# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/04 13:27:45 by msaliuta          #+#    #+#              #
#    Updated: 2019/07/18 18:09:32 by msaliuta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CMPL	=	-Wall -Wextra -Werror
HEADER 	=	-I ./includes
SRCS	=	ft_bzero \
	ft_memset \
	ft_memcpy \
	ft_memccpy \
    ft_memmove \
    ft_memchr \
    ft_memcmp \
    ft_strlen \
    ft_strdup \
    ft_strcpy \
    ft_strncpy \
    ft_strcat \
    ft_strncat \
    ft_strlcat \
    ft_strchr \
    ft_strrchr \
    ft_strstr \
    ft_strnstr \
    ft_strcmp \
    ft_strncmp \
    ft_atoi \
    ft_islower \
    ft_isupper \
    ft_isalpha \
    ft_isdigit \
    ft_isalnum \
    ft_isprint \
    ft_toupper \
    ft_tolower \
    ft_isascii \
    ft_memalloc \
    ft_memdel \
    ft_strnew \
    ft_strdel \
    ft_strclr \
    ft_striter \
    ft_striteri \
    ft_strmap \
    ft_strmapi \
    ft_strequ \
    ft_strnequ \
    ft_strsub \
    ft_strjoin \
    ft_strtrim \
    ft_strsplit \
    ft_itoa \
    ft_putchar \
    ft_putchar_fd \
    ft_putstr \
    ft_putendl \
    ft_putnbr \
    ft_putnbr_fd \
    ft_putstr_fd \
    ft_putendl_fd \
    ft_lstnew \
    ft_lstdelone \
    ft_lstdel \
    ft_lstadd \
    ft_lstiter \
    ft_lstmap \
    ft_memcpy_bwd \
    ft_itoa_base \
    ft_ltoa \
    ft_ltoa_base \
    ft_strlower \
    ft_uitoa \
    ft_uitoa_base \
    ft_ultoa \
    ft_ultoa_base \
    get_next_line \
    ft_printf \
    int_functs \
    parse_mfw \
    longd_functs \
    process_functs \
    print_functs \
    print_width_functs \
    char_functs \
    str_functs \
    ftoa_functs \
    wchar_functs \
    wstr_functs \
    bonus1 \
    prec_print_functs \
    get_functs \
    print_wdthpdr \
    print_prec_tools \
    ft_arrclr \
    ft_atoi_base\

OBJS	=	$(addprefix obj/, $(addsuffix .o, $(SRCS)))

all: $(NAME)

obj/%.o: %.c
	@gcc $(CMPL) -c $< -o $@ $(HEADER)

$(NAME): obj $(OBJS)
	@ar -rc $(NAME) $(OBJS)

obj:
	@mkdir obj

clean:
	@rm -rf obj

fclean: clean
	@rm -rf $(NAME)

re: fclean all

