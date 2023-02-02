void WEAPONHIT() {
  if (targetDistance <= 1.5) {
    if (worldMap[targetMapX][targetMapY] < 90) {
      worldMap[targetMapX][targetMapY] += 30;
    } else {
      if (worldMap[targetMapX][targetMapY] != 91) {
        worldMap[targetMapX][targetMapY] = 0;
      }else{
       // jntmMapX=targetMapX;
        //jntmMapY=targetMapY;
      }
    }
  }
}

bool CHECK_MAP_SIDE() {
  if (targetMapX == 0 || targetMapY == 0 || targetMapX == mapWidth - 1 || targetMapY == mapHeight - 1) {
    return 0;
  } else {
    return 1;
  }
}

void DRAW_WEAPONS_TO_SCREEN(int typeOfWeapon) {
  uint8_t wStart = 0, hStart = 0;
  int n = 0, c = 0;
  uint16_t weaponsBuffer = 0;
  if (stepTemp == 0) {
    wStart = screenWidth - chutou1_texWidth;
    hStart = screenHeight - chutou1_texHeight;
    for (uint8_t a = wStart; a < wStart + chutou1_texWidth; a++) {
      for (uint8_t b = hStart; b < hStart + chutou1_texHeight; b++) {
        weaponsBuffer = chutou1[c] << 8 | chutou1[c + 1];
        c += 2;
        n++;
        if (weaponsBuffer != 0) {
          frameImage[a][b] = weaponsBuffer;
        }
      }
    }
  }
  if (stepTemp == 1) {
    wStart = screenWidth - chutou2_texWidth;
    hStart = screenHeight - chutou2_texHeight;
    for (uint8_t a = wStart; a < wStart + chutou2_texWidth; a++) {
      for (uint8_t b = hStart; b < hStart + chutou2_texHeight; b++) {
        weaponsBuffer = chutou2[c] << 8 | chutou2[c + 1];
        c += 2;
        n++;
        if (weaponsBuffer != 0) {
          frameImage[a][b] = weaponsBuffer;
        }
      }
    }
  }
  if (stepTemp == 2) {
    wStart = screenWidth - chutou3_texWidth - 40;
    hStart = screenHeight - chutou3_texHeight;
    for (uint8_t a = wStart; a < wStart + chutou3_texWidth; a++) {
      for (uint8_t b = hStart; b < hStart + chutou3_texHeight; b++) {
        weaponsBuffer = chutou3[c] << 8 | chutou3[c + 1];
        c += 2;
        n++;
        if (weaponsBuffer != 0) {
          frameImage[a][b] = weaponsBuffer;
        }
      }
    }
  }
}
