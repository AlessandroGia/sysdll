option casemap:none

.code

PUBLIC syscall0
PUBLIC syscall1
PUBLIC syscall2
PUBLIC syscall3
PUBLIC syscall4
PUBLIC syscall5
PUBLIC syscall6

; syscall0(syscall_id)
syscall0 PROC
    mov     eax, ecx
    syscall
    ret
syscall0 ENDP

; syscall1(arg1, syscall_id)
syscall1 PROC
    mov     r10, rcx
    mov     eax, edx
    syscall
    ret
syscall1 ENDP

; syscall2(arg1, arg2, syscall_id)
syscall2 PROC
    mov     r10, rcx
    mov     eax, r8d
    syscall
    ret
syscall2 ENDP

; syscall3(arg1, arg2, arg3, syscall_id)
syscall3 PROC
    mov     r10, rcx
    mov     eax, r9d
    syscall
    ret
syscall3 ENDP

; syscall4(arg1, arg2, arg3, arg4, syscall_id)
syscall4 PROC
    mov     r10, rcx
    mov     eax, dword ptr [rsp + 28h]
    syscall
    ret
syscall4 ENDP

; syscall5(arg1, arg2, arg3, arg4, arg5, syscall_id)
syscall5 PROC
    mov     r10, rcx
    mov     eax, dword ptr [rsp + 30h]
    syscall
    ret
syscall5 ENDP

; syscall6(arg1, arg2, arg3, arg4, arg5, arg6, syscall_id)
syscall6 PROC
    mov     r10, rcx
    mov     eax, dword ptr [rsp + 38h]
    syscall
    ret
syscall6 ENDP

END
