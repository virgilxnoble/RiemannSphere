﻿#ifndef WINDOWSAPP_H
#define WINDOWSAPP_H

#include <Config.h>
#include <Application.h>
#include <Utility.h>
#include <Game.h>

namespace Easy3D {
	
	/**
    * Abstract class, represent the application instance
	* @class Application <Application.h>
    */
	class WindowsApp : Application{
	public:
		/**
		* destroy an window application
		*/
		virtual ~WindowsApp();
		/**
		* load a binary file
		* @return succes
		*/
		virtual bool loadData(const String& path,void*& ptr,size_t &len);
		/**
		* where you can save files data
		* @return path
		*/
		virtual String appDataDirectory();
		/**
		* application root (read only)
		* @return path
		*/
		virtual String appWorkingDirectory();
		/**
		* resources directory (read only)
		* @return path
		*/
		virtual String appResourcesDirectory();			
		/**
		* application exit method
		*/
		virtual void exit();
		/**
		* application loop
		*/
		virtual void loop();		
		/**
		* execute a instance application
		*/
		virtual void exec(Game *game);
		/**
		* application update
		*/
		virtual void update(float dt);
		/**
		* return true if device supports only power of two texture
		*/
		virtual bool onlyPO2();
		/**
		* open save dialog
		*/
		virtual bool openSaveDialog(const String& title,
									const String& path,
									const std::vector<String>& types,
									Utility::Path& out);

	protected:

		//local vars
		int doexit;
		//protected constructor
		WindowsApp();

		friend class Application;

	};


};

#endif