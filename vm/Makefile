SRC_DIR = src/
SRC_FILES = main.c validation.c init.c init_main_struct.c in_cycle.c check.c op.c\
			operations13_16.c values_calculation.c print.c parse_args.c\
			operations1_3.c operations4_8.c operations9_12.c setting_ids.c\
			flags.c reading_bytes.c error.c
LIBFT_DIR = libft
INC = inc/
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))


all:
	gcc  -g $(SRC) -I $(INC) $(LIBFT_DIR)/libft.a
