#include "RaspberryGPIO.h"
#include <iostream>

RaspberryGPIO::RaspberryGPIO(const std::string& chipname) {
    chip = gpiod_chip_open(chipname.c_str());
    if (!chip) {
        std::cerr << "Failed to open chip: " << chipname << std::endl;
    }
}

RaspberryGPIO::~RaspberryGPIO() {
    for (auto& [pin, req] : requests) {
        if(req) gpiod_line_request_release(req);
    }
    if(chip) gpiod_chip_close(chip);
}

void RaspberryGPIO::setLED(bool on) {
    setLEDPin(17, on); // default test
}

void RaspberryGPIO::setLEDPin(int pin, bool on) {
    if (!chip) return;

    // Om vi inte redan requestat pinnen → gör det
    if (requests.find(pin) == requests.end()) {

        gpiod_line_settings* settings = gpiod_line_settings_new();
        gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);

        gpiod_line_config* config = gpiod_line_config_new();
        gpiod_line_config_add_line_settings(config, &pin, 1, settings);

        gpiod_request_config* req_cfg = gpiod_request_config_new();
        gpiod_request_config_set_consumer(req_cfg, "ElectronicGui");

        gpiod_line_request* request =
            gpiod_chip_request_lines(chip, req_cfg, config);

        if (!request) {
            std::cerr << "Failed to request pin " << pin << std::endl;
            return;
        }

        requests[pin] = request;

        gpiod_line_settings_free(settings);
        gpiod_line_config_free(config);
        gpiod_request_config_free(req_cfg);
    }

    // Sätt värdet (DETTA är din fungerande funktion)
    gpiod_line_request_set_value(
        requests[pin],
        pin,
        on ? GPIOD_LINE_VALUE_ACTIVE : GPIOD_LINE_VALUE_INACTIVE
    );
}