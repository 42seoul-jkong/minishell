# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 18:42:42 by jkong             #+#    #+#              #
#    Updated: 2022/05/20 18:42:42 by jkong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES: .c .o .h
.PHONY: all clean fclean re

CC = cc
RM = rm -f

OBJECTS_DIR = objs/

HEADER = minishell.h
SOURCE = shell.c \
			syntax.c lexer.c parser.c \
			parser_state.c parser_utils.c \
			parser_reduce_0.c parser_reduce_1.c \
			parser_reduce_2.c parser_reduce_3.c \
			make_command.c dispose_command.c \
			redir.c here_document.c
OBJECT = $(addprefix $(OBJECTS_DIR), $(SOURCE:.c=.o))

HEADER_LIBFT = libft.h
SOURCE_LIBFT = libft_memory.c libft_string.c
OBJECT_LIBFT = $(addprefix $(OBJECTS_DIR), $(SOURCE_LIBFT:.c=.o))

SOURCE_GENERAL = util_flag.c safe_io.c safe_io_utils.c safe_mem.c \
					string_buffer.c string_vector.c generic_list.c
OBJECT_GENERAL = $(addprefix $(OBJECTS_DIR), $(SOURCE_GENERAL:.c=.o))

TARGET = minishell
OBJS = $(OBJECT) $(OBJECT_LIBFT) $(OBJECT_GENERAL)

LDFLAGS += -lreadline

C_SANITIZER_FLAGS = #address undefined
CFLAGS += $(addprefix -fsanitize=, $(C_SANITIZER_FLAGS))
LDFLAGS += $(addprefix -fsanitize=, $(C_SANITIZER_FLAGS))

C_WARNING_FLAGS = all extra error
CFLAGS += $(addprefix -W, $(C_WARNING_FLAGS))

C_DEBUG_FLAGS = g3
CFLAGS += $(addprefix -, $(C_DEBUG_FLAGS))

all: $(TARGET)
clean:				;	$(RM) -r $(OBJECTS_DIR)
fclean: clean		;	$(RM) $(TARGET)
re: fclean			;	make all

$(OBJECTS_DIR):
	mkdir $(OBJECTS_DIR)

$(OBJS): | $(OBJECTS_DIR)

$(addprefix $(OBJECTS_DIR), %.o): %.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(SOURCE): $(HEADER)

$(SOURCE_LIBFT): $(HEADER_LIBFT)

$(addprefix $(OBJECTS_DIR), util_flag.o): util_flag.h
$(addprefix $(OBJECTS_DIR), safe_io.o safe_io_utils.o): safe_io.h
$(addprefix $(OBJECTS_DIR), safe_mem.o): safe_mem.h
$(addprefix $(OBJECTS_DIR), string_buffer.o): string_buffer.h
$(addprefix $(OBJECTS_DIR), string_vector.o): string_vector.h
$(addprefix $(OBJECTS_DIR), generic_list.o): generic_list.h
