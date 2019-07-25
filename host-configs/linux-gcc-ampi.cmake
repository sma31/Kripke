##
## Copyright (c) 2016, Lawrence Livermore National Security, LLC.
##
## Produced at the Lawrence Livermore National Laboratory.
##
## All rights reserved.
##
##

set(RAJA_COMPILER "RAJA_COMPILER_CLANG" CACHE STRING "")
set(CMAKE_C_COMPILER_WORKS TRUE CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER_WORKS TRUE CACHE INTERNAL "")
set(CMAKE_CUDA_COMPILER_WORKS TRUE CACHE INTERNAL "")


set(CMAKE_C_COMPILER   "ampicc" CACHE PATH "")
set(CMAKE_CXX_COMPILER "ampicxx" CACHE PATH "")

set(CMAKE_CXX_FLAGS "-I/usr/local/cuda/include -L/usr/local/cuda/lib64 -lcudart" CACHE STRING "")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffast-math" CACHE STRING "")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g -ffast-math" CACHE STRING "")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g" CACHE STRING "")

set(ENABLE_CHAI On CACHE BOOL "")
set(ENABLE_CUDA On CACHE BOOL "")
set(ENABLE_OPENMP Off CACHE BOOL "")
set(ENABLE_MPI_WRAPPER On CACHE BOOL "")

set(CMAKE_CUDA_FLAGS "-restrict -gencode=arch=compute_60,code=sm_60 -I$(HOME)/charmworks/charm/netlrts-linux-x86_64-cuda/include -I$(HOME)/charmworks/charm/netlrts-linux-x86_64-cuda/include/ampi -I/usr/local/cuda/include -L/usr/local/cuda/lib64 -lcudart" CACHE STRING "")
set(CMAKE_CUDA_FLAGS_RELEASE "-O3 --expt-extended-lambda" CACHE STRING "")
set(CMAKE_CUDA_FLAGS_RELWITHDEBINFO "-O3 -lineinfo --expt-extended-lambda" CACHE STRING "")
set(CMAKE_CUDA_FLAGS_DEBUG "-O0 -g -G --expt-extended-lambda" CACHE STRING "")
set(CMAKE_CUDA_HOST_COMPILER "g++" CACHE STRING "")
