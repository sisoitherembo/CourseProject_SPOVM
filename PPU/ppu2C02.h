//
// Created by dmitry on 17/05/2021.
//

#ifndef NES_EMULATOR_PPU2C02_H
#define NES_EMULATOR_PPU2C02_H


#pragma once
#include <cstdint>
#include <memory>

#include "../olcPixelEngine/olcPixelGameEngine.h"

#include "Cartridge.h"

class ppu2C02
{
public:
    ppu2C02();
    ~ppu2C02();

private:
    uint8_t     tblName[2][1024];
    uint8_t     tblPattern[2][4096]; // unnececcary
    uint8_t		tblPalette[32];

private:
    olc::Pixel  palScreen[0x40];
    olc::Sprite sprScreen          =   olc::Sprite(256, 240);
    olc::Sprite sprNameTable[2]    = { olc::Sprite(256, 240), olc::Sprite(256, 240) };
    olc::Sprite sprPatternTable[2] = { olc::Sprite(128, 128), olc::Sprite(128, 128) };

public:
    // Debugging Utilities
    olc::Sprite& GetScreen();
    olc::Sprite& GetNameTable(uint8_t i);
    olc::Sprite& GetPatternTable(uint8_t i);
    bool frame_complete = false;

private:
    int16_t scanline = 0;
    int16_t cycle = 0;


public:
    // Communications with Main Bus
    uint8_t cpuRead(uint16_t addr, bool rdonly = false);
    void    cpuWrite(uint16_t addr, uint8_t  data);

    // Communications with PPU Bus
    uint8_t ppuRead(uint16_t addr, bool rdonly = false);
    void    ppuWrite(uint16_t addr, uint8_t data);

private:
    // The Cartridge or "GamePak"
    std::shared_ptr<Cartridge> cart;

public:
    // Interface
    void ConnectCartridge(const std::shared_ptr<Cartridge>& cartridge);
    void clock();
};

#endif //NES_EMULATOR_PPU2C02_H
