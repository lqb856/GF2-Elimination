#include <immintrin.h>
#include <emmintrin.h>

#define AVX_512_CHUNK_SIZE 512 / 64
#define AVX_256_CHUNK_SIZE 256 / 64
#define SSE_128_CHUNK_SIZE 128 / 64