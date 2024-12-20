#ifndef CAMERA_H
#define CAMERA_H

#include "MathEngine.h"

namespace Axiom
{
    class Camera : public Align16
    {
    public:
        enum class Name : char
        {
            NullCamera,
            FrontCamera,
            RightCamera,
            LeftCamera,
            RearCamera,
            TopCamera,
            BottomCamera,
            Uninitialized,
        };

        Camera();
        Camera(const Camera&) = delete;
        Camera& operator =(const Camera&) = delete;
        ~Camera() = default;

        void SetPerspective(float fov, float aspectRatio, float nearDist, float farDist);
        void SetViewport(int x, int y, int width, int height);
        void SetOrientAndPosition(const Vec3& up, const Vec3& lookAt, const Vec3& pos);

        void UpdateCamera();

        Mat4& GetViewMatrix();
        Mat4& GetProjMatrix();

        void GetPos(Vec3& out) const;
        void GetDir(Vec3& out) const;
        void GetUp(Vec3& out) const;
        void GetLookAt(Vec3& out) const;
        void GetRight(Vec3& out) const;

        int GetScreenWidth() const;
        int GetScreenHeight() const;

        void GetFieldOfView(float& value) const;
        void SetFieldOfView(float value);

        void GetNearDist(float& value) const;
        void SetNearDist(float value);

        char* GetName() const;
        void SetName(Name name);

        void GetHelper(Vec3& up, Vec3& tar, Vec3& pos, Vec3& upNorm, Vec3& forwardNorm, Vec3& rightNorm) const;
        void SetHelper(Vec3& up, Vec3& tar, Vec3& pos);

        void GetNearTopLeft(Vec3& out) const;
        void GetNearTopRight(Vec3& out) const;
        void GetNearBottomLeft(Vec3& out) const;
        void GetNearBottomRight(Vec3& out) const;
        void GetFarTopLeft(Vec3& out) const;
        void GetFarTopRight(Vec3& out) const;
        void GetFarBottomLeft(Vec3& out) const;
        void GetFarBottomRight(Vec3& out) const;

    private:
        void SetViewState() const;
        void CalcPlaneHeightWidth();
        void CalcFrustumVerts();
        void CalcFrustumCollisionNormals();
        void UpdateProjectionMatrix();
        void UpdateViewMatrix();

        Mat4 mProjMatrix;
        Mat4 mViewMatrix;

        Vec3 mDir;
        Vec3 mRight;

        Vec3 mUp;
        Vec3 mPos;
        Vec3 mLookAt;

        Vec3 mNearTopLeft;
        Vec3 mNearTopRight;
        Vec3 mNearBottomLeft;

        Vec3 mNearBottomRight;
        Vec3 mFarTopLeft;
        Vec3 mFarTopRight;
        Vec3 mFarBottomLeft;

        Vec3 mFarBottomRight;

        // Normals of the frustum
        Vec3 mFrontNorm;
        Vec3 mBackNorm;
        Vec3 mRightNorm;

        Vec3 mLeftNorm;
        Vec3 mTopNorm;
        Vec3 mBottomNorm;

        // Define the frustum inputs
        float mNearDist;
        float mFarDist;
        float mFovy;
        float mAspectRatio;

        // Screen size in world space
        float mNearHeight;
        float mNearWidth;
        float mFarHeight;
        float mFarWidth;

        // Viewports
        int mViewportX;
        int mViewportY;
        int mViewportWidth;
        int mViewportHeight;

    public:
        Name mName;
        char pad[12];
    };
}

#endif
