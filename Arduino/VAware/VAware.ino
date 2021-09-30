//import header files

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define LED_BUILTIN 2
#define pass (void)0
#define BASE_VAL "0"
#define TIME_DELAY 7000

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
//      if (rxValue.length() > 0) {
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

// Init PINS: assign the pins for the LEDs:
int ledPin1 = 21;
int ledPin2 = 19;
int ledPin3 = 18;

void pnuematicsOperate(int ledPin, String message)
{
  digitalWrite(ledPin, HIGH);
  Serial.println(message);
  delay(TIME_DELAY);
  digitalWrite(ledPin, LOW);
  pLedBuiltinCharacteristic->setValue(BASE_VAL);
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

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
      pnuematicsOperate(ledPin1, "INFLATEEEE");
    }
    else if (value == "2")
    {
      digitalWrite(ledPin2, HIGH);
      Serial.println("RED");
      delay(7000);
      digitalWrite(ledPin2, LOW);
      pLedBuiltinCharacteristic->setValue("0");
//      pnuematicsOperate(ledPin2, "INFLATEEEE");
    }
    else if (value == "3")
    {
      digitalWrite(ledPin3, HIGH);
      Serial.println("BLUE");
      delay(7000);
      digitalWrite(ledPin3, LOW);
      pLedBuiltinCharacteristic->setValue("0");
//      pnuematicsOperate(ledPin3, "INFLATEEEE");
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
