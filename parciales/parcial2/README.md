# Solution

## Problem 1.

[Code Problem 1](./problem1.c)

Compile

```shell
$ make
```

Execute

```
$ ./problem1 | sort -u | wc -l
```

Result: `32` plus one process equals 33.

## Problem 2

[Code Problem 2](./problem2.c)

Compile

```
$ make
```

Execute

```
$ ./problem2 | sort -u | wc -l
```

Result: `1`. Only one, because the main thread ends before the other threads can be executed.

## Problem 3.

[Code Problem 3](./problem3.py)

