<h1 align="center">🍄 IoT Based Mushroom Environment Monitoring System</h1>
<p align="center">

<img src="https://img.shields.io/badge/ESP32-Microcontroller-red?style=for-the-badge&logo=espressif&logoColor=white">

<img src="https://img.shields.io/badge/Arduino-IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white">

<img src="https://img.shields.io/badge/IoT-Connected%20System-blue?style=for-the-badge&logo=internetofthings&logoColor=white">

<img src="https://img.shields.io/badge/Blynk-IoT%20Platform-23C48E?style=for-the-badge">

<img src="https://img.shields.io/badge/Platform-ESP32-green?style=for-the-badge">

<img src="https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white">

</p>
<p align="center">
An IoT-based environmental monitoring system designed to maintain suitable conditions for mushroom cultivation.
The system continuously monitors environmental parameters and allows users to view the data remotely through a
mobile dashboard while also displaying real-time information on an LCD screen.
</p>

<hr>

<h2>📌 Project Overview</h2>

<p>
Mushroom cultivation requires maintaining specific environmental conditions such as humidity,
temperature, soil moisture, and air quality. Monitoring these factors manually can be difficult
and inconsistent.
</p>

<p>
This project introduces a <b>smart monitoring system</b> that automatically collects environmental
data and displays it both locally and remotely using an IoT platform.
</p>

<ul>
<li>Monitor environmental conditions in real time</li>
<li>Display sensor data on an LCD screen</li>
<li>Send live data to a mobile dashboard</li>
<li>Allow remote control of a ventilation system</li>
<li>Maintain a stable growing environment</li>
</ul>

<hr>

<h2>⚙️ System Features</h2>

<ul>
<li>🌡 Real-time temperature monitoring</li>
<li>💧 Humidity monitoring</li>
<li>🌱 Soil moisture monitoring</li>
<li>🌫 Gas level monitoring</li>
<li>📟 20x4 LCD display output</li>
<li>📱 Remote monitoring with Blynk IoT</li>
<li>🌀 Remote fan control through mobile application</li>
</ul>

<hr>

<h2>💻 System Architecture</h2>

<p>
The system is built using an <b>ESP32 microcontroller</b> which acts as the central controller.
Multiple environmental sensors collect data and send it to the ESP32. The microcontroller
processes the data, displays it on an LCD screen, and uploads the information to the
Blynk IoT cloud platform for remote monitoring.
</p>

<hr>

<h2>📚 Libraries Used</h2>

<ul>
<li><b>WiFi.h</b> – Handles WiFi connection for the ESP32</li>
<li><b>BlynkSimpleEsp32.h</b> – Enables communication with the Blynk IoT platform</li>
<li><b>Wire.h</b> – Enables I2C communication</li>
<li><b>LiquidCrystal_I2C.h</b> – Controls the 20×4 LCD display</li>
<li><b>DHT.h</b> – Reads temperature and humidity data from the DHT22 sensor</li>
</ul>

<hr>

<h2>🔑 Blynk Configuration</h2>

<p>
The system connects to a Blynk IoT project using the following identifiers:
</p>

<ul>
<li><b>Template ID</b> – Identifies the Blynk project template</li>
<li><b>Template Name</b> – Name of the IoT dashboard</li>
<li><b>Auth Token</b> – Authentication key linking the device to Blynk cloud</li>
</ul>

<p>
These parameters must be defined before including the Blynk library in the code.
</p>

<hr>

<h2>🌐 WiFi Configuration</h2>

<p>
The ESP32 connects to the internet using a WiFi network. The network credentials
are defined in the code using the following variables:
</p>

<ul>
<li>WiFi SSID – Network name</li>
<li>WiFi Password – Network password</li>
</ul>

<p>
Once connected, the device communicates with the Blynk cloud server and starts
sending environmental data.
</p>

<hr>

<h2>🖥 LCD Display</h2>

<p>
A 20×4 I2C LCD display is used to show real-time environmental data.
The display allows users to monitor the system locally without opening the mobile application.
</p>

<table border="1">
<tr>
<th>Row</th>
<th>Information Displayed</th>
</tr>
<tr>
<td>Row 1</td>
<td>Humidity value</td>
</tr>
<tr>
<td>Row 2</td>
<td>Temperature value</td>
</tr>
<tr>
<td>Row 3</td>
<td>Soil moisture percentage and water status</td>
</tr>
<tr>
<td>Row 4</td>
<td>Gas sensor reading</td>
</tr>
</table>

<hr>

<h2>🌡 Temperature and Humidity Monitoring</h2>

<p>
A DHT22 sensor measures environmental temperature and humidity.
These values are continuously read by the ESP32 and updated every second.
</p>

<ul>
<li>Temperature is measured in degrees Celsius</li>
<li>Humidity is measured in percentage</li>
</ul>

<hr>

<h2>🌱 Soil Moisture Monitoring</h2>

<p>
The soil moisture sensor provides an analog value between 0 and 4095.
The code converts this raw value into a percentage to make the data easier to interpret.
</p>

<p>
A higher percentage indicates wetter soil while a lower value indicates dry soil.
</p>

<hr>

<h2>🌫 Gas Level Monitoring</h2>

<p>
The MQ-7 gas sensor detects gas levels in the environment.
If the sensor reading exceeds the predefined threshold value, the system marks the condition as gas detected.
</p>

<hr>

<h2>📱 Blynk Dashboard Integration</h2>

<p>
The Blynk IoT platform allows users to monitor environmental conditions remotely.
The ESP32 sends sensor data to the Blynk cloud using virtual pins.
</p>

<table border="1">
<tr>
<th>Virtual Pin</th>
<th>Function</th>
</tr>
<tr>
<td>V1</td>
<td>Fan control switch</td>
</tr>
<tr>
<td>V5</td>
<td>Humidity value</td>
</tr>
<tr>
<td>V6</td>
<td>Temperature value</td>
</tr>
<tr>
<td>V7</td>
<td>Soil moisture percentage</td>
</tr>
<tr>
<td>V8</td>
<td>Gas sensor raw value</td>
</tr>
<tr>
<td>V9</td>
<td>Water detection indicator</td>
</tr>
<tr>
<td>V10</td>
<td>Gas detection indicator</td>
</tr>
</table>

<hr>

<h2>🌀 Fan Control System</h2>

<p>
The system includes a relay module connected to a fan.
The relay allows the fan to be controlled remotely from the Blynk mobile application.
</p>

<p>
When the user toggles the fan switch in the app, the command is sent to the ESP32,
which activates or deactivates the relay accordingly.
</p>

<hr>

<h2>⏱ Automated Monitoring Loop</h2>

<p>
The program uses a timer system to perform sensor readings at regular intervals.
Every <b>1 second</b>, the system performs the following tasks:
</p>

<ul>
<li>Read sensor data</li>
<li>Update the LCD display</li>
<li>Send data to the Blynk dashboard</li>
</ul>

<p>
This ensures continuous monitoring of the mushroom cultivation environment.
</p>

<hr>

<h2>⚙ System Initialization</h2>

<p>
When the device starts, the setup function performs several initialization steps:
</p>

<ul>
<li>Start serial communication</li>
<li>Initialize the LCD display</li>
<li>Initialize sensors</li>
<li>Configure input and output pins</li>
<li>Connect to WiFi</li>
<li>Connect to the Blynk cloud server</li>
<li>Start the periodic monitoring timer</li>
</ul>

<hr>

<h2>🔄 Main Program Loop</h2>

<p>
The main loop of the program runs continuously and performs two key tasks:
</p>

<ul>
<li><b>Blynk.run()</b> – Maintains connection with the Blynk cloud server</li>
<li><b>timer.run()</b> – Executes scheduled tasks such as sensor reading</li>
</ul>

<p>
This design ensures that the system continuously monitors environmental conditions
while remaining connected to the IoT dashboard.
</p>

<hr>

<h2>🚀 Future Improvements</h2>

<ul>
<li>Machine learning integration for predicting mushroom growth</li>
<li>Automated humidity and climate control</li>
<li>Smart alert notifications</li>
<li>Environmental data logging and analytics</li>
<li>Advanced IoT dashboard visualization</li>
</ul>

<hr>

<h2>👨‍💻 Team</h2>

<p><b>Team Mycelium</b></p>

<ul>
<li>Tanvir</li>
<li>Proma</li>
<li>Saiful</li>
<li>Redoy</li>
<li>Mehedi</li>
<li>Akash</li>
</ul>

<hr>

<h2>🌍 Sustainability Impact</h2>

<p>
This project supports sustainable agriculture and aligns with several
United Nations Sustainable Development Goals (SDGs):
</p>

<ul>
<li>🌾 Zero Hunger</li>
<li>🏗 Industry, Innovation and Infrastructure</li>
<li>♻ Responsible Consumption and Production</li>
<li>🌍 Climate Action</li>
</ul>

<hr>

<h2>⭐ Support</h2>

<p>
If you find this project useful:
</p>

<ul>
<li>⭐ Star the repository</li>
<li>🍴 Fork the project</li>
<li>🤝 Contribute improvements</li>
</ul>
