NAME = abstract_vm

FLAGS = -Wall -Wextra -Werror
INC = -Iincludes/

SRC =  srcs/main.cpp\
	srcs/AbstractVM.cpp\
	srcs/Operand.cpp\
	srcs/OperandExecuter.cpp\
	srcs/OperandExecuterLexer.cpp\
	srcs/OperandExecuterParser.cpp
   
OBJ_NAME = $(SRC:.cpp=.o)
OBJ_DIR = objs/
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	clang++ -std=c++11 -o $(NAME) $(OBJ) 

$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(OBJ_DIR)/srcs
	clang++ -std=c++11 $(FLAGS) -o $@ -c $< $(INC)
clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
