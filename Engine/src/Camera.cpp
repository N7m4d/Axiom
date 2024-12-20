#include "Camera.h"

#include "StringThis.h"
#include "DirectXDeviceMan.h"

Axiom::Camera::Camera()
	: mName(Name::Uninitialized)
	, pad{}
{
}

void Axiom::Camera::GetHelper(Vec3& up, Vec3& tar, Vec3& pos, Vec3& upNorm, Vec3& forwardNorm, Vec3& pRightNorm) const
{
	GetPos(pos);
	GetLookAt(tar);
	GetUp(upNorm);
	up = pos + upNorm;

	forwardNorm = tar - pos;
	forwardNorm.norm();

	GetRight(pRightNorm);
}

void Axiom::Camera::SetHelper(Vec3& up, Vec3& tar, Vec3& pos)
{
	SetOrientAndPosition(up - pos, tar, pos);
}

char* Axiom::Camera::GetName() const
{
	static char pTmp[128];
	strcpy_s(pTmp, 128, StringMe(mName));
	return pTmp;
}

void Axiom::Camera::SetName(Name name)
{
	mName = name;
}

void Axiom::Camera::SetPerspective(const float fov, const float aspectRatio, const float nearDist, const float farDist)
{
	mAspectRatio = aspectRatio;
	mFovy = MATH_PI_180 * fov;
	mNearDist = nearDist;
	mFarDist = farDist;
}

int Axiom::Camera::GetScreenWidth() const
{
	return mViewportWidth;
}

int Axiom::Camera::GetScreenHeight() const
{
	return mViewportHeight;
}

// Just a pass through to Setup the view port screen sub window
void Axiom::Camera::SetViewport(const int x, const int y, const int width, const int height)
{
	mViewportX = x;
	mViewportY = y;
	mViewportWidth = width;
	mViewportHeight = height;

	SetViewState();
}

// Simple wrapper
void Axiom::Camera::SetViewState() const
{
	D3D11_VIEWPORT tmp;

	tmp.Width = static_cast<float>(mViewportWidth);
	tmp.Height = static_cast<float>(mViewportHeight);
	tmp.TopLeftX = static_cast<float>(mViewportX);
	tmp.TopLeftY = static_cast<float>(mViewportY);
	tmp.MinDepth = 0.0f;
	tmp.MaxDepth = 1.0f;

	DirectXDeviceMan::GetContext()->RSSetViewports(1, &tmp);
}

// Goal, calculate the near height / width, same for far plane 
void Axiom::Camera::CalcPlaneHeightWidth()
{
	mNearHeight = 2.0f * tanf((mFovy * MATH_PI / 180.0f) * .5f) * mNearDist;
	mNearWidth = mNearHeight * mAspectRatio;

	mFarHeight = 2.0f * tanf((mFovy * MATH_PI / 180.0f) * .5f) * mFarDist;
	mFarWidth = mFarHeight * mAspectRatio;
};

void Axiom::Camera::SetOrientAndPosition(const Vec3& up, const Vec3& lookAt, const Vec3& pos)
{
	// Remember the up, lookAt and right are unit length, and are perpendicular.
	// Treat lookAt as king, find Right vect, then correct Up to insure perpendicular.
	// Make sure that all vectors are unit vectors.

	mLookAt = lookAt;
	mDir = -(lookAt - pos); // Right-Hand camera: mDir is flipped
	mDir.norm();

	// Clean up the vectors (Right hand rule)
	mRight = up.cross(mDir);
	mRight.norm();

	mUp = mDir.cross(mRight);
	mUp.norm();

	mPos = pos;
};

void Axiom::Camera::CalcFrustumVerts()
{
	// mDir goes from screen into your EYE so distance from the eye is "negative" mDir
	mNearTopLeft = mPos + mDir * mNearDist + mUp * mNearHeight * 0.5f - mRight * mNearWidth * 0.5f;
	mNearTopRight = mPos + mDir * mNearDist + mUp * mNearHeight * 0.5f + mRight * mNearWidth * 0.5f;
	mNearBottomLeft = mPos + mDir * mNearDist - mUp * mNearHeight * 0.5f - mRight * mNearWidth * 0.5f;
	mNearBottomRight = mPos + mDir * mNearDist - mUp * mNearHeight * 0.5f + mRight * mNearWidth * 0.5f;
	mFarTopLeft = mPos + mDir * mFarDist + mUp * mFarHeight * 0.5f - mRight * mFarWidth * 0.5f;
	mFarTopRight = mPos + mDir * mFarDist + mUp * mFarHeight * 0.5f + mRight * mFarWidth * 0.5f;
	mFarBottomLeft = mPos + mDir * mFarDist - mUp * mFarHeight * 0.5f - mRight * mFarWidth * 0.5f;
	mFarBottomRight = mPos + mDir * mFarDist - mUp * mFarHeight * 0.5f + mRight * mFarWidth * 0.5f;
};

void Axiom::Camera::CalcFrustumCollisionNormals()
{
	// Normals of the frustum around nearTopLeft
	Vec3 a = mNearBottomLeft - mNearTopLeft;
	Vec3 b = mNearTopRight - mNearTopLeft;
	Vec3 c = mFarTopLeft - mNearTopLeft;

	mFrontNorm = a.cross(b);
	mFrontNorm.norm();

	mLeftNorm = c.cross(a);
	mLeftNorm.norm();

	mTopNorm = b.cross(c);
	mTopNorm.norm();

	// Normals of the frustum around farBottomRight
	a = mFarBottomLeft - mFarBottomRight;
	b = mFarTopRight - mFarBottomRight;
	c = mNearBottomRight - mFarBottomRight;

	mBackNorm = a.cross(b);
	mBackNorm.norm();

	mRightNorm = b.cross(c);
	mRightNorm.norm();

	mBottomNorm = c.cross(a);
	mBottomNorm.norm();
};

void Axiom::Camera::UpdateProjectionMatrix()
{
	float d = 1 / tanf(mFovy / 2);

	mProjMatrix[m0] = d / mAspectRatio;
	mProjMatrix[m1] = 0.0f;
	mProjMatrix[m2] = 0.0f;
	mProjMatrix[m3] = 0.0f;

	mProjMatrix[m4] = 0.0f;
	mProjMatrix[m5] = d;
	mProjMatrix[m6] = 0.0f;
	mProjMatrix[m7] = 0.0f;

	mProjMatrix[m8] = 0.0f;
	mProjMatrix[m9] = 0.0f;
	mProjMatrix[m10] = -(mFarDist + mNearDist) / (mFarDist - mNearDist);
	mProjMatrix[m11] = -1.0f;

	mProjMatrix[m12] = 0.0f;
	mProjMatrix[m13] = 0.0f;
	mProjMatrix[m14] = (-2.0f * mFarDist * mNearDist) / (mFarDist - mNearDist);
	mProjMatrix[m15] = 0.0f;

	// Converting from OpenGL-style NDC of [-1,1] to DX's [0,1].  See note: https://anteru.net/blog/2011/12/27/1830/
	// (Note: NDCConvert should be precomputed once and stored for reuse)
	Trans trans(0.0f, 0.0f, 1.0f);
	Scale scale(1.0f, 1.0f, 0.5f);

	mProjMatrix = mProjMatrix * trans * scale;
};

void Axiom::Camera::UpdateViewMatrix()
{
	// This functions assumes the your vUp, vRight, vDir are still unit
	// And perpendicular to each other

	// Set for DX Right-handed space
	mViewMatrix[m0] = mRight[x];
	mViewMatrix[m1] = mUp[x];
	mViewMatrix[m2] = mDir[x];
	mViewMatrix[m3] = 0.0f;

	mViewMatrix[m4] = mRight[y];
	mViewMatrix[m5] = mUp[y];
	mViewMatrix[m6] = mDir[y];
	mViewMatrix[m7] = 0.0f;

	mViewMatrix[m8] = mRight[z];
	mViewMatrix[m9] = mUp[z];
	mViewMatrix[m10] = mDir[z];
	mViewMatrix[m11] = 0.0f;

	// Apply R^t( -Pos ). Use dot-product with the basis vectors
	mViewMatrix[m12] = -mPos.dot(mRight);
	mViewMatrix[m13] = -mPos.dot(mUp);
	mViewMatrix[m14] = -mPos.dot(mDir);
	mViewMatrix[m15] = 1.0f;
};

// Update everything (make sure it's consistent)
void Axiom::Camera::UpdateCamera()
{
	// First find the near height/width, far height/width
	CalcPlaneHeightWidth();

	// Find the frustum physical verts
	CalcFrustumVerts();

	// find the frustum collision normals
	CalcFrustumCollisionNormals();

	// update the projection matrix
	UpdateProjectionMatrix();

	// update the view matrix
	UpdateViewMatrix();

	//projMatrix.Print("Proj");
	//viewMatrix.Print("View");
}

Axiom::Mat4& Axiom::Camera::GetViewMatrix()
{
	return mViewMatrix;
}

Axiom::Mat4& Axiom::Camera::GetProjMatrix()
{
	return mProjMatrix;
}

void Axiom::Camera::GetPos(Vec3& out) const
{
	out = mPos;
}

void Axiom::Camera::GetDir(Vec3& out) const
{
	out = mDir;
}

void Axiom::Camera::GetUp(Vec3& out) const
{
	out = mUp;
}

void Axiom::Camera::GetLookAt(Vec3& out) const
{
	out = mLookAt;
}

void Axiom::Camera::GetRight(Vec3& out) const
{
	out = mRight;
}

void Axiom::Camera::GetFieldOfView(float& value) const
{
	value = mAspectRatio;
};

void Axiom::Camera::SetFieldOfView(const float value)
{
	mAspectRatio = value;
};

void Axiom::Camera::GetNearDist(float& value) const
{
	value = mNearDist;
}

void Axiom::Camera::SetNearDist(const float value)
{
	mNearDist = value;
}

void Axiom::Camera::GetNearTopLeft(Vec3& out) const
{
	out = mNearTopLeft;
}

void Axiom::Camera::GetNearTopRight(Vec3& out) const
{
	out = mNearTopRight;
}

void Axiom::Camera::GetNearBottomLeft(Vec3& out) const
{
	out = mNearBottomLeft;
}

void Axiom::Camera::GetNearBottomRight(Vec3& out) const
{
	out = mNearBottomRight;
}

void Axiom::Camera::GetFarTopLeft(Vec3& out) const
{
	out = mFarTopLeft;
}

void Axiom::Camera::GetFarTopRight(Vec3& out) const
{
	out = mFarTopRight;
}

void Axiom::Camera::GetFarBottomLeft(Vec3& out) const
{
	out = mFarBottomLeft;
}

void Axiom::Camera::GetFarBottomRight(Vec3& out) const
{
	out = mFarBottomRight;
}
