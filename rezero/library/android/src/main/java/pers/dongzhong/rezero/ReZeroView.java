// Created by Dong Zhong on 2021/09/13.

package pers.dongzhong.rezero;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.widget.FrameLayout;

import androidx.annotation.UiThread;

public class ReZeroView extends FrameLayout {
  private long nativePtr;

  public ReZeroView(Context context) {
    this(context, null);
  }

  public ReZeroView(Context context, AttributeSet attrs) {
    super(context, attrs);
    init();
  }

  public static String getVersion() {
    return nativeGetVersion();
  }

  static {
    try {
      System.loadLibrary("rezero");
    } catch (Throwable e) {
      Log.i("rezero", "Failed to load ReZero native libaray: ", e);
    }
  }

  private void init() {
    nativePtr = nativeCreate(getContext());
  }

  @UiThread
  public void release() {
    nativeRelease(nativePtr);
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
