function [coeffs] = lsquares(x,y,n)
%LSQUARES Approximate the solution of overdetermined system.
%   This function uses the Least squares method: http://vmath.ru/vf5/interpolation/mnk#metod_naimenshix_kvadratov
%   NOTE: x should contain unique coords.
s = zeros(1, 2 * n - 1);
for k = 1:2 * n - 1
    s(k) = sum(x .^ (k - 1));
end

t = zeros(n, 1);
for k = 1:n
    t(k, 1) = sum((x .^ (k - 1)) .* y);
end

S = zeros(n, n);
for i = 1:n
    for j = 1:n
        S(i, j) = s(i + j - 1);
    end
end

if abs(det(S)) < eps
    fprintf(1, "Cannot find coefficients: det(S) ~= 0.")
    exit
end

coeffs = flip(S \ t);
end

