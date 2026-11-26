#!/bin/bash

check_cpu() {
    local lscpu_out cpu_cores
    # переменная (локальная)

    lscpu_out=$(lscpu)
    # lscpu - функция которая позволяет выводить характеристики процессора
    # lscpu_out - выполняет lscpu

    cpu_cores=$(echo "$lscpu_out" | grep '^CPU(s):' | cut -d: -f2)
    # echo "$lscpu_out" - выводит lscpu
    # grep '^CPU(s): ' - оставляет только строку начинающуюся с CPU(s): 
    # cut -d: -f2 - берет второе поле

    if ((cpu_cores < MIN_CPU_CORES)); then
        echo "[err] нету ядер CPU: $cpu_cores < $MIN_CPU_CORES " >&2

        return 1
    fi
    # ((...)) - числа сравниваються как числа а не как строчки
    # >&2 - перенаправляет в поток ошибок

    return 0
}