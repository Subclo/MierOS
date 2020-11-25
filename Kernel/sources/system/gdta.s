extern gdtr

global _ZN6mieros6kernel6system8load_gdtEv
_ZN6mieros6kernel6system8load_gdtEv:
    lgdt [gdtr]
    
    jmp 0x08:far_jump

far_jump:
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    pop eax
    ret
