// copyright (c) 2023 James Couse All rights reserved
//
// Created by: James Couse
// Created on: Dec 2023
// This program is the "Space Aliens" program for the GameBoy

#include <gb/gb.h>
#include <stdio.h>

#include "SpaceAliens.c"
#include "MetaSprites.c"

int main() {
    set_sprite_data(0, 16, SpaceAliens);

    set_meta_sprite_tile(0, 1, 2, 3, 4);

    move_meta_sprite(0, 76, 120);

    SHOW_SPRITES;
    DISPLAY_ON;

    return 0;
}
