.386
DATA   SEGMENT  USE16
BNAME  DB   'LIANGYIFEI'      ;�ϰ�����
BPASS  DB   '991026'           ;����
SNAME  DB   'FEISHOP',0DH,0AH,'$'               ;�������ƣ���0����
N      EQU   1000
M      EQU   1000
TAG    DB   '$'
POINT  DB   'print username and password:',0DH,0AH,'$'
TIP    DB   'MISMATCH!',0DH,0AH,'$'
TIP2   DB   'NOT FOUND!TRY AGAIN!',0DH,0AH,'$'
POINT2 DB   'Tell me what you want:',0DH,0AH,'$'
TAG2   DB   0DH,0AH,'$'
IN_NAME DB  11
        DB  ?
		DB  11 DUP(0)
IN_PWD  DB  7
        DB  ?
		DB  7 DUP(0)
IN_GA   DB  11
        DB  0
		DB  11 DUP(0)
AUTH    DB  ?
I      DW  0
J      DB  0
K      DW  0
GA1    DB  'PEN',7 DUP(0) ,10  	;��Ʒ���Ƽ��ۿ�
       DW   35,56,70,25,?   ;�Ƽ��Ȼ�δ����
GA2    DB  'BOOK', 6 DUP(0) ,9  	;��Ʒ���Ƽ��ۿ�
       DW   12,30,25,5,?       ;�Ƽ��Ȼ�δ����
GAN    DB    N-3 DUP('Temp-Value',8,15,0,20,0,30,0,2,0,?,?)
GA3    DB   'BAG',7 DUP(0), 8
       DW    15,20,20000,2,?
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
FUN1: LEA DX,POINT
	  MOV AH,9
	  INT 21H
      LEA DX,IN_NAME
	  MOV AH,10
	  INT 21H
	  LEA DX,TAG2
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
	  LEA DX,TAG2
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
FUN3_1:LEA DX,POINT2
	  MOV AH,9
	  INT 21H 
	  MOV AX,0
	  LEA DX,IN_GA
	  MOV AH,10
	  INT 21H
	  LEA DX,TAG2
	  MOV AH,9
	  INT 21H
	  MOV AX,0
	  CALL TIMER;��ʼ��ʱ
      MOV CL,IN_GA[1]
	  CMP CL,0
	  JE  FUN1
	  MOVZX AX,CL
	  MOV DI,OFFSET IN_GA
	  ADD DI,AX
	  ADD DI,2
	  MOV AL,0
	  MOV [DI],AL
	  CMP AUTH,1
	  JE FUN3_3
	  MOV K,M
FUN3_4:ADD K,-1
	  JS TIME
	  JMP FUN5
FUN3_3:MOV SI,OFFSET GA1
	  SUB SI,21
	  MOV DI,OFFSET IN_GA
	  MOV I,N
	  JMP LOPA3
FUN3_2:CMP AUTH,1
       JNE FUN4
	   MOV CL,IN_GA[1]
	   MOV BX,0
PRINT: ADD CL,-1
       JS PRIN
       MOV AH,02H
       MOV DL,[SI][BX]
	   INT 21H
	   ADD BX,1
	   JMP PRINT
PRIN:  LEA DX,TAG2
	  MOV AH,9
	  INT 21H
	  JMP CLEAR
LOPA3:ADD I,-1
      JS  T3
	  ADD SI,21
	  MOV CL,9
LOPA4:MOV BL,CL
      MOV AL,2[DI+BX]
	  CMP AL,0[SI][BX]
	  JNE LOPA3
	  ADD CL,-1
	  JS FUN3_2
	  JMP LOPA4
FUN4:MOV AX,WORD PTR[SI+19]
	CMP AX,100
    JA  ALEVEL
    CMP AX,50
    JA  BLEVEL
    CMP AX,10
    JA  CLEVEL
    JMP FLEVEL
FUN4_1:MOV AX,0
       MOV AX,WORD PTR [SI+15]
       SUB AX,WORD PTR[SI+17]
	   JS  TIME
	   ADD WORD PTR [SI+17],1
	   MOV AX,0
       JMP FUN3_4
TIME: MOV AX,1
      CALL TIMER
	  JMP FUN3_1
FUN5:MOV SI,OFFSET GA1;����ȫ����Ʒ���Ƽ���
     ADD SI,-21
     MOV I,N
LOPA5:ADD I,-1
    JS  FUN3_3
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
ALEVEL:   LEA DX,'A'
     MOV AH,2
	 INT 21H
	  LEA DX,' '
	  MOV AH,2
	  INT 21H
	 JMP FUN4_1
BLEVEL:   LEA DX,'B'
     MOV AH,2
	 INT 21H
	  LEA DX,' '
	  MOV AH,2
	  INT 21H
	 JMP FUN4_1
CLEVEL:  LEA DX,'C'
     MOV AH,2
	 INT 21H
	  LEA DX,' '
	  MOV AH,2
	  INT 21H
	 JMP FUN4_1
FLEVEL:   LEA DX,'F'
     MOV AH,2
	 INT 21H
	  LEA DX,' '
	  MOV AH,2
	  INT 21H
	 JMP FUN4_1
T1:  MOV AUTH,0
      JMP FUN3_1
T2:   LEA DX,TIP
	  MOV AH,9
	  INT 21H
	  JMP FUN1
T3:   LEA DX,TIP2
      MOV AH,9
	  INT 21H
	  MOV AX,0
      MOV BX,0
	  MOV CX,0
	  MOV DX,0
	  MOV SI,0
	  MOV DI,0
	  MOV BX,11
	  MOV SI ,OFFSET IN_GA
CLEAR2:MOV BYTE PTR[SI+BX],0
      ADD BX,-1
	  CMP BX,0
	  JNE CLEAR2
	  MOV SI,0
	  JMP FUN3_1
CLEAR:MOV AX,0
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
	   JMP FUN1
QUIT: MOV AH,4CH
      INT 21H
;ʱ�������(ms),����Ļ����ʾ�����ִ��ʱ��(ms)
;ʹ�÷���:
;	   MOV  AX, 0	;��ʾ��ʼ��ʱ
;	   CALL TIMER
;	   ... ...	;��Ҫ��ʱ�ĳ���
;	   MOV  AX, 1	
;	   CALL TIMER	;��ֹ��ʱ����ʾ��ʱ���(ms)
;���: �ı���AX��״̬�Ĵ���
TIMER	PROC
	PUSH  DX
	PUSH  CX
	PUSH  BX
	MOV   BX, AX
	MOV   AH, 2CH
	INT   21H	     ;CH=hour(0-23),CL=minute(0-59),DH=second(0-59),DL=centisecond(0-100)
	MOV   AL, DH
	MOV   AH, 0
	IMUL  AX,AX,1000
	MOV   DH, 0
	IMUL  DX,DX,10
	ADD   AX, DX
	CMP   BX, 0
	JNZ   _T1
	MOV   CS:_TS, AX
_T0:	POP   BX
	POP   CX
	POP   DX
	RET
_T1:	SUB   AX, CS:_TS
	JNC   _T2
	ADD   AX, 60000
_T2:	MOV   CX, 0
	MOV   BX, 10
_T3:	MOV   DX, 0
	DIV   BX
	PUSH  DX
	INC   CX
	CMP   AX, 0
	JNZ   _T3
	MOV   BX, 0
_T4:	POP   AX
	ADD   AL, '0'
	MOV   CS:_TMSG[BX], AL
	INC   BX
	LOOP  _T4
	PUSH  DS
	MOV   CS:_TMSG[BX+0], 0AH
	MOV   CS:_TMSG[BX+1], 0DH
	MOV   CS:_TMSG[BX+2], '$'
	LEA   DX, _TS+2
	PUSH  CS
	POP   DS
	MOV   AH, 9
	INT   21H
	POP   DS
	JMP   _T0
_TS	DW    ?
 	DB    'Time elapsed in ms is '
_TMSG	DB    12 DUP(0)
TIMER   ENDP
CODE ENDS
     END START