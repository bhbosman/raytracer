#include "plane_chessboard.h"
#include "rotation.h"
#include "PerlinNoise.h"

ChessBoardPlane::ChessBoardPlane(
        const Material::ptr &m,
        const Vector &normal,
        const Vector &pos,
        const bool rotate):

    inherited(
        m,
        MappingPointCalculation::ptr(new Mapping3DTo2DPoint(normal)),
        normal,
        pos, rotate)
{

}

