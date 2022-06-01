// Custom ESPHome component for AUX-based air conditioners
// Source code and detailed instructions are available on github: https://github.com/GrKoR/esphome_aux_ac_component

#pragma once
#include <Arduino.h>
#include "esphome.h"
#include <stdarg.h>
#include "esphome/core/component.h"
#include "esphome/components/climate/climate.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/core/helpers.h"
#include "frame.h"
#include "frames.h"


namespace esphome {
namespace aux_ac {


class AirCon : public esphome::Component, public esphome::climate::Climate {
    public:
    protected:
    private:
};

} // aux_ac
} // esphome