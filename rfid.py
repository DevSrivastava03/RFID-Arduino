import serial
import pygame
import time
import re

pygame.mixer.init()

serial_port = "/dev/tty.usbmodem1101" 
baud_rate = 9600

try:
    ser = serial.Serial(serial_port, baud_rate, timeout=1)
    print(f"Connected to {serial_port}")
except:
    print(f"⚠️ ERROR: Could not open Serial Port {serial_port}")
    exit()

RFID_SOUNDS = {
    "4d70b18f6180": "sounds/garlic.mp3",
    "4a79a6c5f6180": "sounds/tomato.mp3",
    "4c7bfb18f6180": "sounds/corn.mp3",
    "44e40b18f6180": "sounds/carrot.mp3",
    "4a06db28f6180": "sounds/potato.mp3",
    "42b3db78f6180": "sounds/eggplant.mp3",
    "43dea374f6180": "sounds/pepper.mp3",
    "44c9b18f6180": "sounds/egg.mp3",
    "46524b28f6181": "STOP",  
    "410eeb68f6180": "STOP", 
}

def play_audio(file_path):
    """Play the assigned audio file for the scanned RFID tag."""
    if file_path == "STOP":
        pygame.mixer.stop()
        print("🛑 All sounds stopped!")
    else:
        try:
            pygame.mixer.Sound(file_path).play()
            print(f"🔊 Playing: {file_path}")
            time.sleep(1) 
        except Exception as e:
            print(f"⚠️ Error playing {file_path}: {e}")

uid_pattern = re.compile(r'Detected Tag UID: ([0-9A-Fa-f]+)')

while True:
    try:
        if ser.in_waiting > 0:
            rfid_data = ser.readline().decode(errors='ignore').strip()
            print(f"🔹 Raw data: {rfid_data}")

            # Try to extract UID from the Arduino output
            uid_match = uid_pattern.search(rfid_data)
            
            if uid_match:
                tag_uid = uid_match.group(1).lower()  # Extract UID and convert to lowercase
                print(f"🔹 Extracted UID: {tag_uid}")
                
                if tag_uid in RFID_SOUNDS:
                    play_audio(RFID_SOUNDS[tag_uid])
                else:
                    print("❌ Unknown Tag - No Sound Assigned")
            
    except KeyboardInterrupt:
        print("🔴 Stopping...")
        break

ser.close()
