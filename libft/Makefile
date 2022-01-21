# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gunkim <gunkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/08 17:40:25 by gunkim            #+#    #+#              #
#    Updated: 2021/12/14 18:50:26 by gunkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	libft.a - Makefile
#	----------------------------------------
#	Refer to : http://github.com/google/honggfuzz/blob/master/Makefile

# =========================
# what we want to make
# =========================

NAME    := libft.a

# =========================
# implicit rule
# =========================

CC      := gcc
CFLAGS  := 
CFLAGS  += -Wall
CFLAGS  += -Wextra
CFLAGS  += -Werror

AR      := ar
ARFLAGS := -rcs

RFLAGS  := rm -rf

# =========================
# path
# =========================

DIR_INC := include
DIR_OBJ := obj
DIR_SRC := src

# =========================
# source files
# =========================

SRCS_MANDATORY := \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strnstr.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c

SRCS_BONUS := \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c

ifeq ($(BONUS),true)
	SRCS := $(SRCS_MANDATORY) \
			$(SRCS_BONUS)
else
	SRCS := $(SRCS_MANDATORY)
endif

# =========================
# VPATH
# =========================

VPATH = $(DIR_SRC)

# =========================
# object files
# =========================

OBJS := $(patsubst %.o, $(DIR_OBJ)/%.o, $(SRCS:.c=.o))
OBJS_BONUS := $(patsubst %.o, $(DIR_OBJ)/%.o, $(SRCS_BONUS:.c=.o))

# =========================
# dependency files
# =========================

DEPS := $(SRCS:.c=.d)

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
# .PHONY
# =========================

.PHONY: all clean fclean re bonus

all : $(NAME)

clean : dclean
	@$(RFLAGS) $(OBJS)
	@printf "[$(NAME)] 🧹 Cleaned object files$(LF)"

fclean : clean
	@$(RFLAGS) $(NAME) $(OBJS_BONUS)
	@printf "[$(NAME)] 🧹 Cleaned library$(LF)"

re : fclean all

.PHONY: depend dclean

depend : $(DEPS)

dclean :
	@$(RFLAGS) depend_file
	@printf "[$(NAME)] 🧹 Cleaned dependency files$(LF)"

%.d : %.c
	@$(CC) -MM $< -I$(DIR_INC) | sed 's|^|$(DIR_OBJ)/|' >> depend_file

$(NAME) : $(DIR_OBJ) $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@printf "$(ERCR)[$(NAME)] ✔️  Compiled done\n"

bonus : all
	@make BONUS=true

$(DIR_OBJ) :
	@mkdir -p $(DIR_OBJ)
	@printf "[$(NAME)] 📁 Created directory $(DIR_OBJ) $(LF)"

$(DIR_OBJ)/%.o : %.c
	@$(CC) -g $(CFLAGS) -c $< -o $@ -I $(DIR_INC)
	@printf "$(ERCR)[$(NAME)] 🔧 Compiling object file $@"
 
.SUFFIXES:

# DO NOT DELETE

obj/ft_memset.o: src/ft_memset.c include/libft.h
obj/ft_bzero.o: src/ft_bzero.c include/libft.h
obj/ft_memcpy.o: src/ft_memcpy.c include/libft.h
obj/ft_memccpy.o: src/ft_memccpy.c include/libft.h
obj/ft_memmove.o: src/ft_memmove.c include/libft.h
obj/ft_memchr.o: src/ft_memchr.c include/libft.h
obj/ft_memcmp.o: src/ft_memcmp.c include/libft.h
obj/ft_strlen.o: src/ft_strlen.c include/libft.h
obj/ft_strlcpy.o: src/ft_strlcpy.c include/libft.h
obj/ft_strlcat.o: src/ft_strlcat.c include/libft.h
obj/ft_strchr.o: src/ft_strchr.c include/libft.h
obj/ft_strrchr.o: src/ft_strrchr.c include/libft.h
obj/ft_strnstr.o: src/ft_strnstr.c include/libft.h
obj/ft_strncmp.o: src/ft_strncmp.c include/libft.h
obj/ft_atoi.o: src/ft_atoi.c include/libft.h
obj/ft_isalpha.o: src/ft_isalpha.c include/libft.h
obj/ft_isdigit.o: src/ft_isdigit.c include/libft.h
obj/ft_isalnum.o: src/ft_isalnum.c include/libft.h
obj/ft_isascii.o: src/ft_isascii.c include/libft.h
obj/ft_isprint.o: src/ft_isprint.c include/libft.h
obj/ft_toupper.o: src/ft_toupper.c include/libft.h
obj/ft_tolower.o: src/ft_tolower.c include/libft.h
obj/ft_calloc.o: src/ft_calloc.c include/libft.h
obj/ft_strdup.o: src/ft_strdup.c include/libft.h
obj/ft_substr.o: src/ft_substr.c include/libft.h
obj/ft_strjoin.o: src/ft_strjoin.c include/libft.h
obj/ft_strtrim.o: src/ft_strtrim.c include/libft.h
obj/ft_split.o: src/ft_split.c include/libft.h
obj/ft_itoa.o: src/ft_itoa.c include/libft.h
obj/ft_strmapi.o: src/ft_strmapi.c include/libft.h
obj/ft_putchar_fd.o: src/ft_putchar_fd.c include/libft.h
obj/ft_putstr_fd.o: src/ft_putstr_fd.c include/libft.h
obj/ft_putendl_fd.o: src/ft_putendl_fd.c include/libft.h
obj/ft_putnbr_fd.o: src/ft_putnbr_fd.c include/libft.h
obj/ft_lstnew.o: src/ft_lstnew.c include/libft.h
obj/ft_lstadd_front.o: src/ft_lstadd_front.c include/libft.h
obj/ft_lstsize.o: src/ft_lstsize.c include/libft.h
obj/ft_lstlast.o: src/ft_lstlast.c include/libft.h
obj/ft_lstadd_back.o: src/ft_lstadd_back.c include/libft.h
obj/ft_lstdelone.o: src/ft_lstdelone.c include/libft.h
obj/ft_lstclear.o: src/ft_lstclear.c include/libft.h
obj/ft_lstiter.o: src/ft_lstiter.c include/libft.h
obj/ft_lstmap.o: src/ft_lstmap.c include/libft.h

