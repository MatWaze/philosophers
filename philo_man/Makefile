name = philo
cc = cc
flags = -Wall -Wextra -Werror #-g3 -fsanitize=thread
src = philo.c helper_functions3.c helper_functions.c helper_functions2.c simulation.c
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
