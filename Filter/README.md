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
Linux pc 5.4.0-42-generic #46~18.04.1-Ubuntu SMP Fri Jul 10 07:21:24 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux

$ c++ --version
c++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0

$ cmake --version
cmake version 3.10.2

$ make --version
GNU Make 4.1
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

- Intel(R) Core(TM) i7-7700HQ CPU @ 2.80GHz

Available intrinsics: MMX, SSE, SSE2, SSSE3, SSE4.1, SSE4.2, AVX, AVX2, FMA

```
$ uname -a
Linux pc 5.10.30-1-MANJARO #1 SMP Wed Apr 14 08:07:27 UTC 2021 x86_64 GNU/Linux

$ c++ --version
c++ (GCC) 10.2.0

$ cmake --version
cmake version 3.20.1

$ make --version
GNU Make 4.3
```

```
---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
BM_m128d_OptFilter/2              704 ns          707 ns       994959                                                   
BM_m128d_OptFilter/4              815 ns          813 ns       867307                                                   
BM_m128d_OptFilter/16            2879 ns         2871 ns       252633                                                   
BM_m128d_OptFilter/256         525730 ns       525398 ns         1385                                                   
BM_m128_OptFilter/2               765 ns          761 ns       864010                                                   
BM_m128_OptFilter/4               823 ns          820 ns       830158                                                   
BM_m128_OptFilter/16             2605 ns         2606 ns       267454                                                   
BM_m128_OptFilter/256          468811 ns       468760 ns         1471                                                   
BM_fma_m128d_OptFilter/2          744 ns          740 ns       946191                                                   
BM_fma_m128d_OptFilter/4          872 ns          862 ns       793476                                                   
BM_fma_m128d_OptFilter/16        2834 ns         2820 ns       249222                                                   
BM_fma_m128d_OptFilter/256     515533 ns       515227 ns         1327                                                   
BM_fma_m128_OptFilter/2           734 ns          731 ns       939563                                                   
BM_fma_m128_OptFilter/4           832 ns          827 ns       909044                                                   
BM_fma_m128_OptFilter/16         1303 ns         1300 ns       515172                                                   
BM_fma_m128_OptFilter/256      133652 ns       133622 ns         5329                                                   
BM_fma_m256d_OptFilter/2          781 ns          769 ns       953821                                                   
BM_fma_m256d_OptFilter/4          766 ns          760 ns       843087                                                   
BM_fma_m256d_OptFilter/16        1330 ns         1326 ns       535792
BM_fma_m256d_OptFilter/256     134769 ns       134746 ns         5153
BM_fma_m256_OptFilter/2           745 ns          740 ns      1010518
BM_fma_m256_OptFilter/4           851 ns          834 ns       885719
BM_fma_m256_OptFilter/16         1150 ns         1143 ns       612099
BM_fma_m256_OptFilter/256       68333 ns        68327 ns         9849
BM_DoubleUnoptFilter/2            703 ns          705 ns      1001970
BM_DoubleUnoptFilter/4            917 ns          902 ns       870656
BM_DoubleUnoptFilter/16          2932 ns         2917 ns       234448
BM_DoubleUnoptFilter/256       559913 ns       561232 ns         1310
BM_FloatUnoptFilter/2             775 ns          769 ns       856366
BM_FloatUnoptFilter/4             804 ns          803 ns       851521
BM_FloatUnoptFilter/16           2663 ns         2663 ns       265129
BM_FloatUnoptFilter/256        506821 ns       506478 ns         1321
```

## Вывод

`fma_m256_OptFilter` работает в 7.5 раз быстрее неоптимизированной версии.

