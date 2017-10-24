cmake_minimum_required(VERSION 3.8)
project(hw1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        vath_pth/include/Barrier.h
        vath_pth/include/BkBarrier.h
        vath_pth/include/BLock.h
        vath_pth/include/Common.h
        vath_pth/include/CpuTimer.h
        vath_pth/include/errors.h
        vath_pth/include/InputList.h
        vath_pth/include/JobMgr.h
        vath_pth/include/NPool.h
        vath_pth/include/OBLock.h
        vath_pth/include/OSynchP.h
        vath_pth/include/PipeBL.h
        vath_pth/include/PipeThQ.h
        vath_pth/include/print_container.h
        vath_pth/include/Rand.h
        vath_pth/include/RandInt.h
        vath_pth/include/RBuff_Tbb.h
        vath_pth/include/Reduction.h
        vath_pth/include/RingBuffer.h
        vath_pth/include/RWLock.h
        vath_pth/include/SafeCounter.h
        vath_pth/include/SafeCout.h
        vath_pth/include/SpBarrier.h
        vath_pth/include/SpBLock.h
        vath_pth/include/SpinLock.h
        vath_pth/include/SPool.h
        vath_pth/include/StringTokenizer.h
        vath_pth/include/SynchP.h
        vath_pth/include/Task.h
        vath_pth/include/TBarrier.h
        vath_pth/include/TbbReduction.h
        vath_pth/include/ThDeque.h
        vath_pth/include/ThQueue.h
        vath_pth/include/ThreadMgr.h
        vath_pth/include/ThreadRangeOmp.h
        vath_pth/include/Timer.h
        vath_pth/include/WSDeque.h
        vath_pth/include/WSPool.h
        CalcPi.C
        CalcPiMC.C
        CalcPiSequential.C
        Makefile
        Makefile_original
        Mcobj.C)

add_executable(hw1 ${SOURCE_FILES})