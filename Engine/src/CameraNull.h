#ifndef CAMERA_NULL_H
#define CAMERA_NULL_H

#include "Camera.h"

namespace Axiom
{
    class CameraNull final : public Camera
    {
    public:
        CameraNull();
        CameraNull(const CameraNull&) = delete;
        CameraNull& operator=(const CameraNull& other) = delete;
        ~CameraNull();
    };
}

#endif
