// copyright (c) 2023 James Couse All rights reserved
//
// Created by: James Couse
// Created on: Jan 2024
// This program is the "Space Aliens" program for the GameBoy

#include <gb/gb.h>
#include <stdio.h>

#include "SpaceAliens.c"
#include "MetaSprites.c"
#include "SpaceAliensBackgroundMap.c"

void main() {

    uint8_t joypadData;

    set_sprite_data(0, 16, SpaceAliens);

    set_meta_sprite_tile(0, 1, 2, 3, 4);

    move_meta_sprite(0, 76, 120);

    set_bkg_data(0, 16, SpaceAliens);

    set_bkg_tiles(0, 0, 20, 36, SpaceAliensBackgroundMap);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while (1) {
        joypadData = joypad();

        if (joypadData & J_LEFT) {
            scroll_meta_sprite(0, -1, 0);
        }
        if (joypadData & J_RIGHT) {
            scroll_meta_sprite(0, 1, 0);
        }
        if (joypadData & J_DOWN) {
            scroll_meta_sprite(0, 0, 1);
        }
        if (joypadData & J_UP) {
            scroll_meta_sprite(0, 0, -1);
        }

        scroll_bkg(0, -1);

        wait_vbl_done();
    }
}
