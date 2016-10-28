#include "stdafx.h"
#include "ijl.h"

//----------------------------------------------------------
// An example using the IntelR JPEG Library:
// -- Decode a JPEG image from a JFIF file to Windows DIB.
//----------------------------------------------------------
BOOL DecodeJPGFileToDIB(
	LPCSTR lpszPathName,
	BITMAPINFOHEADER** dib )
{
	BOOL	bres;
	IJLERR	jerr;
	DWORD	width;
	DWORD	height;
	DWORD	nchannels;
	DWORD	dib_line_width;
	DWORD	dib_pad_bytes;
	DWORD	wholeimagesize;
	BYTE*	buffer = NULL;
	BITMAPINFOHEADER* bmih = NULL;

	// Allocate the IJL JPEG_CORE_PROPERTIES structure.
	JPEG_CORE_PROPERTIES jcprops;
	bres = TRUE;
	__try
	{
		// Initialize the IntelR JPEG Library.
		jerr = ijlInit(&jcprops);
		
		if(IJL_OK != jerr){
			bres = FALSE;
			__leave;
		}

		// Get information on the JPEG image
		// (i.e., width, height, and channels).
		jcprops.JPGFile = const_cast<LPSTR>(lpszPathName);
		jerr = ijlRead(&jcprops,IJL_JFILE_READPARAMS);
		if(IJL_OK != jerr)
		{
			bres = FALSE;
			__leave;
		}
		// Set up local data.
		width = jcprops.JPGWidth;
		height = jcprops.JPGHeight;
		nchannels = 3; // Decode into a 3 channel pixel buffer.
		// Compute DIB padding
		dib_line_width = width * nchannels;
		dib_pad_bytes = IJL_DIB_PAD_BYTES(width,nchannels);
		// Compute size of desired pixel buffer.
		wholeimagesize = ( dib_line_width + dib_pad_bytes ) * height;
		// Allocate memory to hold the decompressed image data.
		buffer = new BYTE [sizeof(BITMAPINFOHEADER) + wholeimagesize];
		if(NULL == buffer)
		{
		bres = FALSE;
			__leave;
		}
		bmih = reinterpret_cast<BITMAPINFOHEADER*>(buffer);
		bmih->biSize = sizeof(BITMAPINFOHEADER);
		bmih->biWidth = width;
		bmih->biHeight = height;
		bmih->biPlanes = 1;
		bmih->biBitCount = 24;
		bmih->biCompression = BI_RGB;
		bmih->biSizeImage = 0;
		bmih->biXPelsPerMeter = 0;
		bmih->biYPelsPerMeter = 0;
		bmih->biClrUsed = 0;
		bmih->biClrImportant = 0;
		// Set up the info on the desired DIB properties.
		jcprops.DIBWidth = width;
		jcprops.DIBHeight = -1 * height; // Implies a bottom-up DIB.
										// èCê≥ -1 ïÑçÜÇ∆ÇµÇΩ
		jcprops.DIBChannels = nchannels;
		jcprops.DIBColor = IJL_BGR;
		jcprops.DIBPadBytes = dib_pad_bytes;
		jcprops.DIBBytes = reinterpret_cast<BYTE*>(buffer + sizeof(BITMAPINFOHEADER));

		// Set the JPG color space ... this will always be
		// somewhat of an educated guess at best because JPEG
		// is "color blind" (i.e., nothing in the bit stream
		// tells you what color space the data was encoded from).
		// However, in this example we assume that we are
		// reading JFIF files which means that 3 channel images
		// are in the YCbCr color space and 1 channel images are
		// in the Y color space.
		switch(jcprops.JPGChannels)
		{
		case 1:
			{
				jcprops.JPGColor = IJL_G;
				break;
			}
		case 3:
			{
				jcprops.JPGColor = IJL_YCBCR;
				break;
			}
		default:
			{
				// This catches everything else, but no
				// color twist will be performed by the IJL.
				jcprops.DIBColor = (IJL_COLOR)IJL_OTHER;
				jcprops.JPGColor = (IJL_COLOR)IJL_OTHER;
				break;
			}
		}
		// Now get the actual JPEG image data into the pixel buffer.
		jerr = ijlRead(&jcprops,IJL_JFILE_READWHOLEIMAGE);
		if(IJL_OK != jerr)
		{
			bres = FALSE;
			__leave;
		}
	} // __try
	__finally
	{
		if(FALSE == bres)
		{
			if(NULL != buffer)
			{
				delete [] buffer;
				buffer = NULL;
			}
		}
		// Clean up the IntelR JPEG Library.
		ijlFree(&jcprops);
		*dib = bmih;
	} // __finally

	return bres;

} // DecodeJPGFileToDIB()
