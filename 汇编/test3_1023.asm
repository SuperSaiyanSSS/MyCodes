code segment
    assume cs:code
    main proc far
        repeat:
            call receive
            call crlf
            call screen
            call crlf
        jmp repeat
    main endp
    
    receive proc near
       mov bx, 0
       newchar:
           mov ax, 0
           mov ah, 1
           int 21h
           sub al, '0'
           jl exit
           cmp al, 9
           jng chuli
           sub al, 7
           chuli:   
               cmp al, 16
               jg exit
               cbw
               xchg ax, bx
               mov cx, 16
               mul cx
               add bx, ax
               jmp newchar
               
       exit:
           ret
    receive endp
    
    screen proc near
        mov ch, 16
        rotate:
            mov cl, 1
            rol bx, cl
            mov al, bl
            and al, 1
            add al, '0'
            mov dl, al
            mov ah, 2
            int 21h
            dec ch
            jnz rotate
            ret
    screen endp
    
    crlf  proc near
        mov dl,0dh
        mov ah,2
        int    21h
        mov dl,0ah
        mov ah,2
        int    21h
        ret
    crlf  endp
    
    code ends
end main
        