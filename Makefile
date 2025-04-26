# Chiscaru Andrei - 312CB #
build:
	gcc -o tema3 main.c graf-L.c
run:
	./tema3
clean:
	rm tema3
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema3