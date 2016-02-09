;________________________________________________________________________________________________________________
;работа с WDT
_SETUP_WDT_     MACRO
                mov.w                 #WDTPW+WDTSSEL_1+WDTCNTCL+WDTIS__32K,&WDTCTL ;Pasword, ACLK, Reset to 0, /32k (1s)
                ENDM
;______________________________________________________________________________________________________
;события
#define         ADC_Data_Event        0x0001                          //готовность данных АЦП
#define         TMR_10Hz_Event        0x0002                          //событие 10Hz
#define         BT_LS_Event           0x0004                          //изменение состояния BT_LS
#define         BT_WU_Event           0x0008                          //изменение состояния WU_LS
#define         BT_RX_Event           0x0010                          //событие приема данных BT
#define         USB_RX_Event          0x0020                          //событие приема данных USB
#define         Bat_ADC_Event         0x0040                          //готовность ADC
;______________________________________________________________________________________________________
;тестирование события и вызов процедуры в случае события
_TEST_EVENT_    MACRO                 Event, EventRutine
                LOCAL                 NoEvent
                bit.w                 #Event,&DeviceEvent
                jz                    NoEvent
                call                  #EventRutine
NoEvent         ENDM
;______________________________________________________________________________________________________
;установка события
_SET_EVENT_     MACRO                 Event
                bis.w                 #Event,&DeviceEvent
                ENDM
;______________________________________________________________________________________________________
;установка события
_CLEAR_EVENT_   MACRO                 Event
                bic.w                 #Event,&DeviceEvent
                ENDM
;______________________________________________________________________________________________________
;режимы работы холтера HolterMode
#define         XTGeneratorOn         0x0001
#define         BTConnect             0x0002	
#define         AnalogON              0x0004
#define         USBConnect            0x0008
#define         BTOn                  0x0010
;_______________________________________________________________________________
;тест режима
_TEST_MODE_     MACRO                 Mode
                bit.w                 #Mode,&DeviceMode
                ENDM
;______________________________________________________________________________________________________
;установка режима
_SET_MODE_      MACRO                 Mode
                bis.w                 #Mode,&DeviceMode
                ENDM
;______________________________________________________________________________________________________
;установка режима
_RESET_MODE_    MACRO                 Mode
                bic.w                 #Mode,&DeviceMode
                ENDM
;______________________________________________________________________________________________________
_PAUSE_         MACRO
                LOCAL                 Pause
                mov.w                 #0x000F,REG1
Pause           dec.w                 REG1
                jnz                   Pause
                ENDM
;______________________________________________________________________________________________________
;вызов функции с 1 параметром
_CALL_1DATA_    MACRO                 Function,Data
                mov.w                 Data,REG1
                call                  #Function
                ENDM
;______________________________________________________________________________________________________
;вызов функции с 2 параметрами
_CALL_2DATA_    MACRO                 Function,Data1,Data2
                mov.w                 Data1,REG1
                mov.w                 Data2,REG2
                call                  #Function
                ENDM
;______________________________________________________________________________________________________
;вызов функции с 3 параметрами
_CALL_3DATA_    MACRO                 Function,Data1,Data2,Data3
                mov.w                 Data1,REG1
                mov.w                 Data2,REG2
                mov.w                 Data3,REG3
                call                  #Function
                ENDM
