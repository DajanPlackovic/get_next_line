norminette get_next_line.c | awk '!/OK!$/'
norminette get_next_line_utils.c | awk '!/OK!$/'
norminette get_next_line.h | awk '!/OK!$/'
cc *.c -g -L. -lft
./a.out $@
