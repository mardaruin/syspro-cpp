#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/types.h>

using namespace std;

class IO {
protected:
  bool still_opened;
  bool eof_reached;

public:
  bool is_opened() {
    return still_opened;
  }

  bool is_eof_reached() {
    return eof_reached;
  }

  IO():
      still_opened(true), eof_reached(false){};

  virtual ~IO() { close(); }

  virtual void close() {
    still_opened = false;
    eof_reached  = true;
  }
};

class Reader: virtual public IO {
public:
  virtual ~Reader() = default;

  template<typename T>
  T read() {
    T value{};
    read_bytes(&value, sizeof(T));
    return value;
  }

  std::string read_string() {
    u_int32_t len = read<u_int32_t>();
    std::string result(len, '\0');
    read_bytes(&result[0], len);
    return result;
  }

protected:
  virtual void read_bytes(void* buff, size_t size) = 0;
};

class Writer: virtual public IO {
public:
  virtual ~Writer() = default;

  template<typename T>
  void write(const T& data) {
    write_bytes(&data, sizeof(T));
  }

  void write_string(const std::string& str) {
    u_int32_t len = static_cast<u_int32_t>(str.size());
    write(len);
    write_bytes(str.data(), len);
  }

protected:
  virtual void write_bytes(const void* buff, size_t size) = 0;
};

class ReaderWriter: public Reader,
                    public Writer {
public:
  virtual ~ReaderWriter() = default;

  void reset() {
    this->eof_reached  = false;
    this->still_opened = true;
    specific_reset();
  }

protected:
  virtual void specific_reset() = 0;
};

class StringIO: public ReaderWriter {
private:
  std::string buffer;
  size_t pos = 0;

protected:
  void read_bytes(void* buff, size_t size) override {
    if (pos + size > buffer.size()) {
      eof_reached = true;
      throw std::runtime_error("StringIO: trying to read after EOF.");
    }
    std::memcpy(buff, buffer.data() + pos, size);
    pos += size;
  }

  void write_bytes(const void* buff, size_t size) override {
    const char* src = static_cast<const char*>(buff);
    buffer.append(src, size);
  }

  void specific_reset() override {
    pos = 0;
  }
};

class FileIO: public ReaderWriter {
private:
  FILE* file = nullptr;

protected:
  void read_bytes(void* buff, size_t size) override {
    if (!file) {
      throw std::runtime_error("FileIO: reading from nonexisting file.");
    }
    size_t read = fread(buff, 1, size, file);
    if (read != size) {
      eof_reached = feof(file) != 0;
    }
  }

  void write_bytes(const void* buff, size_t size) override {
    if (!file) {
      throw std::runtime_error("FileIO: writing to nonexisting file.");
    }
    fwrite(buff, 1, size, file);
  }

  void specific_reset() override {
    if (file) {
      fseek(file, 0, SEEK_SET);
    }
  }

public:
  FileIO(const char* filename, const char* mode) {
    file = fopen(filename, mode);
    if (!file) {
      throw std::runtime_error("FileIO: failed to open file.");
    }
  }

  ~FileIO() override {
    close();
  }

  void close() override {
    if (file) {
      fclose(file);
      file = nullptr;
      IO::close();
    }
  }
};
