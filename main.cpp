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

// TODO
//

// - Get SDL Working, Video and Audio (I only need a simple wave, it's just a single sound)

// - Get Dear::ImGUI Working? On a Separate Video?
// - Create a parameter to open the selected ROM by parameter
// - Create the general purpose registers
// - Create PC, I registers
// - Create The Memory, 4Kb
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

#include <SDL.h>

int main(int argc, char **argv)
{
    argc;argv;
    i32 WindowWidth = 1024;
    i32 WindowHeight = 768;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *Window = SDL_CreateWindow("Chip8 - INSERT ROM FILENAME HERE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(Renderer, 255, 0, 255, 255);

    SDL_RenderClear(Renderer);

    SDL_RenderPresent(Renderer);

    SDL_Delay(3000);

    return 0;
}
