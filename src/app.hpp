
#pragma once

//
// アプリケーション
//

#include "defines.hpp"
#include <Eigen/Geometry>


namespace ngs {

class App {
  // 記述が長いので短縮形を定義
  typedef Eigen::Quaternion<GLfloat> Quatf;
  typedef Eigen::Transform< GLfloat, 3, Eigen::Affine> Affinef;

  Quatf rotate_;

  
public:
  App() :
    rotate_(Quatf::Identity())
  {}

  ~App() {
  }


  void update(const float lapsed_time_sec) {
  }

  void draw() {
    glClearColor(0.25f, 0.25f, 0.25f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

		glCullFace(GL_BACK);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glFrustum(-0.5f, 0.5f, 0.5f, -0.5f, 0.8f, 5.0f);
    glTranslated(0.0, 0.0, -2.0f);

    glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

    Affinef m;
    m = rotate_;
    glMultMatrixf(m.data());
    
    // 立方体の頂点情報
		GLfloat vtx[] = {
      // 前
      //  x,     y,    z,
      -0.5f,  0.5f, 0.5f,
       0.5f,  0.5f, 0.5f,
       0.5f, -0.5f, 0.5f,
      -0.5f, -0.5f, 0.5f,
      
      // 後
      -0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      
      // 左
      -0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f,  0.5f,
      
      // 右
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      
      // 上
      -0.5f, 0.5f, -0.5f,
       0.5f, 0.5f, -0.5f,
       0.5f, 0.5f,  0.5f,
      -0.5f, 0.5f,  0.5f,
      
      // 底
      -0.5f, -0.5f,  0.5f,
       0.5f, -0.5f,  0.5f,
       0.5f, -0.5f, -0.5f,      
      -0.5f, -0.5f, -0.5f,
		};
		glVertexPointer(3, GL_FLOAT, 0, vtx);

    // 立方体の面法線
    GLfloat normal[] = {
      // 前
      //  x,     y,    z,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,

      // 後
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,

      // 左
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,

      // 右
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,

      // 上
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,

      // 下
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,
    };
    glNormalPointer(GL_FLOAT, 0, normal);
    
    GLfloat f4Ambient[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, f4Ambient);

    GLfloat f4Diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, f4Diffuse);

    GLfloat f4Specular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, f4Specular);

    GLfloat fShininess = 0.8f;
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, fShininess);

    // 頂点配列から三角形をまとめて描画
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
		// glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glDrawArrays(GL_QUADS, 0, 4 * 6);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
  }


  void touchStart(const Eigen::Vector2f& pos) {
  }

  void touchMove(const Eigen::Vector2f& pos, const Eigen::Vector2f& last_pos) {
    // 現在のタッチ位置 - 前回のタッチ位置 → 移動ベクトル
    Eigen::Vector2f d = pos - last_pos;

    float len = d.norm();
    if (len <= 0.0f) return;

    // 移動ベクトルと垂直なベクトル→回転ベクトル
    Eigen::Vector3f vec = Eigen::Vector3f(-d.y(), d.x(), 0.0f).normalized();

    // 回転量は移動ベクトルの長さから適当に決める
    Quatf q(Eigen::AngleAxisf(len * 0.01f, vec));
    rotate_ = q * rotate_;
  }
  
  void touchCancel(const Eigen::Vector2f& pos) {
  }
  
private:

  
};

}
