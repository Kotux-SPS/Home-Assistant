<h1> Home-Assistant </h1>
<p>Tento kód slouží k měření teploty pomocí digitálního teplotního senzoru Dallas DS18B20. ESP32 čte teplotu a následně
  ji přes Wi-Fi odesílá pomocí MQTT protokolu do Home Asistantu.
  Soupis použitých komponent</p>
<li><a href="https://www.laskakit.cz/esp32-c3-super-mini-wifi-bluetooth-modul/">ESP32 super mini c3</a></li>
<li><a href="https://dratek.cz/arduino-platforma/1187-teplotni-senzor-digitalni-dallas-ds18b20.html">Dallas DS18B20
    Teplotní čidlo</a></li>
<li><a
    href="https://kitsguru.com/products/4-7k-resistance-1-4-watt-5-tolerance?variant=46112897171708&country=AE&currency=INR&utm_medium=product_sync&utm_source=google&utm_content=sag_organic&utm_campaign=sag_organic">Rezistor
    4,7kΩ</a></li>
<li><a
    href="https://dratek.cz/arduino-platforma/1074-mq2-mq-2-senzor-horlavych-plynu-propanu-metanu-butanu-vodiku.html">MQ-2
    senzor hořlavých plynů</a> (Čip: LM393,Sensor: ZYMQ) </li>
<li><a
    href="https://dratek.cz/arduino-platforma/1074-mq2-mq-2-senzor-horlavych-plynu-propanu-metanu-butanu-vodiku.html">VirtualBoxu
    + Home Assistant</a> </li>

<section>
  <h2>Instalace Home Assistant na VirtualBoxu</h2>
  <p>
    V rámci projektu jsem nasadil <strong>Home Assistant</strong>, který běží
    ve virtuálním stroji pomocí <strong>VirtualBoxu</strong> na Windows.
  </p>
  <p>
    Instalace a základní konfigurace byly provedeny podle oficiální dokumentace
    Home Assistantu. Postup jsem neupravoval a řídil se doporučeným návodem.
  </p>
  <p>
    Zdroj:
   <li> <a href="https://www.home-assistant.io/installation/windows/" target="_blank"> 
      instalační návod Home Assistant na Windows 
    </a> </li>
  </p>
</section>

<section>
  
   <h2> Konfigurace MQTT v Home Assistantu </h2>
 
  <p>
    Pro komunikaci mezi ESP32 a Home Assistantem jsem využil protokol MQTT. V Home Assistantu jsem nainstaloval doplněk
    "Mosquitto broker", který slouží jako MQTT broker pro přijímání a odesílání zpráv.
  </p>
</section>

<section>

  <h2>Funkce Home Assitentu a ESP32</h2>

 <p>
  K ESP32 je připojen senzor
  koncentrace plynu (CO₂). Teplotní čidlo je v Home Assistantu přidáno jako
  samostatná entita. Hodnoty ze senzoru CO₂ jsou odesílány z ESP32 do
  Home Assistantu pomocí home-assistant API.
</p>

<p>
  Data ze senzorů nejsou odesílána nepřetržitě, ale pouze v pravidelných
  časových intervalech. Tento přístup snižuje zatížení sítě a především
  spotřebu energie zařízení, což je důležité zejména u IoT systémů.
</p>

<p>
    Teplotní čidlo komunikuje pomocí MQTT pomocí kódu , který jsme my napsaly. Ten posílá komunikační payload do brokeru s topicem
  <br>  <img src="Home-Assistent/Obrázky/kod-payload.png" alt="vizualizovat" width="400"> </br>
</p>

<p>
  Home Assistant umožňuje snadnou komunikaci s různými zařízeními a senzory
  pomocí MQTT protokolu. Po připojení ESP32 k Wi-Fi síti a odeslání dat
  do MQTT brokeru jsou senzory automaticky detekovány a je možné je
  monitorovat a vizualizovat v uživatelském rozhraní.
</p> 
 

</section>

<section>
<h3>Dashboard</h3>
<p>
   Nastavení Dashboard je velice jednoduché a jde lehce nastavit pomocí návodu od oficiálních zdrojů <a href="https://www.home-assistant.io/dashboards/dashboards/#creating-a-new-dashboard" target="_blank">oficiálních zdrojů </a>

</p>

</section>

#Přidat další sekci ohledně Zobrazení dat a dopsat funkce typu : Upozornění při překročení teploty,Historie měření a nějaký obrázky :D
