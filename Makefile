SRC = main.c thread.c utils.c atoi.c time.c monitor.c
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address -g
HRD =  header.h

all: $(NAME)

$(NAME) : $(SRC) $(HRD)
	$(CC)  $(CFLAGS) $(SRC) -o $(NAME)

clean:

fclean:
	rm -rf $(NAME)

re: fclean all