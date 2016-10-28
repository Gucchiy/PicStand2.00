#ifndef	__IDEATECH_H__

// IdeaTech コンポーネントで使われるメッセージ名
#define	ITECH_MES_STRING		_T( "IdeaTechMessage" )

// カンパニー名\アプリケーション名 のカンパニー名
#define	ITECH_APPDATA_FOLDER	_T( "IdeaTech" )

// アンインストール用、AppData フォルダ保存ファイル名
#define	ITECH_APPDATA_TMPFILE	_T( "DatPath.dat" )

/////////////////////////////////////////////////////////////////////
// モジュールに依存しないサービス郡
// ------------------------------------------------------------------
// ディレクトリパスは基本的に、"C:\Root\" といった具合に "\" で終わる。

// ---------------------------------------------------
// モジュールのファイルパスを取得
// ---------------------------------------------------
extern CString ITech_GetModuleFileName();

// ---------------------------------------------------
// モジュールのカレントディレクトリパスを取得
// ---------------------------------------------------
extern CString ITech_GetCurrentDir();

// ---------------------------------------------------
// スタートアップ用ディレクトリパスを取得
// ---------------------------------------------------
extern CString ITech_GetStartupDir();

// ---------------------------------------------------
// アプリケーションデータ用ディレクトリパスを取得
// なければ生成する。
// ---------------------------------------------------
extern CString ITech_GetAppDataDir();

// ---------------------------------------------------
// 指定ファイルがファイルとして存在するかどうかを確認する
// ---------------------------------------------------
// FileName	確認するファイルパス
// ---------------------------------------------------
// 戻り値	TRUE:存在 FALSE:存在しない
// ---------------------------------------------------
extern BOOL ITech_IsTheFileExist( CString FileName );

// ---------------------------------------------------
// 指定パス（フォルダ）を確認して、なければフォルダを生成し、
// 最後に "\\" をつけて retun する。
// ---------------------------------------------------
// PathName	指定パス
// ---------------------------------------------------
// 戻り値	指定フォルダが存在:FALSE
//			指定フォルダがなかったのでフォルダを生成：TRUE
// ---------------------------------------------------
extern BOOL ITech_MakeAndGetDir( CString& PathName );

// ---------------------------------------------------
// フォルダ単位でコピーする。指定するフォルダパスは、"\"
// で終わっていても良い。
// ---------------------------------------------------
// SrcFolder	コピー元フォルダパス
// DstFolder	コピー先フォルダパス
// ---------------------------------------------------
extern BOOL ITech_CopyFiles( CString SrcFolder, CString DstFolder );

// ---------------------------------------------------
// フォルダごと削除する。指定するフォルダパスは、"\"
// で終わっていても良い。フォルダ自体も削除される。
// ---------------------------------------------------
// RemoveFolder	全削除するフォルダパス
// ---------------------------------------------------
extern BOOL ITech_RemoveFiles( CString RemoveFolder );

// ---------------------------------------------------
// AppData フォルダを新規に作成した際に、TempFile に保存。
// Uninstall 時、ITech_RemoveAllUserAppPathOnTempFile
// で、TempFile から自動的に全削除ができる。
// 指定するディレクトリパスは、"\"で終わっていても良い。
// ---------------------------------------------------
// NewAppFolder	追加するディレクトリパス
// ---------------------------------------------------
extern BOOL ITech_AddAppPathToTempFile( CString NewAppFolder );

// ---------------------------------------------------
// 予め ITech_AddAppPathToTempFile で保存されていた
// TempFile を元に、全ユーザープロファイルフォルダを削除。
// Uninstall 時に呼ぶようにする。
// ---------------------------------------------------
extern BOOL ITech_RemoveAllUserAppPathOnTempFile();

// ---------------------------------------------------
// "IdeaTechMessage" の取得
// ---------------------------------------------------
extern UINT ITech_GetIdeaTechMessage();

// ---------------------------------------------------
// ショートカットファイルの作成
// ---------------------------------------------------
// DstShorcutPath	作成されるショートカットへのフルパス
// ModuleFileName	リンクされる実行ファイルへのフルパス
// CurrentFolder	カレントフォルダ
// Title			タイトル
extern BOOL ITech_CreateShorcut( const CString& DstShorcutPath,
	const CString& ModuleFileName, const CString& CurrentFolder, const CString& Title );

#endif