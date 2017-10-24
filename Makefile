#""""""""""""""""""""""""""""""""""""""""
# Some variables concerning library paths
# to find libvath
#
PATHV = -L./vath_pth
LBASE  = -lpthread

#  makefile-compiler
CXX = g++
CPPFLAGS = -I./vath_pth/include -Iinclude
CXXFLAGS = -g -O3

# ----------------< SPool codes > -------------
all: Mcobj CalcPi CalcPiSeq CalcPiMC

CalcPiSeq: CalcPiSequential.o
		${CXX} -o CalcPiSeq CalcPiSequential.o ${PATHV} -lvath ${LBASE}
		rm *.o

CalcPi: CalcPi.o
	${CXX} -o CalcPi CalcPi.o ${PATHV} -lvath ${LBASE}
	rm *.o

Mcobj: Mcobj.o
	${CXX} -o Mcobj Mcobj.o ${PATHV} -lvath ${LBASE}
	rm *.o

CalcPiMC: CalcPiMC.o
	${CXX} -o CalcPiMC CalcPiMC.o ${PATHV} -lvath ${LBASE}
	rm *.o

clean:
	rm -f CalcPi Mcobj CalcPiSeq CalcPiMC
