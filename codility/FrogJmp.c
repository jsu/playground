int solution(int X, int Y, int D) {
    // write your code in C99 (gcc 6.2.0)
    if((Y - X) % D)
        return (Y - X) / D + 1;
    return (Y - X) / D;
}
