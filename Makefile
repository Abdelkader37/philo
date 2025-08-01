SRC = main.c thread.c utils.c atoi.c time.c monitor.c philo.c
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
HRD =  header.h

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ) $(HRD)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean