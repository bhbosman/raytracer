#ifndef BOXKEY_H
#define BOXKEY_H

struct BoxKey
{
public:
    int x;
    int y;
    int z;
    bool operator < (const BoxKey& b) const
    {
        if ( x != b.x )
        {
            return x < b.x;
        }
        if ( y != b.y )
        {
            return y < b.y;
        }
        return z < b.z;
    }
};




#endif // BOXKEY_H
