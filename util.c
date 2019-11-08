int mod(int a, int b) {
    return a > 0 ? a % b : (a % b + b) % b;
}
