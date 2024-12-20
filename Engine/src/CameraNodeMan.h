#ifndef CAMERA_MAN_H
#define CAMERA_MAN_H

#include "ManBase.h"
#include "CameraNode.h"

namespace Axiom
{
	class CameraNodeMan : public ManBase
	{
	public:
		static void Create(int reserveNum = 0, int reserveGrow = 1);
		static void Destroy();

		static CameraNode* Add(Camera::Name name, Camera* camera);
		static CameraNode* Find(Camera::Name name);

		static void Update(float deltaTime);

		static void SetActive(Camera::Name name);
		static Camera* GetActive();

		static void Remove(CameraNode* node);
		static void Dump();
	
	private:
		static CameraNodeMan* GetInstance();

		CameraNodeMan(int reserveNum, int reserveGrow);
		~CameraNodeMan();
	
	protected:
		DLink* derivedCreateNode() override;
	
	private:
		CameraNode* mNodeCompare;
		Camera* mActiveCamera;

		static CameraNodeMan* mInstance;
	};
}

#endif
