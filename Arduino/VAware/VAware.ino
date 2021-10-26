//import header files
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define LED_BUILTIN 2
#define pass (void)0
#define BASE_VAL "0"

// Generated UUID's for different Charateristics
#define SERVICE_UUID "e472cea9-3ae8-4d96-951e-7086fe17d416"
#define LED_BUILTIN_UUID "7abd909a-a9e5-4409-96a9-7aa4fa33426f"

BLEServer *pServer = NULL;
BLECharacteristic *pLedBuiltinCharacteristic = NULL;

bool deviceConnected = false;
bool oldDeviceConnected = false;

// Init Pneumatics Parts: assign the pins for the Pneumatics:
const byte pneumatics1 = 22;
const byte pneumatics2 = 21;
const byte pneumatics3 = 17;
const byte pneumatics4 = 16;
const byte pneumatics5 = 4;
const byte pneumatics6 = 15;

// Init Release Mechanism Checks: assign the pins for RMECHS:
const byte releaseMech1 = 34;
const byte releaseMech2 = 23;
const byte releaseMech3 = 32;
const byte releaseMech4 = 33;
const byte releaseMech5 = 25;
const byte releaseMech6 = 26;

// State Variables
unsigned long previousMillis = 0;
const long interval = 7000;

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
  //  void onWrite(BLECharacteristic *pCharacteristic) {
  //      std::string rxValue = pCharacteristic->getValue();
  //
  //      if (rxValue.length() > 0)
  //      {
  //        Serial.println("*********");
  //        Serial.print("Received Value: ");
  //        for (int i = 0; i < rxValue.length(); i++)
  //          Serial.print(rxValue[i]);
  //
  //        Serial.println();
  //        Serial.println("*********");
  //      }
  //    }
};

void pnuematicsOperate(int pin, int rMech, String message)
{
  unsigned long currentMillis = millis(); //
  
  digitalWrite(pin,HIGH);
  //Serial.println(message);
  //Serial.println(pneuTimerStart);
  //Serial.println(pneuTimerEnd);
  
  while (currentMillis - previousMillis >= interval ) {
    //Serial.println(millis());
    if (digitalRead(rMech) == HIGH)
    {
      //Serial.println(millis());
      //Serial.println("Pressed");
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
  //BLEService *pService = pService->createService(SERVICE_UUID);

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
  //pAdvertising->setMinPreferred();
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}

void loop()
{
//  digitalWrite(releaseMech1, HIGH); //closed is high
//  digitalWrite(releaseMech2, HIGH);
//  digitalWrite(releaseMech3, HIGH);
//  digitalWrite(releaseMech4, HIGH);
//  digitalWrite(releaseMech5, HIGH);
//  digitalWrite(releaseMech6, HIGH);

  
  if (deviceConnected)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    std::string value = pLedBuiltinCharacteristic->getValue();
    unsigned long currentMillis = millis();

    if (value == "1")
    {
      //pnuematicsOperate(pneumatics1, releaseMech1, "INFLATEEEE");
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
