int pinData  = 2; // pin por donde se enviara la informacion de forma serial al H595
int pinLatch = 3; // pin que define cuando se desplegara la informacion en paralelo en el H595
int pinClock = 4; // pin que define cuando se ingresa un nuevo bit al H595


void setup(){
  // velocidad de baudios de la comunicacion serial
  Serial.begin(9600);
  // declaracion de los pines de comunicacion con el H595 como salida
  pinMode(pinData, OUTPUT);
  pinMode(pinLatch, OUTPUT);
  pinMode(pinClock, OUTPUT);
}

void loop() {
  int opcion=1; // opcion es la opcion escogida en el menu por el usuario
  int repeticiones=0; // repeticiones se usa en algunas funciones para repetir una imagen el la matriz de leds 
  long tiempo=0; // guarda el tiempo que se desplegara cada imagen en la matriz de leds

  // creacion de la matriz que guardara las imagenes a desplegar en la matriz de leds
  int **matriz = new int*[8];                       
  for(int i=0; i<8; i++) matriz[i] = new int[8];

  // bucle principal del programa
  while(opcion!=4){
  
    // llama al menu
    opcion = Public();
    // segun lo escogido por el usuario se va al caso correspondiente
    switch (opcion)
    {
      case 1:
      {
        do
        {
        Serial.println("Ingrese el tiempo de encendido apagado (ms): ");
        while(Serial.available() == 0){}
        tiempo = Serial.parseInt();
        }while(tiempo < 1);
          
        do
        {
        Serial.println("Ingrese el numero de repeticiones que quiere: ");
        while(Serial.available() == 0){}
        repeticiones = Serial.parseInt();
        }while(repeticiones < 1);
        
        verificacion(matriz, tiempo, repeticiones);
        Serial.println();
        break;
      }
      case 2:
      {
        do{
        Serial.println("Ingrese el tiempo de espera (ms): ");
        while(Serial.available() == 0){}
        tiempo = Serial.parseInt();
        Serial.println();
        }while(tiempo < 1);

        imagen(matriz, tiempo);
        break;
      }
      case 3:
      {
        do{
        Serial.println("Ingrese el tiempo de espera (ms): ");
        while(Serial.available() == 0){}
        tiempo = Serial.parseInt();
        Serial.println();
        }while(tiempo < 1);

        Serial.println(" Patrones ");
        patrones(matriz, tiempo);
        break;
      }
      case 4:
      {
        Serial.println("El programa finalizo");
        break;
      }
      default:
      {
        Serial.println("Invalido");
        break;
      }
    }
  }
  
  for (int i=0; i<8; i++) delete[] matriz[i];     
  delete[] matriz;
  while(opcion == 4){}
}

// despliega el menu y retorna la opcion escogida por el usuario
int Public(){
  int opcion=10;
  Serial.println(" --------- Menu de opciones ---------- ");
  Serial.println(" 1. Verificar el funcionamiento de los leds. ");
  Serial.println(" 2. Imagen de prueba ingresada por el usuario. ");
  Serial.println(" 3. Mostrar los patrones de prueba 1-4. ");
  Serial.println(" 4. Para finalizar. ");
  Serial.println();

  while((opcion<1) || (opcion>4)){
    Serial.println("Ingrese la opcion que desea: ");
    while(Serial.available() == 0){}
    opcion = Serial.parseInt();
  }
  return opcion;
}


// apaga la matriz de leds
void apagar(int **matriz){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++) matriz[i][j] = 0;     //Llena la matriz con ceros
    }
    H595(0,0);
}

// enciende la matriz de leds
void prender(int **matriz){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++) matriz[i][j] = 1;     //Llena la matriz con ceros
    }
    H595(255,0);
}

// hace la funcion de verificar que la matriz de leds esta funcionando, consiste en apagar y encender todos los leds de la matriz
void verificacion(int **matriz, long tiempo, int repeticiones){
  for(int i=0; i<repeticiones; i++){
      prender(matriz);
      delay(tiempo);
      apagar(matriz);
      delay(tiempo);
  }
}

// recibe por parte del usuario que leds se van a encender o apagar y luego despliega la imagen ingresada por el usuario
void imagen(int **matriz, long tiempo){
  for(int i=0; i<8; i++){                                           //Llena la funcion.
      for(int j=0; j<8; j++){
          do{
          Serial.print("Ingrese la posicion");
          Serial.print("[");
          Serial.print(i);
          Serial.print("]");
          Serial.print("[");
          Serial.print(j);
          Serial.println("] : ");
          while(Serial.available() == 0){}
          matriz[i][j] = Serial.parseInt();  
          }while(matriz[i][j] != 0 && matriz[i][j] != 1);
      }
  }
  vector2sum(matriz, tiempo);
  H595(0,0);
}

// llena la matriz con los '0's y '1's necesarios para mostrar la imagen del patron 1 
void patron1(int **matriz){
  int aux=8;

  for(int j=0; j<4; j++){

      for(int i=0; i<3-j; i++) matriz[i][j]=0;
      for(int i=3-j; i<2+2*j+(3-j); i++) matriz[i][j]=1;
      for(int i=2+2*j+(3-j); i<8; i++) matriz[i][j]=0;
  }
  
  for(int j=4; j<8; j++){

      for(int i=0; i<j-4; i++) matriz[i][j]=0;
      for(int i=j-4; i<aux; i++) matriz[i][j]=1;
      for(int i=aux; i<8; i++) matriz[i][j]=0;
      aux--;
  }
}

// llena la matriz con los '0's y '1's necesarios para mostrar la imagen del patron 2
void patron2(int **matriz){
  for(int i=0; i<8; i++){
      for(int j=0; j<8; j++ ){
          if(i==j) matriz[i][j] =1;
          else
              matriz[i][j]=0;
      }
  }
  for(int i=0; i<8; i++) matriz[i][7-i]=1;
}

// llena la matriz con los '0's y '1's necesarios para mostrar la imagen del patron 3
void patron3(int **matriz){
  int contador=0, b=0;

  for(int l=0; l<2;l++){

      for(int i=0+b; i<2+b; i++){
          contador=0;
          for(int j=0; j<8; j++){
              matriz[i][j]=1;

              if(contador==2){
                  matriz[i][j]=0;
                  contador=0;}
              else
                  contador++;
          }
      }

      for(int i=2+b; i<4+b; i++){
          contador=2;
          for(int j=0; j<8; j++){
              matriz[i][j]=1;

              if(contador==2){
                  matriz[i][j]=0;
                  contador=0;}
              else
                  contador++;
          }
      }
      b +=4;
  }
}

// llena la matriz con los '0's y '1's necesarios para mostrar la imagen del patron 4
void patron4(int **matriz){

  for(int i=0; i<4; i++){                                          //Primeras 4 filas.
      for(int j=0; j<i; j++) matriz[i][j]=0;
      for(int j=i; j<5+i; j++) matriz[i][j]=1;
      for(int j=i+4; j<8; j++) matriz[i][j]=0;
  }

  for(int i=4; i<8; i++){                                          //Primeras 4 filas.
      for(int j=0; j<7-i; j++) matriz[i][j]=0;
      for(int j=7-i; j<7-i+5; j++) matriz[i][j]=1;
      for(int j=7-i+4; j<8; j++) matriz[i][j]=0;
  }
}

// despliega alternadamente los patrones en la matriz de leds
void  patrones(int **matriz, long tiempo){

  patron1(matriz);
  vector2sum(matriz, tiempo);
  H595(0,0);

  patron2(matriz);
  vector2sum(matriz, tiempo);
  H595(0,0);


  patron3(matriz);
  vector2sum(matriz, tiempo);
  H595(0,0);
 

  patron4(matriz);
  vector2sum(matriz, tiempo);
  H595(0,0);

}

// traduce la matriz de '1's y '0's en los bits necesarios para desplegar la imagen (fila por fila) y luego los envia a los integrados H595
void vector2sum(int **matriz, long tiempo){
  byte sumRow=0;
  byte potencias[8]={1,2,4,8,16,32,64,128};
  unsigned long Tactual = millis();
  
  while(millis()-Tactual <= tiempo){
  	  for(int i=0; i<8; i++){
          for(int j=0; j<8; j++){
              sumRow += matriz[i][j]*potencias[j];
          }
          H595((byte)potencias[i],(byte)~sumRow);
          delayMicroseconds(125);
          sumRow = 0;
      }
  }
}

// funcion de control del integrado H595, envia los datos de forma serial a dos integrados en serie y luego los activa
void H595(byte an, byte cat ){
   shiftOut(pinData, pinClock, MSBFIRST, (byte)an);
   shiftOut(pinData, pinClock, MSBFIRST, (byte)cat);
   digitalWrite(pinLatch, HIGH);
   digitalWrite(pinLatch, LOW);
}