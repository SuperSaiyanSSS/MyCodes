DATA SEGMENT
    PARTNO DW 0
    PNAME DB 16 DUP(0)
    COUNT DD 0
    PLENTH EQU $-PARTN0
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA

    MAIN PROC FAR
        PUSH DS
        SUB AX, AX
        PUSH AX
        MOV AX, DATA
        MOV DS, AX    
        
        MOV BX, PLENTH
        
        RET
    MAIN ENDP
CODE ENDS

END MAIN
    
        
        



;DATA SEGMENT
;    SQTAB DB 0,1,4,9,16,25,36,49
;    X DB 5
;    Y DB 1
;
;DATA ENDS
;
;
;
;CODE SEGMENT 
;    ASSUME CS:CODE, DS:DATA   
;    
;SQRTSUB PROC FAR
;    PUSH DS
;    SUB AX, AX
;    PUSH AX
 ;   MOV AX, DATA
 ;   MOV DS, AX
;
;    MOV AL, X
;    MOV AH, 0
 ;   MOV BX, OFFSET SQTAB
 ;   ADD BX, AX
 ;;   MOV AL, [BX]
 ;   MOV Y, AL
 ;   RET
;SQRTSUB ENDP
;CODE ENDS
;END SQRTSUB

    