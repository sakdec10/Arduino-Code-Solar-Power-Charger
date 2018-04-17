//#include <time.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

#define OLED_RESET 4
Adafruit_SSD1306 disp(OLED_RESET);

int relayPin=13;

char keys[4][4] = 
{
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[4] = { 9, 8, 7, 6 };
byte colPins[4] = { 5, 4, 3, 2 };

Keypad mykeypad = Keypad( makeKeymap(keys), rowPins, colPins, 4, 4);
char pass[]="ABC123";
void setup() {
Serial.begin(9600);

  disp.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  //disp.display();
  //delay(2000);

  pinMode(relayPin,OUTPUT);

}

void loop() {
  digitalWrite(relayPin,HIGH);
  unsigned long time = millis();
  if(time>=10800000) 
  {disp.println("Low Battery!");
    disp.println("Press # to Dismiss");
    disp.display();
    while(mykeypad.getKey()!='#');
    }
  beg();
  int i=0;
  int tim=0;
  char key = mykeypad.getKey();
  char userpin[10];
  
  while(key!='#')
  {
  if(key)
  { userpin[i] = key;
    i+=1;
    disp.print("$");
    disp.display();
    delay(200);
    }
   key = mykeypad.getKey();
  }  
  userpin[i]='\0';
  disp.clearDisplay();
  if(strcmp(userpin,pass)==0)
  { disp.setCursor(0,0);
    disp.println("Connect Device Now");
    disp.println("Press # To Finish");
    disp.display();
    digitalWrite(relayPin, LOW);
   while(mykeypad.getKey()!='#'){delay(200); tim+=1;}
   digitalWrite(relayPin, HIGH);
   disp.clearDisplay();
   delay(100);
   disp.setCursor(0,0);
   double energy = (0.24*(tim/3600)) * 1.22;
   disp.print("Charged for: ");
   if(tim>300)
   {disp.print(tim/300);
    disp.println("min");}
    else
    {disp.print(tim/5);
    disp.println("sec");
      }
   disp.print("CO2 Reduced: ");
   disp.print(energy);
   disp.println("lbs");
   disp.display();
   delay(5000);
   //disp.clearDisplay();
  }
  else
  {disp.setCursor(0,0);
    disp.println("Wrong Key");
  disp.display();
  //disp.clearDisplay();
  delay(2000);
    }
}

void beg(void)
{disp.clearDisplay();
  disp.setCursor(0,0);
  disp.setTextColor(WHITE);
  disp.setTextSize(1);
  disp.println("Enter Security Key -");
  disp.println("(End with #)");
  disp.display();
  //disp.setCursor(0,10);
  }


