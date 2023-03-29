#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>
#include <Servo.h>


#define redLed 23
#define greenLed 35
#define blueLed 36
#define tempPin 12
#define soil A1
#define outLed 4
#define Bluetooth Serial1
#define cd A0
#define moter 9
#define fan 32
#define Wifi Serial2
#define close 27
#define open 127


class SmartFarm
{
private:
    
public:
    SmartFarm(void){}
    ~SmartFarm(void){}
    void init(unsigned long baud);
    void lcdPrintf(const char *str,...);
    void lcdPrintf(int i,const char *str,...);
    void fanOn(bool on);
    void fanOn(int pwm);
    void rgbLed(byte r,byte g,byte b);
    void rgbLed(unsigned long rgb);
    void Led(bool b);
    void Led(uint8_t p);
    void serveControll(int p){analogWrite(moter,p);return;}
    void lcdReset();
    uint8_t GetSoil(){return analogRead(soil);}
    uint8_t GetBright(){return analogRead(cd);}
    float GetHumidity(){dht d;return d.readHumidity();}
    float GetTemp(){dht d;return d.readTemperature();}

    class Lcd : public LiquidCrystal_I2C
    {
    private:
        bool is_init;
    public:
        Lcd(void): LiquidCrystal_I2C(0x27,16,2){if(!is_init){is_init = true;Lcd::backlight();}}
        ~Lcd(void){}
        bool isInit(void) { return is_init; };
    };
    class dht:public DHT
    {
    private:
        bool is_init;
    public:
        dht(void):DHT(tempPin,DHT11){}
        ~dht(void){}
    };
    
    class servo : public Servo
    {
    private:
    public:
        servo(void):Servo(){
            Servo::attach(moter);
        }
        ~servo(void){}
    };
    
    
};
void SmartFarm::init(unsigned long baud)
{
    Lcd lcd;
    dht Dht;
    Dht.begin();
    pinMode(redLed,OUTPUT);
    pinMode(greenLed,OUTPUT);
    pinMode(blueLed,OUTPUT);
    pinMode(outLed,OUTPUT);
    pinMode(fan,INPUT);
    pinMode(moter,INPUT);
    Serial.begin(baud);
}
void SmartFarm::fanOn(bool on)
{
    digitalWrite(fan,on);
}
void SmartFarm::fanOn(int pwm)
{
    analogWrite(fan,pwm);
}
void SmartFarm::lcdPrintf(const char *str,...)
{
    Lcd lcd;
    lcd.home();
    lcd.print(str);
}
void SmartFarm::lcdPrintf(int i,const char *str,...)
{
    Lcd lcd;
    lcd.setCursor(0,1);
    lcd.print(str);
}
void SmartFarm::rgbLed(byte r,byte g,byte b) {
  analogWrite(redLed,r);
  analogWrite(greenLed,g);
  analogWrite(blueLed,b);
}
void SmartFarm::rgbLed(unsigned long rgb)
{
  byte red, green, blue;
  red = rgb >> 16 ;
  green = ((rgb & 0x00ff00) >> 8);
  blue = (rgb & 0x0000ff);
  analogWrite(redLed,red);
  analogWrite(greenLed,green);
  analogWrite(blueLed,blue);
}
void SmartFarm::Led(bool b)
{
    digitalWrite(outLed,b);
}
void SmartFarm::Led(uint8_t p)
{
    analogWrite(outLed,p);
}
void SmartFarm::lcdReset()
{
    Lcd lcd;
    lcd.setCursor(0,1);
    lcd.print("                                ");
}