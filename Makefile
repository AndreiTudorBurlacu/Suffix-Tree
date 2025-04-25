#Burlacu Andrei 312 CB

build:
	gcc main.c -o tema2
run:
	./tema2
clean:
	rm  -f tema2
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema1
