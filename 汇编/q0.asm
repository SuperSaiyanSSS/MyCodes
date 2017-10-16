DATA SEGMENT 
    SQTAB DB 0,1,4,9,16,25,36,49
    X DB 5
    Y DB 0
DATA ENDS    

;STACK SEGMENT PARA STACK STACK
;    TAPN DB 100 DUP(0)
;    TOP EQU LENGTH TAPN
;STACK ENDS

CODE SEGMENT 
    ASSUME CS:CODE, DS:DATA
MAIN PROC FAR
    PUSH DS

    PUSH AX         ;this sentence must not be deleted!       
    SUB AX, AX
    MOV AX, DATA
    MOV DS, AX
    
  ;  MOV AX, STACK
  ;  MOV SS, AX
    
    MOV AL, X
    MOV AH, 0
    MOV BX, OFFSET SQTAB
    ADD BX, AX
    
    MOV AL, [BX]
    MOV Y, AL
    
    RET
    
MAIN ENDP
CODE ENDS
END MAIN