NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
MSRC = philosophers.c\
		parsing.c\
		utils1.c\
		dinner.c\
		setters_getters.c\
		write.c\
		monitor.c\

MOBJ = $(MSRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC)	$(CFLAGS) -c $< -o $@

$(NAME): $(MOBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(MOBJ)

clean:
	$(RM) $(MOBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all