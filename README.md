# Тестовое задание для компании ООО "СТЦ"

Выполнены задачи:
* [2.2	Написать реализацию КИХ-фильтра (C++)](Filter/)
* [2.3	Линейный конгруэнтный генератор чисел (C++)](LCG/)
* [2.7	Метод наименьших квадратов (Matlab)](LeastSquares)

## Сборка

```sh
$ sudo apt-get install cmake make g++ git
$ git clone https://github.com/arealhero/stc
$ mkdir stc/build && cd stc/build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
```

В папке `Filter/` будут лежать 2 исполняемых файла (тесты и бенчмарк) для [2.2](Filter/).
В папке `LCG/` исполняемый файл для [2.3](LCG/).

