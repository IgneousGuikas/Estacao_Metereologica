#include <SFE_BMP180.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <dht11.h>

dht11 sensor;
SFE_BMP180 pressure;
Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

#define ALTITUDE 760.0 // Altitude of SparkFun's HQ in Boulder, CO. in meters

int lmPin = A0;
float pressao = 0;
int porcento = 0;
float temperatura = 0;


void setup()
{
  Serial.begin(115200);
  display.begin();
  pinMode(lmPin, INPUT);
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    Serial.println("BMP180 init fail\n\n");
    while(1);
  }
  
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
  char status;
  double T = 0;
  double P = 0;
  double p0 = 0;
  double a = 0;
  
  pressao = 0;
  porcento = 0;
  temperatura = 0;
  
  delay(500);
  
  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);
    
    status = pressure.getTemperature(T);
    if (status != 0)
    {
      status = pressure.startPressure(3);
      if (status != 0)
      {
        delay(status);
        
        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          // Print out the measurement:
          pressao = P;
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
    
  int chk = sensor.read(2);
  switch(chk) {
    case DHTLIB_OK:
      break;
    case DHTLIB_ERROR_CHECKSUM:
      break;
    case DHTLIB_ERROR_TIMEOUT:
      break;
    default:
      break;
  }
  delay(500);
  analogReference(INTERNAL);
  porcento = (((float)sensor.humidity)*1.1215*1.02) - 4.1054;
  analogReference(DEFAULT);
  delay(500);
  
  temperatura = (tempC()*1.0257)-0.496;
  
  // Apresentação de dados
  // Atualiza valor da umidade do solo
  display.fillRect(50,13, 23 , 10, 0);
  display.setCursor(50,14);
  display.println('-'); 
  
  // Atualiza valor da temperatura
  display.fillRect(4,13, 25 , 10, 0);
  display.setCursor(4,14);
  display.println(temperatura,1); 
  
  // Atualiza valor da pressao
  display.fillRect(4, 37, 35 , 10, 0);
  display.setCursor(4,38);
  display.println(pressao,2);
  
  // Atualiza valor da umidade
  display.fillRect(50, 37, 23 , 10, 0);
  display.setCursor(55,38);
  display.println(porcento);
    
  display.display();
  
  delay(2000);
}

float tempC() {
  analogReference(INTERNAL);
  float raw = analogRead(lmPin);
  analogReference(DEFAULT);
  float percent = raw/1023.0; // <2>
  float volts = percent*1.1*1.02; // <3>
  return 100.0*volts; // <4>
}
