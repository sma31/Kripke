#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
# Copyright (c) 2016, Lawrence Livermore National Security, LLC.
#
# Produced at the Lawrence Livermore National Laboratory
#
# LLNL-CODE-689114
#
# All rights reserved.
#
# This file is part of RAJA.
#
# For additional details, please also read RAJA/LICENSE.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the disclaimer below.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the disclaimer (as noted below) in the
#   documentation and/or other materials provided with the distribution.
#
# * Neither the name of the LLNS/LLNL nor the names of its contributors may
#   be used to endorse or promote products derived from this software without
#   specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY,
# LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
#
#=== Usage ===================================================================
# This file allows RAJA to be automatically detected by other libraries
# using CMake.  To build with RAJA, you can do one of two things:
#
#   1. Set the RAJA_DIR environment variable to the root of the Caliper
#      installation.  If you loaded RAJA through a dotkit, this may already
#      be set, and RAJA will be autodetected by CMake.
#
#   2. Configure your project with this option:
#      -DRAJA_DIR=<RAJA install prefix>/share/
#
# If you have done either of these things, then CMake should automatically find
# and include this file when you call find_package(RAJA) from your
# CMakeLists.txt file.
#
#=== Components ==============================================================
#
# To link against these, just do, for example:
#
#   find_package(RAJA REQUIRED)
#   add_executable(foo foo.c)
#   target_link_libraries(foo RAJA)
#
# That's all!
#
if (NOT RAJA_CONFIG_LOADED)
  set(RAJA_CONFIG_LOADED TRUE)

  # Install layout
  set(RAJA_INSTALL_PREFIX /usr/local)
  set(RAJA_INCLUDE_DIR    /usr/local/include)
  set(RAJA_LIB_DIR        /usr/local/lib)
  set(RAJA_CMAKE_DIR      /usr/local/share/raja/cmake)

  # Includes needed to use RAJA
  set(RAJA_INCLUDE_PATH /usr/local/include)
  set(RAJA_LIB_PATH     /usr/local/lib)
  set(RAJA_COMPILE_FLAGS "     -Wall -Wextra ")
  set(RAJA_NVCC_FLAGS -restrict;-arch;sm_35;-std;c++14;--expt-extended-lambda;-ccbin;/usr/bin/c++)

  set(RAJA_RT_LIBRARIES "")

  set(RAJA_TIMER_TYPE    )
  set(ENABLE_CUDA   ON)
  set(ENABLE_FT     OFF)
  set(ENABLE_OPENMP OFF)
  set(ENABLE_TARGET_OPENMP OFF)
  set(ENABLE_TESTS  Off)
  set(RAJA_REPORT_FT     OFF)
  set(RAJA_USE_COMPLEX   OFF)
  set(RAJA_USE_DOUBLE    OFF)
  set(RAJA_USE_FLOAT     OFF)
  # Library targets imported from file
  include(/usr/local/share/raja/cmake/RAJA.cmake)
endif()