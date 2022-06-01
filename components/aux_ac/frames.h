#pragma once
#include <Arduino.h>
#include <vector>
#include "frame.h"

namespace esphome {
namespace aux_ac {


class PingFrame : public Frame {
    public:
        // проверяет себя, точно ли он ping-фрейм
        bool is_ping_frame() {
            if (!this->is_frame_loaded_successfully()) return false;
            return this->has_type(this->AC_FRAME_TYPE_PING);
        };

        // перегружаем конвертацию в строку и пока вызываем метода базового класса
        virtual String toString() const override { return Frame::toString(); };
    protected:
        static const uint8_t AC_FRAME_TYPE_PING = 0x01;
    private:
}; // PingFrame

/*
class CmdFrame : public Frame {
    public:
        bool is_cmd_frame() {
            if (!this->is_frame_loaded_successfully()) return false;
            return this->has_type(this->AC_FRAME_TYPE_CMD);
        };
    protected:
        static const uint8_t AC_FRAME_TYPE_CMD = 0x06;
    private:
}; // CmdFrame


class InfoFrame : public Frame {
    public:
        bool is_info_frame() {
            if (!this->is_frame_loaded_successfully()) return false;
            return this->has_type(this->AC_FRAME_TYPE_INFO);
        };
    protected:
        static const uint8_t AC_FRAME_TYPE_INFO = 0x07;
    private:
}; // InfoFrame


class InitFrame : public Frame {
    public:
        bool is_init_frame() {
            if (!this->is_frame_loaded_successfully()) return false;
            return this->has_type(this->AC_FRAME_TYPE_INIT);
        };
    protected:
        static const uint8_t AC_FRAME_TYPE_INIT = 0x09;
    private:
}; // InitFrame


class UnknFrame : public Frame {
    public:
        bool is_unknown_frame() {
            if (!this->is_frame_loaded_successfully()) return false;
            return this->has_type(this->AC_FRAME_TYPE_UNKN);
        };
    protected:
        static const uint8_t AC_FRAME_TYPE_UNKN = 0x0b;
    private:
}; // UnknFrame
*/

} // aux_ac
} // esphome
