option casemap:none

.code

PUBLIC get_current_peb

get_current_peb PROC
    mov     rax, qword ptr gs:[60h]
    ret
get_current_peb ENDP


END
