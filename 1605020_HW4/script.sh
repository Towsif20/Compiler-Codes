bison -d -y 1605020.y
echo '1'
g++ -w -c -o y.o y.tab.c
echo '2'
flex 1605020.l
echo '3'
#g++ -w -c -o l.o lex.yy.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
g++ -fpermissive -w -c -o l.o lex.yy.c
echo '4'
g++ -o a.out y.o l.o -lfl -ly
echo '5'
./a.out input2.c 1605020_log.txt 1605020_error.txt
