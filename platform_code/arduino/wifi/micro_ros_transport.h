#include <WiFi.h>
#include <WiFiUdp.h>

struct micro_ros_agent_locator
{
    IPAddress address;
    int port;
};

static inline void set_microros_wifi_transports(char *ssid, char *pass, IPAddress agent_ip, uint16_t agent_port)
{
    WiFi.begin(ssid, pass);
    int i = 0;

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        if (i == 0)
        {
            Serial.println("Connecting to WiFi...");
        } else if (i > 0) {
            Serial.print(".");
        }
        i ++;
        
    }

    if (WiFi.status() == WL_CONNECTED)
    {  
        Serial.println("");
        Serial.println("The connection to the WiFi mwetwork has been STABLISHED!");
    }

    static struct micro_ros_agent_locator locator;
    locator.address = agent_ip;
    locator.port = agent_port;

    rmw_uros_set_custom_transport(
        false,
        (void *)&locator,
        platformio_transport_open,
        platformio_transport_close,
        platformio_transport_write,
        platformio_transport_read);
}