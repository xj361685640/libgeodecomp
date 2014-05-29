#ifndef LIBGEODECOMP_MISC_SIMULATIONPARAMETERS_H
#define LIBGEODECOMP_MISC_SIMULATIONPARAMETERS_H

// HPX' config needs to be included before Boost's config:
#include <libgeodecomp/config.h>
#ifdef LIBGEODECOMP_WITH_HPX
#include <hpx/config.hpp>
#endif

#include <libgeodecomp/misc/stdcontaineroverloads.h>
#include <boost/shared_ptr.hpp>
#include <stdexcept>

namespace LibGeoDecomp {

namespace SimulationParametersHelpers {

/**
 * Virtual interface which allows the implementation of auto-tuniers
 * and parameter optimizers without them having to unterstand the
 * actual meaning of the parameters. For that all parameters are
 * mapped to an interval [min, max[ in R.
 *
 * See the unit tests for an explanation on how to use this interface.
 */
class OptimizableParameter
{
public:
    virtual ~OptimizableParameter()
    {}

    /**
     * returns the lower bound of the interval. The lower bound is
     * included in the interval.
     */
    virtual double getMin() const = 0;

    /**
     * returns the upper bound of the interval. The upper bound is
     * excluded from the interval.
     */
    virtual double getMax() const = 0;

    /**
     * The granularity gives the minimum value that a parameter needs
     * to change in order to actually affect the model.
     *
     * Most parameters won't actually have a real-valued valuation.
     * For these the granularity is almost always 1.
     */
    virtual double getGranularity() const = 0;

    /**
     * Returns a real-valued representation of the parameter's current
     * value.
     */
    virtual double getValue() const = 0;

    /**
     * Sets the parameter, based on the given real value. Note that
     * rounding and truncation based on the granularity may occur.
     */
    virtual void setValue(double newValue) = 0;

    /**
     * Move the parameter by the offset given by step. Step sizes
     * below granularity may have no effect.
     */
    virtual void operator+=(double step) = 0;
};

class Parameter : public OptimizableParameter
{
public:
    virtual ~Parameter()
    {}

    virtual Parameter *clone() const = 0;

    virtual operator std::string() const
    {
        throw std::logic_error("illegal cast to std::string");
    }

    virtual operator bool() const
    {
        throw std::logic_error("illegal cast to bool");
    }

    virtual operator int() const
    {
        throw std::logic_error("illegal cast to int");
    }

    virtual operator double() const
    {
        throw std::logic_error("illegal cast to double");
    }


    virtual void operator=(const std::string& other)
    {
        throw std::logic_error("illegal assignment from string");
    }

    virtual void operator=(const char *other)
    {
        *this = std::string(other);
    }

    virtual void operator=(const bool& other)
    {
        throw std::logic_error("illegal assignment from bool");
    }

    virtual void operator=(const int& other)
    {
        throw std::logic_error("illegal assignment from int");
    }

    virtual void operator=(const double& other)
    {
        throw std::logic_error("illegal assignment from double");
    }

    virtual bool operator==(const std::string& other) const
    {
        return false;
    }

    virtual bool operator==(const char *other) const
    {
        return *this == std::string(other);
    }

    virtual bool operator==(const bool& other) const
    {
        return false;
    }

    virtual bool operator==(const int& other) const
    {
        return false;
    }

    virtual bool operator==(const double& other) const
    {
        return false;
    }

    template<typename OTHER_TYPE>
    bool operator!=(const OTHER_TYPE& other) const
    {
        return !(*this == other);
    }

    double sanitizeIndex(double index) const
    {
        if (index < getMin()) {
            index = getMin();
        }
        if (index >= getMax()) {
            index = getMax() - getGranularity();
        }

        return index;
    }
};

template<typename VALUE_TYPE>
class TypedParameter : public Parameter
{
public:
    explicit TypedParameter(const VALUE_TYPE& current) :
        current(current)
    {}

    virtual operator VALUE_TYPE() const
    {
        return current;
    }

    virtual void operator=(const VALUE_TYPE& other)
    {
        current = other;
    }

    virtual bool operator==(const VALUE_TYPE& other) const
    {
        return current == other;
    }

protected:
    VALUE_TYPE current;
};

template<typename VALUE_TYPE>
class Interval : public TypedParameter<VALUE_TYPE>
{
public:
    using TypedParameter<VALUE_TYPE>::current;
    using Parameter::sanitizeIndex;

    Interval(const VALUE_TYPE minimum, const VALUE_TYPE maximum) :
        TypedParameter<VALUE_TYPE>(minimum),
        minimum(minimum),
        maximum(maximum),
        index(0)
    {}

    Parameter *clone() const
    {
        return new Interval<VALUE_TYPE>(*this);
    }

    double getMin() const
    {
        return 0;
    }

    double getMax() const
    {
        return maximum - minimum;
    }

    double getValue() const
    {
        return index;
    }

    void setValue(double newValue)
    {
        index = sanitizeIndex(newValue);
        current = minimum + index;
    }

    double getGranularity() const
    {
        // fixme: for now we only care for integer intervals. this
        // needs to be fixed for real-valued intervals.
        return 1;
    }

    void operator+=(double step)
    {
        index += step;
        index = sanitizeIndex(index);

        current = minimum + index;
    }

private:
    VALUE_TYPE minimum;
    VALUE_TYPE maximum;
    int index;
};

template<typename VALUE_TYPE>
class DiscreteSet : public TypedParameter<VALUE_TYPE>
{
public:
    using TypedParameter<VALUE_TYPE>::current;
    using Parameter::sanitizeIndex;

    explicit DiscreteSet(const std::vector<VALUE_TYPE>& elements) :
        TypedParameter<VALUE_TYPE>(elements.front()),
        elements(elements),
        index(0)
    {}

    Parameter *clone() const
    {
        return new DiscreteSet<VALUE_TYPE>(*this);
    }

    double getMin() const
    {
        return 0;
    }

    double getMax() const
    {
        return elements.size();
    }

    double getValue() const
    {
        return index;
    }

    void setValue(double newValue)
    {
        index = sanitizeIndex(index);
        current = elements[index];
    }

    double getGranularity() const
    {
        return 1;
    }

    void operator+=(double step)
    {
        index += step;
        index = sanitizeIndex(index);

        current = elements[index];
    }

private:
    std::vector<VALUE_TYPE> elements;
    int index;
};

}

class SimulationParameters
{
public:
    typedef boost::shared_ptr<SimulationParametersHelpers::Parameter> ParamPointerType;

    SimulationParameters()
    {}

    SimulationParameters(const SimulationParameters& other) :
        names(other.names)
    {
        for (std::size_t i = 0; i < other.size(); ++i) {
            parameters.push_back(ParamPointerType(other[i].clone()));
        }
    }

    template<typename VALUE_TYPE>
    void addParameter(const std::string& name, const VALUE_TYPE& minimum, const VALUE_TYPE& maximum)
    {
        names[name] = parameters.size();
        parameters.push_back(
            ParamPointerType(
                new SimulationParametersHelpers::Interval<VALUE_TYPE>(minimum, maximum)));
    }

    template<typename VALUE_TYPE>
    void addParameter(const std::string& name, const std::vector<VALUE_TYPE>& elements)
    {
        names[name] = parameters.size();
        parameters.push_back(
            ParamPointerType(
                new SimulationParametersHelpers::DiscreteSet<VALUE_TYPE>(elements)));
    }

    SimulationParametersHelpers::Parameter& operator[](const std::string& name)
    {
        return *parameters[names[name]];
    }

    SimulationParametersHelpers::Parameter& operator[](std::size_t index)
    {
        return *parameters[index];
    }

    const SimulationParametersHelpers::Parameter& operator[](std::size_t index) const
    {
        return *parameters[index];
    }

    std::size_t size() const
    {
        return parameters.size();
    }

private:
    std::map<std::string, int> names;
    std::vector<ParamPointerType> parameters;
};

}

#endif