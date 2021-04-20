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
