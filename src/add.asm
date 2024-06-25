global add
section .text
add:
    ; Function to add two integers
    ; int add(int a, int b)
    mov eax, ecx    ; Move the first argument to eax
    add eax, edx    ; Add the second argument to eax
    ret             ; Return the result in eax

