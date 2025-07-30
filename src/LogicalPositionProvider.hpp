#pragma once

class LogicalPositionProvider {
public:
    virtual void logicalPositionForGridCoordinate(int gridX, int gridY, int* logicalPosX, int* logicalPosY) = 0;
};