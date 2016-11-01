long distancia;
long distancia1;
long tiempo1;

long distancia2;
long tiempo2;

void setup(){
  Serial.begin(9600);
 
  pinMode(13, OUTPUT); // led

  // ultrasonico 1
  pinMode(9, OUTPUT); /* blanco Trig activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(8, INPUT); /* verde Echo activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/
 
  //ultrasonico 2
    pinMode(11, OUTPUT); /* blanco Trig activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(10, INPUT); /* verde Echo activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/
}

void loop(){
  //if (Serial.available() > 0){
  //  if (Serial.read()==  107){ //lee la "k"
    //ultrasonico 1
    digitalWrite(9,LOW); /* Por cuestión de estabilización del sensor*/
    delayMicroseconds(5);
    digitalWrite(9, HIGH); /* envío del pulso ultrasónico*/
    delayMicroseconds(10);
    tiempo1=pulseIn(8, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
    del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
    deja de hacerlo, LOW, la longitud del pulso entrante*/
    distancia1= int(0.017*tiempo1); /*fórmula para calcular la distancia obteniendo un valor entero*/
    /*Monitorización en centímetros por el monitor serial*/
    Serial.println(String(distancia1) + " cm. , sensor izquierdo") ;
    delay(1000);
    //ultrasonico 2
    digitalWrite(11,LOW); /* Por cuestión de estabilización del sensor*/
    delayMicroseconds(5);
    digitalWrite(11, HIGH); /* envío del pulso ultrasónico*/
    delayMicroseconds(10);
    tiempo2=pulseIn(10, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
    del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
    deja de hacerlo, LOW, la longitud del pulso entrante*/
    distancia2= int(0.017*tiempo2); /*fórmula para calcular la distancia obteniendo un valor entero*/
    /*Monitorización en centímetros por el monitor serial*/
    Serial.println(String(distancia2) + " cm. , sensor derecho") ;
    delay(1000);
    
    distancia= int (distancia1 + distancia2)/2 ;
   Serial.println( String(distancia) + " cm. , Distancia promedio ") ;
    
      if (distancia > 20) //Nivel Bajo
  {
    Serial.println(" Contenedor nivel bajo ");
    digitalWrite(13, LOW);  
        
  }
  else if ( distancia < 8 ) // Nivel Alto
  {
          Serial.println(" Contenedor lleno ,nivel alto ");
          digitalWrite(13, HIGH);  
     
  }
            else // Nivel Medio
  {
                   Serial.println(" Contenedor nivel medio ");
                   digitalWrite(13, HIGH);  
                   delay(200);             
                   digitalWrite(13, LOW);    
                   delay(200);  
  }
    }
 // }
                  
//}
