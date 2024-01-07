START    START   1000    test test test
         LDA     error_label    yo yo yo
         DIV     TWO
         MUL     TWO
         COMP    NUM1
         JEQ     EVEN
         JLT     ODD

ODD      LDa     SUM
         ADD     NUM1
         STA     SUM
         LDA     NUM1
         ADD     THREE
         STA     NUM1          suiyfdghousidygf
         COM    NUM2
         JEQ     ODD
         JLT     ODD
         JGT     END

EVEN     LDA     SUM
         ADD     NUM1
         STA     SUM
         LDA     NUM1
         ADD     TWO
         STA     NUM1
         COMP    NUM2
         JEQ     EVEN
         JLT     EVEN
         JGT     END

END      END     START




NUM1     WORD    15
NUM2     WORD    37
TWO      WORD    2
THREE    WORD    3
SUM      WORD    0
AA       BYTE    C'EOF'
BB       BYTE    X'313233'