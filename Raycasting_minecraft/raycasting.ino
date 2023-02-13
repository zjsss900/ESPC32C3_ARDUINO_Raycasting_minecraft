void RAYCASTING() {
  for (int x = 0; x < screenWidth; x++) {
    float cameraX = 2 * x / double(screenWidth) - 1;
    float rayDirX = dirX + planeX * cameraX;
    float rayDirY = dirY + planeY * cameraX;
    int mapX = int(posX);
    int mapY = int(posY);
    float sideDistX;
    float sideDistY;
    float deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
    float deltaDistY = (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);
    float perpWallDist;
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
    float wallX;
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
    float oneStep = 1.0 * texHeight / lineHeight;
    float texPos = (drawStart - pitch - screenHeight / 2 + lineHeight / 2) * oneStep;
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
  float frameTime = (nowFrame - oldFrame) / 1000.0;
  fps = (1.0 / frameTime);
  float moveSpeed = frameTime * 4.0;
  float rotSpeed = frameTime * 2.0;
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
        float oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        break;
      }
    case blockup: {
        float oldDirX = dirX;
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

void DRAW_FLOOR_AND_CEILING(){
  uint16_t color;
  int n=0,c=0;
  int8_t floorTexture=3;
  int8_t ceilingTexture=6;    
  if(texcsh==0){ 
    for(uint8_t a=0;a<texWidth;a++){
      for(uint8_t b=0;b<texHeight;b++){
        floorUsedTexture[n]=texture[floorTexture][c]<<8|texture[floorTexture][c+1];
        ceilingUsedTexture[n]=texture[ceilingTexture][c]<<8|texture[ceilingTexture][c+1];
        c+=2;
        n++;
      }
    }
    texcsh=1;  
  }
  for(int y=0;y<screenHeight;y++){
    float rayDirX0=dirX-planeX;
    float rayDirY0=dirY-planeY;
    float rayDirX1=dirX+planeX;
    float rayDirY1=dirY+planeY;
    int p=y-(screenHeight/2+pitch);
    float posZ=0.5*(screenHeight);
    float rowDistance=posZ/p;
    float floorStepX=rowDistance*(rayDirX1-rayDirX0)/screenWidth;
    float floorStepY=rowDistance*(rayDirY1-rayDirY0)/screenWidth;
    float floorX=posX+rowDistance*rayDirX0;
    float floorY=posY+rowDistance*rayDirY0;    
    for(int x=0;x<screenWidth;++x){
      int cellX=(int)(floorX);
      int cellY=(int)(floorY);
      int tx=(int)(texWidth*(floorX-cellX))&(texWidth-1);
      int ty=(int)(texHeight*(floorY-cellY))&(texHeight-1);
      floorX+=floorStepX;
      floorY+=floorStepY;
      if(y > screenHeight / 2 + pitch){
        color=floorUsedTexture[texWidth * ty + tx];      
      }else{    
        color=ceilingUsedTexture[texWidth*ty+tx];   
      }
      color=CHANGE_SIDE_TEX_COLOR(color);   
      frameImage[x][y]=color;
    }
  }
}

void LOOK_UP_DOWN(){
  if(millis()>=t6+50){
    t6=millis();
    if(pitch<40 && pitchBuffer==0){
      pitch++;
    }
    if(pitch==40){
      pitchBuffer=1;
    }
    if(pitch>-40 && pitchBuffer==1){
      pitch--;
    }
    if(pitch==-40){
      pitchBuffer=0;
    }
  }
}
