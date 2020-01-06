#ifndef PACKAGE_H
#define PACKAGE_H

class Package {
 private:
  int size;
  int ordinal;

 public:
  Package(int, int);

  Package();
  int get_size() const;
  int get_ordinal() const;
};

#endif