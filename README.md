# GLFW 3 Sample Code

## これは何??
GLFW 3を使ったごく簡単なサンプルコードです。

* OpenGL 1.1での立方体描画
* マウスの左クリック→ドラッグで画面中央に表示されている立方体を回転

| ファイル | 説明 |
|----------|------|
| main.cpp     | メイン |
| defines.hpp  | 基本的な定義 |
| execGLFW.hpp | GLFWハンドリング |
| app.hpp      | 立方体の表示と操作 |

## 特徴
GLFW3からはWindowハンドルに対してユーザーポインタを与えられるようになりました。このお陰でコールバックに設定したクラスのstaticメソッドからクラスのインスタンスへアクセスするのが容易になりました。

これでようやく実行環境のクラスのインスタンスをローカル変数にできる!!

	int main() {
	  execGLFW exec;

	  while (exec.doUpdate());
	}
	
Xcode5.0.2とVisualStudio2012にてビルド、動作確認済。

* VisualStudio2013でビルドする場合は、glfw3.dllとWindows/lib/glfw3dll.libをWindows/VS2013のものと置き換えてください。


[⇒GLFW公式](http://www.glfw.org)
