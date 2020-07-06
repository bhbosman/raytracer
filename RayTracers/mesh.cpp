#include "mesh.h"

Mesh::Mesh(const Material::ptr &m, const MappingPointCalculation::ptr &colorCalculation):
    inherited(m, colorCalculation),
    m_Scene(),
    m_GotInheritedData(true)
{

}

Mesh::Mesh():
    inherited(Material::ptr(), MappingPointCalculation::ptr()),
    m_Scene(),
    m_GotInheritedData(false)
{

}

InterSectionType Mesh::intersect(IntersectionCtx &ctx, const Ray &ray) const
{
    return m_Scene.SendRayToScene(ctx, ray);
}

void Mesh::Rotate(const Matrix &rotationMatrix)
{
    m_Scene.Rotate(rotationMatrix);
}

BBox Mesh::bixIt() const
{

    return m_Scene.bixIt() ;
}

void Mesh::add(const MeshTriangle::ptr &triangle)
{
    m_Scene.AddSceneObject(triangle);
}

void Mesh::add(const Vector &v0, const Vector &v1, const Vector &v2)
{
    if (m_GotInheritedData)
    {
        MeshTriangle* meshTriangle = new MeshTriangle(material(), m_ColorCalculation, v0, v1, v2);
        add(MeshTriangle::ptr(meshTriangle));
    }
}
