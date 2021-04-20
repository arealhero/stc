import lsquares.*
import uniquepairs.*;

n = 6;
m = 14;

in_x = rand(1, m) .* 10;
in_y = rand(1, m) .* 10;

[x, y] = uniquepairs(in_x, in_y);

a = lsquares(x, y, n);

range = min(x):0.001:max(x);
plot(x, y, 'b*', range, polyval(a, range), 'r');

