//import header files
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define LED_BUILTIN 2
#define pass (void)0
#define BASE_VAL "0"
#define TIME_DELAY 700

// Generated UUID's for different Charateristics
#define SERVICE_UUID "e472cea9-3ae8-4d96-951e-7086fe17d416"
#define LED_BUILTIN_UUID "7abd909a-a9e5-4409-96a9-7aa4fa33426f"

BLEServer *pServer = NULL;
BLECharacteristic *pLedBuiltinCharacteristic = NULL;

bool deviceConnected = false;
bool oldDeviceConnected = false;

// A call back function to check if device is still connected or not
class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
  }
};

// Init Pneumatics Parts: assign the pins for the Pneumatics:
// a19 GND      j19 3.3V
// a18 23       j18 EN
// a17 22 x      j17 36 x
// a16 1        j16 39 x
// a15 3        j15 34 x
// a14 21 x      j14 35 x
// a13 GND      j13 32 
// a12 19 x      j12 33 z
// a11 18 x      j11 25 z
// a10 5        j10 26 z
// a09 17 x      j09 27
// a08 16 x      j08 14
// a07 4  x      j07 12
// a06 0        j06 GND
// a05 2        j05 13 h
// a04 15       j04 9 h
// a03 8        j03 10
// a02 7        j02 11
// a01 6        j01 5V

int pneumatics1 = 22; // c red      neck      
int pneumatics2 = 21; // c white    left arm
int pneumatics3 = 17; // c green    right wrist
int pneumatics4 = 16; // c blue     torso
int pneumatics5 = 19; // c yellow   left wrist
int pneumatics6 = 18; // c black    right arm

// Init Release Mechanism Checks: assign the pins for RMECHS:
int releaseMech1 = 32; // c red
int releaseMech2 = 13; // c white
int releaseMech3 = 33; // c green
int releaseMech4 = 27; // c blue
int releaseMech5 = 26; // c yellow
int releaseMech6 = 25; // c black

void pnuematicsOperate(int pin, int rMech, String message)
{
  digitalWrite(pin, HIGH);
  Serial.println(message);
  for (int i = 0; i <= TIME_DELAY; i++)
    {
      delay(10);
      if (digitalRead(rMech) == HIGH)
      {
        digitalWrite(pin, LOW);
        break;
      }
    }
  digitalWrite(pin, LOW);
  pLedBuiltinCharacteristic->setValue(BASE_VAL);
}

void setup()
{
  Serial.begin(115200);

  //Bluetooth connection indicator
  pinMode(LED_BUILTIN, OUTPUT);

  //Pneumatics Init Pins
  pinMode(pneumatics1, OUTPUT);
  pinMode(pneumatics2, OUTPUT);
  pinMode(pneumatics3, OUTPUT);
  pinMode(pneumatics4, OUTPUT);
  pinMode(pneumatics5, OUTPUT);
  pinMode(pneumatics6, OUTPUT);

  //ReleaseMech Init Pins
  pinMode(releaseMech1, INPUT_PULLUP);
  pinMode(releaseMech2, INPUT_PULLUP);
  pinMode(releaseMech3, INPUT_PULLUP);
  pinMode(releaseMech4, INPUT_PULLUP);
  pinMode(releaseMech5, INPUT_PULLUP);
  pinMode(releaseMech6, INPUT_PULLUP);

  //Create the BLE DEVICE!
  BLEDevice::init("VAware");

  //Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  //Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  //Create the BLE Charateristic for LED_BUILTIN
  pLedBuiltinCharacteristic = pService->createCharacteristic(
      LED_BUILTIN_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);
  //Might need a Descriptor. DONT KNOW WHAT THAT IS :(

  pLedBuiltinCharacteristic->setValue("Heyo says sid");
  pService->start();

  //Start Advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}

void loop()
{
  if (deviceConnected)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    std::string value = pLedBuiltinCharacteristic->getValue();

    if (value == "1")
    {
      pnuematicsOperate(pneumatics1, releaseMech1, "INFLATEEEE");
    }
    else if (value == "2")
    {
      pnuematicsOperate(pneumatics2, releaseMech2, "INFLATEEEE");
    }
    else if (value == "3")
    {
      pnuematicsOperate(pneumatics3, releaseMech3, "INFLATEEEE");
    }
    else if (value == "4")
    {
      pnuematicsOperate(pneumatics4, releaseMech4, "INFLATEEEE");
    }
    else if (value == "5")
    {
      pnuematicsOperate(pneumatics5, releaseMech5, "INFLATEEEE");
    }
    else if (value == "6")
    {
      pnuematicsOperate(pneumatics6, releaseMech6, "INFLATEEEE");
    }
    else
    {
      pass;
    }
  }

  if (!deviceConnected && oldDeviceConnected)
  {
    pServer->startAdvertising();
    Serial.println("started advertising");
    digitalWrite(LED_BUILTIN, LOW);
    oldDeviceConnected = deviceConnected;
  }

  if (deviceConnected && !oldDeviceConnected)
  {
    oldDeviceConnected = deviceConnected;
  }
}
