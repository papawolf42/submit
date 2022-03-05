GREEN = \033[0;32m
RED = \033[0;31m
LIGHT_SKYBLUE_COLOR=\033[36m\033[01m
CLEAR = \033[0m

NAME = webserv
CC = clang++ -std=c++98
FLAGS = -Wall -Wextra -Werror

DIR_HEADER =	./incs/
DIR_SRC =		./srcs/
DIR_OBJ =		./objs/

SRC =	Request.cpp Response.cpp cgiResponse.cpp addResponse.cpp Resource.cpp Client.cpp main.cpp Config.cpp Libft.cpp FdBase.cpp Server.cpp Location.cpp Webserv.cpp 

SRCS = $(addprefix $(DIR_SRC), $(SRC))
OBJS = $(addprefix $(DIR_OBJ), $(SRC:%.cpp=%.o))

all: $(NAME)

$(NAME): $(DIR_OBJ) $(OBJS)
	@$(CC) $(FLAGS) -I $(DIR_HEADER) $(OBJS) -o $(NAME)
	@echo "$(LIGHT_SKYBLUE_COLOR)MAKEFILE DONE$(CLEAR)"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp
	@$(CC) $(FLAGS) -I $(DIR_HEADER) -c $< -o $@
	@echo "$(GREEN)Compiled "$<" successfully!$(CLEAR)"

clean:
	@echo "$(RED)rm $(OBJS)$(CLEAR)"
	@rm -rf $(DIR_OBJ)
	@echo "$(GREEN)clean successfully!$(CLEAR)"

fclean: clean
	@echo "$(RED)rm $(NAME)$(CLEAR)"
	@rm -f $(NAME)
	@echo "$(GREEN)fclean successfully!$(CLEAR)"

re: fclean all

.PHONY: all clean fclean re
