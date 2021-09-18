// Created by Dong Zhong on 2021/09/16.

package pers.dongzhong.rezero;

import android.content.Context;
import android.graphics.SurfaceTexture;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.TextureView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

class ReZeroTextureView extends TextureView implements RenderSurface {
  private boolean isAttachedToPlatformView = false;
  private boolean isSurfaceAvailable = false;
  private Surface surface;

  @Nullable
  private PlatformView platformView;

  private final SurfaceTextureListener listener = new SurfaceTextureListener() {
    @Override
    public void onSurfaceTextureAvailable(@NonNull SurfaceTexture surface, int width, int height) {
      isSurfaceAvailable = true;

      if (isAttachedToPlatformView) {
        connectToPlatformView();
      }
    }

    @Override
    public void onSurfaceTextureSizeChanged(@NonNull SurfaceTexture surface, int width, int height) {
      if (isAttachedToPlatformView) {
        surfaceChange();
      }
    }

    @Override
    public boolean onSurfaceTextureDestroyed(@NonNull SurfaceTexture surface) {
      isSurfaceAvailable = false;

      if (isAttachedToPlatformView) {
        disconnectFromPlatformView();
      }

      return true;
    }

    @Override
    public void onSurfaceTextureUpdated(@NonNull SurfaceTexture surface) {
      // Nothing to do.
    }
  };

  public ReZeroTextureView(@NonNull Context context) {
    this(context, null);
  }

  public ReZeroTextureView(@NonNull Context context, @Nullable AttributeSet attrs) {
    super(context, attrs);
    init();
  }

  private void init() {
    setSurfaceTextureListener(listener);
  }

  @Override
  public void attachToPlatformView(@NonNull PlatformView platformView) {
    if (this.platformView != null) {
      this.platformView.detachFromRenderSurface();
    }

    this.platformView = platformView;
    isAttachedToPlatformView = true;

    if (isSurfaceAvailable) {
      connectToPlatformView();
    }
  }

  @Override
  public void detachFromPlatformView() {
    if (this.platformView != null) {
      if (getWindowToken() != null) {
        disconnectFromPlatformView();
      }

      this.platformView = null;
      isAttachedToPlatformView = false;
    }
  }

  private void connectToPlatformView() {
    if (this.platformView == null || getSurfaceTexture() == null) {
      throw new IllegalStateException(
          "connectToPlatformView() should only be called when platformView and getSurfaceTexture() are non-null.");
    }

    surface = new Surface(getSurfaceTexture());
    this.platformView.surfaceCreate(surface);
  }

  private void disconnectFromPlatformView() {
    if (this.platformView == null) {
      throw new IllegalStateException(
          "disconnectFromPlatformView() should only be called when platformView is non-null.");
    }

    this.platformView.surfaceDestroy();
    if (surface != null) {
      surface.release();
      surface = null;
    }
  }

  private void surfaceChange() {
    if (this.platformView == null) {
      throw new IllegalStateException(
          "surfaceChange() should only be called when platformView is non-null.");
    }

    this.platformView.surfaceChanged();
  }
}
