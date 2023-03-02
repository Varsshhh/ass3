#include <bits/stdc++.h>
using namespace std;
#include"rdb.h"

class Attr
{
public:
    // Base class for attributes
    virtual bool operator==(const Attr &right) const = 0;
    virtual bool operator!=(const Attr &right) const = 0;
    virtual bool operator<(const Attr &right) const = 0;
    virtual bool operator<=(const Attr &right) const = 0;
    virtual bool operator>(const Attr &right) const = 0;
    virtual bool operator>=(const Attr &right) const = 0;
    virtual ostream& operator<< (std::ostream& os) const = 0;
    virtual Attr* clone() const=0;
    virtual ~Attr() {}
};

// Derived class for integer attributes
class IntAttr : public Attr
{
private:
    int value_;
public:
    IntAttr::IntAttr(int value) : value_(value) {}

    bool IntAttr::operator==(const Attr &right) const override
    {
        const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
        if (rightInt == nullptr)
            return false;
        return (value_ == rightInt->value_);
    }

    bool IntAttr::operator!=(const Attr &right) const override
    {
        const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
        if (rightInt == nullptr)
            return false;
        return (value_ != rightInt->value_);
    }

    bool IntAttr::operator<(const Attr &right) const override
    {
        const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
        if (rightInt == nullptr)
            return false;
        return (value_ < rightInt->value_);
    }

    bool IntAttr::operator<=(const Attr &right) const override
    {
        const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
        if (rightInt == nullptr)
            return false;
        return (value_ <= rightInt->value_);
    }

    bool IntAttr::operator>(const Attr &right) const override
    {
        const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
        if (rightInt == nullptr)
            return false;
        return (value_ > rightInt->value_);
    }

    bool IntAttr::operator>=(const Attr &right) const override
    {
        const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
        if (rightInt == nullptr)
            return false;
        return (value_ >= rightInt->value_);
    }

    IntAttr* IntAttr::clone() const override {
        return new IntAttr(*this);  // create a new object with the same value
    }

    ostream& IntAttr::operator<< (ostream& os) const override {
        os << value_;
        return os;
    }

    IntAttr::~IntAttr(){}

};

// Derived class for string attributes
class StringAttr : public Attr
{
private:
    string value_;
public:
    StringAttr::StringAttr(string value) : value_(value) {}

    bool StringAttr::operator==(const Attr &right) const override
    {
        const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
        if (rightString == nullptr)
            return false;
        return (value_ == rightString->value_);
    }

    bool StringAttr::operator!=(const Attr &right) const override
    {
        const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
        if (rightString == nullptr)
            return false;
        return (value_ != rightString->value_);
    }

    bool StringAttr::operator<(const Attr &right) const override
    {
        const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
        if (rightString == nullptr)
            return false;
        return (value_ < rightString->value_);
    }

    bool StringAttr::operator<=(const Attr &right) const override
    {
        const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
        if (rightString == nullptr)
            return false;
        return (value_ <= rightString->value_);
    }

    bool StringAttr::operator>(const Attr &right) const override
    {
        const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
        if (rightString == nullptr)
            return false;
        return (value_ > rightString->value_);
    }

    bool StringAttr::operator>=(const Attr &right) const override
    {
        const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
        if (rightString == nullptr)
            return false;
        return (value_ >= rightString->value_);
    }

    StringAttr* StringAttr::clone() const override {
        return new StringAttr(*this);  // create a new object with the same value
    }

    ostream& StringAttr::operator<< (ostream& os) const override {
        os << value_;
        return os;
    }
    StringAttr::~StringAttr(){}
};

// Derived class for float attributes
class FloatAttr : public Attr
{
private:
    float value_;
public:
    FloatAttr::FloatAttr(float value) : value_(value) {}

    bool FloatAttr::operator==(const Attr &right) const override
    {
        const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
        if (rightFloat == nullptr)
            return false;
        return (value_ == rightFloat->value_);
    }

    bool FloatAttr::operator!=(const Attr &right) const override
    {
        const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
        if (rightFloat == nullptr)
            return false;
        return (value_ != rightFloat->value_);
    }

    bool FloatAttr::operator<(const Attr &right) const override
    {
        const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
        if (rightFloat == nullptr)
            return false;
        return (value_ < rightFloat->value_);
    }

    bool FloatAttr::operator<=(const Attr &right) const override
    {
        const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
        if (rightFloat == nullptr)
            return false;
        return (value_ <= rightFloat->value_);
    }

    bool FloatAttr::operator>(const Attr &right) const override
    {
        const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
        if (rightFloat == nullptr)
            return false;
        return (value_ > rightFloat->value_);
    }

    bool FloatAttr::operator>=(const Attr &right) const override
    {
        const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
        if (rightFloat == nullptr)
            return false;
        return (value_ >= rightFloat->value_);
    }

    FloatAttr* FloatAttr::clone() const override {
        return new FloatAttr(*this);  // create a new object with the same value
    }

    ostream& FloatAttr::operator<< (ostream& os) const override {
        os << value_;
        return os;
    }
    FloatAttr::~FloatAttr(){}
};


