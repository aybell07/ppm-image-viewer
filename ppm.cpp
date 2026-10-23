#include "ppm.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <ostream>

ppm::ppm(int n_bsize) {
  magicid = "P6";
  maxvalue = 255;
  block_size = n_bsize;
  img = 0;
  Ncol = 0;
  Nrow = 0;
}

ppm::~ppm() { delete[] img; }

void ppm::read(const string &img_name) {
  std::ifstream fin;
  fin.open(img_name.c_str());

  if (!fin.is_open()) {
    std::cerr << "error opening " << img_name << std::endl;
    std::exit(1);
  }
  string tempmagicid;
  int tempmaxvalue;
  fin >> tempmagicid >> Ncol >> Nrow >> tempmaxvalue;

  fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  if (tempmagicid != magicid) {
    std::cerr << "bad file type: not a ppm" << std::endl;
    std::exit(1);
  }

  if (tempmaxvalue != maxvalue) {
    std::cerr << "incompatible max value" << std::endl;
    std::exit(1);
  }

  int Nbytes = 3 * Ncol * Nrow;
  int Nbytes_read = 0;
  byte *buf = new byte[block_size];
  img = new RGB[Ncol * Nrow];

  while (Nbytes_read < Nbytes) {
    int amountToRead = block_size;
    if (amountToRead > Nbytes - Nbytes_read) {
      amountToRead = Nbytes - Nbytes_read;
    }

    fin.read(reinterpret_cast<char *>(buf), amountToRead);

    if (fin.gcount() != amountToRead) {
      std::cerr << "not enough RGB data" << std::endl;
      delete[] buf;
      std::exit(1);
    }

    for (int i = 0; i < amountToRead; i++) {
      int dataPosition = Nbytes_read + i;
      int pixelIndex = dataPosition / 3;
      byte value = buf[i];

      if (dataPosition % 3 == 0) {
        img[pixelIndex].R = value;
      } else if (dataPosition % 3 == 1) {
        img[pixelIndex].G = value;
      } else {
        img[pixelIndex].B = value;
      }
    }
    Nbytes_read += amountToRead;
  }
  /*if (fin.peek() != std::char_traits<char>::eof()) {
    std::cerr << "Extra Data not expected from header." << std::endl;
    delete[] buf;
    fin.close();
    std::exit(1);
  }*/
  fin.close();
  delete[] buf;
}

RGB *ppm::operator[](int i) { return img + i * Ncol; }
