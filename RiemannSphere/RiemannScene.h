#ifndef RIEMANNSCENE_H
#define RIEMANNSCENE_H

#include <Easy3D.h>
#include <CameraManager.h>
#include <SpheresManager.h>
#include <NewtonFractal.h>
#include <HalleyFractal.h>
#include <SchroederFractal.h>

namespace RiemannSphere {

	class RiemannScene : public Easy3D::Scene,
                                Easy3D::Input::KeyboardHandler,
                                Easy3D::Input::MouseHandler
    {
        
        Easy3D::Camera camera;
        Easy3D::Object obj;
        CameraManager  *cameraManager;
        Polynomial<double> poly;
        NewtonFractal<double> newton;
        HalleyFractal<double> halley;
        SchroederFractal<double> schroeder;
        SpheresManager *sphere;
        Easy3D::Font aharoni;
        
        enum SceneInfo{
            ON_RESUME,
            ON_PAUSE
        };
        SceneInfo sceneInfo;

	public:
		
        RiemannScene();
        ~RiemannScene();
        
        virtual void onPause();
        
        virtual void onResume();
        
        virtual void onStart();
        
        virtual void onRun(float dt);
        
        virtual void onEnd();

        virtual void onKeyDown(Easy3D::Key::Keyboard key);
        virtual void onMouseDown(Easy3D::Vec2 mousePosition,
                                 Easy3D::Key::Mouse button);
	};

};

#endif