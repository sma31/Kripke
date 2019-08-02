#ifndef KRIPKE_CONFIG_H__
#define KRIPKE_CONFIG_H__

#define KRIPKE_VERSION "1.2.4"

#define KRIPKE_CXX_COMPILER "/usr/bin/c++"
#define KRIPKE_CXX_FLAGS "     -Wall -Wextra  "
#define KRIPKE_LINK_FLAGS " "

#define KRIPKE_USE_MPI
/* #undef KRIPKE_USE_OPENMP */
#define KRIPKE_USE_CUDA
/* #undef KRIPKE_USE_CHAI */

/* #undef KRIPKE_USE_CALIPER */

#define KRIPKE_ARCH "CUDA"

#define KRIPKE_ARCHV_DEFAULT ArchV_CUDA
#define KRIPKE_LAYOUTV_DEFAULT LayoutV_DGZ

#define KRIPKE_NVCC_COMPILER "/usr/local/cuda/bin/nvcc"
#define KRIPKE_NVCC_FLAGS "--expt-extended-lambda -O3 -DNDEBUG"

#endif
