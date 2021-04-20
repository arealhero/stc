function [out_x,out_y] = uniquepairs(in_x,in_y)
%UNIQUEPAIRS Get unique pairs from two vectors
map = containers.Map(in_x, in_y);
out_x = cell2mat(keys(map));
out_y = cell2mat(values(map));
end

