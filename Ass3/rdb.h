#include <bits/stdc++.h>
using namespace std;


class Attr{
public:
    // Base class for attributes
    virtual bool operator==(const Attr &right) const = 0;
    virtual bool operator!=(const Attr &right) const = 0;
    virtual bool operator<(const Attr &right) const = 0;
    virtual bool operator<=(const Attr &right) const = 0;
    virtual bool operator>(const Attr &right) const = 0;
    virtual bool operator>=(const Attr &right) const = 0;
    // virtual ostream& operator<< (std::ostream& os) const = 0;
    virtual Attr* clone() =0;
    virtual ~Attr() {}
};

// Derived class for integer attributes
class IntAttr : public Attr{
private:
    int value_;
public:
    IntAttr(int value) : value_(value){}
    IntAttr(IntAttr &t):value_(t.value_){} //copy constructor
    bool operator==(const Attr &right) const override;
    bool operator!=(const Attr &right) const override;    
    bool operator<(const Attr &right) const override;
    bool operator<=(const Attr &right) const override;
    bool operator>(const Attr &right) const override;
    bool operator>=(const Attr &right) const override;
    IntAttr* clone() override;
    friend ostream& operator<<(ostream &os, const IntAttr& intattr) ;
    ~IntAttr() {}
};

// Derived class for string attributes
class StringAttr : public Attr{
private:
    string value_;
public:
    StringAttr(string value) : value_(value){}
    StringAttr(StringAttr &t):value_(t.value_){} //copy constructor
    bool operator==(const Attr &right) const override;
    bool operator!=(const Attr &right) const override;
    bool operator<(const Attr &right) const override;
    bool operator<=(const Attr &right) const override;
    bool operator>(const Attr &right) const override;
    bool operator>=(const Attr &right) const override;
    StringAttr* clone() override;
    friend ostream& operator<<(ostream &os, const StringAttr& stringattr) ;
    ~StringAttr(){}
};

// Derived class for float attributes
class FloatAttr : public Attr{
private:
    float value_;
public:
    FloatAttr(float value) : value_(value){}
    FloatAttr(FloatAttr &t):value_(t.value_){} //copy constructor
    bool operator==(const Attr &right) const override;
    bool operator!=(const Attr &right) const override;
    bool operator<(const Attr &right) const override;
    bool operator<=(const Attr &right) const override;
    bool operator>(const Attr &right) const override;
    bool operator>=(const Attr &right) const override;
    FloatAttr* clone() override;
    friend ostream& operator<<(ostream &os, const FloatAttr& floatattr) ;
    ~FloatAttr(){}
};

struct DNFformula
{
    list<list<tuple<string, char, Attr *>>> ops;
};


class Record{
private:
    vector<Attr *> attrptr;
public:
    Record();
    Record(const vector<Attr*>& attrs);
    int size() const;
    void pushAttr(Attr *attr);
    void removeAttr(const int i);
    void clearAttrs();
    vector<Attr*> getAttr() const;
    Attr* getAttrbyindex(const int i);
    void setAttr(const int i, Attr *attr);
    bool operator==(const Record &right) const;
    friend ostream& operator<<(ostream &os, const Record& record) ;
    ~Record();
    friend class Relation;
};

class Relation{
private:
    int nattrs_, nrecs_;
    vector<string> attrnames_;
    vector<int> attrinds_;
    list<Record *> recs_;
    string name_;
public:
    Relation();
    Relation(const string &name, const vector<string> &attrnames, const vector<int> &attrinds);
    int nattrs() const;
    int nrecs() const; 
    void setName(const string &name);
    string getName() const;
    void setAttrNames(const vector<string> &attrnames);
    void addAttr(const string& attrname);
    vector<string> getAttrNames() const;
    void setAttrInds(const vector<int> &attrinds);
    void addAttrInd(const int& attrindex);
    vector<int> getAttrInds() const;
    void clearRecords();
    void addRecord(Record *rec);
    void removeRecord(const int i);
    list<Record *> getRecords();
    Relation *union_(Relation *r1, Relation *r2);
    Relation *difference(Relation *r1, Relation *r2);
    Relation *cartesianProduct(Relation *r1, Relation *r2);
    Relation *projection(Relation *r1, list<string> projectattrs);
    Relation *selection(Relation *r1, DNFformula *f);
    Relation *rename_(Relation *r1, string s1, string s2);
    Relation *naturalJoin(Relation *r1, Relation *r2, list<string> joinattrs);
    friend ostream &operator<<(ostream &out, const Relation &r);
};


