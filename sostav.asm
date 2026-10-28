section .bss
    in_buf  resb 1024    ; сюда читаем файл (до 1024 символов)
    out_buf resb 2048    ; сюда пишем результат

section .text
    global _start

_start:                  ; 1. Читаем файл (до 1024 байт) из стандартного ввода (stdin)
    mov rax, 0           ; syscall read
    mov rdi, 0           ; fd = stdin (откуда читаем)
    mov rsi, in_buf      ; куда читаем
    mov rdx, 1024        ; сколько байт максимум
    syscall

    mov r14, rax         ; r14 = сколько байт реально прочитали
    mov rsi, in_buf      ; rsi = указатель на текущий символ (читаем)
    mov rbx, out_buf     ; rbx = указатель на результат (пишем)
    mov r12, 0           ; r12 = текущее собираемое число

.parse_loop:             ; цикл по символам
    cmp r14, 0           ; если байты кончились
    je .end_parse

    movzx rax, byte [rsi] ; берем символ

    cmp al, '0'          ; это цифра?
    jb .check_number
    cmp al, '9'
    ja .check_number

    sub al, '0'          ; Если дошли сюда, значит это цифра -> '5' -> 5
    imul r12, 10         ; старый результат * 10
    movzx rax, al
    add r12, rax         ; добавляем новую цифру

    inc rsi              ; следующий символ
    dec r14
    jmp .parse_loop

.check_number:           ; проверка на пробел или конец сроки
    cmp r12, 0           ; если число 0, пропускаем
    je .reset_num

    call is_prime.       ; Проверка на простоту
    cmp rax, 1
    jne .reset_num       ; если не простое, пропускаем

    call save_to_out.    ; Если простое, печатаем в out_buf

.reset_num:
    mov r12, 0           ; обнуляем число для следующего
    inc rsi
    dec r14
    jmp .parse_loop

.end_parse:              ; проверка последнего числа (если файл не кончается пробелом)
    cmp r12, 0
    je .print
    call is_prime
    cmp rax, 1
    jne .print
    call save_to_out

.print:                  ; вывод результата
    mov rdx, rbx         ; вычисляем длину результата
    sub rdx, out_buf
    cmp rdx, 0
    je .exit             ; если пусто — выходим

    mov rax, 1           ; syscall write
    mov rdi, 1           ; stdout
    mov rsi, out_buf
    syscall

.exit:
    mov rax, 60          ; syscall exit
    mov rdi, 0
    syscall

is_prime:                ; проверка на простое число
    cmp r12, 2
    jb .no               ; числа меньше 2 не простые
    mov r15, 2           ; делитель

.prime_loop:
    mov rax, r15
    imul rax, r15        ; rax = делитель^2
    cmp rax, r12
    ja .yes              ; если делитель^2 > числа, оно простое

    mov rax, r12
    mov rdx, 0
    div r15              ; делим число на делитель
    cmp rdx, 0
    je .no               ; если остаток 0 — составное
    inc r15
    jmp .prime_loop
.yes:
    mov rax, 1
    ret
.no:
    mov rax, 0
    ret

save_to_out:             ; сохранение числа в out_bufffer
    mov rax, r12
    mov rcx, 0           ; счетчик цифр
    
.div_loop:
    mov rdx, 0
    mov r15, 10
    div r15              ; rax = rax / 10, rdx = остаток
    push rdx             ; остаток кидаем в стек
    inc rcx
    cmp rax, 0
    jne .div_loop

.pop_loop:
    pop rdx
    add dl, '0'          ; превращаем цифру в символ
    mov [rbx], dl
    inc rbx              ; двигаем указатель
    dec rcx
    jnz .pop_loop

    mov byte [rbx], ' '  ; добавляем пробел после числа
    inc rbx
    ret