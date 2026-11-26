#!/bin/bash

check_gpu() {
    if [[ "$REQUIRE_NVIDIA_GPU" != "true" ]]; then
        echo "[skip] проверка NVIDIA gpu не требуеться"

        return 0
    fi
    # [[...]] - расширеный условный оператор 
    # != - строковое сравнение

    if lspci | grep -qi 'NVIDIA'; then
        return 0
        # lspci - выводит список утройств на шине pcl
        # grep -q - возвращает код 0 -> нашлось, 1 -> нет
        # grep -i - регистронезависимо

    else
        echo "[err] NVIDIA gpu not found" >&2

        return 1
    fi
}