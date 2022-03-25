EXTERN FUNC3 :FAR
EXTERN FUNC4 :FAR
EXTERN FUNC5 :FAR
PUBLIC F2T10
PUBLIC RDAIX
.386
DATA   SEGMENT  USE16
LEAP   DW   80 DUP(0)
BNAME  DB   'LIANGYIFEI'      ;老板姓名
BPASS  DB   '991026'           ;密码
SNAME  DB   'FEISHOP',0DH,0AH,'$'               ;网店名称，用0结束
BUF    DB  12 DUP(?)
 N      EQU   30
POINT  DB   'print username and password:',0DH,0AH,'$'
TIP    DB   'MISMATCH!',0DH,0AH,'$'
TIP2   DB   'NOT FOUND!TRY AGAIN!',0DH,0AH,'$'
POINT2 DB   'Tell me what you want:',0DH,0AH,'$'
POINT3 DB   'Tell me what you choose:',0DH,0AH,'$'
POINT4 DB   'ERROR!',0DH,0AH,'$'
TAG    DB   0DH,0AH,'$'
SIGN   DB   ?
DAT DW 0AH
TIP3   DB   'Welcome BOSS!According the following tips to choose:',0DH,0AH,'1.Query product information',0DH,0AH,'2.Modify product information',0DH,0AH,'3.Calculate the recommendation',0DH,0AH,'4.Recommendation ranking',0DH,0AH,'5.All product information',0DH,0AH,'6.Exit',0DH,0AH,'$'
TIP4   DB   'Welcome to FEISHOP!According the following tips to choose:',0DH,0AH,'1.Query product information',0DH,0AH,'6.Exit',0DH,0AH,'$'
IN_NAME DB  11
        DB  ?
		DB  11 DUP(0)
IN_PWD  DB  7
        DB  ?
		DB  7 DUP(0)
IN_GA   DB  11
        DB  ?
		DB  11 DUP(0)
AUTH    DB  ?
I      DW  0
GA1    DB  'PEN',7 DUP(0) ,10  	;商品名称及折扣
       DW   35,56,70,25,?   ;推荐度还未计算
GA2    DB  'BOOK', 6 DUP(0) ,9  	;商品名称及折扣
       DW   12,30,25,5,?       ;推荐度还未计算
GAN    DB    N-2 DUP('Temp-Value',8,15,0,20,0,30,0,2,0,?,?)
NUM    DB   10
       DB   ?
	   DB   10 DUP(0)
DATA   ENDS
STACK  SEGMENT  USE16 STACK
       DB  200  DUP(0)
STACK  ENDS
CODE   SEGMENT  USE16
       ASSUME   CS:CODE, DS:DATA, SS:STACK
START:MOV AX,DATA
      MOV DS,AX
	  LEA DX,SNAME
	  MOV AH,9
	  INT 21H
	  MOV SI,OFFSET GA1;计算全部商品的推荐度
      CALL CACUL 
FUN1: LEA DX,POINT
	  MOV AH,9
	  INT 21H
      LEA DX,IN_NAME
	  MOV AH,10
	  INT 21H
	  LEA DX,TAG
	  MOV AH,9
	  INT 21H
	  MOV CL,IN_NAME[1]
	  CMP CL,0
	  JE  T1
	  CMP CL,1
	  JE  ISQ
	  JMP IPW
ISQ:  MOV CL,IN_NAME[2]
	  CMP CL,'q'
	  JE  QUIT
IPW:  LEA DX,IN_PWD
	  MOV AH,10
	  INT 21H
	  LEA DX,TAG
	  MOV AH,9
	  INT 21H
FUN2_1: MOV CL,IN_NAME[1]
      CMP CL,10
	  JNE T2
	  MOV DI,10
	  JMP LOPA1
FUN2_2: MOV CL,IN_PWD[1]
        CMP CL,6
		JNE T2
		MOV DI,6
		JMP LOPA2
LOPA1:MOV CL,BNAME[DI-1]
	  CMP CL,IN_NAME[DI+1]
	  JNE T2
	  DEC DI
	  CMP DI,0
	  JNE LOPA1
	  JMP FUN2_2
LOPA2:MOV CL,BPASS[DI-1]
      CMP CL,IN_PWD[DI+1]
	  JNE T2
	  DEC DI
	  CMP DI,0
	  JNE LOPA2
	  MOV AUTH,1
FUN3_1:CMP AUTH,1
      JZ PRIN
      LEA DX,TIP4
      MOV AH,9
	  INT 21H
	  JMP FUN3_2
	  PRIN:LEA DX,TIP3
      MOV AH,9
	  INT 21H
FUN3_2:LEA DX,POINT3
       MOV AH,9
	   INT 21H
	   MOV AH,1
	   INT 21H
	   LEA DX,TAG
	   MOV AH,9
	   INT 21H
	   CMP AL,'1'
	   JZ F1C
	   CMP AL,'2'
	   JZ  F2C
	   CMP AL,'3'
	   JZ  F3C
	   CMP AL,'4'
	   JZ  F4C
	   CMP AL,'5'
	   JZ  F5C
	   CMP AL,'6'
	   JZ F6C
WRO:   LEA DX,POINT4
	   MOV AH,9
	   INT 21H
	   JMP FUN3_2
F1C:   CALL FUNC1
       CALL CLEAR
       JMP FUN3_1
F2C:   CMP AUTH,0
       JE WRO
      CALL FUNC2
	  CALL CLEAR
	  JMP FUN3_1
F3C: CMP AUTH,0
     JE WRO
	 MOV SI,OFFSET GA1
	 CALL FUNC3
	   LEA DX,TAG
	  MOV AH,9
	  INT 21H
	 JMP FUN3_1
F4C: CMP AUTH,0
     JE WRO
	  MOV SI,OFFSET GA1
	  CALL FUNC4
	 JMP FUN3_1
F5C: CMP AUTH,0
     JE WRO
	  MOV SI,OFFSET GA1
	  CALL FUNC5
	  LEA DX,TAG
	  MOV AH,9
	  INT 21H
	 JMP FUN3_1
F6C: CALL CLEAR
	 JMP FUN1
 FUNC1   PROC  
      PUSH AX
	  PUSH BX
	  PUSH CX
	  PUSH DX
	  PUSH SI
	  PUSH DI
      LEA DX,POINT2
	  MOV AH,9
	  INT 21H
	  LEA DX,IN_GA
	  MOV AH,10
	  INT 21H
	  LEA DX,TAG
	  MOV AH,9
	  INT 21H
	  MOV CL,IN_GA[1]
	  CMP CL,0
	  JE  F1_3
	  MOV DI,OFFSET IN_GA
	  MOV SI,OFFSET GA1
	  CALL FIND
F1_2:  MOV CL,IN_GA[1]
	   MOV BX,0
PRINTNAME: ADD CL,-1
       JS PRINTVALUE
       MOV AH,02H
       MOV DL,[SI][BX]
	   INT 21H
	   ADD BX,1
	   JMP PRINTNAME
PRINTVALUE:  LEA DX,' '
	         MOV AH,2
	         INT 21H
			 MOV AX,0
			 MOV AL,[SI+10]
			 CALL F2T10
			 MOV AX,WORD PTR[SI+11]
			 CALL F2T10
			 MOV AX,WORD PTR[SI+13]
			 CALL F2T10
			 MOV AX,WORD PTR[SI+15]
			 CALL F2T10
			 MOV AX,WORD PTR[SI+17]
			 CALL F2T10
			 MOV AX,WORD PTR[SI+19]
			 CMP AX,100
             JA  ALEVEL
             CMP AX,50
             JA  BLEVEL
             CMP AX,10
             JA  CLEVEL
             JMP FLEVEL
ALEVEL:   LEA DX,'A'
     MOV AH,2
	 INT 21H
	 LEA DX,TAG
	  MOV AH,9
	  INT 21H
      JMP F1_3
BLEVEL:   LEA DX,'B'
     MOV AH,2
	 INT 21H
	 LEA DX,TAG
	  MOV AH,9
	  INT 21H
	  JMP F1_3
CLEVEL:  LEA DX,'C'
     MOV AH,2
	 INT 21H
	 LEA DX,TAG
	  MOV AH,9
	  INT 21H
	 JMP F1_3
FLEVEL:   LEA DX,'F'
     MOV AH,2
	 INT 21H
	 LEA DX,TAG
	  MOV AH,9
	  INT 21H
F1_3: POP DI
      POP SI
	  POP DX
	  POP CX
	  POP BX
	  POP AX
	  RET
FUNC1  ENDP
FUNC2  PROC
      PUSH AX
	  PUSH BX
	  PUSH CX
	  PUSH DX
	  PUSH SI
	  PUSH DI
      LEA DX,POINT2
	  MOV AH,9
	  INT 21H
	  LEA DX,IN_GA
	  MOV AH,10
	  INT 21H
	  LEA DX,TAG
	  MOV AH,9
	  INT 21H
	  MOV CL,IN_GA[1]
	  CMP CL,0
	  JE F2_6
	  MOV DI,OFFSET IN_GA
	  MOV SI,OFFSET GA1
	  CALL FIND
F2_2: MOV AX,0
	  MOV AL,[SI+10]
	  CALL F2T10
	  LEA DX,'>'
	  MOV AH,2
	  INT 21H
	  LEA DX,NUM
	  MOV AH,10
	  INT 21H
	  MOV DI,OFFSET NUM
	  ADD DI,2
	  MOV CL,NUM[1]
	  CALL F10T2
	  CMP DI,-1
	  JE F2_2
	  MOV [SI+10],AL
	  LEA DX,TAG
	  MOV AH,9
	  INT 21H
F2_3: MOV AX,[SI+11]
	  CALL F2T10
	  LEA DX,'>'
	  MOV AH,2
	  INT 21H
	  LEA DX,NUM
	  MOV AH,10
	  INT 21H
	  MOV DI,OFFSET NUM
	  ADD DI,2
	  MOV CL,NUM[1]
	  CALL F10T2
	  CMP DI,-1
	  JE F2_3
	  MOV [SI+11],WORD PTR AX
	  LEA DX,TAG
	  MOV AH,9
	  INT 21H
 F2_4: MOV AX,[SI+13]
	  CALL F2T10
	  LEA DX,'>'
	  MOV AH,2
	  INT 21H
	  LEA DX,NUM
	  MOV AH,10
	  INT 21H
	  MOV DI,OFFSET NUM
	  ADD DI,2
	  MOV CL,NUM[1]
	  CALL F10T2
	  CMP DI,-1
	  JE F2_4
	  MOV [SI+13],WORD PTR AX
	  LEA DX,TAG
	  MOV AH,9
	  INT 21H
 F2_5: MOV AX,[SI+15]
	  CALL F2T10
	  LEA DX,'>'
	  MOV AH,2
	  INT 21H
	  LEA DX,NUM
	  MOV AH,10
	  INT 21H
	  MOV DI,OFFSET NUM
	  ADD DI,2
	  MOV CL,NUM[1]
	  CALL F10T2
	  CMP DI,-1
	  JE F2_5
	  MOV [SI+15],AL
	  LEA DX,TAG
	  MOV AH,9
	  INT 21H
F2_6: POP DI
      POP SI
	  POP DX
	  POP CX
	  POP BX
	  POP AX
	  RET
FUNC2  ENDP
T1:   MOV AUTH,0
      JMP FUN3_1
T2:   LEA DX,TIP
	  MOV AH,9
	  INT 21H
	  JMP FUN1
T3:   LEA DX,TIP2
      MOV AH,9
	  INT 21H
	  JMP FUN3_1
FIND   PROC 
     PUSH AX
	 PUSH BX
	 PUSH CX
	 PUSH DX
	  MOV CL,IN_GA[1]
	  MOVZX AX,CL
	  ADD DI,AX
	  ADD DI,2
	  MOV AL,0
	  MOV [DI],AL
	  SUB SI,21
	  MOV DI,OFFSET IN_GA
	  MOV I,N
LOPA3:ADD I,-1
      JS  T3
	  ADD SI,21
	  MOV CL,9
LOPA4:MOV BL,CL
      MOV AL,2[DI+BX]
	  CMP AL,0[SI][BX]
	  JNE LOPA3
	  ADD CL,-1
	  JS  FEND
	  JMP LOPA4
FEND: POP DX
      POP CX
	  POP BX
	  POP AX
	  RET
FIND  ENDP
CLEAR PROC
      MOV AX,0
      MOV BX,0
	  MOV CX,0
	  MOV DX,0
	  MOV SI,0
	  MOV DI,0 
	  MOV BX,11
	  MOV SI, OFFSET IN_GA
CLEAR1: MOV BYTE PTR[SI+BX],0
	   ADD BX,-1
	   CMP BX,0
	   JNE CLEAR1
       MOV SI,0
	   RET
CLEAR  ENDP
CACUL  PROC
     PUSH AX
     PUSH BX
     PUSH CX
     PUSH DX
     ADD SI,-21
     MOV I,N
LOPA5:ADD I,-1
    JS  CAUEND
    ADD SI,21
    MOV AX,WORD PTR [SI+11]
    MOV BX,0080H
    MUL BX
    MOV BX,WORD PTR [SI+13]
    DIV BX
    MOV BX,000AH
    MUL BX
    MOV BL,[SI+10]
    MOV BH,00H
    DIV BX
    MOV CX,AX
    MOV AX,WORD PTR [SI+17]
    MOV BX,0040H
    MUL BX
    MOV BX,WORD PTR [SI+15]
    DIV BX
    ADD AX,CX
	MOV WORD PTR [SI+19],AX
	MOV AX,0
	MOV BX,0
	MOV CX,0
	JMP LOPA5
CAUEND: POP DX
        POP CX
		POP BX
		POP AX
		RET
CACUL	ENDP
QUIT: MOV AH,4CH
      INT 21H
F10T2 PROC FAR
	PUSH DX
	PUSH BX
	MOV AX,0
	MOV SIGN,0
	MOV BL,[DI]
	CMP BL,'+'
	JZ  A
	CMP BL,'-'
	JNE NEXT2
	MOV SIGN,1
A:
	DEC CX
	JZ ERR
NEXT1:
	INC DI
	MOV BL,[DI]
NEXT2:
	CMP BL,'0'
	JB ERR
	CMP BL,'9'
	JA ERR
	SUB BL,30H
	MOV BH,0
	MUL DAT
	JO ERR
	ADD AX,BX
	JC ERR
	
	DEC CX
	JNZ NEXT1
	CMP SIGN,1
	JNE QQ
	NEG AX

QQ:
	POP BX
	POP DX
	RET
ERR:
	MOV DI,-1
	JMP QQ
F10T2	ENDP
F2T10  PROC FAR
       PUSH EBX
	   PUSH SI
	   LEA SI,BUF
	   CMP DX,32
	   JE  B
	   MOVSX EAX,AX
B:     OR EAX,EAX
       JNS PLUS
	   NEG EAX
	   MOV BYTE PTR [SI],'-'
	   INC SI
PLUS:  MOV EBX,10
       CALL RDAIX
	   MOV BYTE PTR [SI],'$'
	   LEA DX,BUF
	   MOV AH,9
	   INT 21H
	   LEA DX,' '
	   MOV AH,2
	   INT 21H
	   POP SI
	   POP EBX
	   RET
F2T10 ENDP
RDAIX PROC FAR
      PUSH  CX
	  PUSH EDX
	  XOR CX,CX
LOP1:XOR  EDX,EDX
     DIV  EBX
	 PUSH DX
	 INC  CX
	 OR EAX,EAX
	 JNZ LOP1
LOP2:POP  AX
     CMP AL,10
	 JB L1
	 ADD AL,7
L1:  ADD AL,30H
     MOV [SI],AL
	 INC SI
	 LOOP LOP2
	 POP EDX
	 POP CX
	 RET
RDAIX  ENDP
CODE ENDS
     END START
