// Programa para animar un disco de Zootropo.
// V0.1
// c.: Valentina Arancibia.

#define CAMPO_1 2   // campo A1 del motor PAP
#define CAMPO_2 3   // campo A2
#define CAMPO_3 4   // campo B1
#define CAMPO_4 5   // campo B2
#define FET_OUTPUT 8  //pin donde esta el mosfet de potencia que prende los LED


#define MOTOR_STEPS   48  //cantidad de pasos del motor
#define NUM_FRAMES    13  //cantidad de animaciones que tiene el disco
#define CTE_T_MOTOR   10  //milisegundos entre paso y paso del motor
#define CTE_T_LED_ON  500 // tiempo que debe estar el led encendido (microsegundos)
#define CT_LED_OFF    ((MOTOR_STEPS * CTE_T_MOTOR* 1000)/NUM_FRAMES)-CTE_T_LED_ON // Tiempo para apagar las luces

unsigned long tiempoPasoMotor;
unsigned long tiempoLed, tiempoEntreDestellos;
bool lightsOn = false;


// Configuro todo 
void setup() 
{
pinMode(CAMPO_1, OUTPUT); //hago todo salida
pinMode(CAMPO_2, OUTPUT);
pinMode(CAMPO_3, OUTPUT);
pinMode(CAMPO_4, OUTPUT);
pinMode(FET_OUTPUT, OUTPUT);

// Comienza el estado inicial del motor
digitalWrite(CAMPO_1, LOW); //pongo todo en bajo
digitalWrite(CAMPO_2, LOW);
digitalWrite(CAMPO_3, LOW);
digitalWrite(CAMPO_4, LOW);
digitalWrite(FET_OUTPUT, LOW);
}

void loop() 
{
char paso=0;
char pasosDados=0;

while (true)
  {
  if ((millis() - tiempoPasoMotor) > CTE_T_MOTOR) 
    {
    tiempoPasoMotor = millis();
    if( pasosDados >= MOTOR_STEPS)  //si el motor dio una vuelta, hago reset general
      {
      pasosDados=0;
      tiempoLed=micros()+CTE_T_LED_ON;
      digitalWrite(FET_OUTPUT, HIGH);   
      }
    else pasosDados++;
    switch (paso) 
      {
      case 0:
        {
        digitalWrite (CAMPO_4, LOW),
        digitalWrite (CAMPO_1, HIGH);
        paso=1;
        break;
        }
      case  1:
        {
        digitalWrite (CAMPO_1, LOW);
        digitalWrite (CAMPO_2, HIGH);
        paso=2;
        break;
        }
      case 2:
        {
        digitalWrite (CAMPO_2, LOW);
        digitalWrite (CAMPO_3, HIGH);
        paso=3;
        break;
        }
      case 3:
        {
        digitalWrite (CAMPO_3, LOW);
        digitalWrite (CAMPO_4, HIGH);
        paso=0;
        break;
        }  
      }  
    lightsOn = !lightsOn;
    } //cierre if leds

// Controla el módulo FET para encender y apagar las luces secuencialmente
  if ((millis()- tiempoLed) > tiempoEntreDestellos)
    {
    tiempoLed=micros();
    if(digitalRead(FET_OUTPUT) !=0) //el led esta prendido
      {
      tiempoEntreDestellos = CTE_T_LED_OFF;
      digitalWrite(FET_OUTPUT, LOW);  //lo apago
      }
    else  //si no es que esta apagado, 
      { 
      tiempoEntreDestellos =  CTE_T_LED_ON);
      digitalWrite(FET_OUTPUT, HIGH);  //lo prendo
      }
    }// cierre if de los led
  } //cierre while infinito
} //cierre void loop
  
