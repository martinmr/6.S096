#ifndef _NBODY_WINDOW_H
#define _NBODY_WINDOW_H

#include <nbody/GlutWrapper.h>
#include <nbody/Shaders.h>
#include <nbody/System.h>

#include <glload/gl_3_0.h>
#include <glload/gll.hpp>
#include <GL/freeglut.h>

namespace nBodyShaders {
    const std::string vertex1(
            "#version 130\n"
            "in vec4 position;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = position;\n"
            "}\n"
            );

    const std::string fragment1(
            "#version 130\n"
            "out vec4 outputColor;\n"
            "void main()\n"
            "{\n"
            "   outputColor = vec4(1.0f,0.0f,0.0f,1.0f);"
            "}\n"
            );
} // namespace shaders

namespace nbody {

    class Window : public GlutWrapper {
        System *_system;
        int _nSteps;
        float _dt;
        Window( const Window &) = delete;
        Window operator=(const Window &) = delete;
        public:
        Window( const std::string &title, System *s, int nSteps, float dt,  
                Mode debugMode = Mode::NDEBUG );
        ~Window();

        void updateBuffer();
        void drawBuffer();

        void display();
        void reshape( int theWidth, int theHeight );
        void keyboard( unsigned char key, int x, int y );
    };
}

#endif // _NBODY_WINDOW_H
