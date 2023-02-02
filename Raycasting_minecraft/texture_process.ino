void DRAW_BACKGROUND() {
  uint16_t c;
  for (int x = 0; x < screenWidth; x++) {
    for (int y = 0; y < screenHeight; y++) {
      if (y >= screenHeight / 2 + pitch) {
        c = TFT_OLIVE;
      } else {
        c = TFT_SKYBLUE;
      }
      frameImage[x][y] = c;
    }
  }
}

void wddd() {
  int n = 0;
  for (int x = 0; x < screenWidth; x++) {
    for (int y = 0; y < screenHeight; y++) {
      ddd[n] = frameImage[screenWidth - x][y];
      n++;
    }
  }
}

uint16_t CHANGE_SIDE_TEX_COLOR(uint16_t color) {
  uint16_t newColor;
  uint16_t color_Red, color_Green, color_Blue;
  color_Red = (color & 0xF800) >> 11;
  color_Green = (color & 0x07E0) >> 5;
  color_Blue = color & 0x001F;
  newColor = (int(color_Red / 2) << 11) | (int(color_Green / 2) << 5) | int(color_Blue / 2);
  return newColor;
}

void TRANSFOR_INT8_TO_INT16(uint8_t i) {
  int n = 0, c = 0;
  for (uint8_t a = 0; a < texWidth; a++) {
    for (uint8_t b = 0; b < texHeight; b++) {
      mixTex[n] = texture[i][c] << 8 | texture[i][c + 1];
      c += 2;
      n++;
    }
  }
}

void DO_MIX(uint8_t tex, int8_t lw) {
  int n = 0, c = 0;
  uint16_t lwBuffer = 0;
  TRANSFOR_INT8_TO_INT16(tex);
  for (uint8_t a = 0; a < texWidth; a++) {
    for (uint8_t b = 0; b < texHeight; b++) {
      lwBuffer = liewen[lw][c] << 8 | liewen[lw][c + 1];
      c += 2;
      n++;
      if (lwBuffer == 0) {
        mixTex[n] = lwBuffer;
      }
    }
  }
}

void MIX_TOW_TEX(int8_t texNum) {
  if (texNum >= 30 && texNum < 60) {
    DO_MIX(texNum - 30, 0);
  }
  if (texNum >= 60 && texNum < 90) {
    DO_MIX(texNum - 30 * 2, 1);
  }
  if (texNum > 90 && texNum < 120) {
    DO_MIX(texNum - 30 * 3, 2);
  }
}

void DRAW_TEX(int8_t texNum) {
  if (texNum < 30 && texNum != 15 && texNum != 16) {
    TRANSFOR_INT8_TO_INT16(texNum);
  } else if (texNum == 90) {
    PLAY_JNTM();
  } else if (texNum == 15) {
    PLAY_BADAPPLE(15);
  } else if (texNum == 16) {
    PLAY_BADAPPLE(16);
  } else {
    MIX_TOW_TEX(texNum);
  }
}

void PLAY_JNTM() {
  int n = 0, c = 0;
  for (uint8_t a = 0; a < texWidth; a++) {
    for (uint8_t b = 0; b < texHeight; b++) {
      mixTex[n] = jntm[jntmFrame][c] << 8 | jntm[jntmFrame][c + 1];
      c += 2;
      n++;
    }
  }
  if (millis() >= t4 + 200) {
    t4 = millis();
    if (jntmFrame < 44) {
      jntmFrame++;
    } else {
      jntmFrame = 0;
    }
  }
}

void PLAY_BADAPPLE(int8_t texNum) {
  int n = 0, c = 0;
  for (uint8_t a = 0; a < texWidth; a++) {
    for (uint8_t b = 0; b < texHeight; b++) {
      if (texNum == 15) {
        mixTex[n] = badapple[badappleFrame][c] << 8 | badapple[badappleFrame][c + 1];
      } else if (texNum == 16) {
        mixTex[n] = badapple[badappleFrame][c + texWidth * texHeight * 2] << 8 | badapple[badappleFrame][c + texWidth * texHeight * 2 + 1];
      }
      c += 2;
      n++;
    }
  }
  if (millis() >= t5 + 300) {
    t5 = millis();
    if (badappleFrame < 84) {
      badappleFrame++;
    } else {
      badappleFrame = 0;
    }
  }
}
