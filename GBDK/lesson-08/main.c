// copyright (c) 2023 James Couse All rights reserved
//
// Created by: James Couse
// Created on: Jan 2024
// This program is the "Space Aliens" program for the GameBoy

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "GBDK_Constants.h"
#include "SpaceAliens.c"
#include "MetaSprites.c"
#include "SpaceAliensBackgroundMap.c"
#include "SpaceAliensData.c"
#include "SpaceAliensMap.c"

typedef enum {
    SPLASH, 
    START, 
    GAME, 
    GAME_OVER
} screen_t;

screen_t splash( ) {
    uint8_t joypadData;
    screen_t next_screen = START;

    unsigned int timeCounter = 0;
    printf("\n\n\n\n\n");
    printf("   MT GAME STUDIOS");
    printf("        Presents");
    printf("\n\n\n\n\n\n");
    printf("    Space Aliens");
    DISPLAY_ON;
    while (1) {
        joypadData = joypad();
        if (joypadData & J_START) {
            return next_screen;
        }

        timeCounter++;
        if (timeCounter > (3 * 60)) {
            return next_screen;
        }

        wait_vbl_done();
    }
}

screen_t start() {
    screen_t next_screen = GAME;

    set_bkg_data(0, 215, space_aliens_data);
    set_bkg_tiles(0, 0, 20, 18, space_aliens_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);
    return next_screen;
}
screen_t game() {

    uint8_t joypadData;

    bool aButtonJustPressed = false;
    bool aButtonStillPressed  = false;

    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;


    const int FIXED_Y_SHIP_POSITION_OF_SHIP = 144;
    int shipXPosition = 76;
    int shipYPosition = FIXED_Y_SHIP_POSITION_OF_SHIP;

    set_sprite_data(0, 16, SpaceAliens);

    set_meta_sprite_tile(0, 1, 2, 3, 4);

    move_meta_sprite(0, shipXPosition, shipYPosition);

    set_bkg_data(0, 16, SpaceAliens);

    set_bkg_tiles(0, 0, 20, 36, SpaceAliensBackgroundMap);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while (1) {
        joypadData = joypad();

        if (joypadData & J_LEFT) {
            scroll_meta_sprite(0, -1, 0);
            shipXPosition -= 1;
            if (shipXPosition < 8) {
                shipXPosition = 8;
                move_meta_sprite(0, 8, FIXED_Y_SHIP_POSITION_OF_SHIP);
            }
        }
        if (joypadData & J_RIGHT) {
            scroll_meta_sprite(0, 1, 0);
            shipXPosition += 1;
            if (shipXPosition > SCREEN_WIDTH - 8) {
                shipXPosition = SCREEN_WIDTH - 8;
                move_meta_sprite(0, (uint8_t)(SCREEN_WIDTH - 8), FIXED_Y_SHIP_POSITION_OF_SHIP);
            }
        }
        if (joypadData & J_A) {
            if (aButtonJustPressed == true) {
                aButtonStillPressed = true;
            }
            else {
                aButtonJustPressed = true;

                NR10_REG = 0x16;
                NR11_REG = 0X82;
                NR12_REG = 0x69;
                NR13_REG = 0x59;
                NR14_REG = 0xC6;
            }
        }
        else {
            aButtonJustPressed = false;
            aButtonStillPressed = false;
        }

        scroll_bkg(0, -1);

        wait_vbl_done();
    }
}

void main () {
    screen_t current_screen = SPLASH;

    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;

    while(1) {
        if (current_screen == SPLASH) {
            current_screen = splash();
        }
        else if (current_screen == START) {
            current_screen = start();
        }
        else if (current_screen == GAME) {
            current_screen = game();
        }
        else if (current_screen == GAME_OVER) {
            printf("game_over");
        }
    }
}