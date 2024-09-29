printf "%s " "NORMINETTE ERRORS\n"
norminette get_next_line.c | awk '!/OK!$/'
norminette get_next_line_utils.c | awk '!/OK!$/'
norminette get_next_line.h | awk '!/OK!$/'
printf "%s " "Press enter to continue\n"
read ans
cc *.c -g -L. -lft
if [ $# -eq 0 ]; then
./a.out $(ls *.txt)
else
./a.out $@
fi
