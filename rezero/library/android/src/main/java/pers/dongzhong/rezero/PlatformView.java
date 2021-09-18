// Created by Dong Zhong on 2021/09/16.

package pers.dongzhong.rezero;

import android.view.Surface;

class PlatformView {
  private long nativePtr;
  private RenderSurface renderSurface;

  public PlatformView(ReZeroView rezeroView) {
    nativePtr = nativeCreate(rezeroView);
  }

  public void attachToRenderSurface(RenderSurface renderSurface) {
    if (this.renderSurface != null) {
      detachFromRenderSurface();
    }

    this.renderSurface = renderSurface;
    this.renderSurface.attachToPlatformView(this);
  }

  public void detachFromRenderSurface() {
    if (this.renderSurface != null) {
      this.renderSurface.detachFromPlatformView();
      this.renderSurface = null;
      surfaceDestroy();
    }
  }

  void surfaceCreate(Surface surface) {
    if (nativePtr != 0) {
      nativeSurfaceCreate(nativePtr, surface);
    }
  }

  void surfaceDestroy() {
    if (nativePtr != 0) {
      nativeSurfaceDestroy(nativePtr);
    }
  }

  void surfaceChanged() {
    if (nativePtr != 0) {
      nativeSurfaceChanged(nativePtr);
    }
  }

  void release() {
    if (nativePtr != 0) {
      nativeDestroy(nativePtr);
      nativePtr = 0;
    }
  }

  private native long nativeCreate(ReZeroView rezeroView);
  private native void nativeDestroy(long nativePtr);
  private native void nativeSurfaceCreate(long nativePtr, Surface surface);
  private native void nativeSurfaceDestroy(long nativePtr);
  private native void nativeSurfaceChanged(long nativePtr);
}
