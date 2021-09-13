// Created by Dong Zhong on 2021/09/13.

package pers.dongzhong.rezero.example;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.FrameLayout;
import android.widget.TextView;

import pers.dongzhong.rezero.ReZeroView;

public class MainActivity extends AppCompatActivity {
  private ReZeroView reZeroView;
  private FrameLayout frameLayout;
  private TextView textView;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);

    frameLayout = findViewById(R.id.main_view);

    textView = new TextView(getBaseContext());
    textView.setText(ReZeroView.getVersion());

    frameLayout.addView(textView);
    reZeroView = findViewById(R.id.rezero_view);
  }
}