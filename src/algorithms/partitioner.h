//
// Created by zak on 2/17/17.
//

#ifndef MAP_THE_GAP_PARTITIONER_H
#define MAP_THE_GAP_PARTITIONER_H

#include <iostream>
#include <map>
#include <string>
#include "debug.h"

#include "message.h"

const int WHOLE_CABLE_LENGTH = 1000000;

template <class T>
void partitionPoints(const std::map<int, T> &pointsPerGmina) {
  DEB("partitionPoints\n");
  int slaveId = 1;
  typename std::map<int, T>::const_iterator it = pointsPerGmina.begin();
  DEB("Map size: %lu\n", pointsPerGmina.size());
  int numAllPoints = 0;
  while (it != pointsPerGmina.end()) {
    numAllPoints += (int) it->second.size();
    ++it;
  }
  DEB("After loop\n");

  it = pointsPerGmina.begin();
  while (it != pointsPerGmina.end()) {
    DEB("Dupa!\n");
    int numPointsInGmina = (int) it->second.size();
    putInt(slaveId, numPointsInGmina);
    for (int i = 0; i < numPointsInGmina; ++i) {
      putDouble(slaveId, it->second[i].getX());
      putDouble(slaveId, it->second[i].getY());
    }
    double cableLength = (double) numPointsInGmina * WHOLE_CABLE_LENGTH / numAllPoints;
    putDouble(slaveId, cableLength);
    send(slaveId);
    slaveId = ((slaveId + 1) % (nodes() - 1)) + 1;
    ++it;
  }
}

void partitionData(const std::string &btsPath, const std::string &bpPath);

#endif //MAP_THE_GAP_PARTITIONER_H
