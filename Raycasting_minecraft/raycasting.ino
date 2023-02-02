void RAYCASTING() {
  for (int x = 0; x < screenWidth; x++) {
    double cameraX = 2 * x / double(screenWidth) - 1;
    double rayDirX = dirX + planeX * cameraX;
    double rayDirY = dirY + planeY * cameraX;
    int mapX = int(posX);
    int mapY = int(posY);
    double sideDistX;
    double sideDistY;
    double deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);
    double perpWallDist;
    int stepX, stepY;
    int hit = 0;
    int side;
    if (rayDirX < 0) {
      stepX = -1;
      sideDistX = (posX - mapX) * deltaDistX;
    } else {
      stepX = 1;
      sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0) {
      stepY = -1;
      sideDistY = (posY - mapY) * deltaDistY;
    } else {
      stepY = 1;
      sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }
    while (hit == 0)
    {
      if (sideDistX < sideDistY) {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0;
      } else {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1;
      }
      if (worldMap[mapX][mapY] > 0) {
        hit = 1;
      }
    }
    if (side == 0) {
      perpWallDist = (sideDistX - deltaDistX);
    } else {
      perpWallDist = (sideDistY - deltaDistY);
    }
    if (x == screenWidth / 2) {
      targetDistance = perpWallDist;
      targetMapX = mapX;
      targetMapY = mapY;
    }
    int lineHeight = (int)(screenHeight / perpWallDist);
    int drawStart = -lineHeight / 2 + screenHeight / 2 + pitch;
    if (drawStart < 0) {
      drawStart = 0;
    }
    int drawEnd = lineHeight / 2 + screenHeight / 2 + pitch;
    if (drawEnd >= screenHeight) {
      drawEnd = screenHeight - 1;
    }
    uint16_t color;
    int8_t texNum;
    if (worldMap[mapX][mapY] > 0) {
      texNum = worldMap[mapX][mapY] - 1;
      DRAW_TEX(texNum);
    }
    double wallX;
    if (side == 0) {
      wallX = posY + perpWallDist * rayDirY;
    } else {
      wallX = posX + perpWallDist * rayDirX;
    }
    wallX -= floor(wallX);
    int texX = int(wallX * double(texWidth));
    if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0)) {

      texX = texWidth - texX - 1;
    }
    double oneStep = 1.0 * texHeight / lineHeight;
    double texPos = (drawStart - pitch - screenHeight / 2 + lineHeight / 2) * oneStep;
    for (int y = drawStart; y < drawEnd; y++) {
      int texY = (int)texPos & (texHeight - 1);
      texPos += oneStep;
      color = mixTex[texHeight * texX + texY];
      if (side == 1) {
        color = CHANGE_SIDE_TEX_COLOR(color);
      }
      frameImage[x][y] = color;
    }
  }
  oldFrame = nowFrame;
  nowFrame = millis();
  double frameTime = (nowFrame - oldFrame) / 1000.0;
  fps = (1.0 / frameTime);
  double moveSpeed = frameTime * 4.0;
  double rotSpeed = frameTime * 2.0;
  int8_t a = down_up();
  if (a != 0 && a != 5) {
    if (millis() >= t2 + 300) {
      t2 = millis();
      if (stepTemp == 0) {
        stepTemp = 1;
      } else {
        stepTemp = 0;
      }
    }
  } else {
    if (stepTemp != 0 && a == 0) {
      stepTemp = 0;
    }
    if (a == 5) {
      if (millis() >= t3 + 200) {
        t3 = millis();
        if (attackTemp < 4) {
          stepTemp = attackActoinGroup[attackTemp];
          attackTemp++;
        } else {
          attackTemp = 0;
          stepTemp = 0;
          if (CHECK_MAP_SIDE() == 1) {
            WEAPONHIT();
          }
        }
      }
    }
  }
  switch (a) {
    case 0: {
        break;
      }
    case blocklift: {
        if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) {
          posX -= dirX * moveSpeed;
        }
        if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) {
          posY -= dirY * moveSpeed;
        }
        break;
      }
    case blockright: {
        if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) {
          posX += dirX * moveSpeed;
        }
        if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) {
          posY += dirY * moveSpeed;
        }
        break;
      }
    case blockdown: {
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        break;
      }
    case blockup: {
        double oldDirX = dirX;
        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        break;
      }
    case blockc: {
        //   add_liewenTex
        break;
      }
  }
}
