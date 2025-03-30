//// RFID AND MUSIC 
#include <MFRC522.h>
#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

// MIDI note mappings for each tag (C4 octave)
int garlicNote = 60;  // C4 (Middle C)
int tomatoNote = 62;  // D4
int cornNote = 64;    // E4
int carrotNote = 65;  // F4
int potatoNote = 67;  // G4
int eggplantNote = 69; // A4
int pepperNote = 71;  // B4
int eggNote = 72;     // C5 (one octave above Middle C)

void setup() {
    Serial.begin(115200); // Start serial communication
    SPI.begin();          // Init SPI bus
    mfrc522.PCD_Init();   // Init MFRC522
    Serial.println("Scan an RFID tag...");
}

void loop() {
    if (!mfrc522.PICC_IsNewCardPresent()) return;
    if (!mfrc522.PICC_ReadCardSerial()) return;

    Serial.print("Detected Tag UID: ");
    String tagUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        tagUID += String(mfrc522.uid.uidByte[i], HEX);
    }
    tagUID.toLowerCase();  // Convert to lowercase

    Serial.println(tagUID);

    int noteToPlay = -1; // Default to no note

    // Check which tag was scanned and set the note
    if (tagUID.equalsIgnoreCase("4D70B18F6180")) {
        Serial.println("Tag Name: 🧄 Garlic 🧄");
        noteToPlay = garlicNote;
    } else if (tagUID.equalsIgnoreCase("4A79A6C5F6180")) {
        Serial.println("Tag Name: 🍅 Tomato 🍅");
        noteToPlay = tomatoNote;
    } else if (tagUID.equalsIgnoreCase("4C7BFB18F6180")) {
        Serial.println("Tag Name: 🌽 Corn 🌽");
        noteToPlay = cornNote;
    } else if (tagUID.equalsIgnoreCase("44E40B18F6180")) {
        Serial.println("Tag Name: 🥕 Carrot 🥕");
        noteToPlay = carrotNote;
    } else if (tagUID.equalsIgnoreCase("4A06DB28F6180")) {
        Serial.println("Tag Name: 🥔 Potato 🥔");
        noteToPlay = potatoNote;
    } else if (tagUID.equalsIgnoreCase("42B3DB78F6180")) {
        Serial.println("Tag Name: 🍆 Eggplant 🍆");
        noteToPlay = eggplantNote;
    } else if (tagUID.equalsIgnoreCase("43DEA374F6180")) {
        Serial.println("Tag Name: 🌶 Pepper 🌶");
        noteToPlay = pepperNote;
    } else if (tagUID.equalsIgnoreCase("44C9B18F6180")) {
        Serial.println("Tag Name: 🥚 Egg 🥚");
        noteToPlay = eggNote;
    } else {
        Serial.println("Unknown Tag");
    }

    // If a valid note is found, play it
    if (noteToPlay != -1) {
        playMidiNote(noteToPlay);
    }

    mfrc522.PICC_HaltA(); // Stop communication with the tag
}

void playMidiNote(int note) {
    Serial.write((uint8_t)0x90);  // Note On (MIDI channel 1)
    Serial.write((uint8_t)note);  // Note number (0-127)
    Serial.write((uint8_t)100);   // Velocity (100 = medium volume)

    delay(500); // Hold note for 0.5s

    Serial.write((uint8_t)0x80);  // Note Off (MIDI channel 1)
    Serial.write((uint8_t)note);  // Note number (0-127)
    Serial.write((uint8_t)0);     // Velocity 0 = stop note
}


// #include <MFRC522.h>
// #include <MFRC522Extended.h>
// #include <deprecated.h>
// #include <require_cpp11.h>

// #include <SPI.h>
// #include <MFRC522.h>

// #define SS_PIN 10
// #define RST_PIN 9

// MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

// void setup() {
//     while (millis() < 5000); // wait up to 5 seconds.
//     Serial.begin(9600); // Start serial communication
//     SPI.begin();        // Init SPI bus
//     mfrc522.PCD_Init(); // Init MFRC522
//     Serial.println("Scan an RFID tag...");
// }

// void loop() {
//     if (!mfrc522.PICC_IsNewCardPresent()) return;
//     if (!mfrc522.PICC_ReadCardSerial()) return;

//     Serial.print("Detected Tag UID: ");
// String tagUID = "";
// for (byte i = 0; i < mfrc522.uid.size; i++) {
//     tagUID += String(mfrc522.uid.uidByte[i], HEX);
// }
// Serial.println(tagUID);

// tagUID.toLowerCase();  // Normalize case

// // Check which tag was scanned
// if (tagUID.equalsIgnoreCase("4D70B18F6180")) {
//     Serial.println("Tag Name: 🧄 Garlic 🧄");
// } else if (tagUID.equalsIgnoreCase("4A79A6C5F6180")) {
//     Serial.println("Tag Name: 🍅 Tomato 🍅");
// } else if (tagUID.equalsIgnoreCase("4C7BFB18F6180")) {
//     Serial.println("Tag Name: 🌽 Corn 🌽");
// } else if (tagUID.equalsIgnoreCase("44E40B18F6180")) {
//     Serial.println("Tag Name: 🥕 Carrot 🥕");
// } else if (tagUID.equalsIgnoreCase("4A06DB28F6180")) {
//     Serial.println("Tag Name: 🥔 Potato 🥔");
// } else if (tagUID.equalsIgnoreCase("42B3DB78F6180")) {
//     Serial.println("Tag Name: 🍆 Eggplant 🍆");
// } else if (tagUID.equalsIgnoreCase("43DEA374F6180")) {
//     Serial.println("Tag Name: 🌶 Pepper 🌶");
// } else if (tagUID.equalsIgnoreCase("44C9B18F6180")) {
//     Serial.println("Tag Name: 🥚 Egg 🥚");
// } else {
//     Serial.println("Unknown Tag");
// }

//     mfrc522.PICC_HaltA(); // Stop communication with the tag
// }


///TRIAL

// #include <SPI.h>
// #include <MFRC522.h>

// #define SS_PIN 10   // Can be any digital pin (SDA / SS pin)
// #define RST_PIN 5   // Reset pin (you updated this to Pin 5)

// MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create an MFRC522 instance

// void setup() {
//     Serial.begin(115200);  // Start serial communication
//     while (!Serial);       // Wait for Serial Monitor to open (important for Leonardo)
    
//     SPI.begin();           // Initialize SPI bus (uses the ICSP pins for SCK, MOSI, MISO)
//     mfrc522.PCD_Init();    // Initialize MFRC522
//     Serial.println("Scan an RFID tag...");
// }

// void loop() {
//     if (!mfrc522.PICC_IsNewCardPresent()) {
//         return;  // No new card detected
//     }

//     if (!mfrc522.PICC_ReadCardSerial()) {
//         return;  // Failed to read the card
//     }

//     Serial.print("Scanned UID: ");
//     String tagUID = "";
//     for (byte i = 0; i < mfrc522.uid.size; i++) {
//         tagUID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""); // Add leading zero if needed
//         tagUID += String(mfrc522.uid.uidByte[i], HEX);
//     }
//     Serial.println(tagUID);  // Print UID of the tag
//     mfrc522.PICC_HaltA();    // Stop communication with the tag
// }


// #include <SPI.h>
// #include <MFRC522.h>

// #define SS_PIN 10  // Can be any digital pin
// #define RST_PIN 9

// MFRC522 mfrc522(SS_PIN, RST_PIN);

// void setup() {
//     while (millis() < 5000); // wait up to 5 seconds.
//     Serial.begin(115200);
//     SPI.begin();         // Initialize SPI (Leonardo uses ICSP header)
//     mfrc522.PCD_Init();  // Initialize RFID module
//     Serial.println("Scan an RFID tag...");
// }

// void loop() {
//     if (!mfrc522.PICC_IsNewCardPresent()) return;
//     if (!mfrc522.PICC_ReadCardSerial()) return;

//     Serial.print("Tag UID: ");
//     for (byte i = 0; i < mfrc522.uid.size; i++) {
//         Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//         Serial.print(mfrc522.uid.uidByte[i], HEX);
//     }
//     Serial.println();
//     delay(1000);
// }

