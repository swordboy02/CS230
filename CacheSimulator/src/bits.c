#include "bits.h"
#include "cache.h"

int get_set(Cache *cache, address_type address) {
  // TODO:
  //  Extract the set bits from a 32-bit address.
  //
  int s = cache->set_bits;
  int b = cache->block_bits;
  int bitShift = s+b;
  int tag = 32-bitShift;
  address = ((address<<tag)>>(32-s));
  return address;
}

int get_line(Cache *cache, address_type address) {
  // TODO:
  // Extract the tag bits from a 32-bit address.
  //
  int s = cache->set_bits;
  int b = cache->block_bits;
  int bitShift = s+b;
  address = address>>bitShift;
  return address;
}

int get_byte(Cache *cache, address_type address) {
  // TODO
  // Extract the block offset (byte index) bits from a 32-bit address.
  //
  int b = cache->block_bits;
  int bitShift = 32-b;
  address = address<<bitShift;
  address = address>>bitShift;
  return address;
}
