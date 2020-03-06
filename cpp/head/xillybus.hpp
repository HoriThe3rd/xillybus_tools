//*********************************************************
// This is a wrapper package to make it easy to write/read xillybus.
// xillybus8 is for 8 bit xillybus
// xillybus32 is for 32 bit xillybus
//
// Developer: Sansei Hori
//*********************************************************

#pragma once
#include <vector>

// For 8 bits Xillybus
class xillybus8 {
   public:
    xillybus8(const char dev_file_write[], const char dev_file_read[]);
    ~xillybus8();
    void xillybus_write(unsigned char tx);
    void xillybus_write(unsigned char tx[], const int size);
    void xillybus_write(std::vector<unsigned char> tx);
    unsigned char xillybus_read();
    void xillybus_read_as_array(unsigned char rx[], const int size);
    void xillybus_read_as_vector(std::vector<unsigned char> &rx);

   private:
    int fd_w;
    int fd_r;
    void allwrite(int fd, unsigned char *buf, int len);
    void allread(int fd, unsigned char *buf, int len);
};

// For 32 bits Xillybus
class xillybus32 {
   public:
    xillybus32(const char dev_file_write[], const char dev_file_read[]);
    ~xillybus32();
    void xillybus_write(unsigned int tx);
    void xillybus_write(unsigned int tx[], const int size);
    void xillybus_write(std::vector<unsigned int> tx);
    unsigned int xillybus_read();
    void xillybus_read_as_array(unsigned int rx[], const int size);
    void xillybus_read_as_vector(std::vector<unsigned int> &rx);

   private:
    int fd_w;
    int fd_r;
    void allwrite(int fd, unsigned int *buf, int len);
    void allread(int fd, unsigned int *buf, int len);
};