NAME		=	tir_game

CPP			=	clang++

INCLUDE_DIR	=	./include
INCLUDE_SRC_DIR	=	./srcs/

FLAGS		=	 -std=c++17 -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(INCLUDE_SRC_DIR) -I$(INCLUDE_SRC_DIR)/classes -I$(INCLUDE_SRC_DIR)/classes/config


VPATH		=	./srcs/:./srcs/classes/:./srcs/classes/config/

SRCS		=	bomb.cpp \
                cannon_t.cpp \
                canonball_t.cpp \
                interaction.cpp \
                logic.cpp \
                scope_t.cpp \
                target_c1.cpp \
                wrap_window.cpp \
                Config.cpp \
                main.cpp \
                utils.cpp


HEADERS		=	bomb.hpp \
				cannon_t.hpp \
				canonball_t.hpp \
				interaction.hpp \
				interaction_objects.hpp \
				logic.hpp \
				scope_t.hpp \
				target_c1.hpp \
				wrap_window.hpp \
				shooting_range.hpp \
				Config.hpp

OBJ_DIR		=	./obj/

O_FILE		=	$(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRCS))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ_DIR) $(O_FILE)
	$(CPP) $(FLAGS) $(O_FILE) -o $(NAME)

$(O_FILE): $(OBJ_DIR)%.o: %.cpp $(HEADERS)
	$(CPP) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)



.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR)

PHONY: fclean
fclean: clean
	@rm -f $(NAME)

.PHONY: re
re:		fclean all

.PHONY: run
run: all
	./$(NAME)