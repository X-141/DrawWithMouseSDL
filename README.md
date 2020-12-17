# DrawWithMouseSDL
This is a sample component that allows the user to draw with mouse input.

This package comes with SDL that handles window creation and mouse inputs.
In addition, GTest is packaged for testing.

This package uses an algorithm that calculates the "best fit" line between two
points. The points calculated from the algorithm is then used to draw a line.
This algorithm is necessary as polling for mouse events can be delayed and thus
we need to extrapolate a smooth line.
