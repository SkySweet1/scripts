#!/bin/bash

check_network() {
    local ip_line current_ip
    # локальные переменные

    ip_line=$(ip -o -4 addr show scope global | head -n 1)
    # ip -o -> one-line -> каждый адресс в одну строку
    # -4 -> только IPv4
    # addr show scope global -> показывает только глобальные адреса
    # head -n -1 -> строго первая строка

    current_ip=$(echo "$ip_line" | cut -d' ' -f4 | cut -d'/' -f1)
    # cut -d' ' -f4 -> четвертый елемент строки
    # cut -d'/' -f1 -> отсекает маску

    if [[ $current_ip =~ $ALLOWED_IP_REGEX ]]; then
        return 0

    else
        echo "[ОШИБКА] IP $current_ip вне разрешённого пула" >&2

        return 1

    fi
}