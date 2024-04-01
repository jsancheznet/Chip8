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

// WIP
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

#include "gui.cpp"


void LoadRomToMemory(const std::string &Filename, u8 *Buffer)
{
    std::ifstream File;
    File.open(Filename.c_str(), std::ifstream::binary);

    if(!File)
    {
        std::cout << "Error opening rom " << "\"" << Filename << "\"" << std::endl;
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

    // Read data as a block:
    File.read((char*)Buffer, FileSize);
    File.close();
}

void HandleInput(b32 *IsRunning)
{
    SDL_Event Event;
    while(SDL_PollEvent(&Event))
    {
        ImGui_ImplSDL2_ProcessEvent(&Event);

        switch(Event.type)
        {
            case SDL_QUIT:
            {
                *IsRunning = false;
                break;
            }

            case SDL_KEYDOWN:
            {
                if(Event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                {
                    *IsRunning = false;
                }
                break;
            }
            case SDL_KEYUP:
            {
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void EndFrame(SDL_Renderer *Renderer)
{
    GuiNewFrame();
    ShowMenuBar();
    bool yes = true; yes;
    ImGui::ShowDemoWindow(&yes);
    SDL_SetRenderDrawColor(Renderer, 255, 0, 255, 255);
    SDL_RenderClear(Renderer);
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(Renderer);
}

int main(int Argc, char **Argv)
{

    // Globals
    b32  IsRunning = true;
    u8   Memory[4096] = {0};
    u16 *PC = nullptr;
    u16 *I = nullptr; I;
    u8   V[16] = {0}; V; // Registers
    u8   SoundTimer; SoundTimer;

    if(Argc < 2)
    {
        std::cout << "Error, please add a chip8 file as parameter" << std::endl;
        std::cout << "Example: chip8.exe my_rom.ch8" << std::endl;
        exit(-1);
    }
    std::string RomFilename = Argv[1];

    u8 *ProgramStart = Memory + 0x200;
    LoadRomToMemory(RomFilename, ProgramStart);

    i32 WindowWidth = 1366;
    i32 WindowHeight = 768;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_Window *Window = SDL_CreateWindow("Chip8 Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

    GuiSetup(Window, Renderer);


    // Set the Program counter to the beggining of the loaded ROM
    PC = (u16*)&Memory[512];

    while(IsRunning)
    {
        HandleInput(&IsRunning);

        // Fetch
        u16 Instruction = *PC;
        PC++;

        u16 OpCode = (Instruction & 0x00F0) >> 4;
        switch(OpCode)
        {
            case 0x0:
            {
                // TODO(Jsanchez): Switch between E0 and EE
                // TODO: 00E0 clear the display
                // TODO: 00EE return from a subroutine
                std::cout << "0!" << std::endl;
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
        // render your GUI
        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        ImGui::End();

        EndFrame(Renderer);
    }

    GuiDestroy();
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}
