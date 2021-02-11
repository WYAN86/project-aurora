#ifndef MOVINGAVERAGEACCUMULATOR_H
#define MOVINGAVERAGEACCUMULATOR_H

/**
 * Just some reasoning behind the implementation of this class
 * (source: https://nestedsoftware.com/2018/03/20/calculating-a-moving-average-on-streaming-data-5a7k.22879.html)
 *
 * Let average of dataset x be denoted as avg(x) and number of elements in x as n.
 *
 * avg(x) = sum(x,1,n)/n = 1/n * sum(x,1,n)
 *
 * Let us separate the newest value in the average formula and we get
 *
 * avg(x) = 1/n * (sum(x,1,n-1) + x_n)
 *
 * The formula to calculate the average of n-1 values is
 *
 * avg(x,n-1) = 1/(n-1) * sum(x,1,n-1)
 *
 * By rotating the formula, we get
 *
 * sum(x,1,n-1) = avg(x,n-1) * (n-1)
 *
 * Then, by combining the last two formulas, we get
 *
 * avg(x) = 1/n * ((n-1) * avg(x,n-1) + x_n)
 *
 * Then, by expanding the bracket expressions, we get
 *
 * avg(x) = (n*avg(x,n-1 - avg(x,n-1) + x_n) / n
 *
 * After performing the division by n for the first term, we get
 *
 * avg(x) = avg(x,n-1) - (avg(x,n-1) + x_n)/n
 *
 * By using this formula, we don't have to worry about overflowing.
 */
template <class T,class S>
class MovingAverageAccumulator
{
public:
    MovingAverageAccumulator();
    void accumulate(T newValue);
    bool hasValue();
    S getAverage();
    S reset();
private:
    S average_ = 0;
    int n_ = 0;
};

template<class T, class S>
MovingAverageAccumulator<T, S>::MovingAverageAccumulator()
{

}

template<class T, class S>
void MovingAverageAccumulator<T, S>::accumulate(T newValue)
{
    n_++;
    average_ = average_ + (newValue - average_) / n_;
}

template<class T, class S>
bool MovingAverageAccumulator<T, S>::hasValue()
{
    return n_ != 0;
}

template<class T, class S>
S MovingAverageAccumulator<T, S>::getAverage()
{
    return average_;
}

template<class T, class S>
S MovingAverageAccumulator<T, S>::reset()
{
    S oldAverage = average_;
    average_ = 0;
    n_ = 0;
    return oldAverage;
}

#endif // MOVINGAVERAGEACCUMULATOR_H
