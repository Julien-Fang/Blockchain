all : main

main : main.o exo2.o exo1.o exo3.o exo4.o exo5.o exo6.o exo7.o exo8.o exo9.o
	gcc -o main main.o exo2.o exo1.o exo3.o exo4.o exo5.o exo6.o exo7.o exo8.o exo9.o -lssl -lcrypto 
main.o : main.c exo1.h exo2.h exo3.h exo4.h exo5.h exo6.h exo7.h exo8.h exo9.h
	gcc -Wall -c main.c

exo1.o : exo1.c exo1.h 
	gcc -Wall -c exo1.c

exo2.o : exo1.h exo2.c exo2.h
	gcc -Wall -c exo2.c

exo3.o : exo1.h exo3.c exo2.h exo3.h
	gcc -Wall -c exo3.c

exo4.o : exo1.h exo2.h exo3.h exo4.h exo4.c
	gcc -Wall -c exo4.c

exo5.o : exo1.h exo2.h exo3.h exo4.h exo5.h exo5.c
	gcc -Wall -c exo5.c

exo6.o : exo1.h exo2.h exo3.h exo4.h exo5.h exo6.h exo6.c
	gcc -Wall -c exo6.c

exo7.o : exo1.h exo2.h exo3.h exo4.h exo5.h exo7.c exo7.h exo6.h
	gcc -Wall -c exo7.c -lssl -lcrypto 

exo8.o : exo1.h exo2.h exo3.h exo4.h exo5.h exo7.h exo6.h exo8.c exo8.h
	gcc -Wall -c exo8.c

exo9.o : exo1.h exo2.h exo3.h exo4.h exo5.h exo7.h exo6.h exo9.h exo8.h exo9.c
	gcc -Wall -c exo9.c

clean :
	rm -f *.o main 

