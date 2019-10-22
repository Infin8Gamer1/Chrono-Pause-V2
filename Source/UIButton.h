#pragma once
// -----
// Author: David Wong
// File Name: UIButton.h
// Project: Chrono Pause
// -----

// Includes 
#include <Component.h>			// Component

// UIButton Declaration
namespace Behaviors
{
	// Forward Declarations
	class UIButton;
	// The button callback function. The function has to be global
	typedef void (*UIButtonCallback)(UIButton* button);

	class UIButton : public Component
	{
	private:
		// The global callback function
		UIButtonCallback callback;
	public:
		// Constructor
		UIButton(UIButtonCallback defaultCallback = nullptr);
		// Clones the component
		Component* Clone() const override;
		// Initializes the component
		void Initialize() override;
		// Calls the function pointer assigned to this UI button
		void Call();
		// Sets the function pointer for the UI button
		void SetButtonCallback(UIButtonCallback callback);
	};
}