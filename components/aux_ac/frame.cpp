#include "frame.h"

namespace esphome {
namespace aux_ac {

        void _debugMsg(const String &msg, uint8_t dbgLevel = ESPHOME_LOG_LEVEL_DEBUG, unsigned int line = 0, ... ){
            if (dbgLevel < ESPHOME_LOG_LEVEL_NONE) dbgLevel = ESPHOME_LOG_LEVEL_NONE;
            if (dbgLevel > ESPHOME_LOG_LEVEL_VERY_VERBOSE) dbgLevel = ESPHOME_LOG_LEVEL_VERY_VERBOSE;
            
            if (line == 0) line = __LINE__; // если строка не передана, берем текущую строку

            va_list vl;
            va_start(vl, line);
            esp_log_vprintf_(dbgLevel, Constants::TAG, line, msg.c_str(), vl);
            va_end(vl);
        }


        // UART wrappers: peek
        int peek() {
            uint8_t data;
            if (!_ac_serial->peek_byte(&data)) return -1;
            return data;
        }

        // UART wrappers: read
        int read() {
            uint8_t data;
            if (!_ac_serial->read_byte(&data)) return -1;
            return data;
        }


// загружает фрейм из стрима (UART)
// все данные до стартового байта пропускает
bool Frame::load_from_stream(Stream *stream) {
    if (stream == nullptr) return false;

    while (stream->available()) {
        const uint8_t data = stream->read();
        const uint8_t length = this->data_.size();
        if (length == OFFSET_START_BYTE && data != AC_PACKET_START_BYTE) {
            // какой-то левый байт
            continue;
        }
        if (length == OFFSET_LENGTH && data <= OFFSET_DATA) {
            this->m_data.clear();
            continue;
        }
        this->m_data.push_back(data);
        if (length > OFFSET_DATA && length >= this->m_data[OFFSET_LENGTH]) {
            if (this->isValid())
            return true;
            this->m_data.clear();
        }
    }
    return false;
}



/*
// возвращает байт из данных с проверкой смещения на допустимость
uint8_t Frame::get_byte_(uint8_t byte_offset) {
    // TODO: продумать отработку ошибок! Сейчас возвращает 0x00, что пересекается с нормальными данными.
    if (byte_offset > this->data_.size_()) return 0x00;

    return this->data_[byte_offset];
}


// устанавливает значение байта
// если смещение выходит за пределы допустимого диапазона, то возвращает false. Иначе - true.
bool Frame::set_byte_(uint8_t byte_offset, uint8_t byte_value) {
    if (byte_offset > this->data_.size_()) return false;

    this->data_[byte_offset] = byte_value;
    return true;
}


// устанавливает тело фрейму: старые тело и CRC удаляет, добавляет новое тело, пересчитывает и добавляет CRC
void Frame::set_body(const uint8_t *body_data = nullptr, uint8_t size = 0) {
  this->delete_body_and_crc_();
  if (body_data != nullptr && size != 0) {
    this->append_body_(body_data, size);
  }
  this->data_[OFFSET_LENGTH] = this->data_.size() - OFFSET_DATA;
  this->append_crc_();
}


// удаляет тело фрейма, если это тело есть
// заодно удаляет и CRC
void Frame::delete_body_and_crc_() {
    this->data_.erase(this->data_.begin() + OFFSET_DATA, this->data_.end());
}


// удаляет из фрейма CRC, если она есть
void Frame::delete_crc_(){
    this->data_.erase(this->data_.begin() + OFFSET_DATA + this->body_len_(), this->data_.end());
}


// добавляет фрейму тело, CRC не пересчитывает и не добавляет
void Frame::append_body_(const uint8_t *body_data, uint8_t size) {
    std::copy(body_data, body_data + size, std::back_inserter(this->data_));
}


// возвращает размер тела в байтах
uint8_t Frame::body_len_() const {
    return this->data_[OFFSET_LENGTH];
}


// добавляет фрейму контрольную сумму
void Frame::append_crc_() {
    uint16_t crc16 = this->calc_crc16_();
            pack->crc->crc[0] = crc.crc[1];
            pack->crc->crc[1] = crc.crc[0];

    this->data_.push_back(this->m_calcCS());
}


// рассчитывает и возвращает CRC16 для фрейма
uint16_t Frame::calc_crc16_() {
    uint32_t crc = 0;
    bool extra_byte_appended = false;

    // для расчета CRC16 длина данных должна быть четная
    if ((this->data_.size() % 2) == 1) {    // если размер фрейма нечетный,
        this->data_.push_back(0x00);        // значит надо добавить в конец нулевой байт (и не забыть после расчета его удалить)
        extra_byte_appended = true;         // помечаем себе, что добавили байт
    }

    // рассчитываем CRC16
    uint32_t word = 0;
    for (uint8_t i=0; i < this->data_.size(); i+=2){
        word = (this->data_[i] << 8) + this->data_[i+1];
        crc += word;
    }
    crc = (crc >> 16) + (crc & 0xFFFF);
    crc = ~ crc;

    if (extra_byte_appended) this->data_.pop_back();    // не забываем удалять лишний байты

    return crc & 0xFFFF;
};
*/

} // aux_ac
} // esphome
