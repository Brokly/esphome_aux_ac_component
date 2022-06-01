// Custom ESPHome component for AUX-based air conditioners
// Source code and detailed instructions are available on github: https://github.com/GrKoR/esphome_aux_ac_component

#pragma once
/*
#include <Arduino.h>
#include <stdarg.h>
*/
#include "esphome.h"
#include "frame.h"
#include "frames.h"


namespace esphome {
namespace aux_ac {


class AirCon : public esphome::Component, public esphome::climate::Climate {
    public:
    protected:
        esphome::climate::ClimateTraits traits() override {
            auto traits = climate::ClimateTraits();
            return traits;
        };
        void control(const esphome::climate::ClimateCall &call) override {};
    private:
        Frame frame = {0xBB, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00};
        PingFrame pframe = {0xBB, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
        PingFrame notpframe= {0xBB, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00};
};

} // aux_ac
} // esphome