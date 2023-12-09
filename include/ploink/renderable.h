#ifndef _GAME_RENDERABLE_H
#define _GAME_RENDERABLE_H

#include "ploink/vec.h"
#include "SDL.h"

/// <summary>
/// An object renderable on an SDL renderer
/// </summary>
struct Renderable {
    /// <summary>
    /// Renders the object
    /// </summary>
    /// <param name="renderer">The SDL renderer</param>
    /// <param name="camera">
    /// The camera position. The renderable item
    /// should be rendered relative to the camera
    /// </param>
    virtual void render(SDL_Renderer* renderer,
        Vec camera = { 0, 0 }) const = 0;
};

/// <summary>
/// Represents projection data
/// </summary>
struct ProjectionData {
    /// <summary>
    /// The projection position
    /// </summary>
    Vec pos;

    /// <summary>
    /// Whether the point was projected onto a hazard.
    /// This values is propagated through nested projection
    /// logic
    /// </summary>
    bool is_hazard;
};

/// <summary>
/// A renderable platform
/// </summary>
struct Platform : public Renderable {
    /// <summary>
    /// Projects a point onto the platform. The projected point is the
    /// closest point on the curve to the given point
    /// </summary>
    /// <param name="p">The point to project onto the curve</param>
    /// <returns>The projection data</returns>
    virtual ProjectionData project(Vec p) const = 0;
};

#endif
