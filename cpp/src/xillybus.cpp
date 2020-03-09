#include "xillybus.hpp"
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
//#include <termio.h>
#include <unistd.h>

xillybus8::xillybus8(const char dev_file_write[], const char dev_file_read[]) {
    // Open the device files.
    fd_w = open(dev_file_write, O_WRONLY);
    fd_r = open(dev_file_read, O_RDONLY);
    // Validate results of open functions.
    if (fd_w < 0) {
        std::cout << "xillybus: fd_w open error. Please check the path and the "
                     "permission."
                  << std::endl;
        exit(1);
    }
    if (fd_r < 0) {
        std::cout << "xillybus: fd_r open error. Please check the path and the "
                     "permission."
                  << std::endl;
        exit(1);
    }
}

xillybus8::~xillybus8() {
    close(fd_w);
    close(fd_r);
}

void xillybus8::xillybus_write(unsigned char tx) {
    allwrite(fd_w, &tx, sizeof(tx));
}

void xillybus8::xillybus_write(unsigned char tx[], const int size) {
    allwrite(fd_w, tx, size);
}

void xillybus8::xillybus_write(std::vector<unsigned char> tx) {
    allwrite(fd_w, tx.data(), sizeof(*tx.data()) * tx.size());
}

unsigned char xillybus8::xillybus_read() {
    unsigned char buf;
    allread(fd_r, &buf, sizeof(buf));
    return buf;
}

void xillybus8::xillybus_read_as_array(unsigned char rx[], const int size) {
    allread(fd_r, rx, size);
}

void xillybus8::xillybus_read_as_vector(std::vector<unsigned char> &rx) {
    allread(fd_r, rx.data(), sizeof(*rx.data()) * rx.size());
}

/*
   ---From Xillybus demoapp---
   Plain write() may not write all bytes requested in the buffer, so
   allwrite() loops until all data was indeed written, or exits in
   case of failure, except for EINTR. The way the EINTR condition is
   handled is the standard way of making sure the process can be suspended
   with CTRL-Z and then continue running properly.

   The function has no return value, because it always succeeds (or exits
   instead of returning).

   The function doesn't expect to reach EOF either.
*/

void xillybus8::allwrite(int fd, unsigned char *buf, int len) {
    int sent = 0;
    int rc;

    while (sent < len) {
        rc = write(fd, buf + sent, len - sent);

        if ((rc < 0) && (errno == EINTR)) continue;

        if (rc < 0) {
            std::cerr << "allwrite() failed to write" << std::endl;
            exit(1);
        }

        if (rc == 0) {
            std::cerr << "Reached write EOF (?!)" << std::endl;
            exit(1);
        }

        sent += rc;
    }
}

/*
   ---From Xillybus demoapp---
   Plain read() may not read all bytes requested in the buffer, so
   allread() loops until all data was indeed read, or exits in
   case of failure, except for EINTR. The way the EINTR condition is
   handled is the standard way of making sure the process can be suspended
   with CTRL-Z and then continue running properly.

   The function has no return value, because it always succeeds (or exits
   instead of returning).

   The function doesn't expect to reach EOF either.
*/
void xillybus8::allread(int fd, unsigned char *buf, int len) {
    int received = 0;
    int rc;

    while (received < len) {
        rc = read(fd, buf + received, len - received);

        if ((rc < 0) && (errno == EINTR)) continue;

        if (rc < 0) {
            std::cerr << "allread() failed to read" << std::endl;
            exit(1);
        }

        if (rc == 0) {
            std::cerr << "Reached read EOF (?!)" << std::endl;
            exit(1);
        }

        received += rc;
    }
}

//----------- 32 bit Xillybus用 ---------------
xillybus32::xillybus32(const char dev_file_write[],
                       const char dev_file_read[]) {
    // Open the device files.
    fd_w = open(dev_file_write, O_WRONLY);
    fd_r = open(dev_file_read, O_RDONLY);
    // Validate results of open functions.
    if (fd_w < 0) {
        std::cout << "xillybus: fd_w open error. Please check the path and the "
                     "permission."
                  << std::endl;
        exit(1);
    }
    if (fd_r < 0) {
        std::cout << "xillybus: fd_r open error. Please check the path and the "
                     "permission."
                  << std::endl;
        exit(1);
    }
}

xillybus32::~xillybus32() {
    close(fd_w);
    close(fd_r);
}

void xillybus32::xillybus_write(unsigned int tx) {
    allwrite(fd_w, &tx, sizeof(tx));
    fsync(fd_w);
}

void xillybus32::xillybus_write(unsigned int tx[], const int size) {
    allwrite(fd_w, tx, size);
}

void xillybus32::xillybus_write(std::vector<unsigned int> tx) {
    allwrite(fd_w, tx.data(), sizeof(*tx.data()) * tx.size());
}

unsigned int xillybus32::xillybus_read() {
    unsigned int buf;
    allread(fd_r, &buf, sizeof(buf));
    return buf;
}

void xillybus32::xillybus_read_as_array(unsigned int rx[], const int size) {
    allread(fd_r, rx, size);
}

void xillybus32::xillybus_read_as_vector(std::vector<unsigned int> &rx) {
    allread(fd_r, rx.data(), sizeof(*rx.data()) * rx.size());
}

/*
   Plain write() may not write all bytes requested in the buffer, so
   allwrite() loops until all data was indeed written, or exits in
   case of failure, except for EINTR. The way the EINTR condition is
   handled is the standard way of making sure the process can be suspended
   with CTRL-Z and then continue running properly.

   The function has no return value, because it always succeeds (or exits
   instead of returning).

   The function doesn't expect to reach EOF either.
*/

void xillybus32::allwrite(int fd, unsigned int *buf, int len) {
    int sent = 0;
    int rc;

    while (sent < len) {
        rc = write(fd, buf + sent, len - sent);

        if ((rc < 0) && (errno == EINTR)) continue;

        if (rc < 0) {
            std::cerr << "allwrite() failed to write" << std::endl;
            exit(1);
        }

        if (rc == 0) {
            std::cerr << "Reached write EOF (?!)" << std::endl;
            exit(1);
        }

        sent += rc;
    }
}

/*
   ---From Xillybus demoapp---
   Plain read() may not read all bytes requested in the buffer, so
   allread() loops until all data was indeed read, or exits in
   case of failure, except for EINTR. The way the EINTR condition is
   handled is the standard way of making sure the process can be suspended
   with CTRL-Z and then continue running properly.

   The function has no return value, because it always succeeds (or exits
   instead of returning).

   The function doesn't expect to reach EOF either.
*/
void xillybus32::allread(int fd, unsigned int *buf, int len) {
    int received = 0;
    int rc;

    while (received < len) {
        rc = read(fd, buf + received, len - received);

        if ((rc < 0) && (errno == EINTR)) continue;

        if (rc < 0) {
            std::cerr << "allread() failed to read" << std::endl;
            exit(1);
        }

        if (rc == 0) {
            std::cerr << "Reached read EOF (?!)" << std::endl;
            exit(1);
        }

        received += rc;
    }
}