// Created by Dong Zhong on 2021/09/16.

package pers.dongzhong.rezero;

import androidx.annotation.NonNull;

interface RenderSurface {
  void attachToPlatformView(@NonNull PlatformView platformView);

  void detachFromPlatformView();
}
