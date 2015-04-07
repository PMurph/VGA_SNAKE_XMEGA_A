COMP 4550 - Project - Phase 1
Patrick Murphy - 6850006
murphypc

Hardware:
    - Amtel XMEGA-A1 Xplained
    - VGA Breakout Board
    - 3 x 220 ohm resistors
    - 4 x 10k ohm resistors
    - 4 x push buttons
    
Setup:
    VGA Setup
        - (Red Pin) PORTA - PIN0 -> 220 ohm resistor -> VGA PIN 1
        - (Blue Pin) PORTA - PIN1 -> 220 ohm resistor -> VGA PIN 2
        - (Green Pin) PORTA - PIN2 -> 220 ohm resistor -> VGA PIN 3
        - (HSYNC Pin) PORTA - PIN6 -> VGA PIN 13
        - (VSYNC Pin) PORTA - PIN7 -> VGA PIN 14
        - VGA Pin 9 -> VCC Pin
        - VGA Pins 5, 6, 7, 8, 10 -> Ground
    
    Button Setup:
        - All 4 buttons are in a pulldown circuit
        - Button 0 -> PORTD - PIN 0
        - Button 1 -> PORTD - PIN 1
        - Button 2 -> PORTD - PIN 2
        - Button 3 -> PORTD - PIN 3
        
Functionality
    - Button 0 - Turns Screen Red
    - Button 1 - Turns Screen Green
    - Button 2 - Turns Screen Blue
    - Button 3 - Plays an annoying sound