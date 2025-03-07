#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Common.h"

class CacheConfig {
public:
  uint32_t cacheSize;

  CacheConfig(uint32_t cacheSize = define::rdmaBufferSize) : cacheSize(cacheSize) {}
};

class DSMConfig {
public:
  CacheConfig cacheConfig;
  uint32_t machineNR;
  uint32_t threadNR;
  uint64_t dsmSize;       // G
  uint64_t cxlSize;   

  DSMConfig(const CacheConfig &cacheConfig = CacheConfig(),
            uint32_t machineNR = 2, uint64_t dsmSize = define::dsmSize, uint64_t cxlSize = define::cxlSize)
      : cacheConfig(cacheConfig), machineNR(machineNR), dsmSize(dsmSize), cxlSize(cxlSize){}
};

#endif /* __CONFIG_H__ */
