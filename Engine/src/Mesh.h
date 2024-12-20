#ifndef MESH_H
#define MESH_H

#include "MathEngine.h"
#include "DLink.h"

namespace Axiom
{
    struct Vec2f
    {
        Vec2f()
            : u(0.0f), v(0.0f)
        {
        }

        Vec2f(const Vec2f&) = default;
        Vec2f& operator =(const Vec2f&) = default;
        ~Vec2f() = default;

        Vec2f(const float _u, const float _v)
            : u(_u), v(_v)
        {
        }

        float u;
        float v;
    };

    // Vertex data for a colored cube.
    struct VertexColor
    {
        Vec3 Color;
    };

    struct VertexPos
    {
        Vec3 Position;
    };

    struct VertexNorm
    {
        Vec3 Norm;
    };

    struct VertexTexCoord
    {
        Vec2f TexCoord;
    };

    class Mesh
    {
    public:
        enum class Name
        {
            Cube,
            Pyramid,
            Sphere,
            Diamond,
            Cross,
            NullMesh,
            NotInitialized,
            SpaceFrigate,
            R2D2,
            WatchTower,
            Bone,
            Bone_L,
            Bone_L_001,
            Bone_L_002,
            Bone_R,
            Bone_R_001,
            Bone_R_002,
            Bone_001,
            NULL_MESH
        };

        Mesh() = delete;
        Mesh(Mesh& copyModel) = delete;
        Mesh& operator =(Mesh& copyModel) = delete;
        virtual ~Mesh() = default;

        Mesh(unsigned int numVertices, unsigned int numTriangles);

        void Wash();
        bool Compare(DLink* target);
        char* GetName() const;
        void SetName(Name name);

        virtual void ActivateMesh() = 0;
        virtual void RenderIndexBuffer() = 0;

        Name mName;

        unsigned int mNumVertices;
        unsigned int mNumIndices;
    };
}

#endif
