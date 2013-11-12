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
#include <RiemannSceneGeodesic.h>
#include <RiemannSceneGLSL.h>
#include <RiemannMenu.h>

//last exemple http://pastebin.com/RGFiAuBs

using namespace Easy3D;

class RiemannApp : public Game,
                   public Easy3D::Input::KeyboardHandler {
    
                       
    //UI
    RiemannGui::RiemannMenu menu;
                       
    public:
    
    
    RiemannApp()
    :Game("RiemannSphere",1280,720,32,30,false,Screen::MSAAx4)
    ,menu(Table("assets/menu.e2d")){}
    
    enum SCENE{
        RIEMANN_SCENE_GEODESIC=0,
        RIEMANN_SCENE=1,
        RIEMANN_GLSL_SCENE=2
    };
    
    enum GUI_STATE{
        GUI_DRAW,
        GUI_PRINT
    };
    
    
                       
    void onStart(){
        //add input keyboard
        getInput()->addHandler((Easy3D::Input::KeyboardHandler*)this);
		//scenes
        addSceneAndActive(RIEMANN_SCENE_GEODESIC, new RiemannSphere::RiemannSceneGeodesic());
        //addScene(RIEMANN_SCENE, new RiemannSphere::RiemannScene());
        addScene(RIEMANN_GLSL_SCENE, new RiemannSphere::RiemannSceneGLSL());
        //exit key
        menu.addOnClick("exit", [this](){
            onKeyDown(Key::ESCAPE);
        });
        menu.addOnClick("reload", [this](){
            onKeyDown(Key::R);
        });
        menu.addOnClick("print", [this](){
            setCurrentState(GUI_PRINT);
        });
        addState(GUI_DRAW,new Easy3D::StateLambda([this](float dt){
            //update ui
            menu.update(dt);
            //draw ui
            menu.draw(this);
        }));
        addState(GUI_PRINT,new Easy3D::StateLambda([this](float dt){
            //save
            Image *screenImage=Image::getImageFromScreen(getScreen()->getWidth(),getScreen()->getHeight());
            int i=0; while(1){
                Utility::Path imgPath("image"+String::toString(i)+".tga");
                if(!imgPath.existsFile()){
                    screenImage->save(imgPath);
                    break;
                }
                ++i;
            };
            
            delete screenImage;
            setCurrentState(GUI_DRAW);
        }));
        //enable draw
        setCurrentState(GUI_DRAW);
    }
    
    void onRun(float dt){
    }

    virtual void onKeyDown(Easy3D::Key::Keyboard key){
        //if(key==Key::V) activeScene(RIEMANN_SCENE);
        if(key==Key::C) activeScene(RIEMANN_SCENE_GEODESIC);
		if(key==Key::G) activeScene(RIEMANN_GLSL_SCENE);
        
        /*
         if(key==Key::R && sceneActive()==RIEMANN_SCENE) {
         auto scene=eraseScene(RIEMANN_SCENE);
         delete scene;
         addSceneAndActive(RIEMANN_SCENE, new RiemannSphere::RiemannScene());
         }*/
		if(key==Key::R && sceneActive()==RIEMANN_SCENE_GEODESIC) {
            //scene
            auto scene=eraseScene(RIEMANN_SCENE_GEODESIC);
            //save position
            auto cpi=((RiemannSphere::RiemannSceneGeodesic*)(scene))->getCameraPositionInfo();
            //delete scene
            delete scene;
            //new scene
            auto newscene=new RiemannSphere::RiemannSceneGeodesic();
            //active
            addSceneAndActive(RIEMANN_SCENE_GEODESIC, newscene);
            //set position
            newscene->setCameraPositionInfo(cpi);
        }
		if(key==Key::R && sceneActive()==RIEMANN_GLSL_SCENE) {
            //scene
            auto scene=eraseScene(RIEMANN_GLSL_SCENE);
            //save position
            auto cpi=((RiemannSphere::RiemannSceneGLSL*)(scene))->getCameraPositionInfo();
            //delete scene
            delete scene;
            //new scene
            auto newscene=new RiemannSphere::RiemannSceneGLSL();
            //active
            addSceneAndActive(RIEMANN_GLSL_SCENE, newscene);
            //set position
            newscene->setCameraPositionInfo(cpi);
        }
        if(key==Key::ESCAPE)
            Application::instance()->exit();
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