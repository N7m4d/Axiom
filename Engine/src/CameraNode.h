#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

#include "DLink.h"
#include "Camera.h"

namespace Axiom
{
    class CameraNode : public DLink
    {
    public:
        CameraNode();
        CameraNode(const Camera&) = delete;
        CameraNode& operator =(const Camera&) = delete;
        virtual ~CameraNode();

        void Set(Camera::Name name, Camera* camera);
        Camera* GetCamera() const;

        char* GetName() override;
        void Wash() override;
        bool Compare(DLink* targetNode) override;
        void Dump() override;

    private:
        void InternalClear();

        Camera* mCamera;
    };
}

#endif
