CC = gcc
NAME = libftprintf.a
CFLAGS = -Wall -Werror -Wextra
SRCS = *.c
OBJS = $(SRCS:%.c=%.o)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $^

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all


