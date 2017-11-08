all: raycast.o vec_mathlib.o parse_csv.o
	gcc raycast.o vec_mathlib.o parse_csv.o -o raycast

raycast.o: raycast.c raycast.h
	gcc -c raycast.c

vec_mathlib.o: vec_mathlib.c vec_mathlib.h
	gcc -c vec_mathlib.c

parse_csv.o: parse_csv.c parse_csv.h
	gcc -c parse_csv.c

clean:
	rm *.o raycast