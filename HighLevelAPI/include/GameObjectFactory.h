//------------------------------------------------------------------------------
//
// File Name:	GameObjectFactory.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class GameObject;
class Component;
class Mesh;
class SpriteSource;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

class GameObjectFactory
{
public:
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Create a single instance of the specified game object.
	// Loads the object from a text file (if it exists).
	// Params:
	//   name = The name of the object.
	//   mesh = The mesh used for the object's sprite (if any).
	//   spriteSource = The sprite source used for the object's sprite (if any).
	// Returns:
	//	 If the object file exists and can be loaded, then return a pointer to a new instance 
	//    of the specified game object type, else nullptr.
	GameObject* CreateObject(const std::string& name, Mesh* mesh = nullptr, SpriteSource* spriteSource = nullptr);

	// Create a single instance of the specified component.
	// Params:
	//   name = The name of the component.
	// Returns:
	//	 If the component exists, then return a pointer to a new instance 
	//    of the specified component, else nullptr.
	Component* CreateComponent(const std::string& name);

	// Create a single instance of the specified component.
	// Returns:
	//	 If the component exists, then return a pointer to a new instance 
	//    of the specified component, else nullptr.
	template<class T>
	Component* CreateComponent() {
		std::string compName = std::string(typeid(T).name());

		for (size_t i = 0; i < registeredComponents.size(); i++)
		{
			std::string currentName = std::string(typeid(*registeredComponents[i]).name());

			if (currentName == compName) {
				return registeredComponents[i]->Clone();
			}
		}

		return nullptr;
	}

	// Check if a component exists in the registered components or not
	// Returns:
	//	 a bool that is true if it does exist and false if it doesn't
	template<class T>
	bool ComponentExists() {
		std::string compName = std::string(typeid(T).name());

		for (size_t i = 0; i < registeredComponents.size(); i++)
		{
			std::string currentName = std::string(typeid(*registeredComponents[i]).name());

			if (currentName == compName) {
				return true;
			}
		}

		return false;
	}

	// Saves an object to an archetype file so it can be loaded later.
	void SaveObjectToFile(GameObject* object);

	// Register a component so it can be created on the fly.
	// Template parameters:
	//   ComponentType = The type of the component to be registered.
	template <class ComponentType>
	void RegisterComponent() {
		if (!ComponentExists<ComponentType>()) {
			registeredComponents.push_back(new ComponentType());
		}
	}

	// Returns an instance of the factory.
	static GameObjectFactory& GetInstance();

	// Destructor is private to prevent accidental destruction
	~GameObjectFactory();

private:
	//------------------------------------------------------------------------------
	// Private Variables:
	//------------------------------------------------------------------------------

	// Array containing all components used by objects.
	std::vector<Component*> registeredComponents;

	std::string objectFilePath;

	

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Constructor is private to prevent accidental instantiation
	GameObjectFactory();

	
};

//------------------------------------------------------------------------------
