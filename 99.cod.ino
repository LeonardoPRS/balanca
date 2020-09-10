// INCLUSÃO DE BIBLIOTECAS
#include <HX711.h>

// DEFINIÇÕES DE PINOS
#define pinDT1  22
#define pinSCK1  23
#define pinDT2  24
#define pinSCK2  25
#define pinDT3  26
#define pinSCK3  27
#define pinDT4  28
#define pinSCK4  29
#define pinDT5  30
#define pinSCK5  31
#define pinDT6  32
#define pinSCK6  33
#define pinDT7  34
#define pinSCK7  35
#define pinDT8  36
#define pinSCK8  37

// DEFINIÇÕES
#define pesoMin 0.010
#define pesoMax 65.0

#define escala 0.0f  // aqui estaria o valor de calibração da nossa balanca

// INSTANCIANDO OBJETOS
HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;
HX711 scale5;
HX711 scale6;
HX711 scale7;
HX711 scale8;

// DECLARAÇÃO DE VARAVEIS
float medida1 = 0;  // valor plataforma 1
float medida2 = 0;  // valor plataforma 2
float medida3 = 0;  // valor plataforma 3
float medida4 = 0;  // valor plataforma 4
float medida5 = 0;  // valor eixo dianteiro
float medida6 = 0;  //valor eixo traseiro
float medida0 = 0;  // valor total das plataformas
int valor_lido = 0;  //variavel para teclado

void setup() {
   Serial.begin(57600);

  scale1.begin(pinDT1, pinSCK1); // CONFIGURANDO OS PINOS DO PRIMEIRO HX
  scale1.set_scale(escala); // ENVIANDO O VALOR DA ESCALA CALIBRADO 
  
  scale2.begin(pinDT2, pinSCK2); // CONFIGURANDO OS PINOS DO SEGUNDO HX
  scale2.set_scale(escala); // ENVIANDO O VALOR DA ESCALA CALIBRADO 
  
  scale3.begin(pinDT3, pinSCK3); // CONFIGURANDO OS PINOS DO TERCEIROO HX
  scale3.set_scale(escala); // ENVIANDO O VALOR DA ESCALA CALIBRADO 
  
  scale4.begin(pinDT4, pinSCK4); // CONFIGURANDO OS PINOS DO QUARTO HX
  scale4.set_scale(escala); // ENVIANDO O VALOR DA ESCALA CALIBRADO 
  
  scale5.begin(pinDT5, pinSCK5); // CONFIGURANDO OS PINOS DO QUINTO HX
  scale5.set_scale(escala); // ENVIANDO O VALOR DA ESCALA CALIBRADO 
  
  scale6.begin(pinDT6, pinSCK6); // CONFIGURANDO OS PINOS DO SEXTO HX
  scale6.set_scale(escala); // ENVIANDO O VALOR DA ESCALA CALIBRADO 
  
  scale7.begin(pinDT7, pinSCK7); // CONFIGURANDO OS PINOS DO SETIMO HX
  scale7.set_scale(escala); // ENVIANDO O VALOR DA ESCALA CALIBRADO 
  
  scale8.begin(pinDT8, pinSCK8); // CONFIGURANDO OS PINOS DO OITAVO HX
  scale8.set_scale(escala); // ENVIANDO O VALOR DA ESCALA CALIBRADO 

  delay(2000);
  
  scale1.tare(); // ZERANDO A BALANÇA (INTERPRETACAO DO MODULO HX) PARA DESCONSIDERAR A MASSA DA ESTRUTURA
  scale2.tare(); 
  scale3.tare(); 
  scale4.tare(); 
  scale5.tare(); 
  scale6.tare();
  scale7.tare();
  scale8.tare();
  
  Serial.println("Setup Finalizado!");
}

void loop() {

  medida1 = scale1.get_units(10) + scale2.get_units(10); // SALVANDO NA VARIAVEL O VALOR DA MÉDIA DE 10 MEDIDAS
  medida2 = scale3.get_units(10) + scale4.get_units(10);
  medida3 = scale5.get_units(10) + scale6.get_units(10);
  medida4 = scale7.get_units(10) + scale8.get_units(10);
  medida5 = scale1.get_units(10) + scale2.get_units(10) + scale3.get_units(10) + scale4.get_units(10);
  medida6 = scale5.get_units(10) + scale6.get_units(10) + scale7.get_units(10) + scale8.get_units(10);
  medida0 = scale1.get_units(10)+scale2.get_units(10)+scale3.get_units(10)+scale4.get_units(10)+scale5.get_units(10)+scale6.get_units(10)+scale7.get_units(10)+scale8.get_units(10);
  
  if(Serial.available()>0){
    valor_lido = Serial.read();
}
  if(valor_lido=="0"){
  Serial.print("Peso total: ");  
  Serial.print(medida0, 2); 
  Serial.println(" kg");
  }
  if(valor_lido=="1"){
  Serial.print("Peso roda dianteira esquerda: ");                            // imprime no monitor serial
  Serial.print(medida1, 2);              // imprime peso na balança com 2 casas decimais 
  Serial.println(" kg");                             // imprime no monitor serial 
  }
  if(valor_lido=="2"){
  Serial.print("Peso roda dianteira direita: ");  
  Serial.print(medida2, 2); 
  Serial.println(" kg");
  }
  if(valor_lido=="3"){
  Serial.print("Peso roda traseira esquerda: ");  
  Serial.print(medida3, 2); 
  Serial.println(" kg");
  }
  if(valor_lido=="4"){
  Serial.print("Peso roda traseira direita: ");  
  Serial.print(medida4, 2); 
  Serial.println(" kg");
  }
   if(valor_lido=="5"){
  Serial.print("Peso eixo dianteiro: ");  
  Serial.print(medida5, 2); 
  Serial.println(" kg");
  }
   if(valor_lido=="6"){
  Serial.print("Peso eixo traseiro: ");  
  Serial.print(medida6, 2); 
  Serial.println(" kg");
  }

if(valor_lido=="t"){                  // se pressionar t ou T
  scale1.tare();
  scale2.tare(); 
  scale3.tare(); 
  scale4.tare(); 
  scale5.tare(); 
  scale6.tare();
  scale7.tare();
  scale8.tare();                                // zera a balança
      Serial.println(" Balança zerada");        // imprime no monitor serial
    }
  
  scale1.power_down(); // DESLIGANDO O SENSOR
  scale2.power_down();
  scale3.power_down();
  scale4.power_down();
  scale5.power_down();
  scale6.power_down();
  scale7.power_down();
  scale8.power_down();
  
  delay(1000); // AGUARDA 1 SEGUNDOS
  
  scale1.power_up(); // LIGANDO O SENSOR
  scale2.power_up();
  scale3.power_up();
  scale4.power_up();
  scale5.power_up();
  scale6.power_up();
  scale7.power_up();
  scale8.power_up();
}
