/*
Camacho Julia
Garcia Brayan
Luna Daniel
Carreon Oscar
Ramirez Wendy 
*/
// Tabla de segmentos ajustada para Cátodo Común
const char tabla_hex[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                          0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

char contador = 0;      // Variable para el conteo
char direccion = 1;     // 1 = Ascendente, 0 = Descendente

// Función para activar los pines del display uno por uno
void mostrar_display(char valor) {
    char segmentos = tabla_hex[valor];
    PORTB = 0x00;  // Limpia los pines antes de activar
    Delay_ms(10);   // Pequeña pausa para estabilidad

    // Activa cada pin del display uno por uno según el mapeo correcto
    PORTB.F0 = (segmentos & (1 << 0)) >> 0;  // a ? RB0
    PORTB.F1 = (segmentos & (1 << 1)) >> 1;  // b ? RB1
    PORTB.F2 = (segmentos & (1 << 2)) >> 2;  // c ? RB2
    PORTB.F3 = (segmentos & (1 << 3)) >> 3;  // d ? RB3
    PORTB.F4 = (segmentos & (1 << 4)) >> 4;  // e ? RB4
    PORTB.F5 = (segmentos & (1 << 5)) >> 5;  // f ? RB5
    PORTB.F6 = (segmentos & (1 << 6)) >> 6;  // g ? RB6
    PORTB.F7 = (segmentos & (1 << 7)) >> 7;  // punto (dp) ? RB7
}

// Función para detectar botones con anti-rebote
char boton_presionado(char pin) {
    if (PORTD & (1 << pin)) {  // Verifica si el botón está presionado
        Delay_ms(20);  // Espera para evitar rebotes
        if (PORTD & (1 << pin)) {  // Confirma si sigue presionado
            while (PORTD & (1 << pin));  // Espera hasta que se suelte
            return 1;  // Retorna verdadero si se presionó
        }
    }
    return 0;  // Retorna falso si no se presionó
}

// Función para manejar la cuenta automática
void contar_automatico() {
    mostrar_display(contador);  // Muestra el valor actual primero
    Delay_ms(500);  // Pausa para ver el cambio

    if (direccion == 1) {  // Ascendente
        if (contador < 15) {
            contador++;
        } else {
            PORTC |= (1 << 4);  // Activa el relevador en F
        }
    } else {  // Descendente
        if (contador > 0) {
            contador--;
        } else {
            PORTC &= ~(1 << 4);  // Desactiva el relevador en 0
        }
    }
}

void main() {
    // Configuración de puertos
    TRISB = 0x00;  // PORTB como salida para el display
    TRISD = 0x0C;  // RD2 y RD3 como entradas para los botones
    TRISC = 0x00;  // PORTC como salida (para el relevador)
    PORTB = 0x00;  // Limpia el display
    PORTC = 0x00;  // Limpia el puerto C
    PORTD = 0x00;  // Limpia el puerto D

    mostrar_display(contador);  // Muestra el valor inicial (0)

    while (1) {
        contar_automatico();  // Llama a la función de conteo automático

        if (boton_presionado(2)) {  // Botón UP (RD2)
            direccion = 1;  // Cambia a ascendente
        }

        if (boton_presionado(3)) {  // Botón DOWN (RD3)
            if (contador == 15) {   // Solo cambia si está en F
                direccion = 0;  // Cambia a descendente
            }
        }
    }
}
