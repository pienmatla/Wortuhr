#include <Arduino.h>
#include <EEPROM.h>

namespace eeprom {

//------------------------------------------------------------------------------

template <class T> int writeAnything(int ee, const T &value) {
    const byte *p = (const byte *)(const void *)&value;
    uint32_t i;
    for (i = 0; i < sizeof(value); i++)
        EEPROM.write(ee++, *p++);
    return i;
}

//------------------------------------------------------------------------------

template <class T> int readAnything(int ee, T &value) {
    byte *p = (byte *)(void *)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
        *p++ = EEPROM.read(ee++);
    return i;
}

//------------------------------------------------------------------------------

void write() {
    writeAnything(0, G);
    EEPROM.commit();
}

//------------------------------------------------------------------------------

void read() {
    readAnything(0, G);

    Serial.printf("Version   : %s\n", VERSION);
    Serial.printf("Sernr     : %u\n", G.sernr);
    Serial.printf("Programm  : %u\n", G.prog);
    Serial.printf("Conf      : %u\n", G.conf);
    Serial.printf("FgCol.H   : %f\n", G.color[Foreground].hsb.H);
    Serial.printf("FgCol.S   : %f\n", G.color[Foreground].hsb.S);
    Serial.printf("FgCol.V   : %f\n", G.color[Foreground].hsb.B);
    Serial.printf("FgCol.A   : %u\n", G.color[Foreground].alpha);
    Serial.printf("BgCol.H   : %f\n", G.color[Background].hsb.H);
    Serial.printf("BgCol.S   : %f\n", G.color[Background].hsb.S);
    Serial.printf("BgCol.V   : %f\n", G.color[Background].hsb.B);
    Serial.printf("BgCol.A   : %u\n", G.color[Background].alpha);
    Serial.printf("EfCol.H   : %f\n", G.color[Effect].hsb.H);
    Serial.printf("EfCol.S   : %f\n", G.color[Effect].hsb.S);
    Serial.printf("EfCol.V   : %f\n", G.color[Effect].hsb.B);
    Serial.printf("EfCol.A   : %u\n", G.color[Effect].alpha);
    Serial.printf("Zeitserver: %s\n", G.timeserver);
    Serial.printf("Lauftext  : %s\n", G.scrollingText);
    Serial.printf("H6        : %u\n", G.h6);
    Serial.printf("H8        : %u\n", G.h8);
    Serial.printf("H12       : %u\n", G.h12);
    Serial.printf("H16       : %u\n", G.h16);
    Serial.printf("H18       : %u\n", G.h18);
    Serial.printf("H22       : %u\n", G.h22);
    Serial.printf("H24       : %u\n", G.h24);
    Serial.printf("LDR       : %u\n", G.ldr);
    Serial.printf("LDRCal    : %u\n", G.ldrCal);
    Serial.printf("Uhrtype    : %u\n", G.UhrtypeDef);

    Serial.printf("MQTT_State    : %u\n", G.mqtt.state);
    Serial.printf("MQTT_Server    : %s\n", G.mqtt.serverAdress);
    Serial.printf("MQTT_User    : %s\n", G.mqtt.user);
    Serial.printf("MQTT_Pass    : %s\n", G.mqtt.password);
    Serial.printf("MQTT_ClientId    : %s\n", G.mqtt.clientId);
    Serial.printf("MQTT_Topic    : %s\n", G.mqtt.topic);
    Serial.printf("MQTT_Port    : %u\n", G.mqtt.port);

    Serial.printf("autoLdrEnabled    : %u\n", G.autoLdrEnabled);
    Serial.printf("autoLdrBright    : %u\n", G.autoLdrBright);
    Serial.printf("autoLdrDark    : %u\n", G.autoLdrDark);
    Serial.printf("animType    : %u\n", G.animType);
    Serial.printf("Uhrtype    : %u\n", G.animDuration);
    Serial.printf("animDuration    : %u\n", G.animSpeed);
    Serial.printf("animColorize    : %u\n", G.animColorize);
    Serial.printf("animDemo    : %u\n", G.animDemo);

    Serial.printf("bootLedBlink    : %u\n", G.bootLedBlink);
    Serial.printf("bootLedSweep    : %u\n", G.bootLedSweep);
    Serial.printf("bootShowWifi    : %u\n", G.bootShowWifi);
    Serial.printf("bootShowIP    : %u\n", G.bootShowIP);
    Serial.printf("Colortype    : %u\n", G.Colortype);
    Serial.print("OWM_apikey: ");
    Serial.println(G.openWeatherMap.apikey);
    Serial.print("OWM_city  : ");
    Serial.println(G.openWeatherMap.cityid);

    delay(100);
}
} // namespace eeprom
