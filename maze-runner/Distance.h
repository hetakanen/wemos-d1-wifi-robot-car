class Distance
{
public:
    int rotation;
    float distance;

    void reset();
    void updateIfLonger(int rotation, float distance);
};
