#ifndef _AABBEC_F_H_
#define _AABBEC_F_H_

#include <REAL.H>

#if        defined(BL_LANG_FORT)

#if (BL_SPACEDIM == 1)
#define FORT_LINESOLVE     linesolve1daabbec
#define FORT_ADOTX         adotx1daabbec
#define FORT_NORMA         norma1daabbec
#define FORT_FLUX          flux1daabbec
#endif

#if (BL_SPACEDIM == 2)
#define FORT_GSRB          gsrb2daabbec
#define FORT_JACOBI        jacobi2daabbec
#define FORT_ADOTX         adotx2daabbec
#define FORT_NORMA         norma2daabbec
#define FORT_FLUX          flux2daabbec
#endif

#if (BL_SPACEDIM == 3)
#define FORT_GSRB          gsrb3daabbec
#define FORT_JACOBI        jacobi3daabbec
#define FORT_ADOTX         adotx3daabbec
#define FORT_NORMA         norma3daabbec
#define FORT_FLUX          flux3daabbec
#endif

#else

#if (BL_SPACEDIM == 1)
 
#if  defined(BL_FORT_USE_UPPERCASE)
#define FORT_LINESOLVE     LINESOLVE1DAABBEC
#define FORT_ADOTX    ADOTX1DAABBEC
#define FORT_NORMA    NORMA1DAABBEC
#define FORT_FLUX     FLUX1DAABBEC
#elif defined(BL_FORT_USE_LOWERCASE)
#define FORT_LINESOLVE     linesolve1daabbec_
#define FORT_ADOTX    adotx1daabbec
#define FORT_NORMA    norma1daabbec
#define FORT_FLUX     flux1daabbec
#elif defined(BL_FORT_USE_UNDERSCORE)
#define FORT_LINESOLVE     linesolve1daabbec_
#define FORT_ADOTX    adotx1daabbec_
#define FORT_NORMA    norma1daabbec_
#define FORT_FLUX     flux1daabbec_
#endif
 
#endif

#if (BL_SPACEDIM == 2)

#if  defined(BL_FORT_USE_UPPERCASE)
#define FORT_GSRB     GSRB2DAABBEC
#define FORT_JACOBI   JACOBI2DAABBEC
#define FORT_ADOTX    ADOTX2DAABBEC
#define FORT_NORMA    NORMA2DAABBEC
#define FORT_FLUX     FLUX2DAABBEC
#elif defined(BL_FORT_USE_LOWERCASE)
#define FORT_GSRB     gsrb2daabbec
#define FORT_JACOBI   jacobi2daabbec
#define FORT_ADOTX    adotx2daabbec
#define FORT_NORMA    norma2daabbec
#define FORT_FLUX     flux2daabbec
#elif defined(BL_FORT_USE_UNDERSCORE)
#define FORT_GSRB     gsrb2daabbec_
#define FORT_JACOBI   jacobi2daabbec_
#define FORT_ADOTX    adotx2daabbec_
#define FORT_NORMA    norma2daabbec_
#define FORT_FLUX     flux2daabbec_
#endif

#endif


#if (BL_SPACEDIM == 3)

#if   defined(BL_FORT_USE_UPPERCASE)
#define FORT_GSRB     GSRB3DAABBEC
#define FORT_JACOBI   JACOBI3DAABBEC
#define FORT_ADOTX    ADOTX3DAABBEC
#define FORT_NORMA    NORMA3DAABBEC
#define FORT_FLUX     FLUX3DAABBEC
#elif defined(BL_FORT_USE_LOWERCASE)
#define FORT_GSRB     gsrb3daabbec
#define FORT_JACOBI   jacobi3daabbec
#define FORT_ADOTX    adotx3daabbec
#define FORT_NORMA    norma3daabbec
#define FORT_FLUX     flux3daabbec
#elif defined(BL_FORT_USE_UNDERSCORE)
#define FORT_GSRB     gsrb3daabbec_
#define FORT_JACOBI   jacobi3daabbec_
#define FORT_ADOTX    adotx3daabbec_
#define FORT_NORMA    norma3daabbec_
#define FORT_FLUX     flux3daabbec_
#endif

#endif

#include <ArrayLim.H>

extern "C"
{

#if (BL_SPACEDIM == 1)
    void FORT_LINESOLVE (
        Real* phi       , ARLIM_P(phi_lo), ARLIM_P(phi_hi),
        const Real* rhs , ARLIM_P(rhs_lo), ARLIM_P(phi_hi),
        const Real* alpha, const Real* beta,
        const Real* a   , ARLIM_P(a_lo),   ARLIM_P(a_hi),
        const Real* bX  , ARLIM_P(bX_lo),  ARLIM_P(bX_hi),
        const Real* den0, ARLIM_P(den0_lo),ARLIM_P(den0_hi),
        const int* m0   , ARLIM_P(m0_lo),  ARLIM_P(m0_hi),
        const Real* den2, ARLIM_P(den2_lo),ARLIM_P(den2_hi),
        const int* m2   , ARLIM_P(m2_lo),  ARLIM_P(m2_hi),
        const int* lo, const int* hi, const int *nc,
        const Real *h
        );

    void FORT_ADOTX(
        Real *y      , ARLIM_P(y_lo), ARLIM_P(y_hi),
        const Real *x, ARLIM_P(x_lo), ARLIM_P(x_hi),
        const Real* alpha, const Real* beta,
        const Real* a , ARLIM_P(a_lo),  ARLIM_P(a_hi),
        const Real* bX, ARLIM_P(bX_lo), ARLIM_P(bX_hi),
        const int *lo, const int *hi, const int *nc,
        const Real *h
        );
    
    void FORT_NORMA(
        Real* res      ,
        const Real* alpha, const Real* beta,
        const Real* a , ARLIM_P(a_lo),  ARLIM_P(a_hi),
        const Real* bX, ARLIM_P(bX_lo), ARLIM_P(bX_hi),
        const int *lo, const int *hi, const int *nc,
        const Real *h
        );
    
    void FORT_FLUX(
        const Real *x, ARLIM_P(x_lo), ARLIM_P(x_hi),
        const Real* alpha, const Real* beta,
        const Real* a , ARLIM_P(a_lo),  ARLIM_P(a_hi),
        const Real* bX, ARLIM_P(bX_lo), ARLIM_P(bX_hi),
        const int *xlo, const int *xhi, const int *nc,
        const Real *h,
        const Real* xflux, ARLIM_P(xflux_lo), ARLIM_P(xflux_hi)
        );
#endif    
#if (BL_SPACEDIM == 2)
    void FORT_GSRB (
        Real* phi       , ARLIM_P(phi_lo), ARLIM_P(phi_hi),
        const Real* rhs , ARLIM_P(rhs_lo), ARLIM_P(phi_hi),
        const Real* alpha, const Real* beta,
        const Real* a   , ARLIM_P(a_lo),   ARLIM_P(a_hi),
        const Real* bX  , ARLIM_P(bX_lo),  ARLIM_P(bX_hi),
        const Real* bY  , ARLIM_P(bY_lo),  ARLIM_P(bY_hi),
        const Real* den0, ARLIM_P(den0_lo),ARLIM_P(den0_hi),
        const int* m0   , ARLIM_P(m0_lo),  ARLIM_P(m0_hi),
        const Real* den1, ARLIM_P(den1_lo),ARLIM_P(den1_hi),
        const int* m1   , ARLIM_P(m1_lo),  ARLIM_P(m1_hi),
        const Real* den2, ARLIM_P(den2_lo),ARLIM_P(den2_hi),
        const int* m2   , ARLIM_P(m2_lo),  ARLIM_P(m2_hi),
        const Real* den3, ARLIM_P(den3_lo),ARLIM_P(den3_hi),
        const int* m3   , ARLIM_P(m3_lo),  ARLIM_P(m3_hi),
        const int* lo, const int* hi, const int* blo, const int* bhi, 
	const int *nc, const Real *h, const  int* redblack
        );

    void FORT_JACOBI (
        Real* phi       , ARLIM_P(phi_lo), ARLIM_P(phi_hi),
        const Real* rhs , ARLIM_P(rhs_lo), ARLIM_P(phi_hi),
        const Real* alpha, const Real* beta,
        const Real* a   , ARLIM_P(a_lo),   ARLIM_P(a_hi),
        const Real* bX  , ARLIM_P(bX_lo),  ARLIM_P(bX_hi),
        const Real* bY  , ARLIM_P(bY_lo),  ARLIM_P(bY_hi),
        const Real* den0, ARLIM_P(den0_lo),ARLIM_P(den0_hi),
        const int* m0   , ARLIM_P(m0_lo),  ARLIM_P(m0_hi),
        const Real* den1, ARLIM_P(den1_lo),ARLIM_P(den1_hi),
        const int* m1   , ARLIM_P(m1_lo),  ARLIM_P(m1_hi),
        const Real* den2, ARLIM_P(den2_lo),ARLIM_P(den2_hi),
        const int* m2   , ARLIM_P(m2_lo),  ARLIM_P(m2_hi),
        const Real* den3, ARLIM_P(den3_lo),ARLIM_P(den3_hi),
        const int* m3   , ARLIM_P(m3_lo),  ARLIM_P(m3_hi),
        const int* lo, const int* hi, const int *nc,
        const Real *h
        );

    void FORT_ADOTX(
        Real *y      , ARLIM_P(y_lo), ARLIM_P(y_hi),
        const Real *x, ARLIM_P(x_lo), ARLIM_P(x_hi),
        const Real* alpha, const Real* beta,
        const Real* a , ARLIM_P(a_lo),  ARLIM_P(a_hi),
        const Real* bX, ARLIM_P(bX_lo), ARLIM_P(bX_hi),
        const Real* bY, ARLIM_P(bY_lo), ARLIM_P(bY_hi),
        const int *lo, const int *hi, const int *nc,
        const Real *h
        );
    
    void FORT_NORMA(
        Real* res      ,
        const Real* alpha, const Real* beta,
        const Real* a , ARLIM_P(a_lo),  ARLIM_P(a_hi),
        const Real* bX, ARLIM_P(bX_lo), ARLIM_P(bX_hi),
        const Real* bY, ARLIM_P(bY_lo), ARLIM_P(bY_hi),
        const int *lo, const int *hi, const int *nc,
        const Real *h
        );
    
    void FORT_FLUX(
        const Real *x, ARLIM_P(x_lo), ARLIM_P(x_hi),
        const Real* alpha, const Real* beta,
        const Real* a , ARLIM_P(a_lo),  ARLIM_P(a_hi),
        const Real* bX, ARLIM_P(bX_lo), ARLIM_P(bX_hi),
        const Real* bY, ARLIM_P(bY_lo), ARLIM_P(bY_hi),
        const int *xlo, const int *xhi, 
        const int *ylo, const int *yhi, 
	const int *nc,
        const Real *h,
        const Real* xflux, ARLIM_P(xflux_lo), ARLIM_P(xflux_hi),
        const Real* yflux, ARLIM_P(yflux_lo), ARLIM_P(yflux_hi)
        );
#endif    

#if (BL_SPACEDIM == 3)
    void FORT_GSRB (
        Real* phi,       ARLIM_P(phi_lo), ARLIM_P(phi_hi),
        const Real* rhs, ARLIM_P(rhs_lo), ARLIM_P(rhs_hi),
        const Real* alpha, const Real* beta,
        const Real* a , ARLIM_P(a_lo),  ARLIM_P(a_hi),
        const Real* bX, ARLIM_P(bX_lo), ARLIM_P(bX_hi),
        const Real* bY, ARLIM_P(bY_lo), ARLIM_P(bY_hi),
        const Real* bZ, ARLIM_P(bZ_lo), ARLIM_P(bZ_hi),
        const Real* den0, ARLIM_P(den0_lo), ARLIM_P(den0_hi),
        const int* m0   , ARLIM_P(m0_lo),   ARLIM_P(m0_hi),
        const Real* den1, ARLIM_P(den1_lo), ARLIM_P(den1_hi),
        const int* m1   , ARLIM_P(m1_lo),   ARLIM_P(m1_hi),
        const Real* den2, ARLIM_P(den2_lo), ARLIM_P(den2_hi),
        const int* m2   , ARLIM_P(m2_lo),   ARLIM_P(m2_hi),
        const Real* den3, ARLIM_P(den3_lo), ARLIM_P(den3_hi),
        const int* m3   , ARLIM_P(m3_lo),   ARLIM_P(m3_hi),
        const Real* den4, ARLIM_P(den4_lo), ARLIM_P(den4_hi),
        const int* m4   , ARLIM_P(m4_lo),   ARLIM_P(m4_hi),
        const Real* den5, ARLIM_P(den5_lo), ARLIM_P(den5_hi),
        const int* m5   , ARLIM_P(m5_lo),   ARLIM_P(m5_hi),
        const int* lo, const int* hi, const int* blo, const int* bhi, 
	const int *nc, const Real *h, const  int* redblack
        );

    void FORT_JACOBI (
        Real* phi,       ARLIM_P(phi_lo), ARLIM_P(phi_hi),
        const Real* rhs, ARLIM_P(rhs_lo), ARLIM_P(rhs_hi),
        const Real* alpha, const Real* beta,
        const Real* a , ARLIM_P(a_lo),  ARLIM_P(a_hi),
        const Real* bX, ARLIM_P(bX_lo), ARLIM_P(bX_hi),
        const Real* bY, ARLIM_P(bY_lo), ARLIM_P(bY_hi),
        const Real* bZ, ARLIM_P(bZ_lo), ARLIM_P(bZ_hi),
        const Real* den0, ARLIM_P(den0_lo), ARLIM_P(den0_hi),
        const int* m0   , ARLIM_P(m0_lo),   ARLIM_P(m0_hi),
        const Real* den1, ARLIM_P(den1_lo), ARLIM_P(den1_hi),
        const int* m1   , ARLIM_P(m1_lo),   ARLIM_P(m1_hi),
        const Real* den2, ARLIM_P(den2_lo), ARLIM_P(den2_hi),
        const int* m2   , ARLIM_P(m2_lo),   ARLIM_P(m2_hi),
        const Real* den3, ARLIM_P(den3_lo), ARLIM_P(den3_hi),
        const int* m3   , ARLIM_P(m3_lo),   ARLIM_P(m3_hi),
        const Real* den4, ARLIM_P(den4_lo), ARLIM_P(den4_hi),
        const int* m4   , ARLIM_P(m4_lo),   ARLIM_P(m4_hi),
        const Real* den5, ARLIM_P(den5_lo), ARLIM_P(den5_hi),
        const int* m5   , ARLIM_P(m5_lo),   ARLIM_P(m5_hi),
        const int* lo, const int* hi, const int *nc,
        const Real *h
        );

    void FORT_ADOTX(
        Real *y      , ARLIM_P(y_lo), ARLIM_P(y_hi),
        const Real *x, ARLIM_P(x_lo), ARLIM_P(x_hi),
        const Real* alpha, const Real* beta,
        const Real* a , ARLIM_P(a_lo),  ARLIM_P(a_hi),
        const Real* bX, ARLIM_P(bX_lo), ARLIM_P(bX_hi),
        const Real* bY, ARLIM_P(bY_lo), ARLIM_P(bY_hi),
        const Real* bZ, ARLIM_P(bZ_lo), ARLIM_P(bZ_hi),
        const int *lo, const int *hi, const int *nc,
        const Real *h
        );
    
    void FORT_NORMA(
        Real* res      ,
        const Real* alpha, const Real* beta,
        const Real* a , ARLIM_P(a_lo),  ARLIM_P(a_hi),
        const Real* bX, ARLIM_P(bX_lo), ARLIM_P(bX_hi),
        const Real* bY, ARLIM_P(bY_lo), ARLIM_P(bY_hi),
        const Real* bZ, ARLIM_P(bZ_lo), ARLIM_P(bZ_hi),
        const int *lo, const int *hi, const int *nc,
        const Real *h
        );
    
    void FORT_FLUX(
        const Real *x, ARLIM_P(x_lo), ARLIM_P(x_hi),
        const Real* alpha, const Real* beta,
        const Real* a , ARLIM_P(a_lo),  ARLIM_P(a_hi),
        const Real* bX, ARLIM_P(bX_lo), ARLIM_P(bX_hi),
        const Real* bY, ARLIM_P(bY_lo), ARLIM_P(bY_hi),
        const Real* bZ, ARLIM_P(bZ_lo), ARLIM_P(bZ_hi),
        const int *xlo, const int *xhi, 
        const int *ylo, const int *yhi, 
        const int *zlo, const int *zhi, 
	const int *nc,
        const Real *h,
        Real* xflux, ARLIM_P(xflux_lo), ARLIM_P(xflux_hi),
        Real* yflux, ARLIM_P(yflux_lo), ARLIM_P(yflux_hi),
        Real* zflux, ARLIM_P(zflux_lo), ARLIM_P(zflux_hi)
        );
#endif
}
#endif

#endif /*_AABBEC_F_H_*/
