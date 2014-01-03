
#pragma once

//
// GLFW実行環境
//

// GLFWのリンク形式(Windows)
#define GLFW_DLL

#include "defines.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
#include <Eigen/Geometry>


// リンクするライブラリの指示(Windows)
#if defined (_MSC_VER)
#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "opengl32.lib")
#endif


namespace ngs {

template <typename T>
class ExecGLFW {
  GLFWwindow* window_;

  bool touching_;
  Eigen::Vector2f touch_pos_;
  Eigen::Vector2f touch_last_pos_;
  
  T app_;

  
public:
  ExecGLFW() :
    touching_(false),
    touch_pos_(0.0f, 0.0f),
    touch_last_pos_(0.0f, 0.0f)
  {
    DOUT << "ExecGLFW()" << std::endl;
    
    if (!glfwInit()) throw "Can't Initialize GLFW.";
    
    window_ = glfwCreateWindow(960, 640, PREPRO_TO_STR(PRODUCT_NAME), nullptr, nullptr);
    if (!window_) {
      glfwTerminate();
      throw "Can't create GLFW window.";
    }
    
    glfwSwapInterval(1);
    glfwMakeContextCurrent(window_);

    // GLFWのハンドルに自分自身を登録
    glfwSetWindowUserPointer(window_, this);

    // 各種コールバックを登録
    glfwSetWindowSizeCallback(window_, changeWindowSize);
    glfwSetKeyCallback(window_, createKeyInfo);
    glfwSetCharCallback(window_, createCharaInfo);
    glfwSetMouseButtonCallback(window_, mouseButtonCallback);
    glfwSetCursorPosCallback(window_, mouseMoveCallback);
  }
  
  ~ExecGLFW() {
    DOUT << "~ExecGLFW()" << std::endl;
    
    glfwDestroyWindow(window_);
    glfwTerminate();
  }

  
  bool doUpdate() {
    if (glfwWindowShouldClose(window_)) return false;

    app_.update(1.0f / 60);
    app_.draw();
    
    glfwSwapBuffers(window_);
    glfwPollEvents();    
    
    return true;
  }


  // GLFWのコールバック
  static void changeWindowSize(GLFWwindow* window, const int width, const int height) {
    ExecGLFW* exec = static_cast<ExecGLFW*>(glfwGetWindowUserPointer(window));
  }
  
  static void createKeyInfo(GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
    ExecGLFW* exec = static_cast<ExecGLFW*>(glfwGetWindowUserPointer(window));
  }

  static void createCharaInfo(GLFWwindow* window, const u_int chara) {
    ExecGLFW* exec = static_cast<ExecGLFW*>(glfwGetWindowUserPointer(window));
  }

  static void mouseButtonCallback(GLFWwindow* window, const int button, const int action, const int mods) {
    if (button != GLFW_MOUSE_BUTTON_1) return;

    double pos_x;
    double pos_y;
    glfwGetCursorPos(window, &pos_x, &pos_y);

    ExecGLFW* exec = static_cast<ExecGLFW*>(glfwGetWindowUserPointer(window));
    
    switch (action) {
    case GLFW_PRESS:
      {
        if (exec->touching_) {
          DOUT << "mouseButtonCallback:Already Touching" << std::endl;
          return;
        }

        exec->touching_ = true;
        exec->touch_pos_ << pos_x, pos_y;
        exec->app_.touchStart(exec->touch_pos_);
      }
      break;

    case GLFW_RELEASE:
      {
        if (!exec->touching_) {
          DOUT << "mouseButtonCallback:Don't Touching" << std::endl;
          return;
        }

        exec->touching_ = false;
        exec->touch_pos_ << pos_x, pos_y;
        exec->app_.touchCancel(exec->touch_pos_);
      }
      break;
    }
  }
  
  static void mouseMoveCallback(GLFWwindow* window, const double pos_x, const double pos_y) {
    ExecGLFW* exec = static_cast<ExecGLFW*>(glfwGetWindowUserPointer(window));

    if (!exec->touching_) return;
    
    exec->touch_last_pos_ = exec->touch_pos_;
    exec->touch_pos_ << pos_x, pos_y;
    exec->app_.touchMove(exec->touch_pos_, exec->touch_last_pos_);
  }

  
private:
  
};

}
