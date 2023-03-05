#include <bits/stdc++.h>
using namespace std;
#include "rdb.h"

// IntAttr::IntAttr(int value) : value_(value){}


// IntAttr::IntAttr(IntAttr &t):value_(t.value_){} //copy constructor
int IntAttr::getValue() const{return value_;}
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

void IntAttr::printval() const{cout<<value_<<" ";}
    
IntAttr* IntAttr::clone() 
{
    return new IntAttr(*this); // create a new object with the same value
}



ostream& operator<<(ostream &os, IntAttr* intattr) 
{
    os << intattr->getValue();
    return os;
}

// IntAttr::~IntAttr() {}



// StringAttr::StringAttr(string value) : value_(value) {}

string StringAttr::getValue() const{return value_;}
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

void StringAttr::printval() const{cout<<value_<<" ";}

StringAttr *StringAttr::clone() 
{
    return new StringAttr(*this); // create a new object with the same value
}

ostream& operator<<(ostream &os, StringAttr* stringattr) 
{
    os << stringattr->getValue();
    return os;
}
// StringAttr::~StringAttr() {}



// FloatAttr::FloatAttr(float value) : value_(value) {}

float FloatAttr::getValue() const{return value_;}

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

void FloatAttr::printval() const{cout<<value_<<" ";}

FloatAttr* FloatAttr::clone()  
{
    return new FloatAttr(*this); // create a new object with the same value
}

ostream& operator<<(ostream &os, FloatAttr* floatattr) 
{
    os << floatattr->getValue();
    return os;
}
// FloatAttr::~FloatAttr() {}


ostream& operator<<(ostream &os, Attr* attr){
    if(attr->dtype=="int") {IntAttr* p1=dynamic_cast<IntAttr*>(attr);os<<p1->getValue();}
    else if(attr->dtype=="float"){ FloatAttr* p1=dynamic_cast<FloatAttr*>(attr);os<<p1->getValue();}
    else { StringAttr* p1=dynamic_cast <StringAttr*> (attr);os<<p1->getValue();}
    return os;

}
