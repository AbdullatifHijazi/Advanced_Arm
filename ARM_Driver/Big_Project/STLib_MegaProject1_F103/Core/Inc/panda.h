#ifndef PANDA_H_
#define PANDA_H_

/* Ports Macro */
#define PANDA_PORTA                 GPIOA
#define PANDA_PORTB                 GPIOB
#define PANDA_PORTC                 GPIOC
#define PANDA_PORTD                 GPIOD
#define PANDA_PORTE                 GPIOE

/* Pins Macro */
#define PANDA_PIN0                  GPIO_PIN_0
#define PANDA_PIN1                  GPIO_PIN_1
#define PANDA_PIN2                  GPIO_PIN_2
#define PANDA_PIN3                  GPIO_PIN_3
#define PANDA_PIN4                  GPIO_PIN_4
#define PANDA_PIN5                  GPIO_PIN_5
#define PANDA_PIN6                  GPIO_PIN_6
#define PANDA_PIN7                  GPIO_PIN_7
#define PANDA_PIN8                  GPIO_PIN_8
#define PANDA_PIN9                  GPIO_PIN_9
#define PANDA_PIN10                 GPIO_PIN_10
#define PANDA_PIN11                 GPIO_PIN_11
#define PANDA_PIN12                 GPIO_PIN_12
#define PANDA_PIN13                 GPIO_PIN_13
#define PANDA_PIN14                 GPIO_PIN_14
#define PANDA_PIN15                 GPIO_PIN_15

/* General Outputs */
#define PANDA_BUZ_PORT              PANDA_PORTB
#define PANDA_BUZ_PIN               PANDA_PIN4

#define PANDA_REL1_PORT             PANDA_PORTB
#define PANDA_REL1_PIN              PANDA_PIN5

#define PANDA_REL2_PORT             PANDA_PORTA
#define PANDA_REL2_PIN              PANDA_PIN3

#define PANDA_LED_RED1_PORT         PANDA_PORTA
#define PANDA_LED_RED1_PIN          PANDA_PIN2

#define PANDA_LED_RED2_PORT         PANDA_PORTA
#define PANDA_LED_RED2_PIN          PANDA_PIN1

#define PANDA_LED_GRN_PORT          PANDA_PORTC
#define PANDA_LED_GRN_PIN           PANDA_PIN15

#define PANDA_LED_BLU_PORT          PANDA_PORTC
#define PANDA_LED_BLU_PIN           PANDA_PIN14

#define PANDA_LED_YLW_PORT          PANDA_PORTC
#define PANDA_LED_YLW_PIN           PANDA_PIN13

/* Serial UART */
#define PANDA_TX_PORT               PANDA_PORTA
#define PANDA_TX_PIN                PANDA_PIN9

#define PANDA_RX_PORT               PANDA_PORTA
#define PANDA_RX_PIN                PANDA_PIN10

/* LCD 2x16 */
#define PANDA_LCD_D7_PORT           PANDA_PORTB
#define PANDA_LCD_D7_PIN            PANDA_PIN12

#define PANDA_LCD_D6_PORT           PANDA_PORTB
#define PANDA_LCD_D6_PIN            PANDA_PIN13

#define PANDA_LCD_D5_PORT           PANDA_PORTB
#define PANDA_LCD_D5_PIN            PANDA_PIN14

#define PANDA_LCD_D4_PORT           PANDA_PORTB
#define PANDA_LCD_D4_PIN            PANDA_PIN15

#define PANDA_LCD_EN_PORT           PANDA_PORTA
#define PANDA_LCD_EN_PIN            PANDA_PIN8

#define PANDA_LCD_RS_PORT           PANDA_PORTA
#define PANDA_LCD_RS_PIN            PANDA_PIN11

/* Analog Input */
#define PANDA_ANALOG_INPUT_PORT     PANDA_PORTA
#define PANDA_ANALOG_INPUT_PIN      PANDA_PIN0

/* OLED Display 64x128 */
#define PANDA_OLED_SCL_PORT         PANDA_PORTB
#define PANDA_OLED_SCL_PIN          PANDA_PIN6

#define PANDA_OLED_SDA_PORT         PANDA_PORTB
#define PANDA_OLED_SDA_PIN          PANDA_PIN7

/* 7-Segment Display */
#define PANDA_7SEG_A_PORT           PANDA_PORTA
#define PANDA_7SEG_A_PIN            PANDA_PIN11

#define PANDA_7SEG_B_PORT           PANDA_PORTA
#define PANDA_7SEG_B_PIN            PANDA_PIN8

#define PANDA_7SEG_C_PORT           PANDA_PORTB
#define PANDA_7SEG_C_PIN            PANDA_PIN15

#define PANDA_7SEG_D_PORT           PANDA_PORTB
#define PANDA_7SEG_D_PIN            PANDA_PIN14

#define PANDA_7SEG_E_PORT           PANDA_PORTB
#define PANDA_7SEG_E_PIN            PANDA_PIN13

#define PANDA_7SEG_F_PORT           PANDA_PORTB
#define PANDA_7SEG_F_PIN            PANDA_PIN12

#define PANDA_7SEG_G_PORT           PANDA_PORTA
#define PANDA_7SEG_G_PIN            PANDA_PIN12

#define PANDA_7SEG_DOT_PORT         PANDA_PORTA
#define PANDA_7SEG_DOT_PIN          PANDA_PIN15

#define PANDA_7SEG_COM1_PORT        PANDA_PORTB
#define PANDA_7SEG_COM1_PIN         PANDA_PIN8

#define PANDA_7SEG_COM2_PORT        PANDA_PORTB
#define PANDA_7SEG_COM2_PIN         PANDA_PIN9

#define PANDA_7SEG_COM3_PORT        PANDA_PORTB
#define PANDA_7SEG_COM3_PIN         PANDA_PIN3

/* Keypad 4x4 */
#define PANDA_KPD_ROW1_PORT         PANDA_PORTA
#define PANDA_KPD_ROW1_PIN          PANDA_PIN4

#define PANDA_KPD_ROW2_PORT         PANDA_PORTA
#define PANDA_KPD_ROW2_PIN          PANDA_PIN5

#define PANDA_KPD_ROW3_PORT         PANDA_PORTA
#define PANDA_KPD_ROW3_PIN          PANDA_PIN6

#define PANDA_KPD_ROW4_PORT         PANDA_PORTA
#define PANDA_KPD_ROW4_PIN          PANDA_PIN7

#define PANDA_KPD_COL1_PORT         PANDA_PORTB
#define PANDA_KPD_COL1_PIN          PANDA_PIN11

#define PANDA_KPD_COL2_PORT         PANDA_PORTB
#define PANDA_KPD_COL2_PIN          PANDA_PIN10

#define PANDA_KPD_COL3_PORT         PANDA_PORTB
#define PANDA_KPD_COL3_PIN          PANDA_PIN1

#define PANDA_KPD_COL4_PORT         PANDA_PORTB
#define PANDA_KPD_COL4_PIN          PANDA_PIN0

/* Push Button */
#define PANDA_SW1_PORT              PANDA_PORTB
#define PANDA_SW1_PIN               PANDA_PIN11

#define PANDA_SW2_PORT              PANDA_PORTB
#define PANDA_SW2_PIN               PANDA_PIN10

#define PANDA_SW3_PORT              PANDA_PORTB
#define PANDA_SW3_PIN               PANDA_PIN1

#define PANDA_SW4_PORT              PANDA_PORTB
#define PANDA_SW4_PIN               PANDA_PIN0

#endif /* PANDA_H_ */
