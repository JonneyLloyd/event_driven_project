#ifndef GENERATEROOM_H
#define GENERATEROOM_H

#include <unordered_map>
#include <list>
#include <QVector>
#include <QHash>

class GenerateRoom
{

public:
    /*
     * Constructor
     */
    GenerateRoom(int preset, int length = 16, int width = 16);
    ~GenerateRoom();
    void setPreset(int preset);
    void setLength(int length);
    void setWidth(int width);

    int getPreset();
    int getLength();
    int getWidth();
    QHash<std::pair<int, int>, int> *generateRoom();
    QHash<std::pair<int, int>, int> *generateItems();


private:
    int preset;
    int length;
    int width;

};




#endif // GENERATEROOM_H
