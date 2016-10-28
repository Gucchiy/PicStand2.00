#ifndef	__GLOBAL_H__

#define	PICTURE_FOLDER		_T( "Picture" )
#define	PICSTAND_APPDATA_FOLDER	_T( "PicStand" )
#define	DEFAULT_FILENAME	_T( "" )
#define	FIXEDPIC_FILENAME	_T( "" )
#define	STARTUP_SHORTCUT	_T( "é ê^ÇΩÇƒ.lnk" )
#define	HP_URL				"http://www.idea-tech.net/"
#define	APP_NAME			_T( "é ê^ÇΩÇƒ" )

#define	RGB_BACK			RGB( 128, 125, 166 )
#define	RGB_BACK_R			128
#define	RGB_BACK_G			125
#define	RGB_BACK_B			166
#define	RGB_BACK_SHADOW		RGB(  74,  74, 107 )
#define	RGB_BACK_LIGHT		RGB( 194, 194, 237 )
#define	RGB_BACK_LIGHT_2	RGB( 144, 144, 187 )

#define	CREATE_DARK_COLOR_R( X )	( X * 74 / 128 )
#define	CREATE_DARK_COLOR_G( X )	( X * 74 / 125 )
#define	CREATE_DARK_COLOR_B( X )	( X * 107 / 166 )

#define	CREATE_LIGHT_COLOR_R( X )	( X * 194 / 128 ) 
#define	CREATE_LIGHT_COLOR_G( X )	( X * 194 / 125 )
#define	CREATE_LIGHT_COLOR_B( X )	( X * 237 / 166 )

#define	CREATE_LIGHT_2_COLOR_R( X )	( X * 144 / 128 )
#define	CREATE_LIGHT_2_COLOR_G( X )	( X * 144 / 125 )
#define	CREATE_LIGHT_2_COLOR_B( X )	( X * 187 / 166 )

extern int CX_FRAME;
// #define	CX_FRAME	32
#define	CY_FRAME	32
#define	CX_PICSTAND( PIC_CX )	( CX_FRAME * 2 + (int)PIC_CX )
#define	CY_PICSTAND( PIC_CY )	( CY_FRAME * 2 + (int)PIC_CY )
#define	MCX_PICSTAND	( CX_FRAME * 2 + 153 ) 
#define	MCX_PICSTAND_MENUCHANGE	( MCX_PICSTAND + 90 ) 
#define	MCY_PICSTAND	( CY_FRAME * 2 + 100 )
#define	CX_BARSTAND( PIC_CX )	( CX_FRAME * 2 + (int)PIC_CX )
#define	CY_BARSTAND CY_FRAME
#define	LX_PICTURE	CX_FRAME
#define	LY_PICTURE	CY_FRAME
#define	LEX_PICTURE( PIC_CX )	( CX_FRAME + PIC_CX - 1 ) 
#define	LEY_PICTURE( PIC_CY )	( CY_FRAME + PIC_CY - 1 )
#define	LX_STATUSWND( PS_CX )	( PS_CX - 162 )
#define	LY_STATUSWND( PS_CY )	( PS_CY - 25 )
#define	LX_MENUBTN( PS_CX )		( PS_CX - ( CX_FRAME + 43 ) )
#define	LY_MENUBTN( PS_CY )		( 7 )
#define	LX_STAYBTN( PS_CX )		( ( PS_CX / 2 ) - 10 )
#define	LY_STAYBTN( PS_CY )		( 7 )
#define	LX_BACKBTN				( CX_FRAME - 2 )
#define	LY_BACKBTN				( 7 )
#define	LX_NEXTBTN				( LX_BACKBTN + 25 )
#define	LY_NEXTBTN				( LY_BACKBTN )
	
#define	LX_DRAG( PS_CX )		( PS_CX - 32 )
#define	LY_DRAG( PS_CY )		( PS_CY - 32 )

#define	WDSTG_MIN			( 0.2 )
#define	WDSTG_MAX			( 2.00 )
#define	WDSTG_RATIO_SLIDERBAR				( ( WDSTG_MAX - WDSTG_MIN ) / 100.0 )
#define	WDSTG_POS_SLIDERBAR( WIDE_VALUE )	( (int)( ( (double)WIDE_VALUE - WDSTG_MIN ) / WDSTG_RATIO_SLIDERBAR ) )
#define	WDSTG_WIDE( SLIDERBAR_POS )			( (double)( (double)SLIDERBAR_POS * WDSTG_RATIO_SLIDERBAR + WDSTG_MIN ) )

#define	REG_SECTION_TOP		_T( "" )
#define	REG_KEY_LX			_T( "LX" )
#define	REG_KEY_LY			_T( "LY" )
#define	REG_KEY_FILENAME	_T( "FileName" )
#define	REG_KEY_WIDE		_T( "WIDE" )
#define	REG_KEY_ZORDER		_T( "ZORDER" )
#define	REG_KEY_STAY		_T( "STAY" )
#define	REG_KEY_FIXSIZE		_T( "FIXSIZE" )
#define	REG_KEY_COLOR_R		_T( "ColorR" )
#define	REG_KEY_COLOR_G		_T( "ColorG" )
#define	REG_KEY_COLOR_B		_T( "ColorB" )
#define	REG_KEY_EDGE		_T( "EDGE" )

#define ITMES_MENUBTN	0x00000001
#define ITMES_STATUSWND	0x00000002
#define	ITMES_STAY		0x00000003
#define	ITMES_TASKTRAY	0x00000004
#define	ITMES_NEXTBTN	0x00000005
#define	ITMES_BACKBTN	0x00000006

// 2.0 extensions

#define	MIN_RGB		0
#define	MAX_RGB		255
#define	MIN_WIDTH	8
#define	MAX_WIDTH	50

#define	STATUSWND_DEFALT_STRING	_T("EMPTY")

#define	CUSTOMIZEWND_MES_STRING	_T( "CustomizeWndMessage" )

extern UINT g_uCustomizeWndMessage;
#define	CWM_SET_DEFAULT	0x00000001

extern BOOL Global_Initialize();
extern void Global_Finalize();
extern CString Global_GetCurrentDir();
extern CString Global_GetStartupShorcutPath();
extern CString Global_GetAppDataDir();
extern CString Global_GetPictureDataDir();

#endif
