#pragma once
/*
#include <Arduino.h>
#include <vector>
*/
#include "frame.h"

namespace esphome {
namespace aux_ac {


class PingFrame : public Frame {
    public:
        PingFrame() = delete;
        PingFrame(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end) : Frame(begin, end) {};
        PingFrame(const uint8_t *data, uint8_t size) : Frame(data, size) {};
        PingFrame(std::initializer_list<uint8_t> list) : Frame(list) {};
        PingFrame(uint8_t size) : Frame(size) {};
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

class CmdFrame : public Frame {
    public:
        CmdFrame() = delete;
        CmdFrame(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end) : Frame(begin, end) {};
        CmdFrame(const uint8_t *data, uint8_t size) : Frame(data, size) {};
        CmdFrame(std::initializer_list<uint8_t> list) : Frame(list) {};
        CmdFrame(uint8_t size) : Frame(size) {};
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
        InfoFrame() = delete;
        InfoFrame(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end) : Frame(begin, end) {};
        InfoFrame(const uint8_t *data, uint8_t size) : Frame(data, size) {};
        InfoFrame(std::initializer_list<uint8_t> list) : Frame(list) {};
        InfoFrame(uint8_t size) : Frame(size) {};
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
        InitFrame() = delete;
        InitFrame(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end) : Frame(begin, end) {};
        InitFrame(const uint8_t *data, uint8_t size) : Frame(data, size) {};
        InitFrame(std::initializer_list<uint8_t> list) : Frame(list) {};
        InitFrame(uint8_t size) : Frame(size) {};
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
        UnknFrame() = delete;
        UnknFrame(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end) : Frame(begin, end) {};
        UnknFrame(const uint8_t *data, uint8_t size) : Frame(data, size) {};
        UnknFrame(std::initializer_list<uint8_t> list) : Frame(list) {};
        UnknFrame(uint8_t size) : Frame(size) {};
        bool is_unknown_frame() {
            if (!this->is_frame_loaded_successfully()) return false;
            return this->has_type(this->AC_FRAME_TYPE_UNKN);
        };
    protected:
        static const uint8_t AC_FRAME_TYPE_UNKN = 0x0b;
    private:
}; // UnknFrame

} // aux_ac
} // esphome
