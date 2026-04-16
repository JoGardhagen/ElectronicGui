#include "RaspberryGPIO.h"
#include <iostream>

RaspberryGPIO::RaspberryGPIO(const std::string& chipname)
{
    chip = gpiod_chip_open(chipname.c_str());
    if (!chip)
        std::cerr << "Failed to open chip: " << chipname << std::endl;
}

RaspberryGPIO::~RaspberryGPIO()
{
    for (auto& [p, r] : inputRequests)
        if (r) gpiod_line_request_release(r);

    for (auto& [p, r] : outputRequests)
        if (r) gpiod_line_request_release(r);

    if (chip)
        gpiod_chip_close(chip);
}

// =========================
// OUTPUT
// =========================
void RaspberryGPIO::setLED(bool on)
{
    setLEDPin(17, on);
}

void RaspberryGPIO::setLEDPin(int pin, bool on)
{
    if (!chip) return;

    if (outputRequests.find(pin) == outputRequests.end())
    {
        gpiod_line_settings* settings = gpiod_line_settings_new();
        gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);

        gpiod_line_config* config = gpiod_line_config_new();

        unsigned int lines[1];
        lines[0] = (unsigned int)pin;

        gpiod_line_config_add_line_settings(
            config,
            lines,
            1,
            settings
        );

        gpiod_request_config* req_cfg = gpiod_request_config_new();
        gpiod_request_config_set_consumer(req_cfg, "ElectronicGui");

        gpiod_line_request* request =
            gpiod_chip_request_lines(chip, req_cfg, config);

        if (!request)
        {
            std::cerr << "Failed OUTPUT pin " << pin << std::endl;
            return;
        }

        outputRequests[pin] = request;

        gpiod_line_settings_free(settings);
        gpiod_line_config_free(config);
        gpiod_request_config_free(req_cfg);
    }

    //unsigned int lines[1] = { (unsigned int)pin };
    //int values[1] = { on ? 1 : 0 };
    unsigned int line = (unsigned int)pin;

    gpiod_line_value value = {on ? GPIOD_LINE_VALUE_ACTIVE : GPIOD_LINE_VALUE_INACTIVE};
    //int value = on ? 1 : 0;

    gpiod_line_request_set_value(
        outputRequests[pin],
        line,
        value
    );
}

// =========================
// INPUT (SIM + REAL READ)
// =========================
void RaspberryGPIO::setInputPin(int pin, bool value)
{
    inputCache[pin] = value;
}

bool RaspberryGPIO::getInputPin(int pin)
{
    if (!chip) return false;

    if (inputRequests.find(pin) == inputRequests.end())
    {
        gpiod_line_settings* settings = gpiod_line_settings_new();
        gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_INPUT);
        gpiod_line_settings_set_bias(settings, GPIOD_LINE_BIAS_PULL_DOWN);

        gpiod_line_config* config = gpiod_line_config_new();

        unsigned int lines[1];
        lines[0] = (unsigned int)pin;

        gpiod_line_config_add_line_settings(
            config,
            lines,
            1,
            settings
        );

        gpiod_request_config* req_cfg = gpiod_request_config_new();
        gpiod_request_config_set_consumer(req_cfg, "ElectronicGui");

        gpiod_line_request* request =
            gpiod_chip_request_lines(chip, req_cfg, config);

        if (!request)
        {
            std::cerr << "Failed INPUT pin " << pin << std::endl;
            return false;
        }

        inputRequests[pin] = request;

        gpiod_line_settings_free(settings);
        gpiod_line_config_free(config);
        gpiod_request_config_free(req_cfg);
    }

    unsigned int line = { (unsigned int)pin };

    int value = gpiod_line_request_get_value(
        inputRequests[pin],
        line
    );

    return value == 1;
}