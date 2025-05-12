	;ZONA DE DATOS****************
	LIST P=16F84A          
    INCLUDE <P16F84A.INC>  

    __CONFIG  _CP_OFF & _WDT_OFF & _PWRTE_ON & _XT_OSC  

    ORG 0                    

	;ZONA DE CODIGO************
Inicio:
    bsf STATUS, RP0          
    clrf TRISA               
    clrf TRISB               
    bcf STATUS, RP0          

    clrf PORTA               
    clrf PORTB               

    bsf PORTA, 1             

Principal:
    goto Principal           

    END