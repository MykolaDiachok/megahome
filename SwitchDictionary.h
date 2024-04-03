class SwitchDictionary {
private:
    struct SwitchItem {
        int key;
        int pinNumber;
    };
    
    PinItem items[20]; // Adjust size according to your needs
    int itemCount = 0;

public:
    // Add a pin number and automatically assign a key
    void add(int pinNumber) {
        if (itemCount < sizeof(items) / sizeof(items[0])) {
            items[itemCount].key = itemCount;
            items[itemCount].pinNumber = pinNumber;
            itemCount++;
        }
    }

    // Get pin number by key
    int getPinByKey(int key) {
        for (int i = 0; i < itemCount; i++) {
            if (items[i].key == key) {
                return items[i].pinNumber;
            }
        }
        return -1; // Key not found
    }

    // Get key by pin number
    int getKeyByPin(int pinNumber) {
        for (int i = 0; i < itemCount; i++) {
            if (items[i].pinNumber == pinNumber) {
                return items[i].key;
            }
        }
        return -1; // Pin number not found
    }
};