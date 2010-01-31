#ifndef __DXWRAP_H__
#define __DXWRAP_H__

#include "ddraw.h"

struct ScreenResolution
{
    uae_u32 width;  /* in pixels */
    uae_u32 height; /* in pixels */
};

#define MAX_PICASSO_MODES 300
#define MAX_REFRESH_RATES 100
struct PicassoResolution
{
    struct Resolutions *next;
    struct ScreenResolution res;
    int depth;   /* depth in bytes-per-pixel */
    int refresh[MAX_REFRESH_RATES]; /* refresh-rates in Hz */
    char name[25];
    /* Bit mask of RGBFF_xxx values.  */
    uae_u32 colormodes;
};
extern struct PicassoResolution *DisplayModes;
extern GUID *displayGUID;

#define MAX_DISPLAYS 10
struct MultiDisplay {
    int primary, disabled;
    GUID guid;
    char *name;
    struct PicassoResolution *DisplayModes;
};
extern struct MultiDisplay Displays[MAX_DISPLAYS];

typedef enum {
    BLIT_FALSE,
    BLIT_NOR,
    BLIT_ONLYDST,
    BLIT_NOTSRC,
    BLIT_ONLYSRC,
    BLIT_NOTDST,
    BLIT_EOR,
    BLIT_NAND,
    BLIT_AND,
    BLIT_NEOR,
    BLIT_DST,
    BLIT_NOTONLYSRC,
    BLIT_SRC,
    BLIT_NOTONLYDST,
    BLIT_OR,
    BLIT_TRUE,
    BLIT_LAST
} BLIT_OPCODE;

/* Types for RGBFormat used */
typedef enum {
    RGBFB_NONE,		/* no valid RGB format (should not happen) */
    RGBFB_CLUT,		/* palette mode, set colors when opening screen using
			   tags or use SetRGB32/LoadRGB32(...) */
    RGBFB_R8G8B8,	/* TrueColor RGB (8 bit each) */
    RGBFB_B8G8R8,	/* TrueColor BGR (8 bit each) */
    RGBFB_R5G6B5PC,	/* HiColor16 (5 bit R, 6 bit G, 5 bit B),
			   format: gggbbbbbrrrrrggg */
    RGBFB_R5G5B5PC,	/* HiColor15 (5 bit each), format: gggbbbbb0rrrrrgg */
    RGBFB_A8R8G8B8,	/* 4 Byte TrueColor ARGB (A unused alpha channel) */
    RGBFB_A8B8G8R8,	/* 4 Byte TrueColor ABGR (A unused alpha channel) */
    RGBFB_R8G8B8A8,	/* 4 Byte TrueColor RGBA (A unused alpha channel) */
    RGBFB_B8G8R8A8,	/* 4 Byte TrueColor BGRA (A unused alpha channel) */
    RGBFB_R5G6B5,	/* HiColor16 (5 bit R, 6 bit G, 5 bit B),
			   format: rrrrrggggggbbbbb */
    RGBFB_R5G5B5,	/* HiColor15 (5 bit each), format: 0rrrrrgggggbbbbb */
    RGBFB_B5G6R5PC,	/* HiColor16 (5 bit R, 6 bit G, 5 bit B),
			   format: gggrrrrrbbbbbggg */
    RGBFB_B5G5R5PC,	/* HiColor15 (5 bit each), format: gggrrrrr0bbbbbbgg */

    /* By now, the following formats are for use with a hardware window only
       (bitmap operations may be implemented incompletely) */

    RGBFB_Y4U2V2,	/* 2 Byte TrueColor YUV (CCIR recommendation CCIR601).
			   Each two-pixel unit is stored as one longword
			   containing luminance (Y) for each of the two pixels,
			   and chrominance (U,V) for alternate pixels.
			   The missing chrominance values are generated by
			   interpolation. (Y1-U0-Y0-V0) */
    RGBFB_Y4U1V1,	/* 1 Byte TrueColor ACCUPAK. Four adjacent pixels form
			   a packet of 5 bits Y (luminance) each pixel and 6 bits
			   U and V (chrominance) shared by the four pixels */

    RGBFB_MaxFormats
} RGBFTYPE;

#define RGBFF_NONE	(1<<RGBFB_NONE)
#define RGBFF_CLUT	(1<<RGBFB_CLUT)
#define RGBFF_R8G8B8	(1<<RGBFB_R8G8B8)
#define RGBFF_B8G8R8	(1<<RGBFB_B8G8R8)
#define RGBFF_R5G6B5PC	(1<<RGBFB_R5G6B5PC)
#define RGBFF_R5G5B5PC	(1<<RGBFB_R5G5B5PC)
#define RGBFF_A8R8G8B8	(1<<RGBFB_A8R8G8B8)
#define RGBFF_A8B8G8R8	(1<<RGBFB_A8B8G8R8)
#define RGBFF_R8G8B8A8	(1<<RGBFB_R8G8B8A8)
#define RGBFF_B8G8R8A8	(1<<RGBFB_B8G8R8A8)
#define RGBFF_R5G6B5	(1<<RGBFB_R5G6B5)
#define RGBFF_R5G5B5	(1<<RGBFB_R5G5B5)
#define RGBFF_B5G6R5PC	(1<<RGBFB_B5G6R5PC)
#define RGBFF_B5G5R5PC	(1<<RGBFB_B5G5R5PC)
#define RGBFF_Y4U2V2	(1<<RGBFB_Y4U2V2)
#define RGBFF_Y4U1V1	(1<<RGBFB_Y4U1V1)

#define RGBMASK_8BIT RGBFF_CLUT
#define RGBMASK_16BIT (RGBFF_R5G6B5PC | RGBFF_B5G6R5PC | RGBFF_R5G6B5)
#define RGBMASK_15BIT (RGBFF_R5G5B5PC | RGBFF_B5G5R5PC | RGBFF_R5G5B5)
#define RGBMASK_24BIT (RGBFF_R8G8B8 | RGBFF_B8G8R8)
#define RGBMASK_32BIT (RGBFF_A8R8G8B8 | RGBFF_A8B8G8R8 | RGBFF_R8G8B8A8 | RGBFF_B8G8R8A8)

/************************************************************************/

#define	RGBFF_PLANAR	RGBFF_NONE
#define	RGBFF_CHUNKY	RGBFF_CLUT

#define	RGBFB_PLANAR	RGBFB_NONE
#define	RGBFB_CHUNKY	RGBFB_CLUT

typedef enum
{
    red_mask,
    green_mask,
    blue_mask
} DirectDraw_Mask_e;

typedef enum
{
    invalid_surface,
    primary_surface,
    secondary_surface,
    tertiary_surface,
    overlay_surface,
    lockable_surface
} surface_type_e;

typedef enum
{
    single_buffer,
    double_buffer,
    triple_buffer
} flipping;

struct DirectDrawSurfaceMapper
{
    int initialized;
    int fullscreen;
    int isoverlay;
    int flipping;
    int locked;
    int modeset;
    HWND window;
    struct
    {
        LPDIRECTDRAW ddx;
        LPDIRECTDRAW7 dd;
    } directdraw;
    struct
    {
        LPDIRECTDRAWSURFACE7 surface;
        DDSURFACEDESC2 desc;
    } primary;
    struct
    {
        LPDIRECTDRAWSURFACE7 surface;
        DDSURFACEDESC2 desc;
    } secondary;
    struct
    {
        LPDIRECTDRAWSURFACE7 surface;
        DDSURFACEDESC2 desc;
    } tertiary;
    struct
    {
        LPDIRECTDRAWSURFACE7 surface;
        DDSURFACEDESC2 desc;
    } overlay;
    struct
    {
        DDSURFACEDESC2 desc;
    } current;
    struct
    {
        LPDIRECTDRAWSURFACE7 surface;
        LPDDSURFACEDESC2 lpdesc;
    } lockable;
    LPDIRECTDRAWCLIPPER lpDDC;
    LPDIRECTDRAWPALETTE lpDDP;
    LPDIRECTDRAWPALETTE lpOverlayDDP;
    surface_type_e surface_type;
};
HRESULT DirectDraw_CreateOverlaySurface( int width, int height, int bits );
int DirectDraw_Start( GUID *);
void DirectDraw_Release( void );
HRESULT DirectDraw_SetCooperativeLevel( HWND window, int want_fullscreen );
BOOL DirectDraw_GetCooperativeLevel( HWND *window, int *fullscreen );
HRESULT DirectDraw_SetDisplayMode( int width, int height, int bits, int freq );
HRESULT DirectDraw_GetDisplayMode( void );
HRESULT DirectDraw_CreateClipper( void );
HRESULT DirectDraw_GetCaps( DDCAPS_DX7 *driver_caps, DDCAPS_DX7 *hel_caps );
HRESULT DirectDraw_CreateSurface( int width, int height );
void    DirectDraw_ClearSurfaces( void );
HRESULT DirectDraw_SetClipper( HWND hWnd );
HRESULT DirectDraw_GetClipList( LPRGNDATA cliplist, LPDWORD size );
HRESULT DirectDraw_CreatePalette( LPPALETTEENTRY pal );
HRESULT DirectDraw_SetPalette( int remove );
HRESULT DirectDraw_SetPaletteEntries( int start, int count, PALETTEENTRY *palette );
HRESULT DirectDraw_WaitForVerticalBlank( DWORD flags );
HRESULT DirectDraw_EnumDisplayModes( DWORD flags, LPDDENUMMODESCALLBACK2 callback );
HRESULT DirectDraw_EnumDisplays(LPDDENUMCALLBACKEX callback );
HRESULT DirectDraw_FlipToGDISurface( void );
HRESULT DirectDraw_GetDC( HDC *hdc, surface_type_e surface );
HRESULT DirectDraw_ReleaseDC( HDC hdc, surface_type_e surface );
int DirectDraw_Flip( int );
HRESULT DirectDraw_UpdateOverlay(RECT sr, RECT dr);
int DirectDraw_Blt( surface_type_e dsttype, LPRECT dstrect, surface_type_e srctype, LPRECT srcrect, DWORD flags, LPDDBLTFX fx );
int DirectDraw_BltFast( surface_type_e dsttype, DWORD left, DWORD top, surface_type_e srctype, LPRECT srcrect );
DWORD DirectDraw_GetPixelFormatBitMask( DirectDraw_Mask_e mask );
RGBFTYPE DirectDraw_GetPixelFormat( void );
DWORD DirectDraw_GetPixelFormatFlags( void );
DWORD DirectDraw_GetSurfaceFlags( void );
DWORD DirectDraw_GetSurfaceBitCount( void );
DWORD DirectDraw_GetPrimaryBitCount( void );
void DirectDraw_GetPrimaryWidthHeight(int *w, int *h);
int DirectDraw_DetermineLocking( int wantfull );
BYTE DirectDraw_GetBytesPerPixel( void );
RGBFTYPE DirectDraw_GetSurfacePixelFormat( LPDDSURFACEDESC2 surface );
surface_type_e DirectDraw_GetLockableType( void );
int DirectDraw_SurfaceLock( surface_type_e surface_type );
BOOL DirectDraw_IsLocked( void );
char *DirectDraw_GetSurfacePointer( void );
LONG DirectDraw_GetSurfacePitch( void );
DWORD DirectDraw_CurrentWidth( void );
DWORD DirectDraw_CurrentHeight( void );
DWORD DirectDraw_CurrentRefreshRate (void);
int DirectDraw_GetVerticalBlankStatus (void);

extern void ddraw_unlockscr (void);
#define DirectDraw_SurfaceUnlock() ddraw_unlockscr()

extern const char *DXError (HRESULT hr);

extern char *outGUID (GUID *guid);

#endif
