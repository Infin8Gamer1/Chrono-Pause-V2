#pragma once
// -----
// Author: David Wong
// File Name: CameraController.h
// Project: Chrono Pause
// -----

// Includes
#include <Vector2D.h>

// Forward Declarations
class Camera;
class GameObject;
class Transform;

// CameraController Declaration
namespace Behaviors
{
	class CameraController
	{
	private:
		// Private variables
		// The camera we want to control
		Camera& camera;
		// The transform of the object we are following
		Transform* followedTransform;
		// Camera follow speed
		float cameraFollowSpeed;
		// Prev Translation
		Vector2D prevTranslation;
	public:
		// CameraController Constructor
		// Params:
		//   camera: The camera that is going to follow the target
		//   followedTransform: The transform we are following
		//   cameraFollowSpeed: The speed of the camera in relation to the player
		CameraController(Camera& camera, Transform* followedTransform = nullptr, float cameraFollowSpeed = 0.5f);
		// Sets a new target to follow
		// Params:
		//   target: The target's transform
		void Retarget(Transform* target);
		// Sets a new target to follow
		// Params:
		//   gameObject: The object we are targeting
		void Retarget(GameObject* gameObject);
		// Sets the camera's speed
		// Params: Set's the camera's speed in relation to the followed object
		void SetSpeed(float speed);
		// Resets the camera's position on top of the player
		void Reset();
		// Smoothly follows the player
		void Follow();
	};
}
