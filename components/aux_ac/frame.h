#pragma once
#include <Arduino.h>
#include <vector>
#include "frame_parts.h"

namespace esphome {
namespace aux_ac {


class Frame {
    public:
        void load_from_stream() {};
    protected:
        std::vector<uint8_t> data_;

        static const uint8_t AC_PACKET_START_BYTE = 0xBB;

        static const uint8_t OFFSET_START_BYTE = 0;
    private:
}





//******************************************************************************************************************
//******************************************************************************************************************
//******************************************************************************************************************
/*
class Frame {
    public:
        Frame() { this->header_ = this->frame_data(); };
        const uint8_t *frame_data() const { return this->data_.data(); }
        const uint8_t *frame_body() const { return this->data_.data() + OFFSET_DATA; }
        void set_body(const uint8_t *body_data, uint8_t size);

    protected:
        std::vector<uint8_t> data_;
        FrameHeader *header_ = nullptr;
        FrameHeader get_header() const { return FrameHeader(this->data_.data(), this->AC_HEADER_SIZE); }

        uint8_t get_byte_(uint8_t byte_offset) const;
        bool set_byte_(uint8_t byte_offset, uint8_t byte_value) const;

        void delete_body_and_crc_();
        void delete_crc_();
        void append_body_(const uint8_t *body_data, uint8_t size);
        uint8_t body_len_() const;
        void append_crc_();
        uint16_t calc_crc16_() const;

        static const uint8_t AC_HEADER_SIZE = 8;
        static const uint8_t AC_PACKET_START_BYTE = 0xBB;
        static const uint8_t AC_PACKET_ANSWER = 0x80;

        static const uint8_t OFFSET_START_BYTE = 0;
        static const uint8_t OFFSET_FRAME_TYPE = 2;
        static const uint8_t OFFSET_ANSWER = 3;
        static const uint8_t OFFSET_LENGTH = 6;
        static const uint8_t OFFSET_DATA = 8;
                
    private:
}
*/


} // aux_ac
} // esphome