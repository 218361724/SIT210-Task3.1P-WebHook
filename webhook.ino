#include <PietteTech_DHT.h>

#define DHTTYPE  DHT22
#define DHTPIN   D2

PietteTech_DHT DHT(DHTPIN, DHTTYPE);

void setup()
{
  // Open serial communications
  Serial.begin(9600);
  
  // Initialise temp sensor
  DHT.begin();
}

void loop()
{
  // Ensure if reading not valid
  int result = DHT.acquireAndWait();
  if (result != DHTLIB_OK) {
    return;
  }

  // Log current temp reading
  Serial.print("Temperature (oC): ");
  Serial.println(DHT.getCelsius(), 2);

  // Push temp reading to thingspeak
  Particle.publish("temp", String(DHT.getCelsius()), PRIVATE);

  delay(1000);
}
