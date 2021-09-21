// Created by Dong Zhong on 2021/09/18.

package pers.dongzhong.rezero;

import android.content.Context;
import android.view.Choreographer;
import android.view.WindowManager;

import androidx.annotation.NonNull;

class VsyncWaiter {
  @NonNull
  private WindowManager windowManager;

  private long weakNativePtr;

  static VsyncWaiter create(@NonNull Context context, long weakNativePtr) {
    WindowManager windowManager = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
    return new VsyncWaiter(windowManager, weakNativePtr);
  }

  VsyncWaiter(@NonNull WindowManager windowManager, long weakNativePtr) {
    this.windowManager = windowManager;
    this.weakNativePtr = weakNativePtr;
  }

  private void awaitVsync() {
    Choreographer.getInstance().postFrameCallback(new Choreographer.FrameCallback() {
      @Override
      public void doFrame(long frameTimeNanos) {
        float fps = windowManager.getDefaultDisplay().getRefreshRate();
        long refreshPeriodNanos = (long) (1000000000.0 / fps);
        nativeOnVsync(frameTimeNanos, frameTimeNanos + refreshPeriodNanos, weakNativePtr);
      }
    });
  }

  void release() {
    if (weakNativePtr != 0) {
      nativeRelease(weakNativePtr);
      weakNativePtr = 0;
    }
  }

  private static native void nativeOnVsync(long frameStartTime, long frameEndTime, long weakNativePtr);
  private native void nativeRelease(long weakNativePtr);
}
