SRCS				=	main.c \
						ft_error.c \
						ft_utils1.c \
						ft_utils2.c \
						ft_philo.c \
						actions.c \
						init.c \
						
OBJS				= ${SRCS:.c=.o}

NAME				= philo_three

FLAGS				= -Wall -Wextra -Werror

all :				${NAME}

${NAME} :			${OBJS}
					gcc -o ${NAME} ${FLAGS} ${SRCS}

clean :				
					rm -rf ${OBJS}

fclean : 			clean
					rm -rf ${NAME}

re :				fclean all

.PHONY:				all clean fclean re