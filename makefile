./bin/test_image : ./build/test_image.o ./build/test.o ./build/image.o
	gcc -Wall -o ./bin/test_image ./build/test_image.o ./build/test.o ./build/image.o

./build/test_image.o : ./tests/test_image.c
	gcc -Wall -c ./tests/test_image.c -o ./build/test_image.o

./build/test.o : ./tests/test.c
	gcc -Wall -c ./tests/test.c -o ./build/test.o

./build/image.o : ./src/image.c
	gcc -Wall -c ./src/image.c -o ./build/image.o
