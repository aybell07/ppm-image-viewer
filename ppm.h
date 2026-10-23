#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <string>
using std::string;

typedef unsigned char byte;

struct RGB {
  RGB() { R = 0, G = 0, B = 0; }
  byte R, G, B;
};

class ppm {
public:
  ppm(int);

  ~ppm();

  void read(const string &);

  RGB *operator[](int);

  int get_Nrow() { return Nrow; }
  int get_Ncol() { return Ncol; }

private:
  string magicid;

  int Nrow, Ncol;
  int maxvalue;

  int block_size;
  RGB *img;
};

#endif
