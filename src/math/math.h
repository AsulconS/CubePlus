namespace Math
{
    template<typename T>
    T clamp(const T& val, const T& min, const T& max)
    {
        if(val > max)
            return max;
        else if(val > min)
            return val;
        else
            return min;
    }
}