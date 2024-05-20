## 1. Introduction to GF(2) Elimination
The Gaussian elimination algorithm over the finite field GF(2), also known as binary Gaussian elimination, is a method used to solve systems of linear equations where the coefficients and solutions are in the field of two elements, often denoted as GF(2) or \(\mathbb{F}_2\). 

Here's a brief overview of the algorithm:

1. **Forward Elimination**:
   This step involves transforming the system of equations into an upper triangular form (similar to Gaussian elimination over real numbers), where all elements below the diagonal are zero. Since the coefficients are either 0 or 1 in GF(2), the elimination process is simplified to performing bitwise XOR operations to eliminate the leading variable from subsequent equations.

2. **Back Substitution**:
   Once the system is in upper triangular form, the back substitution step involves solving for the unknowns starting from the last equation and moving upwards. This is achieved by iteratively solving for each variable using the values determined for previously solved variables.

In this project，we parallelized the **Forward Elimination** process with OpenMP、SIMD and Pthread.

## 2. Quick Start
```shell
# 1. clone the project
git clone https://github.com/lqb856/GF2-Elimination.git

# 2. init submodules
git submodule update --init --recursive

# 3. build project
mkdir build
cd build
cmake ..
make -j

# 4. run test in build path
./test/context_test
```
