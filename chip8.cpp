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
//
// - Check if the rom's size is less than the available memory
// - Copy the loaded ROM to the interpreter's memory

// - Create a PrintHelp function and use it in ParseCommandLineArguments
// - Create the general purpose registers
// - Create PC, I registers
// - Create The Memory, 4Kb
// - Copy the chip-8 program to RAM starting at address: 0x200
// - Create the stack (I think it should only be used to store memory addreses)
// - CPU should run at a fixed rate, 700 Instructions per second? Create a new parameter to set this, default at 700 (What the website above says)
// - Create Debug visualization that prints registers, pc, I (Maybe print to console and clear everyframe?)
// - Implement the instructions
//     - 00E0 (Clear Screen)
//     - 1NNN (Jump)
//     - 6XNN (Set Register VX)
//     - 7XNN (Add value to register VX)
//     - ANNN (Set Index Register I)
//     - DXYN (Display/Draw) - This is the hardest instruction
// - Test this newly created instructions with the IBM Logo rom.
// - Get Dear::ImGUI Working? On a Separate Video?

#include <stdint.h>
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

#include <stdio.h>
#include <string.h>

#include <SDL.h>

#include <windows.h>

void ParseCommandLineArguments(i32 Argc, char **Argv, char **RomFilename)
{
    // TODO: This is extremely basic, i should probably implement a
    // more robust way of parsing command line arguments. But this
    // serves for now. Revisit this in the future.

    // We always expect the first argument to be -r and the second argument a filename

    // Error, print help to the screen
    if(Argc < 3)
    {
        printf("Error, program must be executed with a -r parameter\n");
        printf("-r -> rom file to open\n\n");
        printf("Example: chip8.exe -r \"my_rom.ch8\"\n");
        exit(1);
    }

    if(strcmp(Argv[1], "-r") == 0)
    {
        *RomFilename = Argv[2];
        if(RomFilename == nullptr)
        {
            printf("Error, program must be executed with a -r parameter\n");
            printf("-r -> rom file to open\n\n");
            printf("Example: chip8.exe -r \"my_rom.ch8\"\n");
            exit(1);
        }
    }
    else
    {
        // first argument is not 0, assume it all went wrong for
        // now. This should be cleaned up after we have implemented a
        // better argument parser
        printf("Error, program must be executed with a -r parameter\n");
        printf("-r -> rom file to open\n\n");
        printf("Example: chip8.exe -r \"my_rom.ch8\"\n");
        exit(1);
    }
}

// Copy loaded binary data to Data, set DataSize
b32 LoadRomToMemory(char *Filename, u8 *Buffer, size_t *RomSize)
{
    // NOTE(Jsanchez): It might be better to use SDL's file abstraction layer instead of C's standard libs

    FILE *File;
    b32 Result = fopen_s(&File, Filename, "rb");

    if(Result != 0) { printf("Error loading filename: %s\n", Filename); exit(1); }

    fseek(File, 0, SEEK_END);
    *RomSize = ftell(File);

    // CHIP-8 ROMs cannot exceed 4KB – 0.5KB = 3.5KB, check for this!, return when rom is bigger than this
    Assert(*RomSize < (4096 - 512));

    // Copy rom to emulator's memory
    fseek(File, 0, SEEK_SET);
    fread(Buffer, *RomSize, 1, File);

    // Close the open file
    fclose(File);

    return 1;
}

int main(int Argc, char **Argv)
{
    Argc;Argv;

    char *RomFilename = nullptr;

    ParseCommandLineArguments(Argc, Argv, &RomFilename);

    // TODO: Make RomData point to 0x200 in the emulator's memory
    u8 *Buffer = (u8*)malloc(100000);
    size_t RomSize = 0;
    ZeroMemory(Buffer, 4096);
    LoadRomToMemory(RomFilename, Buffer, &RomSize);

    // i32 WindowWidth = 1024;
    // i32 WindowHeight = 768;
    // SDL_Init(SDL_INIT_EVERYTHING);
    // SDL_Window *Window = SDL_CreateWindow("Chip8 - INSERT ROM FILENAME HERE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_ALLOW_HIGHDPI);
    // SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    // SDL_SetRenderDrawColor(Renderer, 255, 0, 255, 255);
    // SDL_RenderClear(Renderer);
    // SDL_RenderPresent(Renderer);
    // SDL_Delay(3000);

    return 0;
}
