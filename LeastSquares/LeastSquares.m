% Source: http://vmath.ru/vf5/interpolation/mnk#metod_naimenshix_kvadratov

n = 6;
m = 14;

% TODO: read from file
in_x = rand(1, m) .* 10;
in_y = rand(1, m) .* 10;

% Get unique x'es
map = containers.Map(in_x, in_y);
x = cell2mat(keys(map));
y = cell2mat(values(map));

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

if det(S) == 0
    fprintf(1, "Cannot find coefficients: det(S) = 0.")
    exit
end

a = flip(S \ t);

range = min(x):0.001:max(x);
plot(x, y, 'b*', range, polyval(a, range), 'r');

