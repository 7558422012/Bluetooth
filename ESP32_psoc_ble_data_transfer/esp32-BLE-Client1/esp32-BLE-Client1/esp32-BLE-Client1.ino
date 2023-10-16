#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer* pServer = NULL;
BLEService* pService = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
uint8_t receivedData = 0;

class MyServerCallbacks : public BLEServerCallbacks {
public:
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
    }

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
    }
};

class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() == 1) {
            receivedData = value[0];
            Serial.print("Received data from client: ");
            Serial.println(receivedData);
        }
    }
};

void setup() {
    Serial.begin(115200);

    // Create the BLE Server
    BLEDevice::init("ESP32 Server");
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Create the BLE Service
    pService = pServer->createService(BLEUUID("892F0F6E-AC1F-40EC-A05C-C2159EF2FFCD"));

    // Create a BLE Characteristic
    pCharacteristic = pService->createCharacteristic(
        BLEUUID("D02BBE5F-BF11-496C-BF60-14852F36D817"),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    );

    // Add a descriptor to enable notifications (optional)
    pCharacteristic->addDescriptor(new BLE2902());

    // Set callbacks for the characteristic
    pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

    // Start the service
    pService->start();

    // Start advertising
    pServer->getAdvertising()->start();
    Serial.println("BLE Server started. Waiting for a client connection...");
}

void loop() {
    if (deviceConnected) {
        // You can add your custom code here to respond to client interactions
        // For example, send sensor data to the client when requested
    }
    delay(1000); // Delay a second between loops.
}
