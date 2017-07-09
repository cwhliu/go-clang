
all:
	g++ -I`llvm-config --includedir` -c libclangExt.cpp
	ar rvs libclangExt.a libclangExt.o

clean:
	rm *.o *.a

