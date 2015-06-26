#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Wire.h>
#include <SPI.h>

int umidade = 0;
int umids = 0;

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

void setup()
{
  Serial.begin(9600);
  display.begin();
  pinMode(A2, INPUT);
  // Ajusta o contraste do display
  display.setContrast(10);
  // Apaga o buffer e o display
  display.clearDisplay();
  // Define tamanho do texto e cor
  display.setTextSize(1);
  display.setTextColor(BLACK);
   
  // Retangulo temperatura
  display.drawRoundRect(0,0, 44,24, 3, 2);
  // Texto inicial temperatura
  display.setCursor(11,3);  // Seta a posição do cursor
  display.println("TEMP");  
  display.setCursor(5,14);
  display.println("----"); 
  display.setCursor(29,14);
  display.drawCircle(31, 15, 1,1);
  display.println(" C");
   
  // Retangulo umidade solo
  display.drawRoundRect(45,0, 39 ,24, 3, 2);
  // Texto inicial Umidade solo
  display.setCursor(50,3);  
  display.println("UMIDS");
  display.setCursor(50,14); 
  display.println("----"); 
  display.setCursor(75,14);
  display.println("%");  
   
  // Retangulo pressao
  display.drawRoundRect(0,25, 48 ,23, 3, 2);
  // Texto inicial Pressao
  display.setCursor(4,28); 
  display.println("PRESSAO");
  display.setCursor(6,38);
  display.println("----"); 
  display.display();
  
  // Retangulo umidade
  display.drawRoundRect(49, 25, 35,23, 3, 2);
  // Texto inicial umidade
  display.setCursor(55,28); 
  display.println("UMID");
  display.setCursor(75,38);
  display.println("%");
  display.setCursor(60,38);
  display.println("--"); 
  display.display();
   
  delay(1000);
}
void loop()
{
  umidade = analogRead(A2);
  int umids = map(umidade, 1023, 0, 0, 100);
  
  // Apresentação de dados
  // Atualiza valor da umidade do solo
  display.fillRect(50,13, 23 , 10, 0);
  display.setCursor(50,14);
  display.println(umids); 
  
  // Atualiza valor da temperatura
  display.fillRect(4,13, 25 , 10, 0);
  display.setCursor(4,14);
  display.println('-'); 
  
  // Atualiza valor da pressao
  display.fillRect(4, 37, 35 , 10, 0);
  display.setCursor(4,38);
  display.println('-');
  
  // Atualiza valor da umidade
  display.fillRect(50, 37, 23 , 10, 0);
  display.setCursor(55,38);
  display.println('-');
    
  display.display();
  
  delay(2000);
}
