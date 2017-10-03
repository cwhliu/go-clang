
all:
	g++ -std=c++11 -I`llvm-config --includedir` -c libclangExt.cpp
	ar rvs libclangExt.a libclangExt.o

clean:
	rm *.o *.a

