/*!
 * \file
 * <!--
 * Copyright 2003, 2004, 2005, 2006 Develer S.r.l. (http://www.develer.com/)
 * Copyright 1999 Bernardo Innocenti <bernie@develer.com>
 * This file is part of DevLib - See README.devlib for information.
 * -->
 *
 * \version $Id$
 *
 * \author Bernardo Innocenti <bernie@develer.com>
 *
 * \brief Graphics private header.
 */

/*#*
 *#* $Log$
 *#* Revision 1.5  2006/05/25 23:35:40  bernie
 *#* Cleanup.
 *#*
 *#* Revision 1.4  2006/03/22 09:50:37  bernie
 *#* Use the same format for fonts and rasters.
 *#*
 *#* Revision 1.3  2006/02/15 09:10:15  bernie
 *#* Implement prop fonts; Fix algo styles.
 *#*
 *#* Revision 1.2  2006/02/10 12:28:33  bernie
 *#* Add font support in bitmaps; Make bitmap formats public.
 *#*
 *#* Revision 1.1  2006/01/26 00:32:49  bernie
 *#* Graphics private header.
 *#*
 *#*/

#ifndef GFX_GFX_P_H
#define GFX_GFX_P_H


#if CONFIG_BITMAP_FMT == BITMAP_FMT_PLANAR_H_MSB

	#define RAST_ADDR(raster, x, y, stride)  ((raster) + (y) * (stride) + (x) / 8)
	#define RAST_MASK(raster, x, y)		 (1 << (7 - (x) % 8))

#elif CONFIG_BITMAP_FMT == BITMAP_FMT_PLANAR_V_LSB

	#define RAST_ADDR(raster, x, y, stride)  ((raster) + ((y) / 8) * (stride) + (x))
	#define RAST_MASK(raster, x, y)          (1 << ((y) % 8))

#else
	#error Unknown value of CONFIG_BITMAP_FMT
#endif /* CONFIG_BITMAP_FMT */

#define BM_ADDR(bm, x, y)  RAST_ADDR((bm)->raster, (x), (y), (bm)->stride)
#define BM_MASK(bm, x, y)  RAST_MASK((bm)->raster, (x), (y))

/*!
 * Plot a pixel in bitmap \a bm.
 *
 * \note bm is evaluated twice.
 * \see BM_CLEAR BM_DRAWPIXEL
 */
#define BM_PLOT(bm, x, y) \
	( *BM_ADDR(bm, x, y) |= BM_MASK(bm, x, y) )

/*!
 * Clear a pixel in bitmap \a bm.
 *
 * \note bm is evaluated twice.
 * \see BM_PLOT BM_DRAWPIXEL
 */
#define BM_CLEAR(bm, x, y) \
	( *BM_ADDR(bm, x, y) &= ~BM_MASK(bm, x, y) )

/*!
 * Set a pixel in bitmap \a bm to the specified color.
 *
 * \note bm is evaluated twice.
 * \note This macro is somewhat slower than BM_PLOT and BM_CLEAR.
 * \see BM_PLOT BM_CLEAR
 */
#define BM_DRAWPIXEL(bm, x, y, fg_pen) \
	do { \
		uint8_t *p = BM_ADDR(bm, x, y); \
		uint8_t mask = BM_MASK(bm, x, y); \
		*p = (*p & ~mask) | ((fg_pen) ? mask : 0); \
	} while (0)

/*!
 * Get the value of the pixel in bitmap \a bm.
 *
 * \return The returned value is either 0 or 1.
 *
 * \note bm is evaluated twice.
 * \see BM_DRAWPIXEL
 */
#define BM_READPIXEL(bm, x, y) \
	( *BM_ADDR(bm, x, y) & BM_MASK(bm, x, y) ? 1 : 0 )

#define RAST_READPIXEL(raster, x, y, stride) \
		( *RAST_ADDR(raster, x, y, stride) & RAST_MASK(raster, x, y) ? 1 : 0 )

#endif /* GFX_GFX_P_H */
