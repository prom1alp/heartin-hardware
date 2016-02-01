;______________________________________________________________________________________________________
;длительность пакета для заполнения 5 слотов БТ
#define         MaxPacSize            322
;______________________________________________________________________________________________________
;режимы ATMode
#define         ATModeInitReset       0
#define         ATModeWorkReset       1
#define         ATModeSetBR           2
#define         ATModeWork            3

#define         ATModeConfig00        10
#define         ATModeConfig01        11
#define         ATModeConfig02        12
#define         ATModeConfig03        13
#define         ATModeConfig04        14
#define         ATModeConfig05        15
#define         ATModeConfig06        16
#define         ATModeConfig07        17
#define         ATModeConfig08        18
#define         ATModeConfig09        19
#define         ATModeConfig10        20
#define         ATModeConfig11        21
#define         ATModeConfig12        22
#define         ATModeConfig13        23
#define         ATModeConfig14        24
#define         ATModeConfig15        25
#define         ATModeConfig16        26
#define         ATModeConfig17        27
#define         ATModeConfig18        28
#define         ATModeConfig19        29
#define         ATModeConfig20        30
#define         ATModeConfig21        31
#define         ATModeConfig22        32
#define         ATModeConfig23        33
#define         ATModeConfig24        34
;________________________________________________________________________________________________________________
#define         _CR_                  0x0D
#define         _LF_                  0x0A
#define         _BTD_                 0x00
;______________________________________________________________________________________________________
;Reset
_BT_RESET_ON_   MACRO
                bic.b                 #0x40,&P1OUT
                ENDM
_BT_RESET_OFF_  MACRO
                bis.b                 #0x40,&P1OUT
                ENDM
;______________________________________________________________________________________________________
_BT_RST_PAUSE_  MACRO                 ;должна быть 5 мс - расчет с учетом обработки данных АЦП без событий
                LOCAL                 MakePause
                LOCAL                 MakePauseInt
                mov.w                 #20,REG1                                ;0.5 мс для опроса АЦП
MakePause       mov.w                 #500,REG2
MakePauseInt    NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                NOP
                dec.w                 REG2
                jnz                   MakePauseInt
                dec.w                 REG1
                jnz                   MakePause
                ENDM
;______________________________________________________________________________________________________
_BT_RESET_      MACRO
                _BT_RESET_ON_ 
                _BT_RST_PAUSE_
                _BT_RESET_OFF_
                ENDM
;______________________________________________________________________________________________________
;WakeUp
_BT_WAKEUP_ON_  MACRO
                bis.b                 #0x80,&P1OUT
                ENDM
_BT_WAKEUP_OFF_ MACRO
                bic.b                 #0x80,&P1OUT
                ENDM
;______________________________________________________________________________________________________
;тест DSM                  
_TEST_DSM_      MACRO
                bit.b                 #0x01,&P2IN
                ENDM
_TEST_RTS_      MACRO
                bit.b                 #0x10,&P1IN
                ENDM
                  
