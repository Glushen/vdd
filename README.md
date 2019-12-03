Эта программа считывает описание переменной или прототип функции на С++
и выводит словесное описание этой переменной или функции.

### Пример
Ввод:
```c++
int f(A a, long b, double)
```
Вывод:
```
'f' is a function
    with arguments
        'a' is a value of type 'A'
        'b' is a value of type long
        a value of type double
    returning a value of type int
```

### Сборка и запуск
Склонируйте репозиторий и соберите проект:
```bash
git clone https://github.com/Glushen/vdd
cd vdd
git submodule update --init
mkdir build
cd build
cmake ..
make
```
После чего запустите программу `cpp_vdd_run`.
