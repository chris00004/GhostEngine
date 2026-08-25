#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "gameManager.h"
#include "inputTypes.h"


//RUN W/ [F5] FOR JSONS TO APPLY!!!

int main()
{
    /* SFML */
    sf::VideoMode internalResolution ( { 640, 360 } );
    sf::VideoMode hdResolution ( { 1920, 1080 } );
    sf::RenderWindow window( hdResolution, "PROJECT SPARR-0", sf::State::Windowed ); //sf::VideoMode::getDesktopMode()

    sf::View view( sf::FloatRect( {0.f, 0.f}, {640.0f, 360.0f} ) );
    window.setView(view);
    //window.setVerticalSyncEnabled( true );

    std::cout << "Window Created." << std::flush;
    GameManager gameManager;
    std::cout << "\nGameMgr Created." << std::flush;

    
    //PROGRAM IS RUNNING
    while ( window.isOpen() )
    {
        //EVENTS
        while ( const std::optional event = window.pollEvent() )
        {
            
            if ( event -> is <sf::Event::Closed>() )
                window.close();
        }

        gameManager.update();
        
        //DRAWING
        window.clear(sf::Color(0, 0, 0));

        gameManager.draw( window );

        window.display();
    }

    return 0;
}










































// // ============================================================================
// // SAT PLAYGROUND
// // A standalone SFML 3 sandbox for building intuition around:
// //   - representing shapes as rotated point lists
// //   - the Separating Axis Theorem (SAT)
// //   - sliding velocity response
// //
// // This is a single, self-contained .cpp file. It does NOT depend on Sparrow's
// // manager architecture on purpose -- it's meant to be a scratch project you
// // build separately, just to watch the math happen.
// //
// // CONTROLS:
// //   Shape A (blue box)     : W A S D to move (has real velocity + sliding), Q / E to rotate
// //   Shape B (coral hexagon): Arrow keys to move, Z / X to rotate
// //   P                      : print SAT axis details to the console
// //   Esc / close window     : quit
// //
// // Shape A now moves like a real character: instead of just teleporting where
// // you tell it, it tries to move by velocity each frame, checks for a
// // collision, and if it finds one, strips out only the part of the velocity
// // that was driving it into the wall -- exactly the "velocity decomposition"
// // diagram from before -- then keeps sliding with what's left.
// //
// // SFML VERSION NOTE:
// // Written against SFML 3.0.x conventions (sf::Vector2u video modes,
// // std::optional-based event polling, sf::Angle for rotation). If your exact
// // SFML 3.0.2 install differs slightly in a method name, the compiler error
// // will point at the exact line -- the *logic* below does not change either way.
// // ============================================================================

// #include <SFML/Graphics.hpp>
// #include <vector>
// #include <cmath>
// #include <limits>
// #include <algorithm>
// #include <iostream>
// #include <optional>

// // ----------------------------------------------------------------------------
// // Small vector helpers. SFML's sf::Vector2f already supports +, -, and
// // scaling, but it doesn't give us dot products or perpendiculars, so we
// // write the handful of operations that everything else in this file is
// // built from. These three functions ARE the math from the diagrams --
// // everything below is just plumbing around them.
// // ----------------------------------------------------------------------------

// // "How much of A points in the same direction as B."
// // This single operation is projection, is checking if velocity points
// // into a wall, and is the overlap test -- all three, depending on context.

// float vdot( const sf::Vector2f& a, const sf::Vector2f& b )
// {
//     return a.x * b.x + a.y * b.y;
// }

// sf::Vector2f vnormalize( const sf::Vector2f& vector )
// {
//     float length = std::sqrt( vdot ( vector, vector ) );
//     if ( length < 0.0001f )
//         return { 0.f, 0.f };
//     return { vector.x / length, vector.y / length };
// }

// // Rotate a vector 90 degrees. Used to turn an edge direction into the
// // axis (normal) that is perpendicular to it.
// sf::Vector2f vperp( const sf::Vector2f& v )
// {
//     return { -v.y, v.x };
// }

// //get center point of a list of points
// sf::Vector2f centroid( const std::vector < sf::Vector2f >& points )
// {
//     sf::Vector2f sum { 0.f, 0.f };
//     for ( const auto& point : points ){
//         sum += point;
//     }
//     return sum / static_cast < float > ( points.size () );
// }

// // ----------------------------------------------------------------------------
// // Turn a shape's LOCAL points (centered on its own origin) into WORLD points
// // (after position + rotation are applied). This is exactly the "OBB anatomy"
// // diagram from before, except instead of computing corners by hand with
// // sin/cos, we let SFML's transform do it -- and because we work with an
// // arbitrary point list instead of hardcoded width/height, this works
// // identically whether the shape is a box, a hexagon, or anything else convex.
// // ----------------------------------------------------------------------------

// std::vector<sf::Vector2f> getWorldPoints( const sf::ConvexShape& shape )
// {
//     std::vector<sf::Vector2f> points;
//     sf::Transform t = shape.getTransform();
//     for ( std::size_t i = 0; i < shape.getPointCount(); ++i ){
//         points.push_back( t.transformPoint( shape.getPoint ( i ) ) );
//     }
//     return points;
// }

// // ----------------------------------------------------------------------------
// // Candidate SAT axes = the normal of every edge. For a box this gives 4 axes
// // (2 unique directions, each counted twice). For a hexagon, 6 axes (3 unique
// // directions). We don't bother de-duplicating parallel axes here -- it costs
// // a few redundant checks, but keeps the code readable, which matters more
// // for a learning sandbox than the extra couple of dot products.
// // ----------------------------------------------------------------------------

// std::vector<sf::Vector2f> getAxes( const std::vector < sf::Vector2f >& points )
// {
//     std::vector<sf::Vector2f> axes;
//     for ( std::size_t i = 0; i < points.size(); ++i )
//     {
//         sf::Vector2f p1 = points [ i ];
//         sf::Vector2f p2 = points [ (i + 1) % points.size() ];
//         sf::Vector2f edge = p2 - p1;
//         // if P1 [ 4, 8 ] & P2 [ 10, 3 ] then edge -> [ 6, 5 ]
//         axes.push_back ( vnormalize ( vperp ( edge ) ) ); 
//         // normalized -> [ 0.768, 0.640 ] vperp -> [ -0.640, 0.768 ]
//     }
//     return axes;
// }

// struct Interval { float min; float max; };

// Interval projectOntoAxis(const std::vector<sf::Vector2f>& points, const sf::Vector2f& axis)
// {
//     // This is the "shadow on the axis" from the projection diagram.
//     float minP = vdot(points[0], axis);
//     float maxP = minP;
//     for (std::size_t i = 1; i < points.size(); ++i)
//     {
//         float p = vdot(points[i], axis);
//         minP = std::min(minP, p);
//         maxP = std::max(maxP, p);
//     }
//     return { minP, maxP };
// }

// struct SATResult
// {
//     bool colliding = false;
//     sf::Vector2f normal{ 0.f, 0.f }; // points from shape A toward shape B
//     float depth = 0.f;               // smallest overlap found (the MTV length)
// };

// SATResult testSAT(const std::vector<sf::Vector2f>& ptsA, const std::vector<sf::Vector2f>& ptsB)
// {
//     SATResult result;
//     result.colliding = true;
//     result.depth = std::numeric_limits<float>::max();

//     std::vector<sf::Vector2f> axes = getAxes(ptsA);
//     std::vector<sf::Vector2f> axesB = getAxes(ptsB);
//     axes.insert(axes.end(), axesB.begin(), axesB.end());

//     for (const auto& axis : axes)
//     {
//         Interval a = projectOntoAxis(ptsA, axis);
//         Interval b = projectOntoAxis(ptsB, axis);

//         float overlap = std::min(a.max, b.max) - std::max(a.min, b.min);

//         if (overlap <= 0.f)
//         {
//             // Gap found on this axis -- stop immediately, no collision.
//             result.colliding = false;
//             result.depth = 0.f;
//             return result;
//         }

//         if (overlap < result.depth)
//         {
//             result.depth = overlap;
//             result.normal = axis;
//         }
//     }

//     // Make sure the normal points from A toward B (SAT alone doesn't tell you
//     // direction, only the axis and how much overlap is on it).
//     sf::Vector2f d = centroid(ptsB) - centroid(ptsA);
//     if (vdot(d, result.normal) < 0.f)
//         result.normal = -result.normal;

//     return result;
// }

// // ----------------------------------------------------------------------------
// // Rendering helpers -- nothing conceptually important below this line, just
// // drawing lines and dots so you can see the shapes, axes, and collision
// // normal on screen.
// // ----------------------------------------------------------------------------

// void drawLine(sf::RenderWindow& window, sf::Vector2f p1, sf::Vector2f p2, sf::Color color, float thickness = 2.f)
// {
//     sf::Vector2f diff = p2 - p1;
//     float length = std::sqrt(vdot(diff, diff));
//     if (length < 0.001f) return;

//     sf::RectangleShape line({ length, thickness });
//     line.setFillColor(color);
//     line.setOrigin({ 0.f, thickness / 2.f });
//     line.setPosition(p1);
//     line.setRotation(sf::radians(std::atan2(diff.y, diff.x)));
//     window.draw(line);
// }

// void drawDot(sf::RenderWindow& window, sf::Vector2f pos, sf::Color color, float radius = 4.f)
// {
//     sf::CircleShape dot(radius);
//     dot.setFillColor(color);
//     dot.setOrigin({ radius, radius });
//     dot.setPosition(pos);
//     window.draw(dot);
// }

// void drawAxes(sf::RenderWindow& window, const std::vector<sf::Vector2f>& worldPts, sf::Color color)
// {
//     sf::Vector2f c = centroid(worldPts);
//     for (const auto& axis : getAxes(worldPts))
//         drawLine(window, c, c + axis * 45.f, color, 1.f);
// }

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode({ 900u, 600u }), "SAT playground");
//     //window.setFramerateLimit(60);

//     // --- Shape A: a box, defined as a plain local point list -----------
//     std::vector<sf::Vector2f> boxLocalPts = { {-12.f,-12.f}, {12.f,-12.f}, {12.f,12.f}, {-12.f,12.f} };
//     sf::ConvexShape shapeA(boxLocalPts.size());
//     for (std::size_t i = 0; i < boxLocalPts.size(); ++i)
//         shapeA.setPoint(i, boxLocalPts[i]);
//     shapeA.setFillColor(sf::Color(55, 140, 220, 160));
//     shapeA.setOutlineColor(sf::Color(55, 140, 220));
//     shapeA.setOutlineThickness(1.f);

//     // --- Shape B: a hexagon -- same code path, just a different point list
//     std::vector<sf::Vector2f> hexLocalPts;
//     for (int i = 0; i < 6; ++i)
//     {
//         float angle = i * 60.f * 3.14159265f / 180.f;
//         hexLocalPts.push_back({ 70.f * std::cos(angle), 70.f * std::sin(angle) });
//     }
//     sf::ConvexShape shapeB(hexLocalPts.size());
//     for (std::size_t i = 0; i < hexLocalPts.size(); ++i)
//         shapeB.setPoint(i, hexLocalPts[i]);
//     shapeB.setFillColor(sf::Color(220, 100, 70, 160));
//     shapeB.setOutlineColor(sf::Color(220, 100, 70));
//     shapeB.setOutlineThickness(1.f);

//     sf::Vector2f posA{ 300.f, 300.f };
//     sf::Vector2f posB{ 550.f, 300.f };
//     float rotA = 0.f;
//     float rotB = 0.f;

//     const float moveSpeed = 220.f;   // pixels per second
//     const float rotSpeed = 90.f;     // degrees per second

//     sf::Clock clock;

//     while (window.isOpen())
//     {
//         float dt = clock.restart().asSeconds();

//         while (const std::optional<sf::Event> event = window.pollEvent())
//         {
//             if (event->is<sf::Event::Closed>())
//                 window.close();

//             if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
//             {
//                 if (keyEvent->code == sf::Keyboard::Key::Escape)
//                     window.close();

//                 if (keyEvent->code == sf::Keyboard::Key::P)
//                 {
//                     // On-demand dump of what SAT is actually doing this frame.
//                     std::vector<sf::Vector2f> ptsA = getWorldPoints(shapeA);
//                     std::vector<sf::Vector2f> ptsB = getWorldPoints(shapeB);
//                     std::vector<sf::Vector2f> axesA = getAxes(ptsA);
//                     std::vector<sf::Vector2f> axesB = getAxes(ptsB);

//                     std::cout << "--- SAT details ---\n";
//                     std::cout << "Shape A has " << axesA.size() << " axes, shape B has " << axesB.size() << "\n";

//                     int axisIndex = 0;
//                     for (const auto& axis : axesA)
//                     {
//                         Interval a = projectOntoAxis(ptsA, axis);
//                         Interval b = projectOntoAxis(ptsB, axis);
//                         float overlap = std::min(a.max, b.max) - std::max(a.min, b.min);
//                         std::cout << "  A-axis " << axisIndex++
//                                    << " | A=[" << a.min << ", " << a.max << "]"
//                                    << " B=[" << b.min << ", " << b.max << "]"
//                                    << " overlap=" << overlap << (overlap <= 0.f ? "  <- separating axis" : "") << "\n";
//                     }
//                     std::cout << "--------------------\n";
//                 }
//             }
//         }

//         // --- Real-time movement / rotation input --------------------------
//         using Key = sf::Keyboard::Key;

//         // Shape A: build a desired velocity from input instead of moving
//         // directly. This is the "attempted move" from the sliding diagram --
//         // it might get partially rejected below once we check for a wall.
//         sf::Vector2f inputDir{ 0.f, 0.f };
//         if (sf::Keyboard::isKeyPressed(Key::W)) inputDir.y -= 1.f;
//         if (sf::Keyboard::isKeyPressed(Key::S)) inputDir.y += 1.f;
//         if (sf::Keyboard::isKeyPressed(Key::A)) inputDir.x -= 1.f;
//         if (sf::Keyboard::isKeyPressed(Key::D)) inputDir.x += 1.f;
//         if (inputDir.x != 0.f || inputDir.y != 0.f)
//             inputDir = vnormalize(inputDir);
//         sf::Vector2f velocity = inputDir * moveSpeed;

//         if (sf::Keyboard::isKeyPressed(Key::Q)) rotA -= rotSpeed * dt;
//         if (sf::Keyboard::isKeyPressed(Key::E)) rotA += rotSpeed * dt;

//         // Shape B is the "wall" here -- still freely movable so you can test
//         // colliding into it from different angles, but it doesn't get any
//         // collision response applied to itself.
//         if (sf::Keyboard::isKeyPressed(Key::Up))    posB.y -= moveSpeed * dt;
//         if (sf::Keyboard::isKeyPressed(Key::Down))  posB.y += moveSpeed * dt;
//         if (sf::Keyboard::isKeyPressed(Key::Left))  posB.x -= moveSpeed * dt;
//         if (sf::Keyboard::isKeyPressed(Key::Right)) posB.x += moveSpeed * dt;
//         if (sf::Keyboard::isKeyPressed(Key::Z))     rotB -= rotSpeed * dt;
//         if (sf::Keyboard::isKeyPressed(Key::X))     rotB += rotSpeed * dt;

//         shapeB.setPosition(posB);
//         shapeB.setRotation(sf::degrees(rotB));
//         std::vector<sf::Vector2f> ptsB = getWorldPoints(shapeB);

//         // --- Step 1: try the full move, exactly as requested --------------
//         shapeA.setRotation(sf::degrees(rotA));
//         sf::Vector2f attemptPos = posA + velocity * dt;
//         shapeA.setPosition(attemptPos);
//         std::vector<sf::Vector2f> ptsA = getWorldPoints(shapeA);
//         SATResult result = testSAT(ptsA, ptsB);

//         bool wasSliding = false;

//         // --- Step 2: if that move causes a collision, correct it ----------
//         if (result.colliding)
//         {
//             // How much of the velocity points into the wall? result.normal
//             // points from A toward B, so a positive dot product here means
//             // "moving toward the wall" -- that's the part we cancel.
//             float into = vdot(velocity, result.normal);
//             if (into > 0.f)
//             {
//                 velocity -= result.normal * into; // strip it, keep the rest
//                 wasSliding = true;

//                 // IMPORTANT: re-test after sliding the velocity, instead of
//                 // reusing the old overlap depth. The old depth was measured
//                 // for the ORIGINAL (rejected) attempt -- applying it to the
//                 // NEW, slid position is a mismatch, and that mismatch is
//                 // exactly what causes jitter: each frame slightly over- or
//                 // under-corrects, so the shape vibrates instead of settling.
//                 attemptPos = posA + velocity * dt;
//                 shapeA.setPosition(attemptPos);
//                 ptsA = getWorldPoints(shapeA);
//                 result = testSAT(ptsA, ptsB);
//             }

//             // Only push out if the (possibly re-tested) position is still
//             // overlapping -- using depth that actually corresponds to it.
//             if (result.colliding)
//                 attemptPos -= result.normal * result.depth;
//         }

//         posA = attemptPos;
//         shapeA.setPosition(posA);
//         ptsA = getWorldPoints(shapeA);
//         result = testSAT(ptsA, ptsB); // refresh for drawing, after correction

//         // --- Draw ----------------------------------------------------
//         window.clear(sf::Color(24, 24, 26));

//         window.draw(shapeA);
//         window.draw(shapeB);

//         for (const auto& p : ptsA) drawDot(window, p, sf::Color(160, 200, 240));
//         for (const auto& p : ptsB) drawDot(window, p, sf::Color(240, 180, 160));

//         drawAxes(window, ptsA, sf::Color(90, 90, 100));
//         drawAxes(window, ptsB, sf::Color(90, 90, 100));

//         // Indicator, top-left corner: green = moving freely,
//         // amber = currently sliding along a wall this frame.
//         sf::RectangleShape indicator({ 30.f, 30.f });
//         indicator.setPosition({ 10.f, 10.f });
//         indicator.setFillColor(wasSliding ? sf::Color(230, 160, 60) : sf::Color(80, 200, 120));
//         window.draw(indicator);

//         if (wasSliding)
//         {
//             // Draw the collision normal at the contact point -- this is the
//             // direction the "into wall" velocity component was removed along.
//             sf::Vector2f c = centroid(ptsA);
//             drawLine(window, c, c + result.normal * 60.f, sf::Color(230, 230, 90), 3.f);
//         }

//         window.display();
//     }

//     return 0;
// }
