function [r, theta, phi] = cart2esf(x, y, z)
    r = sqrt(x^2 + y^2 + z^2);
    theta = atan(sqrt(x^2+y^2)/z);
    phi = atan(y/x);
end