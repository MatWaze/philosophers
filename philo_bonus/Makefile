name = philo_bonus
cc = cc
flags = #-g -fsanitize=thread#-Wall -Wextra -Werror
src = philo_bonus.c ft_atoi.c helper_functions.c helper_functions2.c simulation.c
obj = $(src:.c=.o)

all : $(name)

$(name) : $(obj) Makefile
	$(cc) $(flags) $(obj) -o $(name)

%.o: %.c
	$(cc) $(flags) -c $< -o $@

clean :
	rm -f $(obj)

fclean : clean
	rm -f $(name)

re : fclean all

.PHONY: all clean fclean re