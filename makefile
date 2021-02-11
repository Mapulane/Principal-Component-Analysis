CC=g++
CK=-std=c++11

PCAdriver: PCA.o
	$(CC) $(CCFLAGS) PCA.o -o run

PCA.o: PCA.cpp
	$(CC) -c -o PCA.o PCA.cpp $(CK)

clean:
	@rm -f *.o
	@rm run
