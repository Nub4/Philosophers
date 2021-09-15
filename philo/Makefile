NAME := philo

SRCS_DIR := srcs

SRCS := main.c \
		utils.c \
        init_struct.c \
        philo_actions.c \
        put_msg.c

OBJ_DIR := objs

OBJECTS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

HEADERS_FOLDER := includes/

CC := gcc

RM := rm -f

CFLAGS := -Wall -Wextra -Werror -I$(HEADERS_FOLDER) -pthread

all: $(NAME)

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
		@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJECTS)
		@echo "\033[1;33mBuilding philo..\033[0m"
		@${CC} ${CFLAGS} -o ${NAME} ${OBJECTS}
		@echo "\033[1;32mDONE!\033[0m"

clean:
		@echo "\033[1;31mRemoving object files..\033[0m"
		@${RM} ${OBJECTS}
		@rm -rf ${OBJ_DIR}

fclean: clean
		@echo "\033[1;31mRemoving launch file..\033[0m"
		@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re