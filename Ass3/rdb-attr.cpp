#include <bits/stdc++.h>
using namespace std;
#include "rdb.h"

// IntAttr::IntAttr(int value) : value_(value){}


// IntAttr::IntAttr(IntAttr &t):value_(t.value_){} //copy constructor

bool IntAttr::operator==(const Attr &right) const 
{
    const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
    if (rightInt == nullptr)
        return false;
    return (value_ == rightInt->value_);
}

bool IntAttr::operator!=(const Attr &right) const 
{
    const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
    if (rightInt == nullptr)
        return false;
    return (value_ != rightInt->value_);
}

bool IntAttr::operator<(const Attr &right) const 
{
    const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
    if (rightInt == nullptr)
        return false;
    return (value_ < rightInt->value_);
}

bool IntAttr::operator<=(const Attr &right) const 
{
    const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
    if (rightInt == nullptr)
        return false;
    return (value_ <= rightInt->value_);
}

bool IntAttr::operator>(const Attr &right) const 
{
    const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
    if (rightInt == nullptr)
        return false;
    return (value_ > rightInt->value_);
}

bool IntAttr::operator>=(const Attr &right) const 
{
    const IntAttr *rightInt = dynamic_cast<const IntAttr *>(&right);
    if (rightInt == nullptr)
        return false;
    return (value_ >= rightInt->value_);
}


    
IntAttr* IntAttr::clone() 
{
    return new IntAttr(*this); // create a new object with the same value
}



ostream& operator<<(ostream &os, const IntAttr& intattr)
{
    os << intattr.value_;
    return os;
}

// IntAttr::~IntAttr() {}



// StringAttr::StringAttr(string value) : value_(value) {}

bool StringAttr::operator==(const Attr &right) const 
{
    const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
    if (rightString == nullptr)
        return false;
    return (value_ == rightString->value_);
}

bool StringAttr::operator!=(const Attr &right) const 
{
    const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
    if (rightString == nullptr)
        return false;
    return (value_ != rightString->value_);
}

bool StringAttr::operator<(const Attr &right) const 
{
    const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
    if (rightString == nullptr)
        return false;
    return (value_ < rightString->value_);
}

bool StringAttr::operator<=(const Attr &right) const 
{
    const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
    if (rightString == nullptr)
        return false;
    return (value_ <= rightString->value_);
}

bool StringAttr::operator>(const Attr &right) const 
{
    const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
    if (rightString == nullptr)
        return false;
    return (value_ > rightString->value_);
}

bool StringAttr::operator>=(const Attr &right) const 
{
    const StringAttr *rightString = dynamic_cast<const StringAttr *>(&right);
    if (rightString == nullptr)
        return false;
    return (value_ >= rightString->value_);
}

StringAttr *StringAttr::clone() 
{
    return new StringAttr(*this); // create a new object with the same value
}

ostream& operator<<(ostream &os, const StringAttr& stringattr)
{
    os << stringattr.value_;
    return os;
}
// StringAttr::~StringAttr() {}



// FloatAttr::FloatAttr(float value) : value_(value) {}

bool FloatAttr::operator==(const Attr &right) const 
{
    const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
    if (rightFloat == nullptr)
        return false;
    return (value_ == rightFloat->value_);
}

bool FloatAttr::operator!=(const Attr &right) const 
{
    const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
    if (rightFloat == nullptr)
        return false;
    return (value_ != rightFloat->value_);
}

bool FloatAttr::operator<(const Attr &right) const 
{
    const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
    if (rightFloat == nullptr)
        return false;
    return (value_ < rightFloat->value_);
}

bool FloatAttr::operator<=(const Attr &right) const 
{
    const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
    if (rightFloat == nullptr)
        return false;
    return (value_ <= rightFloat->value_);
}

bool FloatAttr::operator>(const Attr &right) const 
{
    const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
    if (rightFloat == nullptr)
        return false;
    return (value_ > rightFloat->value_);
}

bool FloatAttr::operator>=(const Attr &right) const 
{
    const FloatAttr *rightFloat = dynamic_cast<const FloatAttr *>(&right);
    if (rightFloat == nullptr)
        return false;
    return (value_ >= rightFloat->value_);
}

FloatAttr* FloatAttr::clone()  
{
    return new FloatAttr(*this); // create a new object with the same value
}

ostream& operator<<(ostream &os, const FloatAttr& floatattr)
{
    os << floatattr.value_;
    return os;
}
// FloatAttr::~FloatAttr() {}
