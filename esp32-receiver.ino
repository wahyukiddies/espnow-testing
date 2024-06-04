#include <esp_now.h>
#include <WiFi.h>

// Struktur data yang diterima
typedef struct struct_message {
    char a[250];  // Sesuaikan panjang pesan sesuai kebutuhan
} struct_message;

struct_message myData;

// Callback ketika pesan diterima
void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Pesan diterima: ");
    Serial.println(myData.a);
}

void setup() {
    // Inisialisasi Serial Monitor
    Serial.begin(115200);

    // Set mode WiFi ke station
    WiFi.mode(WIFI_STA);

    // Inisialisasi ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error inisialisasi ESP-NOW");
        return;
    }

    // Registrasi callback penerimaan pesan
    esp_now_register_recv_cb(onDataRecv);
}

void loop() {
    // Tidak ada yang perlu dilakukan di loop
}
