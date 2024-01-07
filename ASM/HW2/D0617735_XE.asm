START    START   1000
         LDA     NUM1
         DIV     #2
         MUL     #2
         COMP    NUM1
         JEQ     EVEN
         JLT     ODD

ODD      LDA     SUM
         ADD     NUM1
         STA     SUM
         LDA     NUM1
         ADD     #3
         STA     NUM1
         COMP    NUM2
         JEQ     ODD
         JLT     ODD
         JGT     END

EVEN     LDA     SUM
         ADD     NUM1
         STA     SUM
         LDA     NUM1
         ADD     #2
         STA     NUM1
         COMP    NUM2
         JEQ     EVEN
         JLT     EVEN
         JGT     END

END      END     START




NUM1     WORD    15
NUM2     WORD    37
SUM      WORD    0