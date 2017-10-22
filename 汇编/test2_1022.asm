stack segment
    db 256 dup(0)
    tos label word
stack ends

mycodes segment
    main proc far
        assume cs: mycodes, ss:stack
        start:

            mov ax, stack
            mov ss, ax
            mov sp, offset tos   
                    
            mov ax, 3     
            push ax
            mov bx, 3
            call fact
            pop  dx  
            ret
            
        fact   
            proc  near
            push  ax
            push  bp
            mov   bp, sp
            mov   ax, [bp+6]
            cmp   ax, 0
            jne   fact1
            inc   ax
            jmp   exit
        fact1: 
            dec   ax
            push  ax
            call  fact
            pop   ax
            mul   word ptr[bp+6]
        exit:  
            mov   [bp+6], ax
            pop   bp
            pop   ax
            ret   
    fact   endp


    mycodes ends
end main

