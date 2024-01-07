
CXXFLAGS=-I./common -Iobjs/ -O3 -std=c++17 -Wall -g -fPIC -lm
CUDA_LINK_FLAGS =  -rdc=true -gencode=arch=compute_61,code=sm_61 -Xcompiler '-fPIC' 
CUDA_COMPILE_FLAGS = --device-c -gencode=arch=compute_61,code=sm_61 -Xcompiler '-fPIC' -g -O3
all: FMIndex

FMIndex: kernel.o
	g++ -o FMIndex -lcuda -lcudart -rdc=true FMIndex.cpp  kernel.o 

kernel.o:
	nvcc -c -arch=sm_37 kernel.cu 

clean: rm -f *.o FMIndex
