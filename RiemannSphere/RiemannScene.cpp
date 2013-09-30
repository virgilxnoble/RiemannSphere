#include <stdafx.h>
#include <RiemannScene.h>
#include <CameraManager.h>

///////////////////////
using namespace RiemannSphere;
using namespace Easy3D;
///////////////////////

RiemannScene::RiemannScene()
    :cameraManager(NULL)
    ,sceneInfo(ON_PAUSE)
    ,sphere("function.test.e2d", 3600*8, 3600*2*8,/*8000,8000,*/  7,/*livels*/ 3.0f,/*sphere radius*/ 180.0f/*detail per livels*/)
{
}

void RiemannScene::onStart(){
    //set clear color
    setClearColorState({25,128,255,255});
    //set projection and modelview
    setCullFaceState(CullFaceState(CullFace::BACK));
	//set client state
	setClientState(ClientState(ClientState::VERTEX|ClientState::COLOR));
    //add camera manage
    addChild(cameraManager=new CameraManager(&camera,Vec3::ZERO));
    cameraManager->setVelocity(Vec3(10,10,.0015));
    cameraManager->setProjectionInfo(Math::torad(10.0f), 1.0, 49);
    camera.setPosition(Vec3(0,0,50),true);
    setMatrixsState(MatrixsState(camera));
    //font
    aharoni.load("assets/game.font.e2d");
    //init
    onResume();
}

void RiemannScene::onResume(){
    //add input
    getInput()->addHandler((Easy3D::Input::KeyboardHandler*)this);
    getInput()->addHandler((Easy3D::Input::MouseHandler*)this);
    //set state
    cameraManager->setCurrentState(CameraManager::EVENTS::ON_ENABLE);
    //save info
    sceneInfo=ON_RESUME;
	//clear and draw
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

void RiemannScene::onRun(float dt){
    doClear();
    camera.update();
    setMatrixsState(MatrixsState(camera));
    
    
    if(getInput()->getKeyDown(Key::Q)){
        Camera cam2;
        cam2.setPerspective(Math::torad(25.0f), 1.0, 20.0);
        cam2.setPosition(Vec3(0,0,20),true);
        cam2.update();
        setMatrixsState(MatrixsState(cam2));
    }
    
    int livel=0;
    
    if(std::abs(cameraManager->getAngle())<0.05){
        livel=1;
    }
    if(std::abs(cameraManager->getAngle())<0.030){
        livel=2;
    }
    if(std::abs(cameraManager->getAngle())<0.020){
        livel=3;
    }
    if(std::abs(cameraManager->getAngle())<0.010){
        livel=4;
    }
    if(std::abs(cameraManager->getAngle())<0.006){
        livel=5;
    }
    if(std::abs(cameraManager->getAngle())<0.0025){
        livel=6;
    }/*
    if(std::abs(cameraManager->getAngle())<0.002){
        livel=7;
    }*/
    
	//draw sfere
	setClientState(ClientState(ClientState::VERTEX|ClientState::COLOR));
    setTextureState(TextureState(TextureState::NONE));
    sphere.draw(camera, livel);
    
	//draw text
	setClientState(ClientState(ClientState::VERTEX|ClientState::UVMAP));
    setTextureState(TextureState(TextureState::TEXTURE2D));
    aharoni.text(Vec2(10,10), "livello:"+String::toString(livel+1));
    
    
}

void RiemannScene::onPause(){
    //remove input
    getInput()->removeHandler((Easy3D::Input::KeyboardHandler*)this);
    getInput()->removeHandler((Easy3D::Input::MouseHandler*)this);
    //set state
    cameraManager->setCurrentState(CameraManager::EVENTS::ON_DISABLE);
    //save info
    sceneInfo=ON_PAUSE;
}

void RiemannScene::onEnd(){
    if(sceneInfo==ON_RESUME) onPause();
}

void RiemannScene::onKeyDown(Key::Keyboard key){}
void RiemannScene::onMouseDown(Vec2 mousePosition, Key::Mouse button){
    // if(button==Key::BUTTON_LEFT)
    //    obj.setTranslation(Vec3(0,0,-0.1f));
    // else if(button==Key::BUTTON_RIGHT)
    //      obj.setTranslation(Vec3(0,0,0.1f));
}
