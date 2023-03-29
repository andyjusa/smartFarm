#include <SmartFarm.h>
SmartFarm smartfarm;
Servo servo = SmartFarm::servo();

void setup()
{
  smartfarm.init(115200);
  servo.attach(moter);
}
void loop()
{
  smartfarm.rgbLed(0x00eddd);
  smartfarm.fanOn(true);
  smartfarm.Led(true);
  smartfarm.lcdPrintf("hello korean");
  smartfarm.lcdReset();
  servo.write(close);
}