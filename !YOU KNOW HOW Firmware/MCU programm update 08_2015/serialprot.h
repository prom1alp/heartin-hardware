#define         RXBufSize             256
;________________________________________________________________________________________________________________
;максимальный размер команды (задаем максимальный размер обрабатываемой комманды)
#define         MaxCommandSize        100
;________________________________________________________________________________________________________________
#define         BTMACSize             12
;________________________________________________________________________________________________________________
;байты протокола
#define         BOF                   0x70
#define         EOF                   0x71
#define         TOGLE                 0x72
#define         TOGLEBYTE             0x80
;________________________________________________________________________________________________________________
#define         DEVTYPE               0x0000
#define         DEVVERSION            0x0000
;________________________________________________________________________________________________________________
;признаки пакетов
#define         SENDDEVREADY          0x40
#define         SENDDEVTYPE           0x41
#define         SENDBTMAC             0x42
#define         SENDDEVDATA           0x43
#define         GETBATTERY            0x44
#define         DevDataSize           64
#define         SETDEVDATA            0x53
#define         SETMODE0              0x20
#define         SETMODE1              0x21
#define         SETMODE2              0x22
#define         SETMODE3              0x23
#define         SENDERRORMODE         0x60
#define         SENDERRORPACKET       0x61
;________________________________________________________________________________________________________________
;положить байт в буфер передачи с прореживанием
_DATA_TO_TXBUF_ MACRO                 Data
                LOCAL                 IsTogle
                LOCAL                 NoTogle
                cmp.b                 #BOF,Data
                jeq                   IsTogle
                cmp.b                 #EOF,Data
                jeq                   IsTogle
                cmp.b                 #TOGLE,Data
                jne                   NoTogle
IsTogle         _BYTE_TO_TXBUF_       #TOGLE
                xor.b                 #TOGLEBYTE,Data
NoTogle         _BYTE_TO_TXBUF_       Data
                ENDM
;________________________________________________________________________________________________________________
;положить байт в буфер передачи
_BYTE_TO_TXBUF_ MACRO                 Data
                LOCAL                 no_buf_board
                LOCAL                 NoBufOversize
                dint
                mov.b                 Data,0(REG5)
                inc.w                 REG5
                cmp.w                 #TXBuffer+TXBufSize,REG5
                jlo                   no_buf_board
                mov.w                 #TXBuffer,REG5
no_buf_board    cmp.w                 REG5,&TXBufOutPnt
                jne                   NoBufOversize
                inc.w                 &TXBufOutPnt
                cmp.w                 #TXBuffer+TXBufSize,&TXBufOutPnt
                jlo                   NoBufOversize
                mov.w                 #TXBuffer,&TXBufOutPnt
NoBufOversize   eint             
                ENDM
;________________________________________________________________________________________________________________
_INIT_CRC_      MACRO
                mov.w                 #0FFFFh,&CRCINIRES
                ENDM
;________________________________________________________________________________________________________________
_ADD_CRC_       MACRO                 Data
                mov.b                 Data,&CRCDIRB_L
                ENDM                  
;________________________________________________________________________________________________________________
_MOV_CRC_       MACRO                 Data
                mov.w                 &CRCINIRES,Data
                ENDM
;________________________________________________________________________________________________________________


