
#include <gb/gb.h>
#include <stdio.h>


#include "player.c"

UINT8 playerx = 88;
UINT8 playery = 48;
UINT8 walkderetion = 0;
UINT8 walkdelay = 160; 

UINT8 walkspeedtype = 0;

UINT8 npcx = 88;
UINT8 npcy = 96;


UINT8 i = 0;

UBYTE walkanimation = 0;
void display () {
        move_sprite(0,playerx,playery);
        move_sprite(1,playerx,playery+8);
        move_sprite(2,playerx+8,playery);
        move_sprite(3,playerx+8,playery+8);

}


void walk (UINT8 *pos, UINT8 step, UINT8 times, UINT8 delaytime){
    for(i = 0; i < times; i++){
    *pos += step;
    display();
    delay(delaytime);
    }
}

UBYTE maywalk (UINT8 posx , UINT8 posy){

    if(posx > 0 & posx < 160 & posy > 0 & posy <= 144){

        if(posx >= npcx & posx < (npcx + 16) & posy >= npcy & posy < (npcy+16) ){
            return 0;
        }else{
             return 1;
        }

        
    }else{
        return 0;
    }

    
    
}


void main () {
set_sprite_data(0,22,playerData);

//player
set_sprite_tile(0,0);
set_sprite_tile(1,1);
set_sprite_tile(2,2);
set_sprite_tile(3,3);



move_sprite(0,playerx,playery);
move_sprite(1,playerx,playery+8);
move_sprite(2,playerx+8,playery);
move_sprite(3,playerx+8,playery+8);


//npc
set_sprite_tile(4,18);
set_sprite_tile(5,19);
set_sprite_tile(6,20);
set_sprite_tile(7,21);



move_sprite(4,npcx,npcy);
move_sprite(5,npcx,npcy+8);
move_sprite(6,npcx+8,npcy);
move_sprite(7,npcx+8,npcy+8);

SHOW_SPRITES;
DISPLAY_ON;


while (1)
{
    if(joypad() == J_DOWN){

        set_sprite_tile(0,0);
        set_sprite_tile(1,1);
        set_sprite_tile(2,2);
        set_sprite_tile(3,3);


        set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
        set_sprite_prop(3, get_sprite_prop(1) & ~S_FLIPX);
        set_sprite_prop(0, get_sprite_prop(1) & ~S_FLIPX);
        set_sprite_prop(2, get_sprite_prop(1) & ~S_FLIPX);
        
        if(walkderetion == 0 & maywalk(playerx, playery+16)){
        
        walk(&playery,4,2,walkdelay);
        if(walkanimation){
            set_sprite_tile(1,4);
            
            set_sprite_tile(3,5);
            
            
            display();
            walkanimation = 0;
        }else{
            set_sprite_tile(1,5);
            set_sprite_prop(1, S_FLIPX);
            set_sprite_tile(3,4);
            set_sprite_prop(3, S_FLIPX);
            display();
            
            walkanimation = 1;
        }
        
        walk(&playery,4,2,walkdelay);

        
        set_sprite_tile(1,1);
        set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
        set_sprite_tile(3,3);
        set_sprite_prop(3, get_sprite_prop(3) &~S_FLIPX);
        display();
        }else{
            walkderetion = 0;
            delay(100);
        }


    }


    if(joypad() == J_UP){
        set_sprite_tile(0,6);
        set_sprite_tile(2,8);
        set_sprite_tile(1,7);
        set_sprite_tile(3,9);


        set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
        set_sprite_prop(3, get_sprite_prop(1) & ~S_FLIPX);
        set_sprite_prop(0, get_sprite_prop(1) & ~S_FLIPX);
        set_sprite_prop(2, get_sprite_prop(1) & ~S_FLIPX);

        if(walkderetion == 2 & maywalk(playerx, playery-16)){
        
        walk(&playery,-4,2,walkdelay);
        if(walkanimation){
            set_sprite_tile(1,4);
            
            set_sprite_tile(3,5);
            
            
            display();
            walkanimation = 0;
        }else{
            set_sprite_tile(1,5);
            set_sprite_prop(1, S_FLIPX);
            set_sprite_tile(3,4);
            set_sprite_prop(3, S_FLIPX);
            display();
            
            walkanimation = 1;
        }
        
        walk(&playery,-4,2,walkdelay);

        
        set_sprite_tile(1,7);
        set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
        set_sprite_tile(3,9);
        set_sprite_prop(3, get_sprite_prop(3) &~S_FLIPX);
        display();
        }else{
            walkderetion = 2;
            delay(100);
        }
    }



    if(joypad() == J_LEFT){
        set_sprite_tile(0,10); 
        set_sprite_tile(2,12); 
        set_sprite_tile(1,11); 
        set_sprite_tile(3,13); 
        set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
        set_sprite_prop(3, get_sprite_prop(1) & ~S_FLIPX);
        set_sprite_prop(0, get_sprite_prop(1) & ~S_FLIPX);
        set_sprite_prop(2, get_sprite_prop(1) & ~S_FLIPX);

        if(walkderetion == 1 & maywalk(playerx-16, playery)){
        
        walk(&playerx,-4,2,walkdelay);
        if(walkanimation){
            set_sprite_tile(1,14);
            
            set_sprite_tile(3,15);
            
            
            display();
            walkanimation = 0;
        }else{
            set_sprite_tile(1,16);
            
            set_sprite_tile(3,17);
            
            display();
            
            walkanimation = 1;
        }
        walk(&playerx,-4,2,walkdelay);
        

        
        set_sprite_tile(1,11);
        
        set_sprite_tile(3,13);
        
        display();
        }else{
            walkderetion = 1;
            delay(100);
        }
    }


    if(joypad() == J_RIGHT){
        set_sprite_tile(0,12); 
        set_sprite_tile(2,10); 
        set_sprite_tile(1,13); 
        set_sprite_tile(3,11); 
        set_sprite_prop(1, S_FLIPX);
        set_sprite_prop(3, S_FLIPX);
        set_sprite_prop(0, S_FLIPX);
        set_sprite_prop(2, S_FLIPX);
        if(walkderetion == 3 & maywalk(playerx+16, playery)){
        
        walk(&playerx,4,2,walkdelay);
        if(walkanimation){
            set_sprite_tile(1,14);
            set_sprite_prop(1, get_sprite_prop(1) & ~S_FLIPX);
            set_sprite_tile(3,15);
            set_sprite_prop(3, get_sprite_prop(1) & ~S_FLIPX);
            
            display();
            walkanimation = 0;
        }else{
            set_sprite_tile(1,17);
            
            set_sprite_tile(3,16);
            
            display();
            
            walkanimation = 1;
        }
        
        walk(&playerx,4,2,walkdelay);
        set_sprite_prop(1, S_FLIPX);
        set_sprite_prop(3, S_FLIPX);
        
        
        set_sprite_tile(1,13);
        
        set_sprite_tile(3,11);
        
        display();
        }else{
            walkderetion = 3;
            delay(100);
        }
    }


    if(joypad() == J_A){
        switch (walkspeedtype)
        {
        case 0:
            walkspeedtype = 1;
            walkdelay = 50;
            break;
        
        case 2: 
            walkspeedtype = 0;
            walkdelay = 160;
            break;
        
        default:
            walkspeedtype = 0;
            walkdelay = 160;
            break;
        }


        delay(1000);

    }





}




}





