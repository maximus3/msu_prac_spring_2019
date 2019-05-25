%include "src/io.inc"

section .rodata
    fin db "%lf", 0
    fout db "%lf", 10, 0
    
section .data
    const_0q5 dq 0.5
    const_3q dq 3.0
    const_5q dq 5.0
    const_2q5 dq 2.5
    const_9q5 dq 9.5

section .text
global _f1
global _f2
global _f3

_f1: ; double x
    push ebp
    mov ebp, esp
    
    finit
    fld qword[const_0q5] ; ST0: 0.5
    fld qword[ebp + 8]
    fld1
    faddp ; ST1: 0.5, ST0: x + 1
    fdivp ; ST0: 0.5/(x + 1)
    fld1
    faddp ; ST0: 0.5/(x + 1) + 1
    fld qword[const_3q]
    fmulp ; (0.5/(x + 1) + 1) * 3
    
    leave
    ret
    
_f2: ; double x
    push ebp
    mov ebp, esp
    
    finit
    fld qword[const_2q5]
    fld qword[ebp + 8]
    fmulp ; ST0: 2.5*x
    fld qword[const_9q5]
    fsubp
    
    leave
    ret
    
_f3: ; double x
    push ebp
    mov ebp, esp
    
    finit
    fld qword[const_5q]
    fld qword[ebp + 8]
    fdivp
    
    leave
    ret