// Chip-8 Disassembler

// Specs
// Memory: 4KB Ram
// Display: 64x32 pixels, monochrome (Black or white)
// Program Counter, "PC" -> Points at the current instruction in memory
// One 16-bit index register called “I” which is used to point at locations in memory
// A stack for 16-bit addresses, which is used to call subroutines/functions and return from them
// An 8-bit delay timer which is decremented at a rate of 60hz until it reaches 0
// An 8-bit sound timer which functions like the delay timer, but which also gives off a beeping sound as long as it's not 0
// 16 8-bit (one byte) general-purpose variable registers numbered 0 through F hexadecile, ie. 0 through 15 in decimal, called V0 through VF
//     - VF is also used as a flag register; many instructions will set it to either 1 or 0 based on some rule, for example using it as a carry flag

// This is a good reference with no spoilers
// https://tobiasvl.github.io/blog/write-a-chip-8-emulator

//
// TODO
//

// - Make the loop run at a configurable Hz speed

// - Mostrar los registers usando dear imgui
// - Hacer que ImGui tenga varias ventanas abiertas y fijas!
// - 00E0 (Clear Screen)
// - Make the emulator loop run at 500hz
// - Cargar un rom desde el menu principal de la ventana
// - Create the Display array, array of bool values, maybe bits?
// - CPU should run at a fixed rate, 700 Instructions per second? Create a new parameter to set this, default at 700 (What the website above says)
// - Create Debug visualization that prints registers, pc, I (Maybe print to console and clear everyframe?)
// - Implement the instructions
//     - 1NNN (Jump)
//     - 6XNN (Set Register VX)
//     - 7XNN (Add value to register VX)
//     - ANNN (Set Index Register I)
//     - DXYN (Display/Draw) - This is the hardest instruction
// - Test this newly created instructions with the IBM Logo rom.
// - Get Dear::ImGUI Working? On a Separate Video?
// - Store Font in memory
// - Create a menu with ImGUI at the top of the window where we can load roms

#include <cstdint>
typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t    i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef float    f32;
typedef double   f64;
typedef i32      b32;

#define INLINE __forceinline
#include <assert.h>
#define Assert(Expr) assert(Expr)
#define InvalidCodePath Assert(!"InvalidCodePath")

#include <iostream>
#include <fstream>
#include <vector>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <SDL.h>

#include "application.cpp"

#include "ui.cpp"

struct chip8_interpreter
{
    u8   Memory[4096];
    u16 *PC;
    u16 *I;
    u8   V[16];
    u8   SoundTimer;
};

void LoadRom(chip8_interpreter *Interpreter, const std::string &Filename)
{
    std::ifstream File;
    File.open(Filename.c_str(), std::ifstream::binary);

    if(!File)
    {
        std::cout << "Error opening rom " << "\"" << Filename << "\"" << std::endl;
        exit(-1);
    }

    // Get the size of the file
    File.seekg (0, File.end);
    i32 FileSize = (i32)File.tellg();
    File.seekg (0, File.beg);

    // Memory starts at the 512 byte. The memory before this was there
    // to hold the chip8 interpreter and fonts.
    int AvailableMemory = 4096 - 512;
    if(FileSize > AvailableMemory)
    {
        std::cout << "ROM file size is bigger than available memory" << std::endl;
        std::cout << "FileSize: " << FileSize << " bytes" << std::endl;
        std::cout << "AvailableMemory: " << AvailableMemory << " bytes" << std::endl;
        exit(-1);
    }

    // Chip8 programs are loaded into memory at the 512 byte
    u8 *ProgramStart = Interpreter->Memory + 0x200;

    // Read data as a block:
    File.read((char*)ProgramStart, FileSize);
    File.close();

    // Set the Program counter to the beggining of the loaded ROM
    Interpreter->PC = (u16*)&Interpreter->Memory[512];
}

int main(int Argc, char **Argv)
{
    HandleApplicationArguments(Argc, Argv);

    application Application = {};
    CreateApplication(&Application, "WindowTitle", 1366, 768);

    chip8_interpreter Interpreter = {};
    LoadRom(&Interpreter, Argv[1]);

    UISetup(Application.Window, Application.Renderer);

    while(Application.IsRunning)
    {
        HandleInput(&Application);

        // Fetch
        u16 Instruction = *Interpreter.PC;
        Interpreter.PC++;

#define OPCODE(Expr) (((Expr) & 0x00F0) >> 4)
        // Decode & Execute
        // u16 OpCode = (Instruction & 0x00F0) >> 4;
        u16 OpCode = OPCODE(Instruction);
        switch(OpCode)
        {
            case 0x0:
            {
                // E000 -> 00E0 y luego & 0x0FFF
                // TODO(Jsanchez): Switch between E0 and EE
                // TODO: 00E0 clear the display
                // TODO: 00EE return from a subroutine
                std::cout << "0!" << std::endl;
                std::cout << std::hex << Instruction << std::endl;
                break;
            }
            case 0x1:
            {
                std::cout << "1!" << std::endl;
                break;
            }
            case 0x2:
            {
                std::cout << "2!" << std::endl;
                break;
            }
            case 0x3:
            {
                std::cout << "3!" << std::endl;
                break;
            }
            case 0x4:
            {
                std::cout << "4!" << std::endl;
                break;
            }
            case 0x5:
            {
                std::cout << "5!" << std::endl;
                break;
            }
            case 0x6:
            {
                std::cout << "6!" << std::endl;
                break;
            }
            case 0x7:
            {
                std::cout << "7!" << std::endl;
                break;
            }
            case 0x8:
            {
                std::cout << "8!" << std::endl;
                break;
            }
            case 0x9:
            {
                std::cout << "9!" << std::endl;
                break;
            }
            case 0xA:
            {
                std::cout << "A!" << std::endl;
                break;
            }
            case 0xB:
            {
                std::cout << "B!" << std::endl;
                break;
            }
            case 0xC:
            {
                std::cout << "C!" << std::endl;
                break;
            }
            case 0xD:
            {
                std::cout << "D!" << std::endl;
                break;
            }
            case 0xE:
            {
                std::cout << "E!" << std::endl;
                break;
            }
            case 0xF:
            {
                std::cout << "F!" << std::endl;
                break;
            }
            default:
            {
                std::cout << "OpCode: " << std::hex << OpCode << " not implemented." << std::endl;
            }
        }

        // Render UI
        UIBeginFrame();
        DrawRegistersWindow();
        UIEndFrame();

        SDL_SetRenderDrawColor(Application.Renderer, 255, 0, 255, 255);
        // SDL_RenderClear(Application.Renderer);
        SDL_RenderPresent(Application.Renderer);
    }

    UIDestroy();


    SDL_DestroyRenderer(Application.Renderer);
    SDL_DestroyWindow(Application.Window);
    SDL_Quit();

    return 0;
}
