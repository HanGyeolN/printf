CC = gcc
NAME = libftprintf.a
CFLAGS = -Wall -Werror -Wextra
LIBFT = ft_memset.c		\
ft_atoi.c			\
ft_bzero.c			\
ft_calloc.c			\
ft_isalnum.c		\
ft_isalpha.c		\
ft_isascii.c		\
ft_isdigit.c		\
ft_isprint.c		\
ft_itoa.c			\
ft_itoa_base.c		\
ft_itoa_base_ll.c	\
ft_itoa_u.c			\
ft_lstadd_back.c	\
ft_lstadd_front.c	\
ft_lstclear.c		\
ft_lstdelone.c		\
ft_lstiter.c		\
ft_lstlast.c		\
ft_lstmap.c			\
ft_lstnew.c			\
ft_lstsize.c		\
ft_memccpy.c		\
ft_memchr.c			\
ft_memcmp.c			\
ft_memcpy.c			\
ft_memmove.c		\
ft_memset.c			\
ft_putchar.c		\
ft_putchar_fd.c		\
ft_putendl_fd.c		\
ft_putnbr.c			\
ft_putnbr_fd.c		\
ft_putstr.c			\
ft_putstr_fd.c		\
ft_split.c			\
ft_strcat.c			\
ft_strchr.c			\
ft_strcmp.c			\
ft_strcpy.c			\
ft_strdup.c			\
ft_strjoin.c		\
ft_strlcat.c		\
ft_strlcpy.c		\
ft_strlen.c			\
ft_strmapi.c		\
ft_strncat.c		\
ft_strncmp.c		\
ft_strncpy.c		\
ft_strnstr.c		\
ft_strrchr.c		\
ft_strrev.c			\
ft_strstr.c			\
ft_strtrim.c		\
ft_substr.c			\
ft_swap.c			\
ft_tolower.c		\
ft_toupper.c		

PRINTF = freejoin.c			\
ft_printf.c			\
ft_printf_utils.c	\
parse_flag.c		\
print_char.c		\
print_hex.c			\
print_int.c			\
print_paddr.c		\
print_perc.c		\
print_str.c			\
print_uint.c		

LIBFT_DIR = libft
PRINTF_DIR = libftprintf

SRC1 = $(addprefix $(LIBFT_DIR)/, $(LIBFT))
SRC2 = $(addprefix $(PRINTF_DIR)/, $(PRINTF))

SRCS = $(SRC1) $(SRC2)
OBJS = $(SRCS:%.c=%.o)

HEADERS = includes

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^ -I $(HEADERS)

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all


