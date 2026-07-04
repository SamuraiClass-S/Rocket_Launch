#include "krpc/encoder.hpp"

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/wire_format_lite.h>

#include <cstddef>
#include <cstdint>  // Додано для стандартних типів (uint32_t, int64_t тощо)
#include <string>

#include "krpc/error.hpp"

// Змінюємо pb на gpb, щоб уникнути конфлікту з внутрішніми неймспейсами Protobuf 7
namespace gpb = google::protobuf;

namespace krpc {
namespace encoder {

static const size_t LITTLE_ENDIAN_32_LENGTH = 4;
static const size_t LITTLE_ENDIAN_64_LENGTH = 8;

std::string encode(double value) {
  uint64_t value2 = gpb::internal::WireFormatLite::EncodeDouble(value);
  std::string data(LITTLE_ENDIAN_64_LENGTH, 0);
  gpb::io::CodedOutputStream::WriteLittleEndian64ToArray(value2, (uint8_t*)&data[0]);
  return data;
}

std::string encode(float value) {
  uint32_t value2 = gpb::internal::WireFormatLite::EncodeFloat(value);
  std::string data(LITTLE_ENDIAN_32_LENGTH, 0);
  gpb::io::CodedOutputStream::WriteLittleEndian32ToArray(value2, (uint8_t*)&data[0]);
  return data;
}

std::string encode(int32_t value) {
  uint32_t zigZagValue = gpb::internal::WireFormatLite::ZigZagEncode32(value);
  size_t length = gpb::io::CodedOutputStream::VarintSize32(zigZagValue);
  std::string data(length, 0);
  gpb::io::CodedOutputStream::WriteVarint32ToArray(zigZagValue, (uint8_t*)&data[0]);
  return data;
}

std::string encode(int64_t value) {
  uint64_t zigZagValue = gpb::internal::WireFormatLite::ZigZagEncode64(value);
  size_t length = gpb::io::CodedOutputStream::VarintSize64(zigZagValue);
  std::string data(length, 0);
  gpb::io::CodedOutputStream::WriteVarint64ToArray(zigZagValue, (uint8_t*)&data[0]);
  return data;
}

std::string encode(uint32_t value) {
  size_t length = gpb::io::CodedOutputStream::VarintSize32(value);
  std::string data(length, 0);
  gpb::io::CodedOutputStream::WriteVarint32ToArray(value, (uint8_t*)&data[0]);
  return data;
}

std::string encode(uint64_t value) {
  size_t length = gpb::io::CodedOutputStream::VarintSize64(value);
  std::string data(length, 0);
  gpb::io::CodedOutputStream::WriteVarint64ToArray(value, (uint8_t*)&data[0]);
  return data;
}

std::string encode(bool value) {
  uint32_t value2 = (value ? 1 : 0);
  size_t length = gpb::io::CodedOutputStream::VarintSize32(value2);
  std::string data(length, 0);
  gpb::io::CodedOutputStream::WriteVarint32ToArray(value2, (uint8_t*)&data[0]); // Виправлено баг оригіналу
  return data;
}

std::string encode(const char* value) {
  return encode(std::string(value));
}

std::string encode(const std::string& value) {
  size_t length = value.size();
  size_t header_length = gpb::io::CodedOutputStream::VarintSize64(length);
  std::string data(header_length + length, 0);
  gpb::io::CodedOutputStream::WriteVarint64ToArray(length, (uint8_t*)&data[0]);
  gpb::io::CodedOutputStream::WriteStringToArray(value, (uint8_t*)&data[header_length]);
  return data;
}

std::string encode(const gpb::MessageLite& message) {
  std::string data;
  if (!message.SerializeToString(&data))
    throw EncodingError("Failed to encode message");
  return data;
}

std::string encode_message_with_size(const gpb::MessageLite& message) {
  size_t length = message.ByteSizeLong();
  size_t header_length = gpb::io::CodedOutputStream::VarintSize64(length);
  std::string data(header_length + length, 0);
  gpb::io::CodedOutputStream::WriteVarint64ToArray(length, (uint8_t*)&data[0]);
  
  // Використовуємо безпечний SerializeToArray замість застарілого методу
  if (!message.SerializeToArray(&data[header_length], static_cast<int>(length)))
    throw EncodingError("Failed to encode message with size");
  return data;
}

}  // namespace encoder
}  // namespace krpc