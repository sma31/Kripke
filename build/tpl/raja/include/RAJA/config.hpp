/*!
 ******************************************************************************
 *
 * \file
 *
 * \brief   Header file for basic RAJA configuration options.
 *
 *          This file contains platform-specific parameters that control
 *          aspects of compilation of application code using RAJA. These
 *          parameters specify: SIMD unit width, data alignment information,
 *          inline directives, etc.
 *
 *          IMPORTANT: These options are set by CMake and depend on the options
 *          passed to it.
 *
 *          IMPORTANT: Exactly one e RAJA_COMPILER_* option must be defined to
 *          ensure correct behavior.
 *
 *          Definitions in this file will propagate to all RAJA header files.
 *
 ******************************************************************************
 */

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2016-18, Lawrence Livermore National Security, LLC.
//
// Produced at the Lawrence Livermore National Laboratory
//
// LLNL-CODE-689114
//
// All rights reserved.
//
// This file is part of RAJA.
//
// For details about use and distribution, please read RAJA/LICENSE.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#ifndef RAJA_config_HPP
#define RAJA_config_HPP

/*!
 ******************************************************************************
 *
 * \brief Enable/disable exploratory fault tolerance mechanism.
 *
 ******************************************************************************
 */
/* #undef ENABLE_FT */

/*!
 ******************************************************************************
 *
 * \brief Default RAJA floating point scalar and pointer options.
 *
 ******************************************************************************
 */
#define RAJA_USE_DOUBLE
#define RAJA_USE_BARE_PTR

/*!
 ******************************************************************************
 *
 * \brief Deprecated tests
 *
 ******************************************************************************
 */
/* #undef RAJA_DEPRECATED_TESTS */

/*!
 ******************************************************************************
 *
 * \brief Programming model back-ends, plus CHAI enable/disable.
 *
 ******************************************************************************
 */
/* #undef RAJA_ENABLE_OPENMP */
/* #undef RAJA_ENABLE_TARGET_OPENMP */
/* #undef RAJA_ENABLE_TBB */
#define RAJA_ENABLE_CUDA
/* #undef RAJA_ENABLE_CLANG_CUDA */
/* #undef RAJA_ENABLE_CHAI */

/*!
 ******************************************************************************
 *
 * \brief Timer options.
 *
 ******************************************************************************
 */
#define RAJA_USE_CHRONO
/* #undef RAJA_USE_GETTIME */
/* #undef RAJA_USE_CLOCK */
/* #undef RAJA_USE_CYCLE */

/*!
 ******************************************************************************
 *
 * \brief Detect the host C++ compiler we are using.
 *
 ******************************************************************************
 */
#if defined(__INTEL_COMPILER)
#define RAJA_COMPILER_INTEL
#elif defined(__xlc__)
#define RAJA_COMPILER_XLC
#elif defined(__clang__)
#define RAJA_COMPILER_CLANG
#elif defined(__PGI)
#define RAJA_COMPILER_PGI
#elif defined(_WIN32)
#define RAJA_COMPILER_MSVC
#elif defined(__GNUC__)
#define RAJA_COMPILER_GNU
#endif


namespace RAJA {

#if defined(RAJA_ENABLE_OPENMP)
#if not defined(_OPENMP)
#error RAJA configured with ENABLE_OPENMP, but OpenMP not supported by current compiler 
#endif // _OPENMP
#endif // RAJA_ENABLE_OPENMP


/*!
 ******************************************************************************
 *
 * \brief RAJA software version number.
 *
 ******************************************************************************
 */
const int RAJA_VERSION_MAJOR = 0;
const int RAJA_VERSION_MINOR = 6;
const int RAJA_VERSION_PATCHLEVEL = 0;


/*!
 ******************************************************************************
 *
 * \brief Useful macros.
 *
 ******************************************************************************
 */

//
//  Platform-specific constants for range index set and data alignment:
//
//     RANGE_ALIGN - alignment of begin/end indices in range segments
//                   (i.e., starting index and length of range segments
//                    constructed by index set builder methods will
//                    be multiples of this value)
//
//     RANGE_MIN_LENGTH - used in index set builder methods
//                        as min length of range segments (an integer multiple
//                        of RANGE_ALIGN)
//
//     DATA_ALIGN - used in compiler-specific intrinsics and typedefs
//                  to specify alignment of data, loop bounds, etc.;
//                  units of "bytes"

const int RANGE_ALIGN = 4;
const int RANGE_MIN_LENGTH = 32;
const int DATA_ALIGN = 64;

#if defined (_WIN32)
#define RAJA_RESTRICT __restrict
#else
#define RAJA_RESTRICT __restrict__
#endif


//
//  Compiler-specific definitions for inline directives, data alignment
//  intrinsics, and SIMD vector pragmas
//
//  Variables for compiler instrinsics, directives, typedefs
//
//     RAJA_INLINE - macro to enforce method inlining
//
//     RAJA_ALIGN_DATA(<variable>) - macro to express alignment of data,
//                              loop bounds, etc.
//
//     RAJA_SIMD - macro to express SIMD vectorization pragma to force
//                 loop vectorization
//
//     RAJA_ALIGNED_ATTR(<alignment>) - macro to express type or variable alignments
//

#if defined(RAJA_COMPILER_GNU)
#define RAJA_ALIGNED_ATTR(N) __attribute__((aligned(N)))
#else
#define RAJA_ALIGNED_ATTR(N) alignas(N)
#endif


#if defined(RAJA_COMPILER_INTEL)
//
// Configuration options for Intel compilers
//

#define RAJA_INLINE inline  __attribute__((always_inline))

#if defined(RAJA_ENABLE_CUDA)
#define RAJA_ALIGN_DATA(d) d
#else
#define RAJA_ALIGN_DATA(d) __assume_aligned(d, RAJA::DATA_ALIGN)
#endif

#if defined(_OPENMP) && (_OPENMP >= 201307)
#define RAJA_SIMD  _Pragma("omp simd")
#define RAJA_NO_SIMD _Pragma("novector")
#else
#define RAJA_SIMD _Pragma("simd")
#define RAJA_NO_SIMD  _Pragma("novector")
#endif


#elif defined(RAJA_COMPILER_GNU)
//
// Configuration options for GNU compilers
//

#define RAJA_INLINE inline  __attribute__((always_inline))

#if defined(RAJA_ENABLE_CUDA)
#define RAJA_ALIGN_DATA(d) d
#else
#define RAJA_ALIGN_DATA(d) __builtin_assume_aligned(d, RAJA::DATA_ALIGN)
#endif

#if defined(_OPENMP) && (_OPENMP >= 201307)
#define RAJA_SIMD  _Pragma("omp simd")
#define RAJA_NO_SIMD 
#elif defined(__GNUC__) && defined(__GNUC_MINOR__) && \
      ( ( (__GNUC__ == 4) && (__GNUC_MINOR__ == 9) ) || (__GNUC__ >= 5) )
#define RAJA_SIMD    _Pragma("GCC ivdep")
#define RAJA_NO_SIMD 
#else
#define RAJA_SIMD
#define RAJA_NO_SIMD
#endif


#elif defined(RAJA_COMPILER_XLC)
//
// Configuration options for xlc compiler (i.e., bgq/sequoia).
//

#define RAJA_INLINE inline  __attribute__((always_inline))

#define RAJA_ALIGN_DATA(d) __alignx(RAJA::DATA_ALIGN, d)

//#define RAJA_SIMD  _Pragma("simd_level(10)")
#if defined(_OPENMP) && (_OPENMP >= 201307)
#define RAJA_SIMD  _Pragma("omp simd")
#define RAJA_NO_SIMD _Pragma("nosimd")
#else
// This pragma is unreliable.  It may not work on Blue Gene/Q or POWER7.
#define RAJA_SIMD  _Pragma("ibm independent_loop")
#define RAJA_NO_SIMD  _Pragma("nosimd")
#endif


#elif defined(RAJA_COMPILER_CLANG)
//
// Configuration options for clang compilers
//

#define RAJA_INLINE inline  __attribute__((always_inline))

#if defined(RAJA_ENABLE_CUDA)
#define RAJA_ALIGN_DATA(d) d
#else
#define RAJA_ALIGN_DATA(d) __builtin_assume_aligned(d, RAJA::DATA_ALIGN)
#endif

#if defined(_OPENMP) && (_OPENMP >= 201307)
#define RAJA_SIMD  _Pragma("omp simd")
#define RAJA_NO_SIMD _Pragma("clang loop vectorize(disable)")
#else

#if ( (__clang_major__ >= 4 ) ||  (__clang_major__ >= 3 && __clang_minor__ > 7) )
#define RAJA_SIMD    _Pragma("clang loop vectorize(assume_safety)")
#else 
#define RAJA_SIMD    _Pragma("clang loop vectorize(enable)")
#endif

#define RAJA_NO_SIMD  _Pragma("clang loop vectorize(disable)")
#endif

#else

#pragma message("RAJA_COMPILER unknown, using default empty macros.")

#define RAJA_INLINE inline
#define RAJA_ALIGN_DATA(d) d
#define RAJA_SIMD
#define RAJA_NO_SIMD

#endif

#define RAJA_HAVE_POSIX_MEMALIGN
#define RAJA_HAVE_ALIGNED_ALLOC
/* #undef RAJA_HAVE_MM_MALLOC */

//
//Creates a general framework for compiler alignment hints
//
// Example usage:
// double *a = RAJA::allocate_aligned_type<double>(RAJA::DATA_ALIGN,10*sizeof(double));
// double *y = RAJA::align_hint

template<typename T>
RAJA_INLINE
T * align_hint(T * x)
{
#if defined (RAJA_COMPILER_INTEL)
  RAJA_ALIGN_DATA(x);
  return x;
#else
  return static_cast<T *>(RAJA_ALIGN_DATA(x));
#endif
}
    
}  // closing brace for RAJA namespace

#endif // closing endif for header file include guard