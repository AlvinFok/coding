COPY     START   2000
FIRST    ADD     AA             (A)CC = AA + BB + 1
         ADD     BB
         ADD     ONE
         STA     CC             CC < ans
         SUB     DD             (A)EE = CC - DD - 2
         SUB     TWO
         STA     EE             EE < ans
         MUL     AA             (A)FF = EE * AA * 3
         MUL     THREE
         STA     FF             FF < ans
         LDA     EE             (A)GG = EE / AA / 4
         DIV     AA
         DIV     FOUR
         STA     GG             GG < ans
         MUL     THREE          (A)HH = GG * 3
         STA     HH             HH < ans
         LDA     ZERO
         STA     II
         LDA     ZERO
         COMP    HH
         JGT     DO
         END     FIRST



AA       WORD    2
BB       WORD    7
DD       WORD    3
CC       RESW    1
EE       RESW    1
FF       RESW    1
GG       RESW    1
HH       RESW    1
II       RESW    1
ZERO     WORD    0
ONE      WORD    1
TWO      WORD    2
THREE    WORD    3
FOUR     WORD    4
SIX      WORD    6

DO       LDA     GG
         DIV     SIX
         STA     II
