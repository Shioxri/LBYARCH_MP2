section .data
float_constant dd 255.0

section .text
bits 64
default rel
global imgCvtGrayFloatToInt

imgCvtGrayFloatToInt:
    push rbx
    push rdi
    push rsi

    mov rax, rcx        
    imul rax, rdx       

    mov rdi, r8         
    mov rsi, r9         
    movss xmm0, [float_constant]   

ARRAY_LOOP:
    test rax, rax    
    jz DONE           

    movss xmm1, [rdi]   
    mulss xmm1, xmm0  
    roundss xmm1, xmm1, 0x00 
    cvttss2si rbx, xmm1  
    mov [rsi], rbx      

    add rdi, 4          
    add rsi, 4        
    dec rax              
    jmp ARRAY_LOOP    

DONE:
    pop rsi
    pop rdi
    pop rbx
    ret
