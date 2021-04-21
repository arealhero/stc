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

Чтобы избавиться от предупреждения "Cpu scaling is enabled", необходимо запустить следующую команду:

```sh
$ echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
```

Чтобы обратно включить режим энергосбережения:

```sh
$ echo powersave | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
```

Посмотреть текущий режим:

```sh
$ cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
```

Посмотреть доступные режимы:

```sh
$ cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_available_governors
```

```
---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
BM_m128d_OptFilter/2             1318 ns         1270 ns       514459
BM_m128d_OptFilter/4             1331 ns         1327 ns       523062
BM_m128d_OptFilter/16            2237 ns         2238 ns       312925
BM_m128d_OptFilter/256         218326 ns       218115 ns         3211
BM_m128_OptFilter/2              1305 ns         1287 ns       530802
BM_m128_OptFilter/4              1330 ns         1326 ns       531164
BM_m128_OptFilter/16             2194 ns         2197 ns       312919
BM_m128_OptFilter/256          218057 ns       217760 ns         3207
BM_fma_m128d_OptFilter/2         1309 ns         1279 ns       512210
BM_fma_m128d_OptFilter/4         1328 ns         1326 ns       525906
BM_fma_m128d_OptFilter/16        2225 ns         2221 ns       313532
BM_fma_m128d_OptFilter/256     217811 ns       217843 ns         3216
BM_fma_m128_OptFilter/2          1298 ns         1244 ns       544648
BM_fma_m128_OptFilter/4          1306 ns         1281 ns       543140
BM_fma_m128_OptFilter/16         1622 ns         1623 ns       432174
BM_fma_m128_OptFilter/256       56665 ns        56619 ns        12364
BM_DoubleUnoptFilter/2           1291 ns         1243 ns       530538
BM_DoubleUnoptFilter/4           1327 ns         1324 ns       528870
BM_DoubleUnoptFilter/16          2221 ns         2216 ns       315886
BM_DoubleUnoptFilter/256       217971 ns       217947 ns         3212
BM_FloatUnoptFilter/2            1295 ns         1251 ns       551899
BM_FloatUnoptFilter/4            1329 ns         1326 ns       528531
BM_FloatUnoptFilter/16           2077 ns         2090 ns       315498
BM_FloatUnoptFilter/256        217411 ns       217272 ns         3223
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
