#include "xillybus.hpp"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termio.h>
#include <signal.h>

xillybus8::xillybus8(const char dev_file_write[], const char dev_file_read[]){
    // Open the device files.
    fd_w = open(dev_file_write, O_WRONLY);
    fd_r = open(dev_file_read, O_RDONLY);
    // Validate results of open functions.
    if(fd_w < 0){
        printf("xillybus: fd_w open error. Please check the path and the permission.");
        exit(1);
    }
    if(fd_r < 0){
        printf("xillybus: fd_r open error. Please check the path and the permission.");
        exit(1);
    }
}

xillybus8::~xillybus8(){
  close(fd_w);
  close(fd_r);
}

void xillybus8::xillybus_write(unsigned char tx){
    allwrite(fd_w, &tx, sizeof(tx));
}

void xillybus8::xillybus_write(unsigned char tx[]){
	allwrite(fd_w, tx, sizeof(tx));
}

void xillybus8::xillybus_write(std::vector<unsigned char> tx){
	allwrite(fd_w, tx.data(), sizeof(*tx.data()) * tx.size());
}

unsigned char xillybus8::xillybus_read(){
    int rc = 0;
    unsigned char buf;
    // check the result.
    while(rc < 1){
      rc = read(fd_r, &buf, sizeof(buf));
      if(rc < 0){
        printf("xillybus8 read error.");
        exit(1);
      }
    }
    return buf;
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

void xillybus8::allwrite(int fd, unsigned char *buf, int len) {
  int sent = 0;
  int rc;

  while (sent < len) {
    rc = write(fd, buf + sent, len - sent);

    if ((rc < 0) && (errno == EINTR))
      continue;

    if (rc < 0) {
      perror("allwrite() failed to write");
      exit(1);
    }

    if (rc == 0) {
      fprintf(stderr, "Reached write EOF (?!)\n");
      exit(1);
    }

    sent += rc;
  }
}

//----------- 32 bit Xillybus用 ---------------
xillybus32::xillybus32(const char dev_file_write[], const char dev_file_read[]){
    // Open the device files.
    fd_w = open(dev_file_write, O_WRONLY);
    fd_r = open(dev_file_read, O_RDONLY);
    // Validate results of open functions.
    if(fd_w < 0){
        printf("xillybus: fd_w open error. Please check the path and the permission.");
        exit(1);
    }
    if(fd_r < 0){
        printf("xillybus: fd_r open error. Please check the path and the permission.");
        exit(1);
    }
}

xillybus32::~xillybus32(){
  close(fd_w);
  close(fd_r);
}

void xillybus32::xillybus_write(unsigned int tx){
    allwrite(fd_w, &tx, sizeof(tx));
    fsync(fd_w);
}

void xillybus32::xillybus_write(unsigned int tx[]){
	allwrite(fd_w, tx, sizeof(tx));
}

void xillybus32::xillybus_write(std::vector<unsigned int> tx){
	allwrite(fd_w, tx.data(), sizeof(*tx.data()) * tx.size());
}

unsigned int xillybus32::xillybus_read(){
    int rc;
    unsigned int buf;
    rc = read(fd_r, &buf, sizeof(buf));
    if(rc<0){
        printf("xillybus read error.");
        exit(1);
    }
    return buf;
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

    if ((rc < 0) && (errno == EINTR))
      continue;

    if (rc < 0) {
      perror("allwrite() failed to write");
      exit(1);
    }

    if (rc == 0) {
      fprintf(stderr, "Reached write EOF (?!)\n");
      exit(1);
    }

    sent += rc;
  }
}