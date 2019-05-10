/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Rect.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppRect
#define _ProjectMobius_hppRect

/**
 * Simple rectangle object.
 * Useful to represent some 2D objects.
 */
typedef struct cMB_MATH_Rect2f {
    // ---  Attributes ---
        /** 2D coordinats of the rectangle's origin. */
        float x, y;
    
        /** Size of the rectangle. */
        float w, h;
    // --- /Attributes ---
} cMB_MATH_Rect2f;


#ifdef __cplusplus
namespace Mobius {
namespace Math {

class Rect2f : public cMB_MATH_Rect2f {
    // ---  Methods ---
        // TODO : Functions !
    // --- /Methods ---
};

}
}
#endif

#endif /* _ProjectMobius_hppRect */
