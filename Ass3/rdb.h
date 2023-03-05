#include <bits/stdc++.h>
using namespace std;


class Attr{
public:
    string dtype;
    Attr(string s):dtype(s){}
    // Base class for attributes
    // virtual auto getValue();
    virtual bool operator==(const Attr &right) const = 0;
    virtual bool operator!=(const Attr &right) const = 0;
    virtual bool operator<(const Attr &right) const = 0;
    virtual bool operator<=(const Attr &right) const = 0;
    virtual bool operator>(const Attr &right) const = 0;
    virtual bool operator>=(const Attr &right) const = 0;
    virtual void printval() const=0;
    // virtual ostream& operator<< (std::ostream& os) const = 0;
    friend ostream& operator<<(ostream &os, Attr* attr);
    virtual Attr* clone() =0;
    virtual ~Attr() {}
};

// Derived class for integer attributes
class IntAttr : public Attr{
private:
    int value_;
public:
    IntAttr(int value,string d="int") : value_(value), Attr(d){}
    IntAttr(IntAttr &t):value_(t.value_), Attr(t.dtype){} //copy constructor
    int getValue() const;
    bool operator==(const Attr &right) const override;
    bool operator!=(const Attr &right) const override;    
    bool operator<(const Attr &right) const override;
    bool operator<=(const Attr &right) const override;
    bool operator>(const Attr &right) const override;
    bool operator>=(const Attr &right) const override;
    void printval() const override;
    IntAttr* clone() override;
    friend ostream& operator<<(ostream &os, IntAttr* intattr) ;
    ~IntAttr() {}
};

// Derived class for string attributes
class StringAttr : public Attr{
private:
    string value_;
public:
    StringAttr(string value,string d="string") : value_(value), Attr(d){}
    StringAttr(StringAttr &t):value_(t.value_), Attr(t.dtype){} //copy constructor
    string getValue() const;
    bool operator==(const Attr &right) const override;
    bool operator!=(const Attr &right) const override;
    bool operator<(const Attr &right) const override;
    bool operator<=(const Attr &right) const override;
    bool operator>(const Attr &right) const override;
    bool operator>=(const Attr &right) const override;
    void printval() const override;
    StringAttr* clone() override;
    friend ostream& operator<<(ostream &os, StringAttr* stringattr) ;
    ~StringAttr(){}
};

// Derived class for float attributes
class FloatAttr : public Attr{
private:
    float value_;
public:
    FloatAttr(float value,string d="float") : value_(value),Attr(d){}
    FloatAttr(FloatAttr &t):value_(t.value_),Attr(t.dtype){} //copy constructor
    float getValue() const;
    bool operator==(const Attr &right) const override;
    bool operator!=(const Attr &right) const override;
    bool operator<(const Attr &right) const override;
    bool operator<=(const Attr &right) const override;
    bool operator>(const Attr &right) const override;
    bool operator>=(const Attr &right) const override;
    void printval() const override;
    FloatAttr* clone() override;
    friend ostream& operator<<(ostream &os, FloatAttr* floatattr) ;
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
    void printrec();
    friend ostream &operator<<(ostream &os, Record record);
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
    friend ostream &operator<<(ostream &os,  Relation* r);
    void printrelation();
};



// ostream& operator<<(ostream &os, Attr* attr){
//     if(attr->dtype=="int") {IntAttr* p1=dynamic_cast<IntAttr*>(attr);os<<p1->getValue();}
//     else if(attr->dtype=="float"){ FloatAttr* p1=dynamic_cast<FloatAttr*>(attr);os<<p1->getValue();}
//     else { StringAttr* p1=dynamic_cast <StringAttr*> (attr);os<<p1->getValue();}
//     return os;

// }

// ostream &operator<<(ostream &os, Relation* r){
//     os << r->getName() << "\n";
//     for (int i = 0; i < r->nattrs(); ++i){
//         os << r->getAttrNames()[i] << " ";
//     }
//     os << "\n";
//     for(auto rec : r->getRecords()){
//         os<<(rec)<<"\n";
//     }
//     return os;
// }


// // ostream &operator<<(ostream &os, Record* record)
// // {
// //     for ( auto attr : record->getAttr())
// //     {
// //         os << attr << " ";
// //     }
// //     return os;
// // }
// ostream& operator<<(ostream &os, Record* record) {
//     for(auto attr: record->getAttr()) {
//         os<<attr<<" ";
//     }
//     return os;
// }