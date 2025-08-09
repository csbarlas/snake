#pragma once

struct GridCoordinate {
    unsigned int x, y;
};

struct LogicalCoordinate {
    int x, y;
};

struct GridSquare {
    LogicalCoordinate topLeft;
    unsigned int sideLength;
};

class LogicalPositionProvider {
public:
    virtual void logicalPositionForGridCoordinate(GridCoordinate coord, GridSquare* result) = 0;
};