//import header files
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define LED_BUILTIN 2
#define pass (void)0
#define BASE_VAL "0"
#define TIME_DELAY 700

BLEServer* pServer = NULL;
BLECharacteristic* pLedBuiltinCharacteristic = NULL;

bool deviceConnected = false;
bool oldDeviceConnected = false;

// Generated UUID's for different Charateristics
#define SERVICE_UUID          "e472cea9-3ae8-4d96-951e-7086fe17d416"
#define LED_BUILTIN_UUID      "7abd909a-a9e5-4409-96a9-7aa4fa33426f"

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

// Init Pneumatics Parts: assign the pins for the Pneumatics:
int pneumatics1 = 22;
int pneumatics2 = 1;
int pneumatics3 = 3;
int pneumatics4 = 21;
int pneumatics5 = 19;
int pneumatics6 = 18;

// Init Release Mechanism Checks: assign the pins for RMECHS:
int releaseMech1 = 5;
int releaseMech2 = 17;
int releaseMech3 = 16;
int releaseMech4 = 2;
int releaseMech5 = 15;
int releaseMech6 = 8;



void pnuematicsOperate(int pin, int rMech, String message)
{
  digitalWrite(pin, HIGH);
  Serial.println(message);
  for (int i = 0; i <= TIME_DELAY; i++){
    delay(10);
    if (releaseMechOpen(rMech) == true)
    {
      digitalWrite(pin, LOW);
      break;
    }
  }
  digitalWrite(pin, LOW);
  pLedBuiltinCharacteristic->setValue(BASE_VAL);
//      digitalWrite(pneumatics2, HIGH);
//      Serial.println("RED");
//      delay(7000);
//      digitalWrite(pneumatics2, LOW);
//      pLedBuiltinCharacteristic->setValue("0");
}

bool releaseMechOpen(int rMech)
{
  if (digitalRead(rMech) == HIGH)
  {
    // not open
    return false;
  }
  else 
  {
    return true;
  }
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
  pinMode(releaseMech1, OUTPUT);
  pinMode(releaseMech2, OUTPUT);
  pinMode(releaseMech3, OUTPUT);
  pinMode(releaseMech4, OUTPUT);
  pinMode(releaseMech5, OUTPUT);
  pinMode(releaseMech6, OUTPUT);

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
          BLECharacteristic::PROPERTY_WRITE
  );
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
