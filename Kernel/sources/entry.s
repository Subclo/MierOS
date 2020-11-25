MAGIC equ 0x1BADB002
FLAGS equ 0x00000003
section .multiboot.data
    dd MAGIC
    dd FLAGS
    dd -(MAGIC+FLAGS)

magic: dd 0
multiboot_struct: dd 0

align 4096
page_table_0: times 1024 dd 0
page_table_768: times 1024 dd 0

page_directory: 
    dd (page_table_0 + 0x03)
    times 767 dd 0
    dd (page_table_768 + 0x03)
    times 255 dd 0

section .multiboot.text
extern kmain
extern _multiboot_end

global boot
boot:
    mov [magic], eax
    mov [multiboot_struct], ebx
    mov edx, _multiboot_end
    shr edx, 12
    add edx, 1

    xor ecx, ecx
.loop1:
    mov eax, ecx
    shl eax, 12
    or eax, 0x03
    mov [page_table_0+ecx*4], eax
    inc ecx
    cmp ecx, edx
    jl .loop1

    mov ecx, _multiboot_end
    shr ecx, 12
    add ecx, 1
.loop2:
    mov eax, ecx
    shl eax, 12
    or eax, 0x03

    mov [page_table_768+ecx*4], eax
    inc ecx
    cmp ecx, 1024
    jl .loop2

    mov eax, page_directory
    mov cr3, eax

    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax

    jmp high_start

section .text
high_start:
    mov ebp, 0
    mov esp, kernel_stack_bottom

    push dword [multiboot_struct]
    push dword [magic]
    call kmain

stop:
    hlt
    jmp stop    

section .bss
    resb 1024*512 ; 0.5 MiB
kernel_stack_bottom: