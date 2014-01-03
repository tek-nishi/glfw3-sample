
//
// メイン
//

#include <cstdlib>
#include "execGLFW.hpp"
#include "app.hpp"


int main() {
  ngs::ExecGLFW<ngs::App> exec;

  while (exec.doUpdate());
}
