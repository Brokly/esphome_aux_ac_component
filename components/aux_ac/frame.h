#pragma once
#include <Arduino.h>
#include <vector>
#include "esphome.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/log.h"

namespace esphome {
namespace aux_ac {


// направление фрейма
enum FrameDirection {
    FDIR_UNKNOWN    = 0,  // неизвестное направление
    FDIR_INCOMING   = 1,  // входящий фрейм
    FDIR_OUTCOMING  = 2,  // исходящий фрейм
};


// состояние фрейма
enum FrameState {
    FSTATE_EMPTY                    = 0b00000000,   // пустой, ничего не загружали
    FSTATE_COMPLETE_WO_ERRORS       = 0b00000101,   // полностью загружен, ошибок нет
    FSTATE_COMPLETE_WITH_ERRORS     = 0b00000111,   // полностью загружен, ошибочен
    FSTATE_INCOMPLETE_WO_ERRORS     = 0b00000100,   // не загружен полностью, ошибок нет, ждём остальные байты
    FSTATE_INCOMPLETE_WITH_ERRORS   = 0b00000110,   // не загружен полностью, есть ошибки (скорее всего таймаут)
};


class Frame {
    public:
        Frame() = delete;
        Frame(std::vector<uint8_t>::const_iterator begin, std::vector<uint8_t>::const_iterator end) : data_(begin, end) {};
        Frame(const uint8_t *data, uint8_t size) : data_(data, data + size) {};
        Frame(std::initializer_list<uint8_t> list) : data_(list) {};
        Frame(uint8_t size) : data_(size, 0) {};

        FrameState get_frame_state() { return this->frame_state_; };        // возврат состояния фрейма:
        bool is_frame_loaded_successfully() { return this->get_frame_state() == FSTATE_COMPLETE_WO_ERRORS; };  // проверка на успешность загрузки фрейма (нет ошибок, все данные загружены)
        uint8_t get_bytes_loaded() { return this->bytes_loaded_; };         // возврат числа уже загруженных байт
        // не знаю, надо ли => // возврат числа байт, оставшихся для полной загрузки фрейма

        FrameDirection get_frame_direction() { return this->frame_dir_; };  // тип фрейма (входящий, исходящий, не известно)

        //bool load_frame(esphome::uart::UARTComponent *serial) {};     // загрузка фрейма из UART
        //bool load_frame(std::vector<uint8_t> vector) {};    // загрузка фрейма из массива
        //bool load_frame(std::vector<uint8_t> vector) {};    // загрузка фрейма из вектора

        // возврат заголовка фрейма (целиком или отдельных байт/бит)
        // установка заголовка фрейма (целиком или отдельных байт/бит)
        void set_type(uint8_t frame_type) { this->data_[this->OFFSET_FRAME_TYPE] = frame_type; }    // устанавливает тип фрейму
        bool has_type(uint8_t frame_type) const { return this->has_byte(this->OFFSET_FRAME_TYPE, frame_type); }  // проверяет тип фрейма

        // проверка CRC фрейма
        // расчет CRC для фрейма
        // присвоение фрейму CRC (удаление старой CRC, расчет, добавление новой CRC)

        // удаление CRC фрейма
        // удаление тела и CRC фрейма

        // добавить тело фрейму (удаляет тело и CRC, добавляет новое тело, обновляет заголовок):
        //      - добавляет из массива
        //      - добавляет из вектора

        // методы работы с байтами
        uint8_t get_byte(uint8_t offset) { return this->decode_byte_uint8(offset, 0xFF); };  // 
        bool has_byte(uint8_t offset, uint8_t value) { return this->get_byte(offset) == value; };  // проверяет соответствие байта
        uint8_t decode_byte_uint8(uint8_t offset, uint8_t mask = 0xFF) { return this->get_value(offset, mask, 0x00); };  // декодировать байт в цифровое значение (смещение байта, маска)
        // установить значение в байте (смещение, маска, значение)

        // методы работы с булевыми значениями
        bool decode_byte_bool(uint8_t offset, uint8_t mask = 0xFF) { return false; }; // декодировать байт в булево значение (смещение байта, маска на 1 бит)
        // установить бит в байте (смещение, маска, булево значение)

        // проверка фрейма на корректность (наследуемая функция):
        //      - проверка стартового байта
        //      - соответствиt фактической длины тела заголовку
        //      - корректность CRC
        //      - проверка по маске фрейма (если байт длины в заголовке указан как не значащий, значит длина тела может быть любой)
        // установить маску фрейма (какие байты/биты значимы для проверки)
        // прочитать маску фрейма (какие байты/биты значимы для проверки)

        virtual String toString() const {};    // конвертирует фрейм в строку, классами-наследниками может перегружаться
    protected:
        // константы
        static const uint8_t AC_PACKET_START_BYTE = 0xBB;
        static const uint8_t AC_PACKET_ANSWER = 0x80;

        static const uint8_t OFFSET_START_BYTE = 0;
        static const uint8_t OFFSET_FRAME_TYPE = 2;
        static const uint8_t OFFSET_ANSWER = 3;
        static const uint8_t OFFSET_LENGTH = 6;
        static const uint8_t OFFSET_DATA = 8;

        // данные фрейма (заголовок, тело, контрольная сумма)
        std::vector<uint8_t> data_;

        FrameDirection frame_dir_ = FDIR_UNKNOWN;
        void set_frame_direction_(FrameDirection _frame_dir) { frame_dir_ = _frame_dir; };    // присваиваем направление фрейма, через функцию, т.к. возможно позже понадобится что-то менять
        // загружает направление фрейма из его заголовка (некоторые типы фреймов могут быть только входящими или только исходящими)
        virtual bool parse_frame_direction_from_header();

        FrameState frame_state_ = FSTATE_EMPTY;
        uint8_t bytes_loaded_ = 0;

        // низкоуровневая работа с байтами в данных фрейма
        // получение значения из байта: вначале применяем маску, потом смещаем значение
        uint8_t get_value(uint8_t offset, uint8_t mask = 0xFF, uint8_t shift = 0x00) const {
            return (this->data_[offset] & mask) >> shift;
        }
        void set_value(uint8_t offset, uint8_t value, uint8_t mask = 0xFF, uint8_t shift = 0x00) {
            this->data_[offset] &= ~(mask << shift);
            this->data_[offset] |= (value << shift);
        }
        void set_mask(uint8_t offset, bool state, uint8_t mask = 0xFF) { this->set_value(offset, state ? mask : 0, mask); }
    private:
};





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