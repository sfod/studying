function [C, sigma] = dataset3Params(X, y, Xval, yval)
%EX6PARAMS returns your choice of C and sigma for Part 3 of the exercise
%where you select the optimal (C, sigma) learning parameters to use for SVM
%with RBF kernel
%   [C, sigma] = EX6PARAMS(X, y, Xval, yval) returns your choice of C and 
%   sigma. You should complete this function to return the optimal C and 
%   sigma based on a cross-validation set.
%

% You need to return the following variables correctly.
C = 1;
sigma = 0.3;

% ====================== YOUR CODE HERE ======================
% Instructions: Fill in this function to return the optimal C and sigma
%               learning parameters found using the cross validation set.
%               You can use svmPredict to predict the labels on the cross
%               validation set. For example, 
%                   predictions = svmPredict(model, Xval);
%               will return the predictions on the cross validation set.
%
%  Note: You can compute the prediction error using 
%        mean(double(predictions ~= yval))
%

perr_min = 1000;

for C_i = [0.01, 0.03, 0.1, 0.3, 1, 3, 10, 30]
    for sigma_i = [0.01, 0.03, 0.1, 0.3, 1, 3, 10, 30]
        model= svmTrain(X, y, C_i, @(x1, x2) gaussianKernel(x1, x2, sigma_i)); 
        prediction = svmPredict(model, Xval);
        perr = mean(double(prediction ~= yval));
        if perr < perr_min
            perr_min = perr;
            C = C_i
            sigma = sigma_i
        end
    end
end

% fprintf('optimal C = %f, sigma = %f (prediction error is %f)\n', C, sigma, perr_min);

% =========================================================================

end
