#include <ESP8266WiFi.h>
#include <espnow.h>

// Alamat MAC dari penerima (ESP32)
uint8_t receiverAddress[] = {0xCC, 0xDB, 0xA7, 0x16, 0xCF, 0xA4}; // Ganti dengan alamat MAC ESP32 Anda
// CC:DB:A7:16:CF:A4

// Struktur data yang akan dikirim
typedef struct struct_message {
    char a[250];  // Sesuaikan panjang pesan sesuai kebutuhan
} struct_message;

struct_message myData;

// Callback ketika pesan terkirim
void onDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
    Serial.print("Status pengiriman: ");
    Serial.println(sendStatus == 0 ? "Berhasil" : "Gagal");
}

void setup() {
    // Inisialisasi Serial Monitor
    Serial.begin(115200);

    // Set mode WiFi ke station
    WiFi.mode(WIFI_STA);

    // Inisialisasi ESP-NOW
    if (esp_now_init() != 0) {
        Serial.println("Error inisialisasi ESP-NOW");
        return;
    }

    // Registrasi callback pengiriman pesan
    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_register_send_cb(onDataSent);

    // Registrasi peer (penerima)
    esp_now_add_peer(receiverAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
    // Pesan yang akan dikirim, ganti pesan di sini
    strcpy(myData.a, "palmer !");

    // Mengirimkan pesan
    uint8_t result = esp_now_send(receiverAddress, (uint8_t *) &myData, sizeof(myData));

    if (result == 0) {
        Serial.println("Pesan terkirim");
    } else {
        Serial.println("Error mengirimkan pesan");
    }

    delay(2000); // Kirim pesan setiap 2 detik
}
