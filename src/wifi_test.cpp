#include "WiFi.h"
#ifdef WIFITEST
String get_encryption_type(wifi_auth_mode_t encryptionType)
{
    switch (encryptionType)
    {
    case (WIFI_AUTH_OPEN):
        return "Open";
    case (WIFI_AUTH_WEP):
        return "WEP";
    case (WIFI_AUTH_WPA_PSK):
        return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
        return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
        return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
        return "WPA2_ENTERPRISE";
    }
}

void setup()
{
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
}

void loop()
{
    Serial.println("uPesy WiFi Scan Demo");
    Serial.println("[*] Scanning WiFi network");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("[*] Scan done");
    if (n == 0)
    {
        Serial.println("[-] No WiFi networks found");
    }
    else
    {
        Serial.println((String) "[+] " + n + " WiFi networks found\n");
        for (int i = 0; i < n; ++i)
        {
            // Print SSID, RSSI and WiFi Encryption for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(" dB) [");
            Serial.print(get_encryption_type(WiFi.encryptionType(i)));
            Serial.println("]");
            delay(10);
        }
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(5000);
}
#endif