// map value from [low1, high2] -> [low2, high2]
//
double map(double value, double low1, double high1, double low2, double high2) {
    double denom, a, b;

    denom = high1 - low1;
    a = (high2 - low2)/denom;
    b = (high1 * low2 - high2 * low1)/denom;
    return a * value + b;
}


// normalizes value
// that is maps a number between low and high to between 0 and 1
// returns map(value, low, high, 0, 1)
//
double norm(double value, double low, double high) {
    return (value-low)/(high-low);
}


// inverse norm called lerp(low, high, value) in Processing
// better name is unNorm()?    (tags: lrep lper lepr)
//  returns map(value, 0, 1, low, high)
//
double unNorm(double value, double low, double high) {
    return value * (high-low) + low;
}


// pin value between low and high
//
double pin(double value, double low, double high) {
    if (value>high) return high;
    if (value<low) return low;
    return value;
}
