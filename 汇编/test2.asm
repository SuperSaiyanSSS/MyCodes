DATA SEGMENT
    
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
    
    MAIN PROC FAR
        PUSH AX
        PUSH CX
        PUSH BX
        SUB CX, CX
        SUB AX, AX
        MOV BL, 1    ;this point can be changed to diff nums
        MOV CL, BL
        AND CL, 9
        SUB CL, 9
        JZ SUCCESS
        
        MOV CX, 2
        
mov ax,4c00h
int 21h

        RET
        
        SUCCESS:
        MOV CX, 3

mov ax,4c00h
int 21h

        RET
     
    MAIN ENDP
    CODE ENDS
END MAIN
        
    