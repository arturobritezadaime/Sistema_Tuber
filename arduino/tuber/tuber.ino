#define CONTAINER_ID 1
#define CONTAINER_HEIGHT 40.0 /*altura del contenedor*/

#define LED 13  
#define TRIG1 9 
#define ECHO1 8 
#define TRIG2 11 
#define ECHO2 10

int lastValue = -1;

void setup(){
    Serial.begin(9600);
   
    //led
    pinMode(LED, OUTPUT);
  
    // ultrasonico 1
    pinMode(TRIG1, OUTPUT);
    pinMode(ECHO1, INPUT);
   
    //ultrasonico 2
    pinMode(TRIG2, OUTPUT);
    pinMode(ECHO2, INPUT);
}


/**
 * devuelve la distancia del sensor ultrasonico en centimetros
 * @param trig pin del trig del sensor
 * @param echo pin del echo del sensor
 * @return la distancia
 */
long getDistance(int trig, int echo) {
    
    digitalWrite(trig,LOW);
    delayMicroseconds(5);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);

    return 0.017*pulseIn(echo, HIGH);
}


/**
 * devuelve el porcentaje de carga del contenedor
 * @return porcentaje de carga del contenedor
 */
int getContainerLoad() {
    long distance1 = getDistance(TRIG1, ECHO1);
    long distance2 = getDistance(TRIG2, ECHO2);
    long avgDistance = (distance1 + distance2)/2;
    int load = map(avgDistance, CONTAINER_HEIGHT, 0, 0, 100);

    return constrain(load, 0, 100);
}


/**
 * envia la cadena JSON por el puerto serie
 * @param load porcentaje de carga del contenedor
 */
void sendAsJSON(int load) {
    Serial.print("{\"id\":");
    Serial.print(CONTAINER_ID);
    Serial.print(",\"load\":");
    Serial.print(load);
    Serial.println("}");
}

/**
 * Comprueba cada 3 segundos si la carga del contenedor cambio.
 * Si lo hizo envia una cadena en formato JSON con el estado del
 * contenedor por el puerto serie
 */
void loop(){
 
    int load = getContainerLoad();
    if(load != lastValue) {
        lastValue = load;
        sendAsJSON(load);
    }

    delay(3000);
}
