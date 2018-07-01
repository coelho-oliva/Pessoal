function J = computeCost(X, y, theta)
% Compute cost for linear regression
%   J =  COMPUTECOST(X, y, theta) computes the cost of using theta as the
%   parameter for linear regression to fit the data points in X and y

m = length(y); % number of training examples

% Using matrix multiplication(inner product) method
predictions = X*theta;     %size(theta) = (n+1,1) | size(X) = (m,n+1);
sqrErrors = (predictions - y).^2;   % vector predictions - y, then all
                                    %elements squared
J = (1/(2*m))*sum(sqrErrors);

% =========================================================================

end
