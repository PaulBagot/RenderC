./bin/test_image : ./build/test_image.o ./build/image.o
	gcc -Wall -o ./bin/test_image ./build/test_image.o ./build/image.o -lcunit

./build/test_image.o : ./tests/test_image.c
	gcc -Wall -c ./tests/test_image.c -o ./build/test_image.o

./build/image.o : ./src/image.c
	gcc -Wall -c ./src/image.c -o ./build/image.o
