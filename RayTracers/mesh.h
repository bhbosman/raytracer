#ifndef MESH_H
#define MESH_H
#include "sceneobject.h"
#include "intersection.h"
#include "ray.h"
#include "vector.h"
#include "scene.h"
#include "meshtriangle.h"
#include "normalscene.h"
#include "vector.h"
#include "rply.h"


class Mesh: public SceneObject
{
private:
    std::vector<double> m_XPoints;
    std::vector<double> m_YPoints;
    std::vector<double> m_ZPoints;
    std::vector<double> m_Points;

    typedef SceneObject inherited;
    NormalScene m_Scene;
    bool m_GotInheritedData;

    void buildModel(unsigned long vertices, int triangles)
    {
        bool b =  (m_XPoints.size() == m_YPoints.size());
        b &=  (m_YPoints.size() == m_ZPoints.size());
        b &=  (m_ZPoints.size() == m_XPoints.size());
        b &=  (m_XPoints.size() == vertices);
        //
        if (b)
        {
            if(triangles == 0)
            {

            }
            else
            {
                for (std::vector<double>::const_iterator it = m_Points.begin();
                     it != m_Points.end(); ++it)
                {
                    int p = (int)(*it);
                    if (p == 3)
                    {
                        int n = (m_Points.end() -  it);
                        if (n >= 3)
                        {
                            Vector a[3];
                            for(int index = 0; index < 3; index++)
                            {
                                ++it;
                                p = (int)(*it);
                                a[index] = Vector(m_XPoints.at(p), m_YPoints.at(p), m_ZPoints.at(p)) ;

                            }
                            add(a[0], a[1], a[2]);
                        }
                    }
                }
            }
        }
    }


public:
    Mesh(const Material::ptr& m, const MappingPointCalculation::ptr &colorCalculation);
    Mesh();
    virtual InterSectionType intersect(IntersectionCtx& ctx, const Ray &ray)  const override;
    virtual void Rotate(const Matrix& rotationMatrix) override;
    virtual BBox bixIt() const override;
    void add(const MeshTriangle::ptr& triangle);
    void add(const Vector& v0, const Vector& v1, const Vector& v2);
    void AddPointX(const double x)
    {
        m_XPoints.push_back(x);
    }
    void AddPointY(const double y)
    {
        m_YPoints.push_back(y);
    }
    void AddPointZ(const double z)
    {
        m_ZPoints.push_back(z);
    }


    void addFace(double p)
    {
        m_Points.push_back(p);
    }
    void readPLYFile()
    {

        long nvertices, ntriangles;
        p_ply ply = ply_open("/Users/brendanbosman/input2.ply", NULL, 0, NULL);
        if (!ply) return ;
        if (!ply_read_header(ply)) return ;
        nvertices = ply_set_read_cb(ply, "vertex", "x", vertex_cb_X, this, 0);
        ply_set_read_cb(ply, "vertex", "y", vertex_cb_Y, this, 0);
        ply_set_read_cb(ply, "vertex", "z", vertex_cb_Z, this, 1);
        //        ply_read_element(ply,)
        ntriangles = ply_set_read_cb(ply, "face", "vertex_indices", face_cb, this, 0);
        printf("%ld\n%ld\n", nvertices, ntriangles);
        if (ply_read(ply))
        {
            buildModel(nvertices, ntriangles);
        }
        ply_close(ply);
    }

    static int vertex_cb_X(p_ply_argument argument)
    {

        Mesh* mesh;
        ply_get_argument_user_data(argument, (void**)&mesh, NULL);
             mesh->AddPointX(ply_get_argument_value(argument));
        return 1;
    }
    static int vertex_cb_Y(p_ply_argument argument)
    {

        Mesh* mesh;
        ply_get_argument_user_data(argument, (void**)&mesh, NULL);
             mesh->AddPointY(ply_get_argument_value(argument));
        return 1;
    }
    static int vertex_cb_Z(p_ply_argument argument)
    {

        Mesh* mesh;
        ply_get_argument_user_data(argument, (void**)&mesh, NULL);
             mesh->AddPointZ(ply_get_argument_value(argument));
        return 1;
    }



    static int face_cb(p_ply_argument argument) {
        Mesh* mesh;
        ply_get_argument_user_data(argument, (void**)&mesh, NULL);
        mesh->addFace(ply_get_argument_value(argument));
        return 1;
    }

}
    ;
#endif // MESH_H
