//------------------------------------------------------------------------------
//
// File Name:	Animation.cpp
// Author(s):	Jacob Holyfield
// Project:		BetaEngine
// Course:		CS230
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "Animation.h"
#include "Sprite.h"
#include "GameObject.h"
#include <SpriteSource.h>
#include <Parser.h>

Animation::Animation() : Component("Animation")
{
	frameIndex = 0;

	frameStart = 0;
	frameEnd = 0;
	
	frameDelay = 0;

	frameDuration = 20;

	isRunning = false;
	isLooping = false;
	isDone = false;
	playInReverse = false;

	sprite = nullptr;

	lastSpriteSource = nullptr;

	autoPlay = false;
}

Component * Animation::Clone() const
{
	Animation* out = new Animation();

	//out->sprite = sprite;

	return out;
}

void Animation::Initialize()
{
	sprite = GetOwner()->GetComponent<Sprite>();

	lastSpriteSource = sprite->GetSpriteSource();

	if (autoPlay) {
		Play(0.1f, isLooping);
	}
}

//void Animation::Deserialize(Parser& parser)
//{
//	//get autoPlay
//	bool _autoPlay;
//	parser.ReadVariable("AutoPlay", _autoPlay);
//
//	autoPlay = _autoPlay;
//
//	if (autoPlay)
//	{
//		//get is loop
//		bool _isLoop;
//		parser.ReadVariable("Loop", _isLoop);
//
//		isLooping = _isLoop;
//	}
//}
//
//void Animation::Serialize(Parser& parser) const
//{
//	parser.WriteVariable("AutoPlay", autoPlay);
//
//	if (autoPlay)
//	{
//		parser.WriteVariable("Loop", isLooping);
//	}
//}

void Animation::Play(float frameDurationInput, bool isLoopingInput, bool playInReverseInput)
{
	//std::cout << "Animation::Play" << std::endl;

	lastSpriteSource = sprite->GetSpriteSource();

	isLooping = isLoopingInput;
	playInReverse = playInReverseInput;


	if (!playInReverse) {
		frameStart = sprite->GetSpriteSource()->GetFrameStart();
		frameEnd = sprite->GetSpriteSource()->GetFrameStart() + sprite->GetSpriteSource()->GetFrameCount() - 1;
	}
	else {
		frameStart = sprite->GetSpriteSource()->GetFrameStart() + sprite->GetSpriteSource()->GetFrameCount() - 1;
		frameEnd = sprite->GetSpriteSource()->GetFrameStart();
	}
	
	frameIndex = frameStart;

	//std::cout << "Start : " << frameStart << ", End : " << frameEnd << std::endl;

	GetOwner()->GetComponent<Sprite>()->SetFrame(frameIndex);

	frameDuration = frameDurationInput;
	frameDelay = frameDuration;

	isRunning = true;
	isDone = false;
}

void Animation::PlayB(int frameStartInput, int frameCount, float frameDurationInput, bool isLoopingInput, bool playInReverseInput)
{
	//std::cout << "Animation::Play" << std::endl;

	lastSpriteSource = sprite->GetSpriteSource();

	isLooping = isLoopingInput;
	playInReverse = playInReverseInput;


	if (!playInReverse) {
		frameStart = frameStartInput;
		frameEnd = frameStartInput + frameCount - 1;
	}
	else {
		frameStart = frameStartInput + frameCount - 1;
		frameEnd = frameStartInput;
	}

	frameIndex = frameStart;

	//std::cout << "Start : " << frameStart << ", End : " << frameEnd << std::endl;

	GetOwner()->GetComponent<Sprite>()->SetFrame(frameIndex);

	frameDuration = frameDurationInput;
	frameDelay = frameDuration;

	isRunning = true;
	isDone = false;
}

void Animation::FixedUpdate(float dt)
{
	//std::cout << "Animation::FixedUpdate" << std::endl;

	//check if sprite source has been updated
	if (lastSpriteSource != sprite->GetSpriteSource()) {
		lastSpriteSource = sprite->GetSpriteSource();
		Play(frameDuration, isLooping, playInReverse);
	}
	
	isDone = false;

	if (!isRunning) {
		return;
	}

	frameDelay -= dt;

	//move on to the next frame if delay has been reached
	if (frameDelay <= 0.0f) {
		

		//move frame up or down
		if (playInReverse) {
			frameIndex--;
		} else {
			frameIndex++;
		}

		if ((frameIndex > frameEnd && !playInReverse) || (frameIndex < frameEnd && playInReverse))
		{
			if (isLooping)
			{
				frameIndex = frameStart;
				isDone = true;
				isRunning = true;
			} else {
				frameIndex = frameStart;
				isDone = true;
				isRunning = false;
			}
		}

		sprite->SetFrame(frameIndex);

		frameDelay = frameDuration;
	}
}

bool Animation::IsDone() const
{
	return isDone;
}

bool Animation::IsRunning() const {
	return isRunning;
}

void Animation::SetFrameDuration(float duration)
{
	frameDuration = duration;
}
