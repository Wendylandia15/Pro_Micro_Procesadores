   void main() {
    TRISB = 0x00;  // Configura PORTB como salida
    LATB = 0x00;   // Inicializa PORTB en bajo

    while(1) {
        LATB.F0 = 1;  // Enciende el LED (RB0 en alto)
        Delay_ms(1000); // Espera 1 segundo
        LATB.F0 = 0;  // Apaga el LED (RB0 en bajo)
        Delay_ms(1000); // Espera 1 segundo
    }
}