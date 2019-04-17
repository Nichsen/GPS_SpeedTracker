#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 3, TXPin = 4; //GPS communication
static const uint32_t GPSBaud = 9600;

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET); //Connection to I2C SCL and SDA!

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

int maxspeed = 0, speed1 = 0;
int maxhigh = 0, high1 = 0;
int maxsatelite = 0, satelite1 = 0;
void setup()
{

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);// initialize with the I2C addr 0x3C (for the 128x32)(initializing the display)

  ss.begin(GPSBaud);

  

  
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("GPS Speed Tracker ");
    display.setCursor(0, 10);
    display.print("NICHSEN 04'2019");
    display.setCursor(0, 20);
    display.print("Start Up: ");
    display.display(); //show
    delay(4000); 
  
  
  display.setCursor(0, 0);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Geschwindigkeiten");
  display.setCursor(0, 10);
  display.print("Hoehe (Meter)");
  display.setCursor(0, 20);
  display.print("Satelliten");
  display.display(); // Important!
  delay(7000);
}

void loop()
{
	satelite1 = (abs(gps.satellites.value()));
	while (satelite1<3){
	display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("GPS Signal...");
    display.setCursor(0, 10);
    display.print("wird gesucht !");
    display.setCursor(0, 20);
    display.print("Anzahl Sat.: ");
	display.print(satelite1);
    display.display(); //show
    delay(1000);
	satelite1 = (abs(gps.satellites.value()));
	}
	
	
	
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("km/h ");
  display.print(abs(gps.speed.kmph()));
  display.print("  ");
  speed1 = (abs(gps.speed.kmph()));
  if ( speed1 > maxspeed) {
    maxspeed = speed1;
  }
  display.print("  ");
  display.print(maxspeed);

  display.setCursor(0, 10);
  display.print("h(m) ");
  display.print(abs(gps.altitude.meters()));
  display.print("  ");
  high1 = (abs(gps.altitude.meters()));
  if ( high1 > maxhigh) {
    maxhigh = high1;
  }
  display.print("  ");
  display.print(maxhigh);


  display.setCursor(0, 20);
  display.print("Sat: ");
  display.print(satelite1);
  satelite1 = (abs(gps.satellites.value()));
  if ( satelite1 > maxsatelite) {
    maxsatelite = satelite1;
  }
  display.print("    ");
  display.print(maxsatelite);

  
  display.display();
  smartDelay(800);

  if (millis() > 5000 && gps.charsProcessed() < 10)
   // display.setCursor(0, 0);
  //lcd.print("Sat.   ERROR");
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

