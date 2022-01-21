# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/13 22:16:25 by gunkim            #+#    #+#              #
#    Updated: 2022/01/21 18:47:39 by gunkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	miniRT - Makefile
#	----------------------------------------
#	Refer to : https://github.com/google/honggfuzz/blob/master/Makefile
#	Refer to : https://github.com/JaeSeoKim/42cursus/blob/master/01_ft_printf/Makefile

# =========================
# what we want to make
# =========================

NAME        := pipex
NAME_BONUS  := pipex_bonus

# =========================
# library path
# =========================

DIR_LIBFT   := libft

LIB_LIBFT   := libft.a

NAME_LIBFT  := $(DIR_LIBFT)/$(LIB_LIBFT)

# =========================
# implicit rule
# =========================

CC        := gcc

CFLAGS    :=
CFLAGS    += -g
# CFLAGS    := -g3 -fsanitize=address
CFLAGS    += -Wall
CFLAGS    += -Wextra
CFLAGS    += -Werror

INCLUDE   :=
INCLUDE   += -I include
INCLUDE   += -I $(DIR_LIBFT)/include

LIBFLAGS  :=
LIBFLAGS  += -L $(DIR_LIBFT) -lft

RM        := rm
RFLAGS    := -rf

# =========================
# path
# =========================

DIR_INC       := include
DIR_OBJ       := obj
DIR_SRC       := src
DIR_SRC_BONUS := src_bonus

# =========================
# source files
# =========================

SRCS := $(addprefix $(DIR_SRC)/, \
	main.c \
	utils.c \
)

SRCS_BONUS := $(addprefix $(DIR_SRC)/, \
	main_bonus.c \
	utils_bonus.c \
)

# =========================
# vpath
# =========================

vpath %.c \
	$(DIR_SRC) \
	$(DIR_SRC_BONUS)

# =========================
# object files
# =========================

OBJS := $(addprefix $(DIR_OBJ)/, $(notdir $(SRCS:.c=.o)))
OBJS_BONUS := $(addprefix $(DIR_OBJ)/, $(notdir $(SRCS_BONUS:.c=.o)))
DEPS := $(notdir $(SRCS:.c=.d))

# =========================
# ANSI/VT100
# =========================

LF      := \n
CR      := \r
ESC     := \e

ER      := $(ESC)[1K
CRLF    := $(CR)$(LF)
ERCR    := $(ER)$(CR)

# =========================
# rules
# =========================

.PHONY: all clean fclean re

all : $(NAME)

bonus : $(NAME_BONUS)

clean :
	@$(MAKE) clean -C $(DIR_LIBFT)
	@$(RM) $(RFLAGS) $(OBJS)

fclean :
	@$(MAKE) fclean -C $(DIR_LIBFT)
	@$(RM) $(RFLAGS) $(NAME) $(OBJS)
	@printf "[$(NAME)] ✔️  Cleaned all !!$(LF)"

re : fclean all

$(NAME) : $(NAME_LIBFT) $(DIR_OBJ) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBFLAGS) $(OBJS) -o $@
	@printf "$(ERCR)[$(NAME)] ✔️  Make complete !!"

$(NAME_BONUS) : $(NAME_LIBFT) $(DIR_OBJ) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBFLAGS) $(OBJS_BONUS) -o $@
	@printf "$(ERCR)[$(NAME)] ✔️  Make complete !!"

$(DIR_OBJ) :
	@mkdir -p $(DIR_OBJ)
	@printf "[$(NAME)] 📁 Created directory $(DIR_OBJ)$(LF)"

$(DIR_OBJ)/%.o : %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -I$(DIR_INC)
	@printf "$(ERCR)[$(NAME)] 🔧 Compiling object file $@"

$(NAME_LIBFT) :
	@$(MAKE) -s all -C $(DIR_LIBFT)

.PHONY: depend clean_depend

depend : $(DEPS)

clean_depend :
	@$(RM) $(RFLAGS) depend_file
	@printf "[$(NAME)] 🧹 Cleaned dependency files$(LF)"

%.d : %.c
	@$(CC) $(INCLUDES) -MM $< | sed 's|^|$(DIR_OBJ)/|' | sed 's|$(DIR_OBJ)/  ||' >> depend_file

# DO NOT DELETE
