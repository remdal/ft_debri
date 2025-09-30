#ifndef RMDLCONFIG_H
#define RMDLCONFIG_H

constexpr size_t kMaxFramesInFlight = 3;

bool deviceSupportsResidencySets(MTL::Device* pDevice);

#endif // RMDLCONFIG_H