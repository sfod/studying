function idx = findClosestCentroids(X, centroids)
%FINDCLOSESTCENTROIDS computes the centroid memberships for every example
%   idx = FINDCLOSESTCENTROIDS (X, centroids) returns the closest centroids
%   in idx for a dataset X where each row is a single example. idx = m x 1 
%   vector of centroid assignments (i.e. each entry in range [1..K])
%

% Set K
K = size(centroids, 1);

% You need to return the following variables correctly.
idx = zeros(size(X,1), 1);

% ====================== YOUR CODE HERE ======================
% Instructions: Go over every example, find its closest centroid, and store
%               the index inside idx at the appropriate location.
%               Concretely, idx(i) should contain the index of the centroid
%               closest to example i. Hence, it should be a value in the 
%               range 1..K
%
% Note: You can use a for-loop over the examples to compute this.
%

% fprintf('X size is %d:%d\n', size(X));
% fprintf('centroids size is %d:%d\n', size(centroids));

% fprintf('centroids: (%d:%d) (%d:%d) (%d:%d)\n', centroids(1, :), centroids(2, :), centroids(3, :));
% fprintf('X: (%f:%f) (%f:%f) (%f:%f)\n', X(1, :), X(2, :), X(3, :));

for i = 1:rows(X)
    diff_min = 0;
    for j = 1:K
        diff = sum((X(i, :) - centroids(j, :)) .^ 2);
        if idx(i) == 0 || diff < diff_min
            diff_min = diff;
            idx(i) = j;
        end
    end
end

% =============================================================

end

