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


namespace esphome {
namespace aux_ac {

using climate::ClimatePreset;
using climate::ClimateTraits;
using climate::ClimateMode;
using climate::ClimateSwingMode;
using climate::ClimateFanMode;    


class Constants {
public:
    static const std::string AC_FIRMWARE_VERSION;

    static const char *const TAG;
    static const std::string MUTE;
    static const std::string TURBO;
    static const std::string CLEAN;
    static const std::string FEEL;
    static const std::string HEALTH;
    static const std::string ANTIFUNGUS;

    /// минимальная и максимальная температура в градусах Цельсия, ограничения самого кондиционера
    static const float AC_MIN_TEMPERATURE;
    static const float AC_MAX_TEMPERATURE;
    /// шаг изменения целевой температуры, градусы Цельсия
    static const float AC_TEMPERATURE_STEP;

    // периодичность опроса кондиционера на предмет изменения состояния
    // изменение параметров с пульта не сообщается в UART, поэтому надо запрашивать состояние, чтобы быть в курсе
    // значение в миллисекундах
    static const uint32_t AC_STATES_REQUEST_INTERVAL;
};

const std::string Constants::AC_FIRMWARE_VERSION = "0.3.0";
const char *const Constants::TAG = "AirCon";

// custom fan modes
const std::string Constants::MUTE = "mute";
const std::string Constants::TURBO = "turbo";

// custom presets
const std::string Constants::CLEAN = "Clean";
//const std::string Constants::FEEL = "Feel";
const std::string Constants::HEALTH = "Health";
const std::string Constants::ANTIFUNGUS = "Antifungus";

// params
const float Constants::AC_MIN_TEMPERATURE = 16.0;
const float Constants::AC_MAX_TEMPERATURE = 32.0;
const float Constants::AC_TEMPERATURE_STEP = 0.5;
const uint32_t Constants::AC_STATES_REQUEST_INTERVAL = 7000;

} // aux_ac
} // esphome