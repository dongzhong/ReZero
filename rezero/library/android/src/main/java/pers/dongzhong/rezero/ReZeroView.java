// Created by Dong Zhong on 2021/09/13.

package pers.dongzhong.rezero;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.widget.FrameLayout;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.UiThread;

public class ReZeroView extends FrameLayout {
  private long nativePtr;
  private RenderMode renderMode;
  private RenderSurface renderSurface;

  @Nullable
  private PlatformView platformView;

  @UiThread
  public ReZeroView(@NonNull Context context) {
    this(context, null, null);
  }

  @UiThread
  public ReZeroView(@NonNull Context context, @Nullable AttributeSet attrs) {
    this(context, attrs, null);
  }

  @UiThread
  public ReZeroView(@NonNull Context context, @Nullable RenderMode renderMode) {
    this(context, null, renderMode);
  }

  @UiThread
  public ReZeroView(@NonNull Context context, @Nullable AttributeSet attrs, @Nullable RenderMode renderMode) {
    super(context, attrs);
    this.renderMode = renderMode == null ? RenderMode.texture : renderMode;
    init();
  }

  public static String getVersion() {
    return nativeGetVersion();
  }

  static {
    try {
      System.loadLibrary("rezero");
    } catch (Throwable e) {
      Log.i("rezero", "Failed to load ReZero native library: ", e);
    }
  }

  private void init() {
    nativePtr = nativeCreate(getContext());
    platformView = new PlatformView(this);

    switch (renderMode) {
      case texture:
        ReZeroTextureView textureView = new ReZeroTextureView(getContext());
        renderSurface = textureView;
        addView(textureView);
        break;
      case surface:
        ReZeroSurfaceView surfaceView = new ReZeroSurfaceView(getContext());
        renderSurface = surfaceView;
        addView(surfaceView);
        break;
    }
    platformView.attachToRenderSurface(renderSurface);
  }

  @UiThread
  public void release() {
    if (platformView != null) {
      platformView.release();
      platformView = null;
    }

    if (nativePtr != 0) {
      nativeRelease(nativePtr);
      nativePtr = 0;
    }
  }

  @Override
  protected void finalize() throws Throwable {
    release();
    super.finalize();
  }

  private static native String nativeGetVersion();
  private native long nativeCreate(Context context);
  private native void nativeRelease(long nativePtr);
}
