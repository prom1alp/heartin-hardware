;________________________________________________________________________________________________________________
;������ � WDT
_SETUP_WDT_     MACRO
                mov.w                 #WDTPW+WDTSSEL_1+WDTCNTCL+WDTIS__32K,&WDTCTL ;Pasword, ACLK, Reset to 0, /32k (1s)
                ENDM
;______________________________________________________________________________________________________
;�������
#define         ADC_Data_Event        0x0001                          //���������� ������ ���
#define         TMR_10Hz_Event        0x0002                          //������� 10Hz
#define         BT_LS_Event           0x0004                          //��������� ��������� BT_LS
#define         BT_WU_Event           0x0008                          //��������� ��������� WU_LS
#define         BT_RX_Event           0x0010                          //������� ������ ������ BT
#define         USB_RX_Event          0x0020                          //������� ������ ������ USB
#define         Bat_ADC_Event         0x0040                          //���������� ADC
;______________________________________________________________________________________________________
;������������ ������� � ����� ��������� � ������ �������
_TEST_EVENT_    MACRO                 Event, EventRutine
                LOCAL                 NoEvent
                bit.w                 #Event,&DeviceEvent
                jz                    NoEvent
                call                  #EventRutine
NoEvent         ENDM
;______________________________________________________________________________________________________
;��������� �������
_SET_EVENT_     MACRO                 Event
                bis.w                 #Event,&DeviceEvent
                ENDM
;______________________________________________________________________________________________________
;��������� �������
_CLEAR_EVENT_   MACRO                 Event
                bic.w                 #Event,&DeviceEvent
                ENDM
;______________________________________________________________________________________________________
;������ ������ ������� HolterMode
#define         XTGeneratorOn         0x0001
#define         BTConnect             0x0002	
#define         AnalogON              0x0004
#define         USBConnect            0x0008
#define         BTOn                  0x0010
;_______________________________________________________________________________
;���� ������
_TEST_MODE_     MACRO                 Mode
                bit.w                 #Mode,&DeviceMode
                ENDM
;______________________________________________________________________________________________________
;��������� ������
_SET_MODE_      MACRO                 Mode
                bis.w                 #Mode,&DeviceMode
                ENDM
;______________________________________________________________________________________________________
;��������� ������
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
;����� ������� � 1 ����������
_CALL_1DATA_    MACRO                 Function,Data
                mov.w                 Data,REG1
                call                  #Function
                ENDM
;______________________________________________________________________________________________________
;����� ������� � 2 �����������
_CALL_2DATA_    MACRO                 Function,Data1,Data2
                mov.w                 Data1,REG1
                mov.w                 Data2,REG2
                call                  #Function
                ENDM
;______________________________________________________________________________________________________
;����� ������� � 3 �����������
_CALL_3DATA_    MACRO                 Function,Data1,Data2,Data3
                mov.w                 Data1,REG1
                mov.w                 Data2,REG2
                mov.w                 Data3,REG3
                call                  #Function
                ENDM
