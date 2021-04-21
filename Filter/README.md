# КИХ-фильтр

## CPU scaling is enabled

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

## Benchmarks

- Intel(R) Core(TM)2 Duo CPU     E6550  @ 2.33GHz

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

```
-------------------------------------------------------------------
Benchmark                         Time             CPU   Iterations
-------------------------------------------------------------------
BM_m128d_OptFilter/2           1491 ns         1352 ns       519104
BM_m128d_OptFilter/4           1657 ns         1512 ns       462568
BM_m128d_OptFilter/16          4210 ns         4046 ns       173019
BM_m128d_OptFilter/256       635546 ns       635373 ns         1098
BM_m128_OptFilter/2            1540 ns         1402 ns       499915
BM_m128_OptFilter/4            1724 ns         1537 ns       458428
BM_m128_OptFilter/16           4329 ns         4136 ns       169446
BM_m128_OptFilter/256        644355 ns       643132 ns         1092
BM_DoubleUnoptFilter/2         1467 ns         1326 ns       523903
BM_DoubleUnoptFilter/4         1663 ns         1503 ns       464168
BM_DoubleUnoptFilter/16        4008 ns         3833 ns       181890
BM_DoubleUnoptFilter/256     593189 ns       593010 ns         1179
BM_FloatUnoptFilter/2          1435 ns         1294 ns       537658
BM_FloatUnoptFilter/4          1573 ns         1436 ns       489295
BM_FloatUnoptFilter/16         3930 ns         3779 ns       185225
BM_FloatUnoptFilter/256      592605 ns       592446 ns         1180
```

- AMD Ryzen 7 4800H with Radeon Graphics

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
---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
BM_m128d_OptFilter/2             1533 ns         1532 ns       407470
BM_m128d_OptFilter/4             1628 ns         1614 ns       420047
BM_m128d_OptFilter/16            2233 ns         2231 ns       348110
BM_m128d_OptFilter/256         218060 ns       218087 ns         3220
BM_m256d_OptFilter/2             1313 ns         1320 ns       515467
BM_m256d_OptFilter/4             1328 ns         1330 ns       525504
BM_m256d_OptFilter/16            2261 ns         2262 ns       309435
BM_m256d_OptFilter/256         218233 ns       218251 ns         3211
BM_m256_OptFilter/2              1344 ns         1344 ns       516335
BM_m256_OptFilter/4              1495 ns         1491 ns       493444
BM_m256_OptFilter/16             2258 ns         2264 ns       323162
BM_m256_OptFilter/256          218267 ns       218318 ns         3212
BM_m128_OptFilter/2              1296 ns         1291 ns       533750
BM_m128_OptFilter/4              1306 ns         1319 ns       530825
BM_m128_OptFilter/16             2248 ns         2227 ns       313994
BM_m128_OptFilter/256          217870 ns       217893 ns         3217
BM_fma_m128d_OptFilter/2         1288 ns         1255 ns       530272
BM_fma_m128d_OptFilter/4         1363 ns         1354 ns       531707
BM_fma_m128d_OptFilter/16        2221 ns         2216 ns       356064
BM_fma_m128d_OptFilter/256     217876 ns       217905 ns         3223
BM_fma_m256d_OptFilter/2         1303 ns         1298 ns       531871
BM_fma_m256d_OptFilter/4         1292 ns         1296 ns       538808
BM_fma_m256d_OptFilter/16        1650 ns         1649 ns       424214
BM_fma_m256d_OptFilter/256      56654 ns        56651 ns        12340
BM_fma_m128_OptFilter/2          1289 ns         1272 ns       552958
BM_fma_m128_OptFilter/4          1373 ns         1341 ns       556381
BM_fma_m128_OptFilter/16         1624 ns         1607 ns       436430
BM_fma_m128_OptFilter/256       56234 ns        56239 ns        12454
BM_fma_m256_OptFilter/2          1300 ns         1296 ns       539898
BM_fma_m256_OptFilter/4          1308 ns         1312 ns       533530
BM_fma_m256_OptFilter/16         1446 ns         1440 ns       486705
BM_fma_m256_OptFilter/256       29232 ns        29224 ns        23951
BM_DoubleUnoptFilter/2           1297 ns         1251 ns       566634
BM_DoubleUnoptFilter/4           1386 ns         1374 ns       496730
BM_DoubleUnoptFilter/16          2217 ns         2211 ns       316297
BM_DoubleUnoptFilter/256       217425 ns       217417 ns         3221
BM_FloatUnoptFilter/2            1292 ns         1238 ns       566139
BM_FloatUnoptFilter/4            1305 ns         1319 ns       531216
BM_FloatUnoptFilter/16           2214 ns         2216 ns       316807
BM_FloatUnoptFilter/256        217480 ns       217483 ns         3220
```

## Вывод

`fma_m256_OptFilter` работает в 7.5 раз быстрее неоптимизированной версии.

