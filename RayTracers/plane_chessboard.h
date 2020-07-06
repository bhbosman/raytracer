#ifndef PLANE_CHESSBOARD_H
#define PLANE_CHESSBOARD_H

#include "plane.h"
#include "matrix.h"
class ChessBoardPlane: public Plane
{
private:
    typedef Plane inherited;
private:
//    boost::shared_ptr<TColor> _m_Block1;
//    boost::shared_ptr<TColor> m_Block2;
public:
    ChessBoardPlane(
            const Material::ptr& m,
            const Vector& normal,
            const Vector& pos,
            const bool rotate);
};

#endif // PLANE_CHESSBOARD_H
