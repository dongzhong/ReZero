// Created by Dong Zhong on 2021/09/16.

package pers.dongzhong.rezero;

import android.content.Context;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

class ReZeroSurfaceView extends SurfaceView implements RenderSurface {
  private boolean isAttachedToPlatformView = false;
  private boolean isSurfaceAvailable = false;

  @Nullable
  private PlatformView platformView;

  private final SurfaceHolder.Callback callback = new SurfaceHolder.Callback() {
    @Override
    public void surfaceCreated(@NonNull SurfaceHolder holder) {
      isSurfaceAvailable = true;

      if (isAttachedToPlatformView) {
        connectToPlatformView();
      }
    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder holder, int format, int width, int height) {
      if (isAttachedToPlatformView) {
        surfaceChange();
      }
    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder holder) {
      isSurfaceAvailable = false;

      if (isAttachedToPlatformView) {
        disconnectFromPlatformView();
      }
    }
  };

  public ReZeroSurfaceView(Context context) {
    this(context, null);
  }

  public ReZeroSurfaceView(Context context, AttributeSet attrs) {
    super(context, attrs);
    init();
  }

  private void init() {
    getHolder().addCallback(callback);
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
    if (this.platformView == null || getHolder() == null) {
      throw new IllegalStateException(
          "connectToPlatformView() should only be called when platformView and getHolder() are non-null.");
    }

    this.platformView.surfaceCreate(getHolder().getSurface());
  }

  private void disconnectFromPlatformView() {
    if (this.platformView == null) {
      throw new IllegalStateException(
              "disconnectFromPlatformView() should only be called when platformView is non-null.");
    }

    this.platformView.surfaceDestroy();
  }

  private void surfaceChange() {
    if (this.platformView == null) {
      throw new IllegalStateException(
              "surfaceChange() should only be called when platformView is non-null.");
    }

    this.platformView.surfaceChanged();
  }

  @Override
  protected void onVisibilityChanged(View changedView, int visibility) {
    super.onVisibilityChanged(changedView, visibility);
    if (this.platformView != null) {
      this.platformView.setVisibilityChanged(isShown());
    }
  }
}
