# Filter

## Benchmarks

Intel(R) Core(TM)2 Duo CPU     E6550  @ 2.33GHz
Available intrinsics: MMX, SSE, SSE2, SSSE3

```sh
$ uname -a
Linux pc 5.11.10-arch1-1 #1 SMP PREEMPT Fri, 26 Mar 2021 00:11:29 +0000 x86_64 GNU/Linux

$ c++ --version
c++ (GCC) 10.2.0

$ cmake --version
cmake version 3.20.1

$ make --version
GNU Make 4.3
```

`double`s (using `_mm_mul_pd`):

```
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_OptFilter/2           1219 ns         1211 ns       578201
BM_OptFilter/4           1404 ns         1392 ns       511403
BM_OptFilter/16          4363 ns         4328 ns       160378
BM_OptFilter/256       711514 ns       710518 ns         1004
BM_UnoptFilter/2         1418 ns         1410 ns       496584
BM_UnoptFilter/4         1607 ns         1598 ns       438876
BM_UnoptFilter/16        4281 ns         4265 ns       166065
BM_UnoptFilter/256     677142 ns       675935 ns         1029
```

`float`s (using `_mm_mul_ps`):


AMD Ryzen 7 4800H with Radeon Graphics
Available intrinsics: MMX, SSE, SSE2, SSSE3, SSE4.1, SSE4.2, AVX, AVX2, FMA

```sh
$ uname -a
Linux pc 5.8.0-49-generic #55~20.04.1-Ubuntu SMP Fri Mar 26 01:01:07 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux

$ c++ --version
c++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0

$ cmake --version
cmake version 3.16.3

$ make --version
GNU Make 4.2.1
```

```
----------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
BM_m128d_OptFilter/2             1293 ns         1225 ns       571454
BM_m128d_OptFilter/4             1325 ns         1323 ns       531710
BM_m128d_OptFilter/16            2193 ns         2190 ns       312372
BM_m128d_OptFilter/256         219203 ns       218849 ns         3206
BM_m128_OptFilter/2              1294 ns         1269 ns       507333
BM_m128_OptFilter/4              1312 ns         1316 ns       530682
BM_m128_OptFilter/16             2221 ns         2217 ns       315905
BM_m128_OptFilter/256          217770 ns       217692 ns         3220
BM_fma_m128d_OptFilter/2         1291 ns         1228 ns       571609
BM_fma_m128d_OptFilter/4         1319 ns         1325 ns       530026
BM_fma_m128d_OptFilter/16        2183 ns         2180 ns       315139
BM_fma_m128d_OptFilter/256     217220 ns       217103 ns         3223
BM_DoubleUnoptFilter/2           1296 ns         1235 ns       509598
BM_DoubleUnoptFilter/4           1325 ns         1324 ns       529084
BM_DoubleUnoptFilter/16          2225 ns         2218 ns       315588
BM_DoubleUnoptFilter/256       217371 ns       217248 ns         3221
```

## SIMD

I tried to use

```c++
__m128d sum = { 0.0, 0.0 };

for (/*...*/)
{
	__m128d res = _mm_mul_pd(/*...*/);
	sum = _mm_add_pd(sum, res);
}

return sum[0] + sum[1];

```

but the precision drops drastically (difference between OptFilter and UnoptFilter outputs is ~1.5e-10).


Ubuntu 18.04

```
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_OptFilter/2           1220 ns         1217 ns       556354
BM_OptFilter/4           1431 ns         1431 ns       492115
BM_OptFilter/16          4171 ns         4164 ns       166693
BM_OptFilter/256       698824 ns       697416 ns         1060
BM_UnoptFilter/2         1259 ns         1259 ns       559742
BM_UnoptFilter/4         1361 ns         1358 ns       555822
BM_UnoptFilter/16        4088 ns         4082 ns       169248
BM_UnoptFilter/256     691982 ns       690660 ns         1093
```
