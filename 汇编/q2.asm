DATA SEGMENT 
    S1 DB  6,'SHITE1'
    S2 DB  6,'SHITE1'    
    
    MATCH DB 'M', 'A', 'C', 'T', 'H', '$'      ;注意最后以美元结束
    NOMATCH DB 'N', 'O', 'M', 'A', 'T', 'C', 'H', '$'
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
    
    MAIN PROC FAR
        PUSH DS
        PUSH AX
        SUB AX, AX    
        SUB BX, BX
        
        MOV AX, DATA
        MOV DS, AX
        MOV ES, AX
        
        MOV AL, [S1]
        
        CMP AL, [S2]
        JZ END1         ;如果相等则继续       
        
        MOV BX, 4        ;如果个数不相等就GG 
        MOV DX ,OFFSET NOMATCH
        MOV AH, 9
        INT 21H
        
        
        RET
        
        END1:

            MOV  SI, OFFSET S1   

            MOV  DI, OFFSET S2       
            
            MOV  CX, 6
            
            CLD 
            
            
            REPZ CMPSB;
            
            JZ XIANGDENG
            
            MOV  BX, 4    
            
            MOV DX ,OFFSET NOMATCH
            MOV AH, 9
            INT 21H
            
            RET      
            
            XIANGDENG:
                MOV BX, 3
                        
                MOV DX ,OFFSET MATCH 
                MOV AH, 9
                INT 21H
                
                
                RET
            
            
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

    