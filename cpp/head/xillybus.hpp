//*********************************************************
// This is a wrapper package to make it easy to write/read xillybus.
// xillybus8 is for 8 bit xillybus
// xillybus32 is for 32 bit xillybus
//
// Developer: Sansei Hori
//*********************************************************

#pragma once

// For 8 bits Xillybus
class xillybus8{
public:
    xillybus8(const char dev_file_write[], const char dev_file_read[]);
    ~xillybus8();
    void xillybus_write(unsigned char tx);
    unsigned char xillybus_read();
private:
    int fd_w;
    int fd_r;
    void allwrite(int fd, unsigned char *buf, int len);
};

// For 32 bits Xillybus
class xillybus32{
public:
    xillybus32(const char dev_file_write[], const char dev_file_read[]);
    ~xillybus32();
    void xillybus_write(unsigned int tx);
    unsigned int xillybus_read();
private:
    int fd_w;
    int fd_r;
    void allwrite(int fd, unsigned int *buf, int len);
};