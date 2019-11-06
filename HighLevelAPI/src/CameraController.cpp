// -----
// Author: David Wong
// File Name: CameraController.cpp
// Project: Chrono Pause
// -----

// Includes
#include <stdafx.h>
#include "CameraController.h"			// Camera Controller

#include <GameObject.h>					// Game Object
#include <Transform.h>					// Transform
#include <Camera.h>						// Camera
#include <Vector2D.h>					// Vector 2D

// Public Member Functions

	CameraController::CameraController(Camera& camera_, Transform* followedTransform_, float cameraFollowSpeed_)
		: camera(camera_), followedTransform(followedTransform_), cameraFollowSpeed(cameraFollowSpeed_)
	{
	}

	void CameraController::Reset()
	{
		camera.SetTranslation(followedTransform->GetTranslation());
	}

	void CameraController::Retarget(Transform* target)
	{
		followedTransform = target;
	}

	void CameraController::Retarget(GameObject* gameObject)
	{
		Retarget(gameObject->GetComponent<Transform>());
	}

	void CameraController::SetSpeed(float speed)
	{
		cameraFollowSpeed = speed;
	}

	void CameraController::Follow()
	{
		if (followedTransform)
		{
			// Get the distance between the camera and the transform
			Vector2D fromCameraToTransform = followedTransform->GetTranslation() - camera.GetTranslation();
			fromCameraToTransform *= cameraFollowSpeed;
			// Translate the camera in the direction
			camera.SetTranslation(camera.GetTranslation() + fromCameraToTransform);
			prevTranslation = camera.GetTranslation() + fromCameraToTransform;
		}
		else
		{
			camera.SetTranslation(prevTranslation);
		}
	}
