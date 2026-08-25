
//Game Object
- have Vec3 position (topleft)
- have Vec3 size
- have Vec3 positionFadeVolume (topleft)
- have Vec3 sizeFadeVolume
- have Vec3 speed
- have Vec3 speedExternal
- have Vec3 speedCombined

//Entity
- have ref to current platform
- have ref to current slope
- know angle of current slope
- draw itself at current slope's angle (only horizontal slopes)
- have ref to closest solid in move direction
- able to perform wall-related mechanics with closest solid

//Player
- have Vec3 hitbox -> public getter
- have ref to current solid beneath
- have ref to current solid in front of player move direction at same z pos
- accelerate down slope based on angle ( internal speed )
- jumping on slopes
    - pushes player back depending on angle and player speed is that direction ( external speed )
    - adds extra vspd up or down depending on angle and player speed in that direction ( external speed )
- slope only pushes player down if current slope's push force val is > than player friction val ( internal speed )
- adds/subracts external x, y, & z speeds from player speed
- keep internal & external speeds separate, combine to one value before applying move speeds


//Solids
- have bool 
- register if player y behind
- register if player z under
- able to act simply as an invisible blocker, allows no player-wall contact related actions
- able to toggle cam facing sides to be pure black or assigned texture
- able to control z draw distance from player
- able to toggle if cast shadow
    - if cast shadow, able to set visible z distance
- able to be breakable or not
- all textures adjust in accordance to width, depth, & height
- slope adjusts in accordance to width, depth, & height
- slope surface texture draws in accordance to its angle
- slope calculates a entity push down force based on angle


//Editor Trigger Volume Events
- change background layers
- change global light
    - lerp
    - instant
    - smoothing
        - X: transition to desired global light value based on player x pos within volumes width
        - Y: transition to desired global light value based on player y pos within volumes depth
        - Center: transition to desired global light value based on player distance to center within volume
- spawn gameObjects and tweaking their spawn properties
- select gameObject and editing properties
- set player guide ring zFloor value


//Editor Trigger Volume Properties
- while inside  *-> disable for functions that will cause issues
    - frame skip
- if entered
- if exited
- permanent or one time use
