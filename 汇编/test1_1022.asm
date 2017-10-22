decihex segment
    assume cs:decihex
    main proc far
        repeat:
            call decibin
            call crlf
            call binihex
            call crlf
            jmp repeat
    main endp

    decibin proc near
        mov bx, 0
    newchar:
        mov ah, 1
        int 21h
        
        sub al, '0'
        jl exit
        cmp al, 9
        jg exit
        cbw
        
        xchg ax, bx
        mov cx, 10
        mul cx
        add bx, ax
        jmp newchar
        
    exit: ret
    decibin endp
    
    binihex proc near
        mov ch, 4
    rotate:
        mov cl, 4
        rol bx, cl
        
        mov al, bl
        and al, 0fh
        add al, '0'
        cmp al, '9'
        jl printit
        add al, 7
        
    printit:
        mov dl, al
        mov ah, 2
        int 21h
        dec ch
        jnz rotate
        ret
        
    binihex endp
                 
    crlf proc near
        mov dl, 0dh
        mov ah, 2
        int 21h
        mov dl, 0ah
        mov ah, 2
        int 21h
        ret
    crlf endp
    
    decihex ends
end main
        
        
    
        
        