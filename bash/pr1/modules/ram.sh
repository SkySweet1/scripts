#!/bin/bash

check_ram() {
    local free_out ram_gb
    # локальная переменная

    free_out=$(free -g)
    # показвает использование памяти (-g в гигабайтах)

    ram_gb=$(echo "$free_out" | grep 'Mem:' | tr -s ' ' | cut -d ' ' -f2)
    # grep 'Mem:' - оставляет строку с общим обьемом памяти
    # tr -s ' ' - сжимает подряд идущие пробелы в один (free выводит колонки с переменным числом пробелов)
    # cut -d ' ' -f2 - делит по одному пробелу - берет второе поле = total в gb

    if ((ram_gb < MIN_RAM_GB)); then
        echo "[err] нету озу: $ram_gb gb < $MIN_RAM_GB gb" >&2

        return 1
    fi

    return 0
}