#include <gb/gb.h>

#include <stdio.h>

#include "media/main_map_tiles.c"
#include "media/main_map.c"
#include "media/mapL1.c"


#include "media/player.c"



UINT8 playerPos[2];

UINT8 i;
UINT8 gravity = 1;
UBYTE jump = 0;
UINT8 jumpCount = 0;
UBYTE jumpLock = 0;

UBYTE buttonDown = 0;

UINT8 mapwidth;
UINT8 level = 0;
void pDelay (UINT8 time) {
    for(i = 0; i< time ; i++) {
        wait_vbl_done();
    }
}

void dead (){
    move_sprite(0,24,144); 
    playerPos[0] = 24;
    playerPos[1] = 144;
}

void goLevel(UINT8 level){
    switch (level)
    {
    case 1:
        

        set_bkg_tiles(0,0,20,18,mapL1);
        mapwidth = mapL1Width;
        level = 1;
        break;
    
    default:
        

        set_bkg_tiles(0,0,20,18,main_map);
        mapwidth = main_mapWidth;
        level = 0;
        break;
    }

}


UBYTE isCollidingBackground (UINT8 newPosX,UINT8 newPosY) {
    UINT16 newPosXgrid = (newPosX - 8) /8;
    UINT16 newPosYgrid = (newPosY -16) /8;
    UINT16 map_array_pos = (mapwidth * newPosYgrid + newPosXgrid);
    if(level == 0){
        if(main_map[map_array_pos] == 0x27){
                move_sprite(0,152,24); 
                playerPos[0] = 152;
                playerPos[1] = 24;
            }
        if(main_map[map_array_pos] == 0x29){
            move_sprite(0,144,104); 
            playerPos[0] = 144;
            playerPos[1] = 104;
        }
        if(main_map[map_array_pos] == 0x28){
            goLevel(1);
        }
    }
    if(main_map[map_array_pos] == 0x00 || main_map[map_array_pos] == 0x0F){ 
        
        
        
        if(main_map[map_array_pos] == 0x0F & (newPosY % 8) >6 ){
            dead();
        }
        
        
        return 0;
    } else{
        return 1;
    }
    
}


void main(){

    set_bkg_data(0,45,map_tiles);
    

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    set_sprite_data(0,3,player);

    set_sprite_tile(0,0);
    
    move_sprite(0,24,144); 
       playerPos[0] = 24;
    playerPos[1] = 144;
    goLevel(0);
    

    while (1){
        buttonDown = 0;
        
        if(joypad() & J_RIGHT){
            buttonDown = 1;
            if(!isCollidingBackground(playerPos[0]+1 + 4 , playerPos[1] +7)){
                playerPos[0] += 1;
                scroll_sprite(0,1,0);
            }
            if(isCollidingBackground(playerPos[0]+ 4 , playerPos[1] + 8)){
            set_sprite_tile(0,1);
            set_sprite_prop(0,get_sprite_prop(0) & ~S_FLIPX);
            }


        }
         if(joypad() & J_LEFT){
             buttonDown = 1;
            if(!isCollidingBackground(playerPos[0]-1 + 4 , playerPos[1] + 7)){
                playerPos[0] -= 1;
                scroll_sprite(0,-1,0);
            }

            if(isCollidingBackground(playerPos[0]+ 4 , playerPos[1] + 8)){
            set_sprite_tile(0,1);
            
            set_sprite_prop(0,S_FLIPX);
            }
            


        }
         if(joypad() & J_A){
             buttonDown = 1;
            if(!jumpLock)
                jump = 1;
            
        }


        if(!buttonDown & isCollidingBackground(playerPos[0]+ 4 , playerPos[1] + 8)){
            // defauld
            if(!jump){
            set_sprite_prop(0,get_sprite_prop(0) & ~S_FLIPX);
            set_sprite_tile(0,0);
            }
        }
            
        
        

        
            
        

        if(!isCollidingBackground(playerPos[0]+ 4 , playerPos[1] + 8)){
            playerPos[1] += gravity;
            set_sprite_tile(0,2);
            set_sprite_prop(0,S_FLIPX);
            scroll_sprite(0,0,gravity);
            
        }else{
            jumpLock = 0;
        }


        if(jump){
            jumpLock = 1;
            gravity = 0;
            if(!isCollidingBackground(playerPos[0]+ 4 , playerPos[1]+2)) {
                playerPos[1] -= 2;
                scroll_sprite(0,0,-2);
            }
            set_sprite_tile(0,2);
            
            set_sprite_prop(0,S_FLIPX);

            jumpCount++;
            if(jumpCount > 13){
                jump = 0;
                jumpCount = 0;
                gravity = 1;
            }
        }


        pDelay(1);
    }


}