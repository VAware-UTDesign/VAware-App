//import header files

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define LED_BUILTIN 2
#define pass (void)0

BLEServer* pServer = NULL;
BLECharacteristic* pLedBuiltinCharacteristic = NULL;

bool deviceConnected = false;
bool oldDeviceConnected = false;

// Generated UUID's for different Charateristics
#define SERVICE_UUID        "e472cea9-3ae8-4d96-951e-7086fe17d416"
#define LED_BUILTIN_UUID    "7abd909a-a9e5-4409-96a9-7aa4fa33426f"


// A call back function to check if device is still connected or not
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };
  
  void onDisconnect(BLEServer* pserver) {
    deviceConnected = false;
  }
};

// Init PINS: assign the pins for the LEDs:
int led_pin_1 = 21;
int led_pin_2 = 19;
int led_pin_3 = 18;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(led_pin_1, OUTPUT);
  pinMode(led_pin_2, OUTPUT);
  pinMode(led_pin_3, OUTPUT);

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
                            BLECharacteristic::PROPERTY_READ    |
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

void loop() {
  //The loop function
  if (deviceConnected) {
    digitalWrite(LED_BUILTIN, HIGH);
    //delay(500);
    std::string value = pLedBuiltinCharacteristic->getValue();
    
    if (value == "1") {
      digitalWrite(led_pin_1, HIGH);
      Serial.println("GREEN");
      delay(10000);
      digitalWrite(led_pin_1, LOW);
      pLedBuiltinCharacteristic->setValue("0");
    }
    else if (value == "2") {
      digitalWrite(led_pin_2, HIGH);
      Serial.println("RED");
      delay(7000);
      digitalWrite(led_pin_2, LOW);
      pLedBuiltinCharacteristic->setValue("0");
    }
    else if (value == "3") {
      digitalWrite(led_pin_3, HIGH);
      Serial.println("BLUE");
      delay(7000);
      digitalWrite(led_pin_3, LOW);
      pLedBuiltinCharacteristic->setValue("0");
    }
    else {
      pass;
    }
//    else if (value == "4") {
//      digitalWrite(led_pin_4, HIGH);
//      delay(7000);
//      digitalWrite(led_pin_3, LOW);
//      pLedBuiltinCharacteristic->setValue("0");
//    }
    
    
  }

  if (!deviceConnected && oldDeviceConnected) {
    //delay(500);
    pServer->startAdvertising();
    Serial.println("started advertising");
    digitalWrite(LED_BUILTIN, LOW);
    oldDeviceConnected = deviceConnected;
  }

  if (deviceConnected && !oldDeviceConnected) {
    oldDeviceConnected = deviceConnected;
  }
}
