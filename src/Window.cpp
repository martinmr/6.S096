#include <nbody/GlutWrapper.h>
#include <nbody/Shaders.h>
#include <nbody/Window.h>
#include <nbody/Vector3.h>

#include <glload/gl_3_0.h>
#include <glload/gll.hpp>
#include <GL/freeglut.h>

#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cmath>


namespace nbody {

    Window::Window( const std::string &title, System *s, int nSteps, float dt, 
                    Mode debugMode) : 
        GlutWrapper{ title, debugMode }, _system {s}, _nSteps{nSteps}, 
        _dt{dt} {
            _instance = this; 
        }

    Window::~Window() {}

    void Window::reshape( int theWidth, int theHeight ) {
        glViewport( 0, 0, (GLsizei) theWidth, (GLsizei) theHeight );
    }

    void Window::keyboard( unsigned char key, int /*x*/, int /*y*/ ) {
        const char ESCAPE_KEY = 27;
        if( key == ESCAPE_KEY ) {
            glutLeaveMainLoop();
        }
    }

    void Window::updateBuffer() {
        if(_nSteps > 0) {
               
            _system->update( _dt );
            
            size_t nBodies = _bufSize / 4;
            for( size_t i = 0; i < nBodies; ++i ) {
                Vector3f position = _system->body( i ).position();     
                _buf[4*i] =  position.x();
                _buf[4*i+1] = position.y();
                _buf[4*i+2] = position.z();
                _buf[4*i+3] = 1.0f; // ignore extra
            }

            glBindBuffer( GL_ARRAY_BUFFER, _positionBufferObject );
            glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( float ) * _bufSize, _buf );
            glBindBuffer( GL_ARRAY_BUFFER, 0 );

            _nSteps--;
        }
    }

    void Window::drawBuffer() {
        glUseProgram( _program );
        glBindBuffer( GL_ARRAY_BUFFER, _positionBufferObject );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );

        glDrawArrays( GL_POINTS, 0, (GLsizei) _bufSize );
        glDisableVertexAttribArray( 0 );
        glUseProgram( 0 );
    }

    void Window::display() {

        updateBuffer();

        glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        drawBuffer();

        glutSwapBuffers();
        glutPostRedisplay();
    }

} //namespace nbody
