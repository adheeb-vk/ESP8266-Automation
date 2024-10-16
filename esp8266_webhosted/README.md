## Controlling ESP8266 using Web Interface

In this project you can simply host a web interface on your esp8266's IP address and control the digit though web.

### Step 1:
Copy or Download the code from the repository and open it inside you Arduino IDE. Select your board as Generic ESP8266 Module. If you are trying ESP8266 for the first time you need to install the packages for it. For installing manually you can follow the instructions.

__Open File > Preferences or Control + Comma (Ctrl + ,)__

<img width="345" alt="Screenshot 2024-10-16 161539" src="https://github.com/user-attachments/assets/47759b64-5486-4d55-b619-b6acab997d8d">

___http://arduino.esp8266.com/stable/package_esp8266com_index.json___ Paste this link on the 'Additional Boards Manager URL's' input section click OK.

<img width="605" alt="Screenshot 2024-10-16 161745" src="https://github.com/user-attachments/assets/5d02d396-2554-4505-9168-6d5ad80ef884">

### Step 2:
Edit the code `YOUR_SSID` with your Wifi name and `YOUR_PASSWORD` with your Wifi password.


<img width="314" alt="Screenshot 2024-10-16 165708" src="https://github.com/user-attachments/assets/f70d2fd6-261b-4e3e-a2c7-8e5eae115a92">

### Step 3:
You can make the IP static. ⚠️ Make sure no other device is using the same IP

`local_IP` - IP of your desire (Change only the last three numbers of your router's IP)

`gateway` - Your Wifi router's IP

### Step 4:
Next select the board and upload it. ⚠️ Make sure it is compiling.

For selecting board: __Tools > Board > esp8266 > Generic ESP8266 Module__

<img width="667" alt="Screenshot 2024-10-16 162916" src="https://github.com/user-attachments/assets/daf2c4d8-fa4d-4fb0-b533-fe7f9c74a744">

### Step 5:
After uploading open serial monitor on Arduino IDE (Ctrl + Shift + M). If it is printing with `....` it is trying to connect with your network and After successful connection it will display `connected to Wifi` over there on the serial monitor with the IP address.

<img width="188" alt="Screenshot 2024-10-16 171552" src="https://github.com/user-attachments/assets/a48a9a15-a9a9-4510-b6f4-447ec9b471f9">
 
### Step 6:
Open the browser and enter the IP address printed on the serial monitor. You will be having a web interface like this 👇.

<img width="943" alt="Screenshot 2024-10-16 172010" src="https://github.com/user-attachments/assets/99a23c61-7351-4c06-b451-a0995feb6d86">

### Step 7:
Connect your ESP8266 with LEDs or Relays to Digital Pins `D1`, `D2`, `D3` and `D4`

Now you can control your LED or Relay with the assigned pins (D1, D2, D3, D4) throungh web. ⚠️ You sould connect GND to ESP if Relay is powered externally. If you are connecting LEDS for testing purpose connect the anode(positive) to each digital pins mentioned above and cathode of all to GND.

You can edit the HTML code for better interface.

### HAPPY HACKING 😊



