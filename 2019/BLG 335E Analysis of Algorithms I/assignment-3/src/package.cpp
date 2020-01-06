#include "package.h"

Package::Package(int size, int ordinal) {
  this->size = size;
  this->ordinal = ordinal;
}

Package::Package() { this->size = 0; }

int Package::get_size() const { return size; }

int Package::get_ordinal() const { return ordinal; }
