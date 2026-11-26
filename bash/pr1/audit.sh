#!/bin/bash

set -euo pipefail
# -e                завершить скрипт при первой команде с ненулевым кодом
# -u                обращение к неопределенной переменной считаеться ошибкой
# -o pipefail       пайплайн возвращает ненулевой код если любая из команд в нем упала (абсолютно любая)

if [[ $# -ne 1 ]]; then
    echo "usage: $0 [path_to_config]" >&2
    # $0 - имя запущенного скрипта

    exit 1
    # выход с кодом ошибки если аргумент не один
fi
# $#                количество переданных аргументов
# -ne               число не равно...

CONFIG_PATH="$1"

if [[ ! -r "$CONFIG_PATH" ]]; then
    echo "[err] config not found: $CONFIG_PATH" >&2
    exit 1
fi
# -r                файл читаем
# !                 отрицание того что файл читаеться т е "файл не читаться"

source "$CONFIG_PATH"
# выполнение содержимого файла в текущем shell поэтому переменные MIN_CPU_CORES и тд становяться доступны в audit.sh

MODULES="cpu ram gpu network"
# строка со списком модулей

ERRORS_COUNT=0
# счетчик ошибок - старт с нуля

for module in $MODULES; do
# цикл разбивает $MODULES по пробелам -> по очереди принимает cpu, ram, gpu, network

    MODULE_PATH="./modules/${module}.sh"
    # ${module} - подстановка значения переменной с фигурными скобками

    if [[ ! -f "$MODULE_PATH" ]]; then
    # -f файл
    # ! отрицание -> файла нет

        echo "[err] module not found: $MODULE_PATH" >&2
        (( ++ERRORS_COUNT ))
        # ((...)) - арифметика
        # ++ - префиксный инкремент

        continue
        # пропустить и перейти к следующему модулю
    fi

    source "$MODULE_PATH"
    # подключает файл модуля -> функция check_<module> теперь доступна

    "check_${module}" || (( ++ERRORS_COUNT ))
    # вызов функции с именем check_cpu / check_ram / и др - подставяться через ${module}
    # || - если фукнция вернет ненулевой код то выполниться инкремент счетчика ошибок

done
# конец цикла

if (( ERRORS_COUNT == 0 )); then
    echo "[err] хост полностью соответствует минимальным системным требованиям."
    exit 0

else
    echo "[err] Хост не прошел аудит ресурсов." >&2
    exit 1

fi