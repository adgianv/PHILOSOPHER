NAME = philo
CC = gcc

FLAGS = -Wall -Wextra -Werror
SRCS = $(wildcard *.c)

PHILO_OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(PHILO_OBJS)
	$(CC) $(FLAGS) $(PHILO_OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo " - Deleting object files..."
	@rm -rf $(PHILO_OBJS)

fclean:
	@echo " - Deleting all files..."
	@rm -rf $(PHILO_OBJS)
	@rm -rf $(NAME)

re: clean all