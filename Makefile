SRC = main.c threads.c utils.c atoi.c
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror# -fsanitize=thread -g
HRD =  header.h

all: $(NAME)

$(NAME) : $(SRC) $(HRD)
	$(CC)  $(CFLAGS) $(SRC) -o $(NAME)

clean:

fclean:
	rm -rf $(NAME)

re: fclean all