//
//  main.cpp
//  RiemannSphere
//
//  Created by Gabriele Di Bari on 14/08/13.
//  Copyright (c) 2013 Gabriele Di Bari. All rights reserved.
//
#include <stdafx.h>
#include <stdio.h>
#include <Config.h>
#include <Application.h>
#include <Game.h>
#include <RiemannScene.h>
#include <RiemannSceneGLSL.h>

//last exemple http://pastebin.com/RGFiAuBs

using namespace Easy3D;

class RiemannApp : public Game,
                   public Easy3D::Input::KeyboardHandler {
    
    public:
    
    
		RiemannApp():Game("RiemannSphere",1280,720,32,30,false,Screen::MSAAx4){}
    
    enum SCENE{
        RIEMANN_SCENE=0,
        RIEMANN_GLSL_SCENE=1
    };
    
    void onStart(){
        //add input keyboard
        getInput()->addHandler((Easy3D::Input::KeyboardHandler*)this);
		//scenes
        addScene(RIEMANN_SCENE, new RiemannSphere::RiemannScene());
        addSceneAndActive(RIEMANN_GLSL_SCENE, new RiemannSphere::RiemannSceneGLSL());
    }
    
    void onRun(float dt){
    }

	virtual void onKeyDown(Easy3D::Key::Keyboard key){
		if(key==Key::C) activeScene(RIEMANN_SCENE);
		if(key==Key::G) activeScene(RIEMANN_GLSL_SCENE);
	}

    void onEnd(){
		getInput()->removeHandler((Easy3D::Input::KeyboardHandler*)this);    
    }
    
    
        
};

int main(int argc,const char *args[]){
    
    Application::create();
    Application::instance()->exec(new RiemannApp());
    delete Application::instance()->getGame();
    return 0;
}